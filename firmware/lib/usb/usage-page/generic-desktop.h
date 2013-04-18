/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * USB Generic Desktop Codes (usage page 0x01)
 *
 * Prefix: `GENERIC_DESKTOP__`
 *
 * Taken from [the HID Usage Tables pdf][1], Section 4, which can be found on
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


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__GENERIC_DESKTOP__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__GENERIC_DESKTOP__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


//      Name                                               ID       Usage Type  Section of HID Tables
//      -------------------------------------------------- ----     ----------  ---------------------

//      (Undefined)                                        0x00  // -           -

#define GENERIC_DESKTOP__Pointer                           0x01  // CP          4.1
#define GENERIC_DESKTOP__Mouse                             0x02  // CA          4.1

//      (Reserved)                                         0x03  // -           -

#define GENERIC_DESKTOP__Joystick                          0x04  // CA          4.1
#define GENERIC_DESKTOP__GamePad                           0x05  // CA          4.1
#define GENERIC_DESKTOP__Keyboard                          0x06  // CA          4.1
#define GENERIC_DESKTOP__Keypad                            0x07  // CA          4.1
#define GENERIC_DESKTOP__MultiAxisController               0x08  // CA          4.1
#define GENERIC_DESKTOP__TabletPCSystemControls            0x09  // CA          4.1

//      (Reserved)                                   0x0A..0x2F  // -           -

#define GENERIC_DESKTOP__X                                 0x30  // DV          4.2
#define GENERIC_DESKTOP__Y                                 0x31  // DV          4.2
#define GENERIC_DESKTOP__Z                                 0x32  // DV          4.2
#define GENERIC_DESKTOP__Rx                                0x33  // DV          4.2
#define GENERIC_DESKTOP__Ry                                0x34  // DV          4.2
#define GENERIC_DESKTOP__Rz                                0x35  // DV          4.2
#define GENERIC_DESKTOP__Slider                            0x36  // DV          4.3
#define GENERIC_DESKTOP__Dial                              0x37  // DV          4.3
#define GENERIC_DESKTOP__Wheel                             0x38  // DV          4.3
#define GENERIC_DESKTOP__HatSwitch                         0x39  // DV          4.3
#define GENERIC_DESKTOP__CountedBuffer                     0x3A  // CL          4.6
#define GENERIC_DESKTOP__ByteCount                         0x3B  // DV          4.6
#define GENERIC_DESKTOP__MotionWakeup                      0x3C  // OSC         4.3
#define GENERIC_DESKTOP__Start                             0x3D  // OOC         4.3
#define GENERIC_DESKTOP__Select                            0x3E  // OOC         4.3

//      (Reserved)                                         0x3F  // -           -

#define GENERIC_DESKTOP__Vx                                0x40  // DV          4.3.1
#define GENERIC_DESKTOP__Vy                                0x41  // DV          4.3.1
#define GENERIC_DESKTOP__Vz                                0x42  // DV          4.3.1
#define GENERIC_DESKTOP__Vbrx                              0x43  // DV          4.3.1
#define GENERIC_DESKTOP__Vbry                              0x44  // DV          4.3.1
#define GENERIC_DESKTOP__Vbrz                              0x45  // DV          4.3.1
#define GENERIC_DESKTOP__Vno                               0x46  // DV          4.3.1
#define GENERIC_DESKTOP__FeatureNotification               0x￼47  // DV,DF       4.8
#define GENERIC_DESKTOP__ResolutionMultiplier              0x48  // DV          -

//      (Reserved)                                   0x49..0x7F  // -           -

#define GENERIC_DESKTOP__SystemControl                     0x80  // CA          4.5
#define GENERIC_DESKTOP__SystemPowerDown                   0x81  // OSC         4.5
#define GENERIC_DESKTOP__SystemSleep                       0x82  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemWakeUp                      0x83  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemContextMenu                 0x84  // OSC         4.5
#define GENERIC_DESKTOP__SystemMainMenu                    0x85  // OSC         4.5
#define GENERIC_DESKTOP__SystemAppMenu                     0x86  // OSC         4.5
#define GENERIC_DESKTOP__SystemMenuHelp                    0x87  // OSC         4.5
#define GENERIC_DESKTOP__SystemMenuExit                    0x88  // OSC         4.5
#define GENERIC_DESKTOP__SystemMenuSelect                  0x89  // OSC         4.5
#define GENERIC_DESKTOP__SystemMenuRight                   0x8A  // RTC         4.5
#define GENERIC_DESKTOP__SystemMenuLeft                    0x8B  // RTC         4.5
#define GENERIC_DESKTOP__SystemMenuUp                      0x8C  // RTC         4.5
#define GENERIC_DESKTOP__SystemMenuDown                    0x8D  // RTC         4.5
#define GENERIC_DESKTOP__SystemColdRestart                 0x8E  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemWarmRestart                 0x8F  // OSC         4.5.1
#define GENERIC_DESKTOP__DPadUp                            0x90  // OOC         4.7
#define GENERIC_DESKTOP__DPadDown                          0x91  // OOC         4.7
#define GENERIC_DESKTOP__DPadRight                         0x92  // OOC         4.7
#define GENERIC_DESKTOP__DPadLeft                          0x93  // OOC         4.7

//      (Reserved)                                   0x94..0x9F  // -           -

#define GENERIC_DESKTOP__SystemDock                        0xA0  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemUndock                      0xA1  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemSetup                       0xA2  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemBreak                       0xA3  // OSC         4.9
#define GENERIC_DESKTOP__SystemDebuggerBreak               0xA4  // OSC         4.9
#define GENERIC_DESKTOP__ApplicationBreak                  0xA5  // OSC         4.9
#define GENERIC_DESKTOP__ApplicationDebuggerBreak          0xA6  // OSC         4.9
#define GENERIC_DESKTOP__SystemSpeakerMute                 0xA7  // OSC         4.5.1
#define GENERIC_DESKTOP__SystemHibernate                   0xA8  // OSC         4.5.1

//      (Reserved)                                   0xA9..0xAF  // -           -

#define GENERIC_DESKTOP__SystemDisplayInvert               0xB0  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplayInternal             0xB1  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplayExternal             0xB2  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplayBoth                 0xB3  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplayDual                 0xB4  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplayToggleIntExt         0x￼B5  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplaySwapPrimarySecondary 0xB6  // OSC         4.10
#define GENERIC_DESKTOP__SystemDisplayLCDAutoscale         0xB7  // OSC         4.10

//      (Reserved)                                 0xB8..0xFFFF  // -           -


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__SRC__LIB__USB__USAGE_PAGE__GENERIC_DESKTOP__H

