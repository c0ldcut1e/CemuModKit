#pragma once

#include "../cut.h"
#include "../vpadbase/base.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VPADAccStatus VPADAccStatus;
typedef struct VPADDirection VPADDirection;
typedef struct VPADStatus VPADStatus;
typedef struct VPADTouchCalibrationParam VPADTouchCalibrationParam;
typedef struct VPADTouchData VPADTouchData;
typedef struct VPADVec2D VPADVec2D;
typedef struct VPADVec3D VPADVec3D;

//! Wii U GamePad buttons.
typedef enum VPADButtons
{
    //! The A button.
    VPAD_BUTTON_A = 0x8000,
    //! The B button.
    VPAD_BUTTON_B = 0x4000,
    //! The X button.
    VPAD_BUTTON_X = 0x2000,
    //! The Y button.
    VPAD_BUTTON_Y = 0x1000,
    //! The left button of the D-pad.
    VPAD_BUTTON_LEFT = 0x0800,
    //! The right button of the D-pad.
    VPAD_BUTTON_RIGHT = 0x0400,
    //! The up button of the D-pad.
    VPAD_BUTTON_UP = 0x0200,
    //! The down button of the D-pad.
    VPAD_BUTTON_DOWN = 0x0100,
    //! The ZL button.
    VPAD_BUTTON_ZL = 0x0080,
    //! The ZR button.
    VPAD_BUTTON_ZR = 0x0040,
    //! The L button.
    VPAD_BUTTON_L = 0x0020,
    //! The R button.
    VPAD_BUTTON_R = 0x0010,
    //! The + button.
    VPAD_BUTTON_PLUS = 0x0008,
    //! The - button.
    VPAD_BUTTON_MINUS = 0x0004,
    //! The HOME button.
    VPAD_BUTTON_HOME = 0x0002,
    //! The SYNC button.
    VPAD_BUTTON_SYNC = 0x0001,
    //! The right stick button.
    VPAD_BUTTON_STICK_R = 0x00020000,
    //! The left stick button.
    VPAD_BUTTON_STICK_L = 0x00040000,
    //! The TV button.
    VPAD_BUTTON_TV = 0x00010000,
    //! The emulated left button on the right stick.
    VPAD_STICK_R_EMULATION_LEFT = 0x04000000,
    //! The emulated right button on the right stick.
    VPAD_STICK_R_EMULATION_RIGHT = 0x02000000,
    //! The emulated up button on the right stick.
    VPAD_STICK_R_EMULATION_UP = 0x01000000,
    //! The emulated down button on the right stick.
    VPAD_STICK_R_EMULATION_DOWN = 0x00800000,
    //! The emulated left button on the left stick.
    VPAD_STICK_L_EMULATION_LEFT = 0x40000000,
    //! The emulated right button on the left stick.
    VPAD_STICK_L_EMULATION_RIGHT = 0x20000000,
    //! The emulated up button on the left stick.
    VPAD_STICK_L_EMULATION_UP = 0x10000000,
    //! The emulated down button on the left stick.
    VPAD_STICK_L_EMULATION_DOWN = 0x08000000,
} VPADButtons;

//! Touch pad validity.
typedef enum VPADTouchPadValidity
{
    //! Both X and Y touchpad positions are accurate.
    VPAD_VALID = 0x0,

    //! X position is inaccurate.
    VPAD_INVALID_X = 0x1,

    //! Y position is inaccurate.
    VPAD_INVALID_Y = 0x2,
} VPADTouchPadValidity;

//! Touch pad resolution.
typedef enum VPADTouchPadResolution
{
    //! 1920 x 1080 resolution.
    VPAD_TP_1920X1080 = 0,
    //! 1280 x 720 resolution.
    VPAD_TP_1280X720 = 1,
    //! 854 x 480 resolution.
    VPAD_TP_854X480 = 2,
} VPADTouchPadResolution;

//! Read error.
typedef enum VPADReadError
{
    //! No error occurred, and data was written to the buffers.
    VPAD_READ_SUCCESS = 0,
    //! There was no sample new data available to write.
    VPAD_READ_NO_SAMPLES = -1,
    //! The requested controller or channel was invalid.
    VPAD_READ_INVALID_CONTROLLER = -2,
    //! VPAD channel is busy, perhaps being accessed by another thread
    VPAD_READ_BUSY = -4,
    //! VPAD is uninitialized, need to call VPADInit()
    VPAD_READ_UNINITIALIZED = -5,
} VPADReadError;

//! LCD mode.
typedef enum VPADLcdMode
{
    //! Display is in standby and will turn back on if any buttons are pressed.
    VPAD_LCD_STANDBY = 0,
    //! Display is completely off and will remain so until explicitly changed.
    VPAD_LCD_OFF = 1,
    //! Display is on as normal.
    VPAD_LCD_ON = 0xFF,
} VPADLcdMode;

