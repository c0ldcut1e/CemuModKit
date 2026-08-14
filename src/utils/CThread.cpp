#include "CThread.h"

#include <cstring>

#include <coreinit/memdefaultheap.h>
#include <coreinit/time.h>
#include <utils/Utils.h>

CThread::CThread(Entry entry, void *userData) { Create(entry, userData); }

CThread::CThread(Entry entry, void *userData, const Options &options) { Create(entry, userData, options); }

CThread::~CThread() { Reset(); }

CThread::CThread(CThread &&other) noexcept { MoveFrom(other); }

CThread &CThread::operator=(CThread &&other) noexcept
{
    if (this != &other)
    {
        Reset();
        MoveFrom(other);
    }

    return *this;
}

bool CThread::Create(Entry entry, void *userData)
{
    Options options{};
    return Create(entry, userData, options);
}

bool CThread::Create(Entry entry, void *userData, const Options &options)
{
    Reset();
    if (!entry)
    {
        return false;
    }

    uint32_t stackSize = options.m_stackSize ? options.m_stackSize : 0x8000;
    stackSize          = (stackSize + 0xF) & ~0xF;

    uint32_t threadSize = (sizeof(OSThread) + 0xF) & ~0xF;
    uint32_t allocSize  = threadSize + stackSize;
    void *allocation    = MEMAllocFromDefaultHeapEx(allocSize, 0x10);
    if (!allocation)
    {
        return false;
    }

    memset(allocation, 0, allocSize);

    OSThread *thread = (OSThread *) allocation;
    void *stackTop   = (uint8_t *) allocation + allocSize;

    m_thread     = thread;
    m_allocation = allocation;
    m_stackTop   = stackTop;
    m_stackSize  = stackSize;
    m_entry      = entry;
    m_userData   = userData;
    m_created    = false;
    m_detached   = (options.m_attributes & OS_THREAD_ATTRIB_DETACHED) != 0;
    m_ownsThread = true;
    m_name       = options.m_name ? options.m_name : "";

    OSThreadAttributes attributes = options.m_attributes;
    if (options.m_trackStackUsage)
    {
        attributes = (OSThreadAttributes) (attributes | OS_THREAD_ATTRIB_STACK_USAGE);
    }

    BOOL ok = OSCreateThread(thread, Trampoline, (int) this, nullptr, stackTop, stackSize, options.m_priority, attributes);
    if (!ok)
    {
        ReleaseOwnedMemory();
        return false;
    }

    if (options.m_runQuantum != 0)
    {
        OSSetThreadRunQuantum(thread, options.m_runQuantum);
    }

    if (options.m_name)
    {
        OSSetThreadName(thread, options.m_name);
    }

    if (options.m_trackStackUsage)
    {
        OSSetThreadStackUsage(thread);
    }

    m_created = true;
    if (!options.m_startSuspended)
    {
        Start();
    }

    return true;
}

bool CThread::Start() { return m_created && OSResumeThread(m_thread) >= 0; }

bool CThread::Join(int *outResult)
{
    if (!m_created || m_detached)
    {
        return false;
    }

    int result = 0;
    BOOL ok    = OSJoinThread(m_thread, &result);
    if (!ok)
    {
        return false;
    }

    if (outResult)
    {
        *outResult = result;
    }

    ReleaseOwnedMemory();
    return true;
}

void CThread::Detach()
{
    if (!m_created || m_detached)
    {
        return;
    }

    OSDetachThread(m_thread);
    m_detached = true;
}

void CThread::Cancel()
{
    if (m_created)
    {
        OSCancelThread(m_thread);
    }
}

void CThread::Reset()
{
    if (!m_created)
    {
        ReleaseOwnedMemory();
        return;
    }

    if (!m_detached)
    {
        Join();
    }
    else
    {
        m_thread     = nullptr;
        m_allocation = nullptr;
        m_stackTop   = nullptr;
        m_stackSize  = 0;
        m_entry      = nullptr;
        m_userData   = nullptr;
        m_created    = false;
        m_detached   = false;
        m_ownsThread = true;
        m_name.clear();
    }
}

bool CThread::IsCreated() const { return m_created; }

bool CThread::IsDetached() const { return m_detached; }

bool CThread::IsTerminated() const { return m_created && OSIsThreadTerminated(m_thread); }

bool CThread::IsSuspended() const { return m_created && OSIsThreadSuspended(m_thread); }

int CThread::Suspend() { return m_created ? (int) OSSuspendThread(m_thread) : -1; }

int CThread::Resume() { return m_created ? OSResumeThread(m_thread) : -1; }

bool CThread::SetPriority(int priority) { return m_created && OSSetThreadPriority(m_thread, priority); }

int CThread::Priority() const { return m_created ? OSGetThreadPriority(m_thread) : -1; }

bool CThread::SetAffinity(uint32_t affinity) { return m_created && OSSetThreadAffinity(m_thread, affinity); }

uint32_t CThread::Affinity() const { return m_created ? OSGetThreadAffinity(m_thread) : 0; }

bool CThread::SetRunQuantum(uint32_t quantum) { return m_created && OSSetThreadRunQuantum(m_thread, quantum); }

bool CThread::EnableStackUsage() { return m_created && OSSetThreadStackUsage(m_thread); }

int CThread::CheckStackUsage() { return m_created ? OSCheckThreadStackUsage(m_thread) : 0; }

void CThread::ClearStackUsage()
{
    if (m_created)
    {
        OSClearThreadStackUsage(m_thread);
    }
}

OSThread *CThread::Native() { return m_thread; }

const OSThread *CThread::Native() const { return m_thread; }

const std::string &CThread::Name() const { return m_name; }

int CThread::Trampoline(int argc, const char **argv)
{
    UNUSED_PARAMETER(argv);
    CThread *self = (CThread *) argc;
    if (!self || !self->m_entry)
    {
        return -1;
    }

    return self->m_entry(self->m_userData);
}

void CThread::ReleaseOwnedMemory()
{
    void *allocation = m_ownsThread ? m_allocation : nullptr;

    m_thread     = nullptr;
    m_allocation = nullptr;
    m_stackTop   = nullptr;
    m_stackSize  = 0;
    m_entry      = nullptr;
    m_userData   = nullptr;
    m_created    = false;
    m_detached   = false;
    m_ownsThread = true;
    m_name.clear();

    if (allocation)
    {
        MEMFreeToDefaultHeap(allocation);
    }
}

void CThread::MoveFrom(CThread &other)
{
    m_thread     = other.m_thread;
    m_allocation = other.m_allocation;
    m_stackTop   = other.m_stackTop;
    m_stackSize  = other.m_stackSize;
    m_entry      = other.m_entry;
    m_userData   = other.m_userData;
    m_created    = other.m_created;
    m_detached   = other.m_detached;
    m_ownsThread = other.m_ownsThread;
    m_name       = other.m_name;

    other.m_thread     = nullptr;
    other.m_allocation = nullptr;
    other.m_stackTop   = nullptr;
    other.m_stackSize  = 0;
    other.m_entry      = nullptr;
    other.m_userData   = nullptr;
    other.m_created    = false;
    other.m_detached   = false;
    other.m_ownsThread = true;
    other.m_name.clear();
}
