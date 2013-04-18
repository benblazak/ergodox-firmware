/* ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * USB LED Codes (usage page 0x08)
 *
 * Prefix: `LED__`
 *
 * Taken from [the HID Usage Tables pdf][1], Section 11, which can be found on
 * [the HID Page][2] at <http://www.usb.org>
 *
 * - Usage Types (from Section 3.4)
 *   - Controls
 *       - LC   : Linear Control
 *       - OOC  : On/Off Control
 *       - MC   : Momentary Control
 *       - OSC  : One Shot Control
 *       - RTC  : Re-Trigger Control
 *   - Data
 *       - Sel  : Selector
 *       - SV   : Static Value
 *       - SF   : Static Flag
 *       - DF   : Dynamic Flag
 *       - DV   : Dynamic Value
 *   - Collection
 *       - NAry : Named Array
 *       - CA   : Collection Application
 *       - CL   : Collection Logical
 *       - CP   : Collection Physical
 *       - US   : Usage Switch
 *       - UM   : Usage Modifier
 *
 * [1]: http://www.usb.org/developers/devclass_docs/Hut1_12v2.pdf
 * [2]: http://www.usb.org/developers/hidpage
 */


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__LED__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__LED__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


//      Name                         ID       Usage Type  Section of HID Tables
//      ---------------------------- ----     ----------  ---------------------

//      (Undefined)                  0x00  // -           -

#define LED__NumLock                 0x01  // OOC         11.1
#define LED__CapsLock                0x02  // OOC         11.1
#define LED__ScrollLock              0x03  // OOC         11.1
#define LED__Compose                 0x04  // OOC         11.1
#define LED__Kana                    0x05  // OOC         11.1
#define LED__Power                   0x06  // OOC         11.6
#define LED__Shift                   0x07  // OOC         11.1
#define LED__DoNotDisturb            0x08  // OOC         11.2
#define LED__Mute                    0x09  // OOC         11.3
#define LED__ToneEnable              0x0A  // OOC         11.3
#define LED__HighCutFilter           0x0B  // OOC         11.3
#define LED__LowCutFilter            0x0C  // OOC         11.3
#define LED__EqualizerEnable         0x0D  // OOC         11.3
#define LED__SoundFieldOn            0x0E  // OOC         11.3
#define LED__SurroundOn              0x0F  // OOC         11.3
#define LED__Repeat                  0x10  // OOC         11.3
#define LED__Stereo                  0x11  // OOC         11.3
#define LED__SamplingRateDetect      0x12  // OOC         11.3
#define LED__Spinning                0x13  // OOC         11.4
#define LED__CAV                     0x14  // OOC         11.3
#define LED__CLV                     0x15  // OOC         11.3
#define LED__RecordingFormatDetect   0x16  // OOC         11.4
#define LED__OffHook                 0x17  // OOC         11.2
#define LED__Ring                    0x18  // OOC         11.2
#define LED__MessageWaiting          0x19  // OOC         11.2
#define LED__DataMode                0x1A  // OOC         11.2
#define LED__BatteryOperation        0x1B  // OOC         11.6
#define LED__BatteryOK               0x1C  // OOC         11.6
#define LED__BatteryLow              0x1D  // OOC         11.6
#define LED__Speaker                 0x1E  // OOC         11.2
#define LED__HeadSet                 0x1F  // OOC         11.2
#define LED__Hold                    0x20  // OOC         11.2
#define LED__Microphone              0x21  // OOC         11.2
#define LED__Coverage                0x22  // OOC         11.2
#define LED__NightMode               0x23  // OOC         11.2
#define LED__SendCalls               0x24  // OOC         11.2
#define LED__CallPickup              0x25  // OOC         11.2
#define LED__Conference              0x26  // OOC         11.2
#define LED__Standby                 0x27  // OOC         11.6
#define LED__CameraOn                0x28  // OOC         11.3
#define LED__CameraOff               0x29  // OOC         11.3
#define LED__OnLine                  0x2A  // OOC         11.6
#define LED__OffLine                 0x2B  // OOC         11.6
#define LED__Busy                    0x2C  // OOC         11.6
#define LED__Ready                   0x2D  // OOC         11.6
#define LED__PaperOut                0x2E  // OOC         11.5
#define LED__PaperJam                0x2F  // OOC         11.5
#define LED__Remote                  0x30  // OOC         11.6
#define LED__Forward                 0x31  // OOC         11.4
#define LED__Reverse                 0x32  // OOC         11.4
#define LED__Stop                    0x33  // OOC         11.4
#define LED__Rewind                  0x34  // OOC         11.4
#define LED__FastForward             0x35  // OOC         11.4
#define LED__Play                    0x36  // OOC         11.4
#define LED__Pause                   0x37  // OOC         11.4
#define LED__Record                  0x38  // OOC         11.4
#define LED__Error                   0x39  // OOC         11.6
#define LED__UsageSelectedIndicator  0x3A  // US          11.6
#define LED__UsageInUseIndicator     0x3B  // US          11.6
#define LED__UsageMultiModeIndicator 0x3C  // UM          11.6
#define LED__IndicatorOn             0x3D  // Sel         11.6
#define LED__IndicatorFlash          0x3E  // Sel         11.6
#define LED__IndicatorSlowBlink      0x3F  // Sel         11.6
#define LED__IndicatorFastBlink      0x40  // Sel         11.6
#define LED__IndicatorOff            0x41  // Sel         11.6
#define LED__FlashOnTime             0x42  // DV          11.6
#define LED__SlowBlinkOnTime         0x43  // DV          11.6
#define LED__SlowBlinkOffTime        0x44  // DV          11.6
#define LED__FastBlinkOnTime         0x45  // DV          11.6
#define LED__FastBlinkOffTime        0x46  // DV          11.6
#define LED__UsageIndicatorColor     0x47  // UM          11.6
#define LED__IndicatorRed            0x48  // Sel         11.6
#define LED__IndicatorGreen          0x49  // Sel         11.6
#define LED__IndicatorAmber          0x4A  // Sel         11.6
#define LED__GenericIndicator        0x4B  // OOC         11.6
#define LED__SystemSuspend           0x4C  // OOC         11.6
#define LED__ExternalPowerConnected  0x4D  // OOC         11.6

//      (Reserved)           0x4E..0xFFFF  // -           -


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__SRC__LIB__USB__USAGE_PAGE__LED__H

