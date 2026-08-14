#pragma once

#include "../input.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsVPADInput
{
    int (*VPADRead)(VPADChan chan, VPADStatus *buffers, uint32_t count, VPADReadError *outError);
    void (*VPADGetTPCalibrationParam)(VPADChan chan, VPADTouchCalibrationParam *outParam);
    void (*VPADSetTPCalibrationParam)(VPADChan chan, const VPADTouchCalibrationParam *param);
    void (*VPADGetTPCalibratedPoint)(VPADChan chan, VPADTouchData *calibratedData, const VPADTouchData *uncalibratedData);
    void (*VPADGetTPCalibratedPointEx)(VPADChan chan, VPADTouchPadResolution tpResolution, VPADTouchData *calibratedData,
                                       const VPADTouchData *uncalibratedData);
    void (*VPADSetAccParam)(VPADChan chan, float playRadius, float sensitivity);
    void (*VPADGetAccParam)(VPADChan chan, float *outPlayRadius, float *outSensitivity);
    void (*VPADSetBtnRepeat)(VPADChan chan, float delaySec, float pulseSec);
    void (*VPADEnableStickCrossClamp)(VPADChan chan);
    void (*VPADDisableStickCrossClamp)(VPADChan chan);
    void (*VPADSetLStickClampThreshold)(VPADChan chan, int max, int min);
    void (*VPADSetRStickClampThreshold)(VPADChan chan, int max, int min);
    void (*VPADGetGyroZeroDriftMode)(VPADChan chan, VPADGyroZeroDriftMode *mode);
    void (*VPADGetLStickClampThreshold)(VPADChan chan, int *max, int *min);
    void (*VPADGetRStickClampThreshold)(VPADChan chan, int *max, int *min);
    void (*VPADSetCrossStickEmulationParamsL)(VPADChan chan, float rotationDegree, float range, float radius);
    void (*VPADSetCrossStickEmulationParamsR)(VPADChan chan, float rotationDegree, float range, float radius);
    void (*VPADGetCrossStickEmulationParamsL)(VPADChan chan, float *outRotationDegree, float *outRange, float *outRadius);
    void (*VPADGetCrossStickEmulationParamsR)(VPADChan chan, float *outRotationDegree, float *outRange, float *outRadius);
    void (*VPADSetGyroDirReviseBase)(VPADChan chan, VPADDirection *base);
    void (*VPADSetGyroDirReviseParam)(VPADChan chan, float param);
    void (*VPADSetGyroDirection)(VPADChan chan, VPADDirection *dir);
    void (*VPADSetGyroZeroDriftMode)(VPADChan chan, VPADGyroZeroDriftMode mode);
    void (*VPADDisableGyroDirRevise)(VPADChan chan);
    int (*VPADControlMotor)(VPADChan chan, uint8_t *pattern, uint8_t length);
    void (*VPADStopMotor)(VPADChan chan);
    int (*VPADSetLcdMode)(VPADChan chan, VPADLcdMode lcdMode);
    int (*VPADGetLcdMode)(VPADChan chan, VPADLcdMode *outLcdMode);
    VPADSamplingCallback (*VPADSetSamplingCallback)(VPADChan chan, VPADSamplingCallback callback);
    BOOL (*VPADGetButtonProcMode)(VPADChan chan);
} ImportsVPADInput;

#ifdef __cplusplus
}
#endif
