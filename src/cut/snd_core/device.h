#pragma once

#include "../cut.h"
#include "result.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AXDeviceFinalOutput AXDeviceFinalOutput;

typedef void (*AXDeviceFinalMixCallback)(void *);
typedef void (*AXAuxCallback)(void *, void *);

//! A value from enum AX_DEVICE_MODE.
typedef uint32_t AXDeviceMode;

//! A value from enum AX_DEVICE_TYPE.
typedef uint32_t AXDeviceType;

enum AX_DEVICE_MODE
{
    AX_DEVICE_MODE_STEREO   = 0,
    AX_DEVICE_MODE_SURROUND = 1,
    AX_DEVICE_MODE_DPL2     = 2,
    AX_DEVICE_MODE_6CH      = 3,
    AX_DEVICE_MODE_MONO     = 5,
};

enum AX_DEVICE_TYPE
{
    AX_DEVICE_TYPE_TV         = 0,
    AX_DEVICE_TYPE_DRC        = 1,
    AX_DEVICE_TYPE_CONTROLLER = 2,
};

struct AXDeviceFinalOutput
{
    uint32_t channelCount;
    uint32_t unk1;
    uint32_t unk2;
    uint32_t unk3;
    uint32_t size;
};
CUT_CHECK_OFFSET(AXDeviceFinalOutput, 0x00, channelCount);
CUT_CHECK_OFFSET(AXDeviceFinalOutput, 0x04, unk1);
CUT_CHECK_OFFSET(AXDeviceFinalOutput, 0x08, unk2);
CUT_CHECK_OFFSET(AXDeviceFinalOutput, 0x0C, unk3);
CUT_CHECK_OFFSET(AXDeviceFinalOutput, 0x10, size);
CUT_CHECK_SIZE(AXDeviceFinalOutput, 0x14);

CUT_IMPORT AXResult (*AXGetDeviceMode)(AXDeviceType type, AXDeviceMode *mode);

CUT_IMPORT AXResult (*AXGetDeviceFinalMixCallback)(AXDeviceType type, AXDeviceFinalMixCallback *func);

CUT_IMPORT AXResult (*AXRegisterDeviceFinalMixCallback)(AXDeviceType type, AXDeviceFinalMixCallback func);

CUT_IMPORT AXResult (*AXGetAuxCallback)(AXDeviceType type, uint32_t deviceIndex, uint32_t auxBusIndex, AXAuxCallback *callback, void **userData);

CUT_IMPORT AXResult (*AXRegisterAuxCallback)(AXDeviceType type, uint32_t deviceIndex, uint32_t auxBusIndex, AXAuxCallback callback, void *userData);

CUT_IMPORT AXResult (*AXSetAuxReturnVolume)(AXDeviceType type, uint32_t deviceIndex, uint32_t auxBusIndex, uint16_t volume);

CUT_IMPORT AXResult (*AXSetDeviceUpsampleStage)(AXDeviceType type, BOOL postFinalMix);

CUT_IMPORT AXResult (*AXGetDeviceUpsampleStage)(AXDeviceType type, uint32_t *stage);

CUT_IMPORT AXResult (*AXSetDeviceRemixMatrix)(AXDeviceType type, uint32_t inputChannelCount, uint32_t outputChannelCount, const float *matrix);

CUT_IMPORT AXResult (*AXGetDeviceRemixMatrix)(AXDeviceType type, uint32_t inputChannelCount, uint32_t outputChannelCount, float **matrix);

CUT_IMPORT AXResult (*AXGetDeviceFinalOutput)(AXDeviceType type, int16_t *sampleBufferOutput, uint32_t bufferSize, AXDeviceFinalOutput *output);

#ifdef __cplusplus
}
#endif