//! Gyro zero drift mode.
typedef enum VPADGyroZeroDriftMode
{
    VPAD_GYRO_ZERODRIFT_LOOSE = 0,
    VPAD_GYRO_ZERODRIFT_STANDARD,
    VPAD_GYRO_ZERODRIFT_TIGHT,
    VPAD_GYRO_ZERODRIFT_NONE
} VPADGyroZeroDriftMode;

//! 2D vector.
struct VPADVec2D
{
    //! x.
    float x;
    //! y.
    float y;
};
CUT_CHECK_OFFSET(VPADVec2D, 0x00, x);
CUT_CHECK_OFFSET(VPADVec2D, 0x04, y);
CUT_CHECK_SIZE(VPADVec2D, 0x08);

//! 3D vector.
struct VPADVec3D
{
    //! x.
    float x;
    //! y.
    float y;
    //! z.
    float z;
};
CUT_CHECK_OFFSET(VPADVec3D, 0x00, x);
CUT_CHECK_OFFSET(VPADVec3D, 0x04, y);
CUT_CHECK_OFFSET(VPADVec3D, 0x08, z);
CUT_CHECK_SIZE(VPADVec3D, 0x0C);

//! Direction.
struct VPADDirection
{
    //! x.
    VPADVec3D x;
    //! y.
    VPADVec3D y;
    //! z.
    VPADVec3D z;
};
CUT_CHECK_OFFSET(VPADDirection, 0x00, x);
CUT_CHECK_OFFSET(VPADDirection, 0x0C, y);
CUT_CHECK_OFFSET(VPADDirection, 0x18, z);
CUT_CHECK_SIZE(VPADDirection, 0x24);

//! Touch calibration parameter.
struct VPADTouchCalibrationParam
{
    //! X offset.
    uint16_t adjustX;
    //! Y offset.
    uint16_t adjustY;
    //! X scale.
    float scaleX;
    //! Y scale.
    float scaleY;
};
CUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x00, adjustX);
CUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x02, adjustY);
CUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x04, scaleX);
CUT_CHECK_OFFSET(VPADTouchCalibrationParam, 0x08, scaleY);
CUT_CHECK_SIZE(VPADTouchCalibrationParam, 0x0C);

//! Touch data.
struct VPADTouchData
{
    //! The x-coordinate of a touched point.
    uint16_t x;
    //! The y-coordinate of a touched point.
    uint16_t y;

    //! 0 if screen is not currently being touched.
    uint16_t touched;

    //! Bitfield of #VPADTouchPadValidity to indicate how touch sample accuracy.
    uint16_t validity;
};
CUT_CHECK_OFFSET(VPADTouchData, 0x00, x);
CUT_CHECK_OFFSET(VPADTouchData, 0x02, y);
CUT_CHECK_OFFSET(VPADTouchData, 0x04, touched);
CUT_CHECK_OFFSET(VPADTouchData, 0x06, validity);
CUT_CHECK_SIZE(VPADTouchData, 0x08);

struct VPADAccStatus
{
    VPADVec3D acc;
    float magnitude;
    float variation;
    VPADVec2D vertical;
};
CUT_CHECK_OFFSET(VPADAccStatus, 0x00, acc);
CUT_CHECK_OFFSET(VPADAccStatus, 0x0C, magnitude);
CUT_CHECK_OFFSET(VPADAccStatus, 0x10, variation);
CUT_CHECK_OFFSET(VPADAccStatus, 0x14, vertical);
CUT_CHECK_SIZE(VPADAccStatus, 0x1c);

struct VPADStatus
{
    //! Indicates what VPADButtons are held down.
    uint32_t hold;

    //! Indicates what VPADButtons have been pressed since last sample.
    uint32_t trigger;

    //! Indicates what VPADButtons have been released since last sample.
    uint32_t release;

    //! Position of left analog stick.
    VPADVec2D leftStick;

    //! Position of right analog stick.
    VPADVec2D rightStick;

    //! Status of DRC accelorometer.
    VPADAccStatus accelorometer;

    //! Status of DRC gyro.
    VPADVec3D gyro;

    //! Status of DRC angle.
    VPADVec3D angle;

    uint8_t error;

    CUT_UNKNOWN_BYTES(0x01);

    //! Current touch position on DRC.
    VPADTouchData tpNormal;

    //! Filtered touch position, first level of smoothing.
    VPADTouchData tpFiltered1;

    //! Filtered touch position, second level of smoothing.
    VPADTouchData tpFiltered2;

    CUT_UNKNOWN_BYTES(0x02);

    VPADDirection direction;

    //! Set to 1 if headphones are plugged in, 0 otherwise.
    BOOL usingHeadphones;

    //! Status of DRC magnetometer.
    VPADVec3D mag;

