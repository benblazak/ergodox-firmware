/* ----------------------------------------------------------------------------
 * USB LED Codes (usage page 0x08)
 *
 * Taken from [the HID Usage Tables pdf][1], Section 11,
 * which can be found on [the HID Page][2] at <http://www.usb.org>
 *
 * - applicable Usage Types (from Section 3.4)
 *   - OOC : On/Off Control
 *   - Sel : Selector
 *   - DV  : Dynamic Value
 *   - US  : Usage Switch
 *   - UM  : Usage Modifier
 *
 * [1]: http://www.usb.org/developers/devclass_docs/Hut1_12v2.pdf
 * [2]: http://www.usb.org/developers/hidpage
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef USB_USAGE_PAGE_LED_h
	#define USB_USAGE_PAGE_LED_h
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


//      Name                        ID       Usage Type  Section of HID Tables
//      --------------------------- ----     ----------  ----------------------

//      (Undefined)                 0x00  // -           -

#define LED_NumLock                 0x01  // OOC         11.1
#define LED_CapsLock                0x02  // OOC         11.1
#define LED_ScrollLock              0x03  // OOC         11.1
#define LED_Compose                 0x04  // OOC         11.1
#define LED_Kana                    0x05  // OOC         11.1
#define LED_Power                   0x06  // OOC         11.6
#define LED_Shift                   0x07  // OOC         11.1
#define LED_DoNotDisturb            0x08  // OOC         11.2
#define LED_Mute                    0x09  // OOC         11.3
#define LED_ToneEnable              0x0A  // OOC         11.3
#define LED_HighCutFilter           0x0B  // OOC         11.3
#define LED_LowCutFilter            0x0C  // OOC         11.3
#define LED_EqualizerEnable         0x0D  // OOC         11.3
#define LED_SoundFieldOn            0x0E  // OOC         11.3
#define LED_SurroundOn              0x0F  // OOC         11.3
#define LED_Repeat                  0x10  // OOC         11.3
#define LED_Stereo                  0x11  // OOC         11.3
#define LED_SamplingRateDetect      0x12  // OOC         11.3
#define LED_Spinning                0x13  // OOC         11.4
#define LED_CAV                     0x14  // OOC         11.3
#define LED_CLV                     0x15  // OOC         11.3
#define LED_RecordingFormatDetect   0x16  // OOC         11.4
#define LED_OffHook                 0x17  // OOC         11.2
#define LED_Ring                    0x18  // OOC         11.2
#define LED_MessageWaiting          0x19  // OOC         11.2
#define LED_DataMode                0x1A  // OOC         11.2
#define LED_BatteryOperation        0x1B  // OOC         11.6
#define LED_BatteryOK               0x1C  // OOC         11.6
#define LED_BatteryLow              0x1D  // OOC         11.6
#define LED_Speaker                 0x1E  // OOC         11.2
#define LED_HeadSet                 0x1F  // OOC         11.2
#define LED_Hold                    0x20  // OOC         11.2
#define LED_Microphone              0x21  // OOC         11.2
#define LED_Coverage                0x22  // OOC         11.2
#define LED_NightMode               0x23  // OOC         11.2
#define LED_SendCalls               0x24  // OOC         11.2
#define LED_CallPickup              0x25  // OOC         11.2
#define LED_Conference              0x26  // OOC         11.2
#define LED_Standby                 0x27  // OOC         11.6
#define LED_CameraOn                0x28  // OOC         11.3
#define LED_CameraOff               0x29  // OOC         11.3
#define LED_OnLine                  0x2A  // OOC         11.6
#define LED_OffLine                 0x2B  // OOC         11.6
#define LED_Busy                    0x2C  // OOC         11.6
#define LED_Ready                   0x2D  // OOC         11.6
#define LED_PaperOut                0x2E  // OOC         11.5
#define LED_PaperJam                0x2F  // OOC         11.5
#define LED_Remote                  0x30  // OOC         11.6
#define LED_Forward                 0x31  // OOC         11.4
#define LED_Reverse                 0x32  // OOC         11.4
#define LED_Stop                    0x33  // OOC         11.4
#define LED_Rewind                  0x34  // OOC         11.4
#define LED_FastForward             0x35  // OOC         11.4
#define LED_Play                    0x36  // OOC         11.4
#define LED_Pause                   0x37  // OOC         11.4
#define LED_Record                  0x38  // OOC         11.4
#define LED_Error                   0x39  // OOC         11.6
#define LED_UsageSelectedIndicator  0x3A  // US          11.6
#define LED_UsageInUseIndicator     0x3B  // US          11.6
#define LED_UsageMultiModeIndicator 0x3C  // UM          11.6
#define LED_IndicatorOn             0x3D  // Sel         11.6
#define LED_IndicatorFlash          0x3E  // Sel         11.6
#define LED_IndicatorSlowBlink      0x3F  // Sel         11.6
#define LED_IndicatorFastBlink      0x40  // Sel         11.6
#define LED_IndicatorOff            0x41  // Sel         11.6
#define LED_FlashOnTime             0x42  // DV          11.6
#define LED_SlowBlinkOnTime         0x43  // DV          11.6
#define LED_SlowBlinkOffTime        0x44  // DV          11.6
#define LED_FastBlinkOnTime         0x45  // DV          11.6
#define LED_FastBlinkOffTime        0x46  // DV          11.6
#define LED_UsageIndicatorColor     0x47  // UM          11.6
#define LED_IndicatorRed            0x48  // Sel         11.6
#define LED_IndicatorGreen          0x49  // Sel         11.6
#define LED_IndicatorAmber          0x4A  // Sel         11.6
#define LED_GenericIndicator        0x4B  // OOC         11.6
#define LED_SystemSuspend           0x4C  // OOC         11.6
#define LED_ExternalPowerConnected  0x4D  // OOC         11.6

//      (Reserved)          0x4E..0xFFFF  // -           -


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif

