#pragma once

#include "../cut.h"
#include "device.h"
#include "result.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXVoice AXVoice;
typedef struct AXVoiceAdpcmLoopData AXVoiceAdpcmLoopData;
typedef struct AXVoiceAdpcm AXVoiceAdpcm;
typedef struct AXVoiceBiquad AXVoiceBiquad;
typedef struct AXVoiceDeviceBusMixData AXVoiceDeviceBusMixData;
typedef struct AXVoiceDeviceMixData AXVoiceDeviceMixData;
typedef struct AXVoiceLink AXVoiceLink;
typedef struct AXVoiceLpf AXVoiceLpf;
typedef struct AXVoiceOffsets AXVoiceOffsets;
typedef struct AXVoiceSrc AXVoiceSrc;
typedef struct AXVoiceVeData AXVoiceVeData;

//! A value from enum AX_VOICE_FORMAT.
typedef uint16_t AXVoiceFormat;

//! A value from enum AX_VOICE_LOOP.
typedef uint16_t AXVoiceLoop;

//! A value from enum AX_VOICE_SRC_TYPE.
typedef uint32_t AXVoiceSrcType;

//! A value from enum AX_VOICE_STATE.
typedef uint32_t AXVoiceState;

//! A value from enum AX_VOICE_RENDERER.
typedef uint32_t AXVoiceRenderer;

//! A value from enum AX_VOICE_RATIO_RESULT.
typedef int AXVoiceSrcRatioResult;

//! A value from enum AX_VOICE_TYPE.
typedef uint32_t AXVoiceType;

typedef void (*AXVoiceCallbackFn)(void *);
typedef void (*AXVoiceCallbackExFn)(void *, uint32_t, uint32_t);

enum AX_VOICE_FORMAT
{
    AX_VOICE_FORMAT_ADPCM  = 0,
    AX_VOICE_FORMAT_LPCM16 = 10,
    AX_VOICE_FORMAT_LPCM8  = 25,
};

enum AX_VOICE_LOOP
{
    AX_VOICE_LOOP_DISABLED = 0,
    AX_VOICE_LOOP_ENABLED  = 1,
};

enum AX_VOICE_RENDERER
{
    AX_VOICE_RENDERER_DSP  = 0,
    AX_VOICE_RENDERER_CPU  = 1,
    AX_VOICE_RENDERER_AUTO = 2,
};

enum AX_VOICE_RATIO_RESULT
{
    AX_VOICE_RATIO_RESULT_SUCCESS                = 0,
    AX_VOICE_RATIO_RESULT_LESS_THAN_ZERO         = -1,
    AX_VOICE_RATIO_RESULT_GREATER_THAN_SOMETHING = -2,
};

enum AX_VOICE_SRC_TYPE
{
    AX_VOICE_SRC_TYPE_NONE     = 0,
    AX_VOICE_SRC_TYPE_LINEAR   = 1,
    AX_VOICE_SRC_TYPE_LOWPASS1 = 2,
    AX_VOICE_SRC_TYPE_LOWPASS2 = 3,
    AX_VOICE_SRC_TYPE_LOWPASS3 = 4,
};

enum AX_VOICE_STATE
{
    AX_VOICE_STATE_STOPPED = 0,
    AX_VOICE_STATE_PLAYING = 1,
};

enum AX_VOICE_TYPE
{
    AX_VOICE_TYPE_NORMAL = 0,
};

struct AXVoiceLink
{
    AXVoice *next;
    AXVoice *prev;
};
CUT_CHECK_OFFSET(AXVoiceLink, 0x0, next);
CUT_CHECK_OFFSET(AXVoiceLink, 0x4, prev);
CUT_CHECK_SIZE(AXVoiceLink, 0x8);

struct AXVoiceOffsets
{
    AXVoiceFormat dataType;
    AXVoiceLoop loopingEnabled;
    uint32_t loopOffset;
    uint32_t endOffset;
    uint32_t currentOffset;
    const void *data;
};
CUT_CHECK_OFFSET(AXVoiceOffsets, 0x0, dataType);
CUT_CHECK_OFFSET(AXVoiceOffsets, 0x2, loopingEnabled);
CUT_CHECK_OFFSET(AXVoiceOffsets, 0x4, loopOffset);
CUT_CHECK_OFFSET(AXVoiceOffsets, 0x8, endOffset);
CUT_CHECK_OFFSET(AXVoiceOffsets, 0xc, currentOffset);
CUT_CHECK_OFFSET(AXVoiceOffsets, 0x10, data);
CUT_CHECK_SIZE(AXVoiceOffsets, 0x14);

