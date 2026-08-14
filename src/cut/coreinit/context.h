#pragma once

#include "../cut.h"

#ifdef __cplusplus
extern "C" {
#endif

//! A bitfield of enum OS_CONTEXT_STATE.
typedef uint16_t OSContextState;

enum OS_CONTEXT_STATE
{
    OS_CONTEXT_STATE_OSCALLBACK     = 1 << 3,
    OS_CONTEXT_STATE_USERMODE_SAVED = 1 << 4
};

typedef struct OSContext OSContext;

#define OS_CONTEXT_TAG 0x4F53436F6E747874ull

struct CUT_ALIGNAS(8) OSContext
{
    //! Should always be set to the value OS_CONTEXT_TAG.
    uint64_t tag;

    uint32_t gpr[32];
    uint32_t cr;
    uint32_t lr;
    uint32_t ctr;
    uint32_t xer;
    uint32_t srr0;
    uint32_t srr1;
    uint32_t dsisr;
    uint32_t dar;
    CUT_UNKNOWN_BYTES(0xC);
    uint32_t fpscr;
    double fpr[32];
    uint16_t spinLockCount;
    OSContextState state;
    uint32_t gqr[8];
    //! Current core index
    uint32_t upir;
    double psf[32];
    uint64_t coretime[3];
    uint64_t starttime;
    uint32_t error;
    CUT_UNKNOWN_BYTES(4);
    uint32_t pmc1;
    uint32_t pmc2;
    uint32_t pmc3;
    uint32_t pmc4;
    uint32_t mmcr0;
    uint32_t mmcr1;
};
CUT_CHECK_OFFSET(OSContext, 0x00, tag);
CUT_CHECK_OFFSET(OSContext, 0x08, gpr);
CUT_CHECK_OFFSET(OSContext, 0x88, cr);
CUT_CHECK_OFFSET(OSContext, 0x8c, lr);
CUT_CHECK_OFFSET(OSContext, 0x90, ctr);
CUT_CHECK_OFFSET(OSContext, 0x94, xer);
CUT_CHECK_OFFSET(OSContext, 0x98, srr0);
CUT_CHECK_OFFSET(OSContext, 0x9c, srr1);
CUT_CHECK_OFFSET(OSContext, 0xa0, dsisr);
CUT_CHECK_OFFSET(OSContext, 0xa4, dar);
CUT_CHECK_OFFSET(OSContext, 0xb4, fpscr);
CUT_CHECK_OFFSET(OSContext, 0xb8, fpr);
CUT_CHECK_OFFSET(OSContext, 0x1b8, spinLockCount);
CUT_CHECK_OFFSET(OSContext, 0x1ba, state);
CUT_CHECK_OFFSET(OSContext, 0x1bc, gqr);
CUT_CHECK_OFFSET(OSContext, 0x1dc, upir);
CUT_CHECK_OFFSET(OSContext, 0x1e0, psf);
CUT_CHECK_OFFSET(OSContext, 0x2e0, coretime);
CUT_CHECK_OFFSET(OSContext, 0x2f8, starttime);
CUT_CHECK_OFFSET(OSContext, 0x300, error);
CUT_CHECK_OFFSET(OSContext, 0x308, pmc1);
CUT_CHECK_OFFSET(OSContext, 0x30c, pmc2);
CUT_CHECK_OFFSET(OSContext, 0x310, pmc3);
CUT_CHECK_OFFSET(OSContext, 0x314, pmc4);
CUT_CHECK_OFFSET(OSContext, 0x318, mmcr0);
CUT_CHECK_OFFSET(OSContext, 0x31c, mmcr1);
CUT_CHECK_SIZE(OSContext, 0x320);

#ifdef __cplusplus
}
#endif