    //! Current volume set by the slide control.
    uint8_t slideVolume;

    //! Battery level of controller.
    uint8_t battery;

    //! Status of DRC microphone.
    uint8_t micStatus;

    //! Unknown volume related value.
    uint8_t slideVolumeEx;

    CUT_UNKNOWN_BYTES(0x8);
};
CUT_CHECK_OFFSET(VPADStatus, 0x00, hold);
CUT_CHECK_OFFSET(VPADStatus, 0x04, trigger);
CUT_CHECK_OFFSET(VPADStatus, 0x08, release);
CUT_CHECK_OFFSET(VPADStatus, 0x0C, leftStick);
CUT_CHECK_OFFSET(VPADStatus, 0x14, rightStick);
CUT_CHECK_OFFSET(VPADStatus, 0x1C, accelorometer);
CUT_CHECK_OFFSET(VPADStatus, 0x38, gyro);
CUT_CHECK_OFFSET(VPADStatus, 0x44, angle);
CUT_CHECK_OFFSET(VPADStatus, 0x50, error);
CUT_CHECK_OFFSET(VPADStatus, 0x52, tpNormal);
CUT_CHECK_OFFSET(VPADStatus, 0x5A, tpFiltered1);
CUT_CHECK_OFFSET(VPADStatus, 0x62, tpFiltered2);
CUT_CHECK_OFFSET(VPADStatus, 0x6C, direction);
CUT_CHECK_OFFSET(VPADStatus, 0x94, mag);
CUT_CHECK_OFFSET(VPADStatus, 0xA0, slideVolume);
CUT_CHECK_OFFSET(VPADStatus, 0xA1, battery);
CUT_CHECK_OFFSET(VPADStatus, 0xA2, micStatus);
CUT_CHECK_OFFSET(VPADStatus, 0xA3, slideVolumeEx);
CUT_CHECK_SIZE(VPADStatus, 0xAC);

typedef void (*VPADSamplingCallback)(VPADChan chan);

/**
 * Read controller data from the desired Gamepad.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel to read from.
 *
 * \param buffers
 * Pointer to an array of VPADStatus buffers to fill.
 *
 * \param count
 * Number of buffers to fill.
 *
 * \param outError
 * Pointer to write read error to (if any). See #VPADReadError for meanings.
 *
 * \warning
 * You must check outError - the VPADStatus buffers may be filled with random
 * or invalid data on error, not necessarily zeroes.
 *
 * \return
 * The amount of buffers read or 0 on failure. Check outError for reason.
 *
 * \sa
 * - VPADStatus
 */
CUT_IMPORT int (*VPADRead)(VPADChan chan, VPADStatus *buffers, uint32_t count, VPADReadError *outError);

/**
 * Get touch pad calibration parameters.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the calibration parameter from.
 *
 * \param outParam
 * Pointer to the calibration to get.
 */
CUT_IMPORT void (*VPADGetTPCalibrationParam)(VPADChan chan, VPADTouchCalibrationParam *outParam);

/**
 * Set touch pad calibration parameters.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to set the calibration parameter to.
 *
 * \param param
 * Pointer to the calibration to set.
 */
CUT_IMPORT void (*VPADSetTPCalibrationParam)(VPADChan chan, const VPADTouchCalibrationParam *param);

/**
 * Transform touch data according to the current calibration data.
 * The calibration used may either be the system default or set by the
 * application via VPADSetTPCalibrationParam().
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the calibration data from.
 *
 * \param calibratedData
 * Pointer to write calibrated touch data to.
 *
 * \param uncalibratedData
 * Pointer to the source data to apply the calibration to.
 *
 * \sa
 * - VPADTouchData
 */
CUT_IMPORT void (*VPADGetTPCalibratedPoint)(VPADChan chan, VPADTouchData *calibratedData, const VPADTouchData *uncalibratedData);

/**
 * Transform touch data according to the current calibration data.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to get the calibration data from.
 *
 * \param tpResolution
 * Touchpad resolution.
 *
 * \param calibratedData
 * Pointer to write calibrated touch data to.
 *
 * \param uncalibratedData
 * Pointer to the source data to apply the calibration to.
 *
 * \sa
 * - VPADTouchData
 */
CUT_IMPORT void (*VPADGetTPCalibratedPointEx)(VPADChan chan, VPADTouchPadResolution tpResolution, VPADTouchData *calibratedData,
                                              const VPADTouchData *uncalibratedData);

CUT_IMPORT void (*VPADSetAccParam)(VPADChan chan, float playRadius, float sensitivity);

CUT_IMPORT void (*VPADGetAccParam)(VPADChan chan, float *outPlayRadius, float *outSensitivity);

