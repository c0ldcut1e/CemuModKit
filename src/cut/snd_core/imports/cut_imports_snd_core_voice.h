#pragma once

#include "../voice.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsSndCoreVoice
{
    BOOL (*AXUserIsProtected)();
    int (*AXUserBegin)();
    int (*AXUserEnd)();
    int (*AXVoiceBegin)(AXVoice *v);
    int (*AXVoiceEnd)(AXVoice *v);
    BOOL (*AXVoiceIsProtected)(AXVoice *v);
    AXVoice *(*AXAcquireVoice)(uint32_t priority, AXVoiceCallbackFn callback, void *userContext);
    AXVoice *(*AXAcquireVoiceEx)(uint32_t priority, AXVoiceCallbackExFn callback, void *userContext);
    BOOL (*AXCheckVoiceOffsets)(AXVoiceOffsets *offsets);
    void (*AXFreeVoice)(AXVoice *voice);
    uint32_t (*AXGetMaxVoices)();
    uint32_t (*AXGetVoiceCurrentOffsetEx)(AXVoice *voice, const void *samples);
    uint32_t (*AXGetVoiceLoopCount)(AXVoice *voice);
    void (*AXGetVoiceOffsets)(AXVoice *voice, AXVoiceOffsets *offsets);
    BOOL (*AXIsVoiceRunning)(AXVoice *voice);
    void (*AXSetVoiceAdpcm)(AXVoice *voice, AXVoiceAdpcm *adpcm);
    void (*AXSetVoiceAdpcmLoop)(AXVoice *voice, AXVoiceAdpcmLoopData *loopData);
    void (*AXSetVoiceCurrentOffset)(AXVoice *voice, uint32_t offset);
    void (*AXSetVoiceCurrentOffsetEx)(AXVoice *voice, uint32_t offset, const void *samples);
    AXResult (*AXSetVoiceDeviceMix)(AXVoice *voice, AXDeviceType type, uint32_t id, AXVoiceDeviceMixData *mixData);
    void (*AXSetVoiceEndOffset)(AXVoice *voice, uint32_t offset);
    void (*AXSetVoiceEndOffsetEx)(AXVoice *voice, uint32_t offset, const void *samples);
    void (*AXSetVoiceLoopOffset)(AXVoice *voice, uint32_t offset);
    void (*AXSetVoiceLoopOffsetEx)(AXVoice *voice, uint32_t offset, const void *samples);
    void (*AXSetVoiceLoop)(AXVoice *voice, AXVoiceLoop loop);
    void (*AXSetVoiceOffsets)(AXVoice *voice, AXVoiceOffsets *offsets);
    void (*AXSetVoiceOffsetsEx)(AXVoice *voice, AXVoiceOffsets *offsets, const void *samples);
    void (*AXSetVoiceSamplesAddr)(AXVoice *voice, void *samples);
    void (*AXSetVoiceSrc)(AXVoice *voice, AXVoiceSrc *src);
    AXVoiceSrcRatioResult (*AXSetVoiceSrcRatio)(AXVoice *voice, float ratio);
    void (*AXSetVoiceSrcType)(AXVoice *voice, AXVoiceSrcType type);
    void (*AXSetVoiceState)(AXVoice *voice, AXVoiceState state);
    void (*AXSetVoiceType)(AXVoice *voice, AXVoiceType type);
    void (*AXSetVoiceVe)(AXVoice *voice, AXVoiceVeData *veData);
    void (*AXComputeLpfCoefs)(uint32_t freq, uint16_t *a0, uint16_t *b0);
    void (*AXSetVoiceLpf)(AXVoice *voice, AXVoiceLpf *lpf);
    void (*AXSetVoiceLpfCoefs)(AXVoice *voice, uint16_t a0, uint16_t b0);
    void (*AXSetVoiceBiquad)(AXVoice *voice, AXVoiceBiquad *biquad);
    void (*AXSetVoiceBiquadCoefs)(AXVoice *voice, uint16_t b0, uint16_t b1, uint16_t b2, uint16_t a1, uint16_t a2);
} ImportsSndCoreVoice;

#ifdef __cplusplus
}
#endif
