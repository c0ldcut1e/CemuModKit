#include "Main.h"

#include "cut/cut_imports.h"
#include <whb/crash.h>

extern "C" {
void __init_cut_sbrk_heap(MEMHeapHandle heapHandle);
void __init_cut_thread();
void __init_cut_devoptab();
void __init_cut_socket();

__attribute__((used, section(".text.entry"))) void entry(Imports *imports)
{
    cut_setAllImports(imports);

    if (MEMGetBaseHeapHandle)
    {
        MEMHeapHandle mem2 = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2);
        __init_cut_sbrk_heap(mem2);
    }

    __init_cut_thread();
    __init_cut_devoptab();
    __init_cut_socket();

    // WHBInitCrashHandler();

    ModKitMain();
}
} // extern "C"