struct AXVoice
{
    uint32_t index;
    AXVoiceState state;
    uint32_t volume;
    AXVoiceRenderer renderer;
    AXVoiceLink link;
    AXVoice *cbNext;
    uint32_t priority;
    AXVoiceCallbackFn callback;
    void *userContext;
    uint32_t syncBits;
    CUT_UNKNOWN_BYTES(0x8);
    AXVoiceOffsets offsets;
    AXVoiceCallbackExFn callbackEx;
    uint32_t callbackReason;
    float unk0;
    float unk1;
};
CUT_CHECK_OFFSET(AXVoice, 0x0, index);
CUT_CHECK_OFFSET(AXVoice, 0x4, state);
CUT_CHECK_OFFSET(AXVoice, 0x8, volume);
CUT_CHECK_OFFSET(AXVoice, 0xc, renderer);
CUT_CHECK_OFFSET(AXVoice, 0x10, link);
CUT_CHECK_OFFSET(AXVoice, 0x18, cbNext);
CUT_CHECK_OFFSET(AXVoice, 0x1c, priority);
CUT_CHECK_OFFSET(AXVoice, 0x20, callback);
CUT_CHECK_OFFSET(AXVoice, 0x24, userContext);
CUT_CHECK_OFFSET(AXVoice, 0x28, syncBits);
CUT_CHECK_OFFSET(AXVoice, 0x34, offsets);
CUT_CHECK_OFFSET(AXVoice, 0x48, callbackEx);
CUT_CHECK_OFFSET(AXVoice, 0x4c, callbackReason);
CUT_CHECK_OFFSET(AXVoice, 0x50, unk0);
CUT_CHECK_OFFSET(AXVoice, 0x54, unk1);
CUT_CHECK_SIZE(AXVoice, 0x58);

struct AXVoiceDeviceBusMixData
{
    uint16_t volume;
    int16_t delta;
};
CUT_CHECK_OFFSET(AXVoiceDeviceBusMixData, 0x0, volume);
CUT_CHECK_OFFSET(AXVoiceDeviceBusMixData, 0x2, delta);
CUT_CHECK_SIZE(AXVoiceDeviceBusMixData, 0x4);

struct AXVoiceDeviceMixData
{
    AXVoiceDeviceBusMixData bus[4];
};
CUT_CHECK_OFFSET(AXVoiceDeviceMixData, 0x0, bus);
CUT_CHECK_SIZE(AXVoiceDeviceMixData, 0x10);

struct AXVoiceVeData
{
    uint16_t volume;
    int16_t delta;
};
CUT_CHECK_OFFSET(AXVoiceVeData, 0x0, volume);
CUT_CHECK_OFFSET(AXVoiceVeData, 0x2, delta);
CUT_CHECK_SIZE(AXVoiceVeData, 0x4);

struct AXVoiceLpf
{
    uint16_t on;
    int16_t yn1;
    int16_t a0;
    int16_t b0;
};
CUT_CHECK_OFFSET(AXVoiceLpf, 0x0, on);
CUT_CHECK_OFFSET(AXVoiceLpf, 0x2, yn1);
CUT_CHECK_OFFSET(AXVoiceLpf, 0x4, a0);
CUT_CHECK_OFFSET(AXVoiceLpf, 0x6, b0);
CUT_CHECK_SIZE(AXVoiceLpf, 0x8);

struct AXVoiceBiquad
{
    uint16_t on;
    int16_t xn1;
    int16_t xn2;
    int16_t yn1;
    int16_t yn2;
    uint16_t b0;
    uint16_t b1;
    uint16_t b2;
    uint16_t a1;
    uint16_t a2;
};
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x00, on);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x02, xn1);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x04, xn2);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x06, yn1);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x08, yn2);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x0A, b0);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x0C, b1);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x0E, b2);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x10, a1);
CUT_CHECK_OFFSET(AXVoiceBiquad, 0x12, a2);
CUT_CHECK_SIZE(AXVoiceBiquad, 0x14);

struct AXVoiceAdpcmLoopData
{
    uint16_t predScale;
    int16_t prevSample[2];
};
CUT_CHECK_OFFSET(AXVoiceAdpcmLoopData, 0x0, predScale);
CUT_CHECK_OFFSET(AXVoiceAdpcmLoopData, 0x2, prevSample);
CUT_CHECK_SIZE(AXVoiceAdpcmLoopData, 0x6);

struct AXVoiceAdpcm
{
    int16_t coefficients[16];
    uint16_t gain;
    uint16_t predScale;
    int16_t prevSample[2];
};
CUT_CHECK_OFFSET(AXVoiceAdpcm, 0x0, coefficients);
CUT_CHECK_OFFSET(AXVoiceAdpcm, 0x20, gain);
CUT_CHECK_OFFSET(AXVoiceAdpcm, 0x22, predScale);
CUT_CHECK_OFFSET(AXVoiceAdpcm, 0x24, prevSample);
CUT_CHECK_SIZE(AXVoiceAdpcm, 0x28);

#pragma pack(push, 1)
struct AXVoiceSrc
{
    uint32_t ratio;
    uint16_t currentOffsetFrac;
    int16_t lastSample[4];
};
CUT_CHECK_OFFSET(AXVoiceSrc, 0x0, ratio);
CUT_CHECK_OFFSET(AXVoiceSrc, 0x4, currentOffsetFrac);
CUT_CHECK_OFFSET(AXVoiceSrc, 0x6, lastSample);
CUT_CHECK_SIZE(AXVoiceSrc, 0xe);
#pragma pack(pop)

