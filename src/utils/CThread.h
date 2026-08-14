#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

#include <coreinit/thread.h>

class CThread
{
public:
    using Entry = int (*)(void *userData);

    struct Options
    {
        const char *m_name              = nullptr;
        uint32_t m_stackSize            = 0x8000;
        int m_priority                  = 16;
        OSThreadAttributes m_attributes = OS_THREAD_ATTRIB_AFFINITY_ANY;
        bool m_startSuspended           = false;
        bool m_trackStackUsage          = false;
        uint32_t m_runQuantum           = 0;
    };

    CThread() = default;
    CThread(Entry entry, void *userData = nullptr);
    CThread(Entry entry, void *userData, const Options &options);
    ~CThread();

    CThread(const CThread &)            = delete;
    CThread &operator=(const CThread &) = delete;

    CThread(CThread &&other) noexcept;
    CThread &operator=(CThread &&other) noexcept;

    bool Create(Entry entry, void *userData = nullptr);
    bool Create(Entry entry, void *userData, const Options &options);
    bool Start();
    bool Join(int *outResult = nullptr);
    void Detach();
    void Cancel();
    void Reset();

    bool IsCreated() const;
    bool IsDetached() const;
    bool IsTerminated() const;
    bool IsSuspended() const;

    int Suspend();
    int Resume();
    bool SetPriority(int priority);
    int Priority() const;
    bool SetAffinity(uint32_t affinity);
    uint32_t Affinity() const;
    bool SetRunQuantum(uint32_t quantum);
    bool EnableStackUsage();
    int CheckStackUsage();
    void ClearStackUsage();

    OSThread *Native();
    const OSThread *Native() const;
    const std::string &Name() const;

private:
    static int Trampoline(int argc, const char **argv);
    void ReleaseOwnedMemory();
    void MoveFrom(CThread &other);

    OSThread *m_thread   = nullptr;
    void *m_allocation   = nullptr;
    void *m_stackTop     = nullptr;
    uint32_t m_stackSize = 0;
    Entry m_entry        = nullptr;
    void *m_userData     = nullptr;
    bool m_created       = false;
    bool m_detached      = false;
    bool m_ownsThread    = true;
    std::string m_name;
};