/**
 * Set a repeat for held buttons - instead of appearing to be continually held,
 * repeated presses and releases will be simulated at the given frequency. This
 * is similar to what happens with most computer keyboards when you hold a key.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * Denotes which channel to set up button repeat on.
 *
 * \param delaySec
 * The amount of time, in seconds, to wait until a button should start
 * repeating.
 *
 * \param pulseSec
 * The amount of time to wait between simulated presses - effectively setting
 * the period of the repetition.
 */
CUT_IMPORT void (*VPADSetBtnRepeat)(VPADChan chan, float delaySec, float pulseSec);

CUT_IMPORT void (*VPADEnableStickCrossClamp)(VPADChan chan);

CUT_IMPORT void (*VPADDisableStickCrossClamp)(VPADChan chan);

CUT_IMPORT void (*VPADSetLStickClampThreshold)(VPADChan chan, int max, int min);

CUT_IMPORT void (*VPADSetRStickClampThreshold)(VPADChan chan, int max, int min);

CUT_IMPORT void (*VPADGetGyroZeroDriftMode)(VPADChan chan, VPADGyroZeroDriftMode *mode);

CUT_IMPORT void (*VPADGetLStickClampThreshold)(VPADChan chan, int *max, int *min);

CUT_IMPORT void (*VPADGetRStickClampThreshold)(VPADChan chan, int *max, int *min);

CUT_IMPORT void (*VPADSetCrossStickEmulationParamsL)(VPADChan chan, float rotationDegree, float range, float radius);

CUT_IMPORT void (*VPADSetCrossStickEmulationParamsR)(VPADChan chan, float rotationDegree, float range, float radius);

CUT_IMPORT void (*VPADGetCrossStickEmulationParamsL)(VPADChan chan, float *outRotationDegree, float *outRange, float *outRadius);

CUT_IMPORT void (*VPADGetCrossStickEmulationParamsR)(VPADChan chan, float *outRotationDegree, float *outRange, float *outRadius);

CUT_IMPORT void (*VPADSetGyroDirReviseBase)(VPADChan chan, VPADDirection *base);

CUT_IMPORT void (*VPADSetGyroDirReviseParam)(VPADChan chan, float param);

CUT_IMPORT void (*VPADSetGyroDirection)(VPADChan chan, VPADDirection *dir);

CUT_IMPORT void (*VPADSetGyroZeroDriftMode)(VPADChan chan, VPADGyroZeroDriftMode mode);

CUT_IMPORT void (*VPADDisableGyroDirRevise)(VPADChan chan);

/**
 * Turns on the rumble motor on the desired Gamepad.
 * A custom rumble pattern can be set by setting bytes in the input buffer.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to rumble.
 *
 * \param pattern
 * Pointer to an array of bytes, where each byte represents the status of the
 * rumble at a given time. 0xFF denotes rumble while 0x00 denotes no rumble.
 *
 * \param length
 * The size of the rumble pattern, in bytes.
 *
 * \if false
 * meta: find out if the bytes in buffer are an analog intensity control (e.g
 * is 0x7F "half intensity"?) or are simply binary motor on/off toggles
 * \endif
 */
CUT_IMPORT int (*VPADControlMotor)(VPADChan chan, uint8_t *pattern, uint8_t length);

/**
 * Stops the desired Gamepad's rumble motor and cancels any ongoing rumble
 * pattern.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to stop rumbling.
 */
CUT_IMPORT void (*VPADStopMotor)(VPADChan chan);

/**
 * Sets the current mode of the display on the given Gamepad. This function can
 * be used to turn the display on and off, or place it in standby.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to have its display mode changed.
 *
 * \param lcdMode
 * One of \link VPADLcdMode \endlink representing the new status of the display.
 *
 * \returns
 * 0 on success, or a negative value on error.
 */
CUT_IMPORT int (*VPADSetLcdMode)(VPADChan chan, VPADLcdMode lcdMode);

/**
 * Get the current status of the given Gamepad's display.
 *
 * \note
 * Retail Wii U systems have a single Gamepad on \link VPADChan::VPAD_CHAN_0
 * VPAD_CHAN_0. \endlink
 *
 * \param chan
 * The channel of the Gamepad to get the display mode from.
 *
 * \param outLcdMode
 * Pointer to write a value of \link VPADLcdMode \endlink into.
 *
 * \returns
 * 0 on success, or a negative value on error.
 */
CUT_IMPORT int (*VPADGetLcdMode)(VPADChan chan, VPADLcdMode *outLcdMode);

CUT_IMPORT VPADSamplingCallback (*VPADSetSamplingCallback)(VPADChan chan, VPADSamplingCallback callback);

/**
 * Returns the proc mode of the given Gamepad.
 *
 * \param chan
 * The channel of the Gamepad to get the proc mode from
 */
CUT_IMPORT BOOL (*VPADGetButtonProcMode)(VPADChan chan);

#ifdef __cplusplus
}
#endif
