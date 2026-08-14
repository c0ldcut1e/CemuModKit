#pragma once

#include "../device.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsSndCoreDevice
{
    AXResult (*AXGetDeviceMode)(AXDeviceType type, AXDeviceMode *mode);
    AXResult (*AXGetDeviceFinalMixCallback)(AXDeviceType type, AXDeviceFinalMixCallback *func);
    AXResult (*AXRegisterDeviceFinalMixCallback)(AXDeviceType type, AXDeviceFinalMixCallback func);
    AXResult (*AXGetAuxCallback)(AXDeviceType type, uint32_t deviceIndex, uint32_t auxBusIndex, AXAuxCallback *callback, void **userData);
    AXResult (*AXRegisterAuxCallback)(AXDeviceType type, uint32_t deviceIndex, uint32_t auxBusIndex, AXAuxCallback callback, void *userData);
    AXResult (*AXSetAuxReturnVolume)(AXDeviceType type, uint32_t deviceIndex, uint32_t auxBusIndex, uint16_t volume);
    AXResult (*AXSetDeviceUpsampleStage)(AXDeviceType type, BOOL postFinalMix);
    AXResult (*AXGetDeviceUpsampleStage)(AXDeviceType type, uint32_t *stage);
    AXResult (*AXSetDeviceRemixMatrix)(AXDeviceType type, uint32_t inputChannelCount, uint32_t outputChannelCount, const float *matrix);
    AXResult (*AXGetDeviceRemixMatrix)(AXDeviceType type, uint32_t inputChannelCount, uint32_t outputChannelCount, float **matrix);
    AXResult (*AXGetDeviceFinalOutput)(AXDeviceType type, int16_t *sampleBufferOutput, uint32_t bufferSize, AXDeviceFinalOutput *output);
} ImportsSndCoreDevice;

#ifdef __cplusplus
}
#endif