CUT_IMPORT BOOL (*AXUserIsProtected)();

CUT_IMPORT int (*AXUserBegin)();

CUT_IMPORT int (*AXUserEnd)();

CUT_IMPORT int (*AXVoiceBegin)(AXVoice *v);

CUT_IMPORT int (*AXVoiceEnd)(AXVoice *v);

CUT_IMPORT BOOL (*AXVoiceIsProtected)(AXVoice *v);

CUT_IMPORT AXVoice *(*AXAcquireVoice)(uint32_t priority, AXVoiceCallbackFn callback, void *userContext);

CUT_IMPORT AXVoice *(*AXAcquireVoiceEx)(uint32_t priority, AXVoiceCallbackExFn callback, void *userContext);

CUT_IMPORT BOOL (*AXCheckVoiceOffsets)(AXVoiceOffsets *offsets);

CUT_IMPORT void (*AXFreeVoice)(AXVoice *voice);

CUT_IMPORT uint32_t (*AXGetMaxVoices)();

CUT_IMPORT uint32_t (*AXGetVoiceCurrentOffsetEx)(AXVoice *voice, const void *samples);

CUT_IMPORT uint32_t (*AXGetVoiceLoopCount)(AXVoice *voice);

CUT_IMPORT void (*AXGetVoiceOffsets)(AXVoice *voice, AXVoiceOffsets *offsets);

CUT_IMPORT BOOL (*AXIsVoiceRunning)(AXVoice *voice);

CUT_IMPORT void (*AXSetVoiceAdpcm)(AXVoice *voice, AXVoiceAdpcm *adpcm);

CUT_IMPORT void (*AXSetVoiceAdpcmLoop)(AXVoice *voice, AXVoiceAdpcmLoopData *loopData);

CUT_IMPORT void (*AXSetVoiceCurrentOffset)(AXVoice *voice, uint32_t offset);

CUT_IMPORT void (*AXSetVoiceCurrentOffsetEx)(AXVoice *voice, uint32_t offset, const void *samples);

CUT_IMPORT AXResult (*AXSetVoiceDeviceMix)(AXVoice *voice, AXDeviceType type, uint32_t id, AXVoiceDeviceMixData *mixData);

CUT_IMPORT void (*AXSetVoiceEndOffset)(AXVoice *voice, uint32_t offset);

CUT_IMPORT void (*AXSetVoiceEndOffsetEx)(AXVoice *voice, uint32_t offset, const void *samples);

CUT_IMPORT void (*AXSetVoiceLoopOffset)(AXVoice *voice, uint32_t offset);

CUT_IMPORT void (*AXSetVoiceLoopOffsetEx)(AXVoice *voice, uint32_t offset, const void *samples);

CUT_IMPORT void (*AXSetVoiceLoop)(AXVoice *voice, AXVoiceLoop loop);

CUT_IMPORT void (*AXSetVoiceOffsets)(AXVoice *voice, AXVoiceOffsets *offsets);

CUT_IMPORT void (*AXSetVoiceOffsetsEx)(AXVoice *voice, AXVoiceOffsets *offsets, const void *samples);

CUT_IMPORT void (*AXSetVoiceSamplesAddr)(AXVoice *voice, void *samples);

CUT_IMPORT void (*AXSetVoiceSrc)(AXVoice *voice, AXVoiceSrc *src);

CUT_IMPORT AXVoiceSrcRatioResult (*AXSetVoiceSrcRatio)(AXVoice *voice, float ratio);

CUT_IMPORT void (*AXSetVoiceSrcType)(AXVoice *voice, AXVoiceSrcType type);

CUT_IMPORT void (*AXSetVoiceState)(AXVoice *voice, AXVoiceState state);

CUT_IMPORT void (*AXSetVoiceType)(AXVoice *voice, AXVoiceType type);

CUT_IMPORT void (*AXSetVoiceVe)(AXVoice *voice, AXVoiceVeData *veData);

CUT_IMPORT void (*AXComputeLpfCoefs)(uint32_t freq, uint16_t *a0, uint16_t *b0);

CUT_IMPORT void (*AXSetVoiceLpf)(AXVoice *voice, AXVoiceLpf *lpf);

CUT_IMPORT void (*AXSetVoiceLpfCoefs)(AXVoice *voice, uint16_t a0, uint16_t b0);

CUT_IMPORT void (*AXSetVoiceBiquad)(AXVoice *voice, AXVoiceBiquad *biquad);

CUT_IMPORT void (*AXSetVoiceBiquadCoefs)(AXVoice *voice, uint16_t b0, uint16_t b1, uint16_t b2, uint16_t a1, uint16_t a2);

#ifdef __cplusplus
}
#endif
