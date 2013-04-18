/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */

/**                                                                 description
 * USB HID Consumer Codes (usage page 0x0C)
 *
 * Prefix: `CONSUMER__`
 *
 * Taken from [the HID Usage Tables pdf][1], Section 15, which can be found on
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


#ifndef ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__CONSUMER__H
#define ERGODOX_FIRMWARE__FIRMWARE__LIB__USB__USAGE_PAGE__CONSUMER__H
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------


//      Name                                          ID         Usage Type  Section of HID Tables
//      --------------------------------------------- ------     ----------  ---------------------

//      (Unassigned)                                  0x0000  // -           -

#define CONSUMER__ConsumerControl                     0x0001  // CA          15.1
#define CONSUMER__NumericKeyPad                       0x0002  // NAry        15.2
#define CONSUMER__ProgrammableButtons                 0x0003  // NAry        15.14
#define CONSUMER__Microphone                          0x0004  // CA          15.1
#define CONSUMER__Headphone                           0x0005  // CA          15.1
#define CONSUMER__GraphicEqualizer                    0x0006  // CA          15.1

//      (Reserved)                            0x0007..0x001F  // -           -

#define CONSUMER__Plus10                              0x0020  // OSC         15.2
#define CONSUMER__Plus100                             0x0021  // OSC         15.2
#define CONSUMER__AM_PM                               0x0022  // OSC         15.2

//      (Reserved)                            0x0023..0x002F  // -           -

#define CONSUMER__Power                               0x0030  // OOC         15.3
#define CONSUMER__Reset                               0x0031  // OSC         15.3
#define CONSUMER__Sleep                               0x0032  // OSC         15.3
#define CONSUMER__SleepAfter                          0x0033  // OSC         15.3
#define CONSUMER__SleepMode                           0x0034  // RTC         15.3
#define CONSUMER__Illumination                        0x0035  // OOC         15.3
#define CONSUMER__FunctionButtons                     0x0036  // NAry        15.3

//      (Reserved)                            0x0037..0x003F  // -           -

#define CONSUMER__Menu                                0x0040  // OOC         15.4
#define CONSUMER__MenuPick                            0x0041  // OSC         15.4
#define CONSUMER__MenuUp                              0x0042  // OSC         15.4
#define CONSUMER__MenuDown                            0x0043  // OSC         15.4
#define CONSUMER__MenuLeft                            0x0044  // OSC         15.4
#define CONSUMER__MenuRight                           0x0045  // OSC         15.4
#define CONSUMER__MenuEscape                          0x0046  // OSC         15.4
#define CONSUMER__MenuValueIncrease                   0x0047  // OSC         15.4
#define CONSUMER__MenuValueDecrease                   0x0048  // OSC         15.4

//      (Reserved)                            0x0049..0x005F  // -           -

#define CONSUMER__DataOnScreen                        0x0060  // OOC         15.5
#define CONSUMER__ClosedCaption                       0x0061  // OOC         15.5
#define CONSUMER__ClosedCaptionSelect                 0x0062  // OSC         15.5
#define CONSUMER__VCR_TV                              0x0063  // OOC         15.5
#define CONSUMER__BroadcastMode                       0x0064  // OSC         15.5
#define CONSUMER__Snapshot                            0x0065  // OSC         15.5
#define CONSUMER__Still                               0x0066  // OSC         15.5

//      (Reserved)                            0x0067..0x007F  // -           -

#define CONSUMER__Selection                           0x0080  // NAry        15.6
#define CONSUMER__AssignSelection                     0x0081  // OSC         15.6
#define CONSUMER__ModeStep                            0x0082  // OSC         15.6
#define CONSUMER__RecallLast                          0x0083  // OSC         15.6
#define CONSUMER__EnterChannel                        0x0084  // OSC         15.6
#define CONSUMER__OrderMovie                          0x0085  // OSC         15.6
#define CONSUMER__Channel                             0x0086  // LC          15.6
#define CONSUMER__MediaSelection                      0x0087  // NAry        15.6
#define CONSUMER__MediaSelectComputer                 0x0088  // Sel         15.6
#define CONSUMER__MediaSelectTV                       0x0089  // Sel         15.6
#define CONSUMER__MediaSelectWWW                      0x008A  // Sel         15.6
#define CONSUMER__MediaSelectDVD                      0x008B  // Sel         15.6
#define CONSUMER__MediaSelectTelephone                0x008C  // Sel         15.6
#define CONSUMER__MediaSelectProgramGuide             0x008D  // Sel         15.6
#define CONSUMER__MediaSelectVideoPhone               0x008E  // Sel         15.6
#define CONSUMER__MediaSelectGames                    0x008F  // Sel         15.6
#define CONSUMER__MediaSelectMessages                 0x0090  // Sel         15.6
#define CONSUMER__MediaSelectCD                       0x0091  // Sel         15.6
#define CONSUMER__MediaSelectVCR                      0x0092  // Sel         15.6
#define CONSUMER__MediaSelectTuner                    0x0093  // Sel         15.6
#define CONSUMER__Quit                                0x0094  // OSC         15.6
#define CONSUMER__Help                                0x0095  // OOC         15.6
#define CONSUMER__MediaSelectTape                     0x0096  // Sel         15.6
#define CONSUMER__MediaSelectCable                    0x0097  // Sel         15.6
#define CONSUMER__MediaSelectSatellite                0x0098  // Sel         15.6
#define CONSUMER__MediaSelectSecurity                 0x0099  // Sel         15.6
#define CONSUMER__MediaSelectHome                     0x009A  // Sel         15.6
#define CONSUMER__MediaSelectCall                     0x009B  // Sel         15.6
#define CONSUMER__ChannelIncrement                    0x009C  // OSC         15.6
#define CONSUMER__ChannelDecrement                    0x009D  // OSC         15.6
#define CONSUMER__MediaSelectSAP                      0x009E  // Sel         15.6

//      (Reserved)                                    0x009F  // -           -

#define CONSUMER__VCRPlus                             0x00A0  // OSC         15.6
#define CONSUMER__Once                                0x00A1  // OSC         15.6
#define CONSUMER__Daily                               0x00A2  // OSC         15.6
#define CONSUMER__Weekly                              0x00A3  // OSC         15.6
#define CONSUMER__Monthly                             0x00A4  // OSC         15.6

//      (Reserved)                            0x00A5..0x00AF  // -           -

#define CONSUMER__Play                                0x00B0  // OOC         15.7
#define CONSUMER__Pause                               0x00B1  // OOC         15.7
#define CONSUMER__Record                              0x00B2  // OOC         15.7
#define CONSUMER__FastForward                         0x00B3  // OOC         15.7
#define CONSUMER__Rewind                              0x00B4  // OOC         15.7
#define CONSUMER__ScanNextTrack                       0x00B5  // OSC         15.7
#define CONSUMER__ScanPreviousTrack                   0x00B6  // OSC         15.7
#define CONSUMER__Stop                                0x00B7  // OSC         15.7
#define CONSUMER__Eject                               0x00B8  // OSC         15.7
#define CONSUMER__RandomPlay                          0x00B9  // OOC         15.7
#define CONSUMER__SelectDisc                          0x00BA  // NAry        15.7
#define CONSUMER__EnterDisc                           0x00BB  // MC          15.7
#define CONSUMER__Repeat                              0x00BC  // OSC         15.7
#define CONSUMER__Tracking                            0x00BD  // LC          15.7
#define CONSUMER__TrackNormal                         0x00BE  // OSC         15.7
#define CONSUMER__SlowTracking                        0x00BF  // LC          15.7
#define CONSUMER__FrameForward                        0x00C0  // RTC         15.7
#define CONSUMER__FrameBack                           0x00C1  // RTC         15.7
#define CONSUMER__Mark                                0x00C2  // OSC         15.8
#define CONSUMER__ClearMark                           0x00C3  // OSC         15.8
#define CONSUMER__RepeatFromMark                      0x00C4  // OOC         15.8
#define CONSUMER__ReturnToMark                        0x00C5  // OSC         15.8
#define CONSUMER__SearchMarkForward                   0x00C6  // OSC         15.8
#define CONSUMER__SearchMarkBackwards                 0x00C7  // OSC         15.8
#define CONSUMER__CounterReset                        0x00C8  // OSC         15.8
#define CONSUMER__ShowCounter                         0x00C9  // OSC         15.8
#define CONSUMER__TrackingIncrement                   0x00CA  // RTC         15.7
#define CONSUMER__TrackingDecrement                   0x00CB  // RTC         15.7
#define CONSUMER__Stop_Eject                          0x00CC  // OSC         15.7
#define CONSUMER__Play_Pause                          0x00CD  // OSC         15.7
#define CONSUMER__Play_Skip                           0x00CE  // OSC         15.7

//      (Reserved)                            0x00CF..0x00DF  // -           -

#define CONSUMER__Volume                              0x00E0  // LC          15.9.1
#define CONSUMER__Balance                             0x00E1  // LC          15.9.2
#define CONSUMER__Mute                                0x00E2  // OOC         15.9.1
#define CONSUMER__Bass                                0x00E3  // LC          15.9.3
#define CONSUMER__Treble                              0x00E4  // LC          15.9.4
#define CONSUMER__BassBoost                           0x00E5  // OOC         15.9.3
#define CONSUMER__SurroundMode                        0x00E6  // OSC         15.9.5
#define CONSUMER__Loudness                            0x00E7  // OOC         15.9.5
#define CONSUMER__MPX                                 0x00E8  // OOC         15.9.5
#define CONSUMER__VolumeIncrement                     0x00E9  // RTC         15.9.1
#define CONSUMER__VolumeDecrement                     0x00EA  // RTC         15.9.1

//      (Reserved)                            0x00EB..0x00EF  // -           -

#define CONSUMER__SpeedSelect                         0x00F0  // OSC         15.10
#define CONSUMER__PlaybackSpeed                       0x00F1  // NAry        15.10
#define CONSUMER__StandardPlay                        0x00F2  // Sel         15.10
#define CONSUMER__LongPlay                            0x00F3  // Sel         15.10
#define CONSUMER__ExtendedPlay                        0x00F4  // Sel         15.10
#define CONSUMER__Slow                                0x00F5  // OSC         15.10

//      (Reserved)                            0x00F6..0x00FF  // -           -

#define CONSUMER__FanEnable                           0x0100  // OOC         15.11
#define CONSUMER__FanSpeed                            0x0101  // LC          15.11
#define CONSUMER__LightEnable                         0x0102  // OOC         15.11
#define CONSUMER__LightIlluminationLevel              0x0103  // LC          15.11
#define CONSUMER__ClimateControlEnable                0x0104  // OOC         15.11
#define CONSUMER__RoomTemperature                     0x0105  // LC          15.11
#define CONSUMER__SecurityEnable                      0x0106  // OOC         15.11
#define CONSUMER__FireAlarm                           0x0107  // OSC         15.11
#define CONSUMER__PoliceAlarm                         0x0108  // OSC         15.11
#define CONSUMER__Proximity                           0x0109  // LC          15.11
#define CONSUMER__Motion                              0x010A  // OSC         15.11
#define CONSUMER__DuressAlarm                         0x010B  // OSC         15.11
#define CONSUMER__HoldupAlarm                         0x010C  // OSC         15.11
#define CONSUMER__MedicalAlarm                        0x010D  // OSC         15.11

//      (Reserved)                            0x010E..0x014F  // -           -

#define CONSUMER__BalanceRight                        0x0150  // RTC         15.9.2
#define CONSUMER__BalanceLeft                         0x0151  // RTC         15.9.2
#define CONSUMER__BassIncrement                       0x0152  // RTC         15.9.3
#define CONSUMER__BassDecrement                       0x0153  // RTC         15.9.3
#define CONSUMER__TrebleIncrement                     0x0154  // RTC         15.9.4
#define CONSUMER__TrebleDecrement                     0x0155  // RTC         15.9.4

//      (Reserved)                            0x0156..0x015F  // -           -

#define CONSUMER__SpeakerSystem                       0x0160  // CL          15.12.1
#define CONSUMER__ChannelLeft                         0x0161  // CL          15.12.1
#define CONSUMER__ChannelRight                        0x0162  // CL          15.12.1
#define CONSUMER__ChannelCenter                       0x0163  // CL          15.12.1
#define CONSUMER__ChannelFront                        0x0164  // CL          15.12.1
#define CONSUMER__ChannelCenterFront                  0x0165  // CL          15.12.1
#define CONSUMER__ChannelSide                         0x0166  // CL          15.12.1
#define CONSUMER__ChannelSurround                     0x0167  // CL          15.12.1
#define CONSUMER__ChannelLowFrequencyEnhancement      0x0168  // CL          15.12.1
#define CONSUMER__ChannelTop                          0x0169  // CL          15.12.1
#define CONSUMER__ChannelUnknown                      0x016A  // CL          15.12.1

//      (Reserved)                            0x016B..0x016F  // -           -

#define CONSUMER__SubChannel                          0x0170  // LC          15.13
#define CONSUMER__SubChannelIncrement                 0x0171  // OSC         15.13
#define CONSUMER__SubChannelDecrement                 0x0172  // OSC         15.13
#define CONSUMER__AlternateAudioIncrement             0x0173  // OSC         15.13
#define CONSUMER__AlternateAudioDecrement             0x0174  // OSC         15.13

//      (Reserved)                            0x0175..0x017F  // -           -

#define CONSUMER__ApplicationLaunchButtons            0x0180  // NAry        15.15
#define CONSUMER__AL_LaunchButtonConfigurationTool    0x0181  // Sel         15.15
#define CONSUMER__AL_ProgrammableButtonConfiguration  0x0182  // Sel         15.15
#define CONSUMER__AL_ConsumerControlConfiguration     0x0183  // Sel         15.15
#define CONSUMER__AL_WordProcessor                    0x0184  // Sel         15.15
#define CONSUMER__AL_TextEditor                       0x0185  // Sel         15.15
#define CONSUMER__AL_Spreadsheet                      0x0186  // Sel         15.15
#define CONSUMER__AL_GraphicsEditor                   0x0187  // Sel         15.15
#define CONSUMER__AL_PresentationApp                  0x0188  // Sel         15.15
#define CONSUMER__AL_DatabaseApp                      0x0189  // Sel         15.15
#define CONSUMER__AL_EmailReader                      0x018A  // Sel         15.15
#define CONSUMER__AL_Newsreader                       0x018B  // Sel         15.15
#define CONSUMER__AL_Voicemail                        0x018C  // Sel         15.15
#define CONSUMER__AL_Contacts_AddressBook             0x018D  // Sel         15.15
#define CONSUMER__AL_Calendar_Schedule                0x018E  // Sel         15.15
#define CONSUMER__AL_Task_ProjectManager              0x018F  // Sel         15.15
#define CONSUMER__AL_Log_Journal_Timecard             0x0190  // Sel         15.15
#define CONSUMER__AL_Checkbook_Finance                0x0191  // Sel         15.15
#define CONSUMER__AL_Calculator                       0x0192  // Sel         15.15
#define CONSUMER__AL_A_VCapture_Playback              0x0193  // Sel         15.15
#define CONSUMER__AL_LocalMachineBrowser              0x0194  // Sel         15.15
#define CONSUMER__AL_LAN_WANBrowser                   0x0195  // Sel         15.15
#define CONSUMER__AL_InternetBrowser                  0x0196  // Sel         15.15
#define CONSUMER__AL_RemoteNetworking_ISPConnect      0x0197  // Sel         15.15
#define CONSUMER__AL_NetworkConference                0x0198  // Sel         15.15
#define CONSUMER__AL_NetworkChat                      0x0199  // Sel         15.15
#define CONSUMER__AL_Telephony_Dialer                 0x019A  // Sel         15.15
#define CONSUMER__AL_Logon                            0x019B  // Sel         15.15
#define CONSUMER__AL_Logoff                           0x019C  // Sel         15.15
#define CONSUMER__AL_Logon_Logoff                     0x019D  // Sel         15.15
#define CONSUMER__AL_TerminalLock_Screensaver         0x019E  // Sel         15.15
#define CONSUMER__AL_ControlPanel                     0x019F  // Sel         15.15
#define CONSUMER__AL_CommandLineProcessor_Run         0x01A0  // Sel         15.15
#define CONSUMER__AL_Process_TaskManager              0x01A1  // Sel         15.15
#define CONSUMER__AL_SelectTask_Application           0x01A2  // Sel         15.15
#define CONSUMER__AL_NextTask_Application             0x01A3  // Sel         15.15
#define CONSUMER__AL_PreviousTask_Application         0x01A4  // Sel         15.15
#define CONSUMER__AL_PreemptiveHaltTask_Application   0x01A5  // Sel         15.15
#define CONSUMER__AL_IntegratedHelpCenter             0x01A6  // Sel         15.15
#define CONSUMER__AL_Documents                        0x01A7  // Sel         15.15
#define CONSUMER__AL_Thesaurus                        0x01A8  // Sel         15.15
#define CONSUMER__AL_Dictionary                       0x01A9  // Sel         15.15
#define CONSUMER__AL_Desktop                          0x01AA  // Sel         15.15
#define CONSUMER__AL_SpellCheck                       0x01AB  // Sel         15.15
#define CONSUMER__AL_GrammarCheck                     0x01AC  // Sel         15.15
#define CONSUMER__AL_WirelessStatus                   0x01AD  // Sel         15.15
#define CONSUMER__AL_KeyboardLayout                   0x01AE  // Sel         15.15
#define CONSUMER__AL_VirusProtection                  0x01AF  // Sel         15.15
#define CONSUMER__AL_Encryption                       0x01B0  // Sel         15.15
#define CONSUMER__AL_ScreenSaver                      0x01B1  // Sel         15.15
#define CONSUMER__AL_Alarms                           0x01B2  // Sel         15.15
#define CONSUMER__AL_Clock                            0x01B3  // Sel         15.15
#define CONSUMER__AL_FileBrowser                      0x01B4  // Sel         15.15
#define CONSUMER__AL_PowerStatus                      0x01B5  // Sel         15.15
#define CONSUMER__AL_ImageBrowser                     0x01B6  // Sel         15.15
#define CONSUMER__AL_AudioBrowser                     0x01B7  // Sel         15.15
#define CONSUMER__AL_MovieBrowser                     0x01B8  // Sel         15.15
#define CONSUMER__AL_DigitalRightsManager             0x01B9  // Sel         15.15
#define CONSUMER__AL_DigitalWallet                    0x01BA  // Sel         15.15

//      (Reserved)                                    0x01BB  // -           -

#define CONSUMER__AL_InstantMessaging                 0x01BC  // Sel         15.15
#define CONSUMER__AL_OEMFeatures_Tips_TutorialBrowser 0x01BD  // Sel         15.15
#define CONSUMER__AL_OEMHelp                          0x01BE  // Sel         15.15
#define CONSUMER__AL_OnlineCommunity                  0x01BF  // Sel         15.15
#define CONSUMER__AL_EntertainmentContentBrowser      0x01C0  // Sel         15.15
#define CONSUMER__AL_OnlineShoppingBrowser            0x01C1  // Sel         15.15
#define CONSUMER__AL_SmartCardInformation_Help        0x01C2  // Sel         15.15
#define CONSUMER__AL_MarketMonitor_FinanceBrowser     0x01C3  // Sel         15.15
#define CONSUMER__AL_CustomizedCorporateNewsBrowser   0x01C4  // Sel         15.15
#define CONSUMER__AL_OnlineActivityBrowser            0x01C5  // Sel         15.15
#define CONSUMER__AL_Research_SearchBrowser           0x01C6  // Sel         15.15
#define CONSUMER__AL_AudioPlayer                      0x01C7  // Sel         15.15

//      (Reserved)                            0x01C8..0x01FF  // -           -

#define CONSUMER__GenericGUIApplicationControls       0x0200  // NAry        15.16
#define CONSUMER__AC_New                              0x0201  // Sel         15.16
#define CONSUMER__AC_Open                             0x0202  // Sel         15.16
#define CONSUMER__AC_Close                            0x0203  // Sel         15.16
#define CONSUMER__AC_Exit                             0x0204  // Sel         15.16
#define CONSUMER__AC_Maximize                         0x0205  // Sel         15.16
#define CONSUMER__AC_Minimize                         0x0206  // Sel         15.16
#define CONSUMER__AC_Save                             0x0207  // Sel         15.16
#define CONSUMER__AC_Print                            0x0208  // Sel         15.16
#define CONSUMER__AC_Properties                       0x0209  // Sel         15.16

#define CONSUMER__AC_Undo                             0x021A  // Sel         15.16
#define CONSUMER__AC_Copy                             0x021B  // Sel         15.16
#define CONSUMER__AC_Cut                              0x021C  // Sel         15.16
#define CONSUMER__AC_Paste                            0x021D  // Sel         15.16
#define CONSUMER__AC_SelectAll                        0x021E  // Sel         15.16
#define CONSUMER__AC_Find                             0x021F  // Sel         15.16
#define CONSUMER__AC_FindandReplace                   0x0220  // Sel         15.16
#define CONSUMER__AC_Search                           0x0221  // Sel         15.16
#define CONSUMER__AC_GoTo                             0x0222  // Sel         15.16
#define CONSUMER__AC_Home                             0x0223  // Sel         15.16
#define CONSUMER__AC_Back                             0x0224  // Sel         15.16
#define CONSUMER__AC_Forward                          0x0225  // Sel         15.16
#define CONSUMER__AC_Stop                             0x0226  // Sel         15.16
#define CONSUMER__AC_Refresh                          0x0227  // Sel         15.16
#define CONSUMER__AC_PreviousLink                     0x0228  // Sel         15.16
#define CONSUMER__AC_NextLink                         0x0229  // Sel         15.16
#define CONSUMER__AC_Bookmarks                        0x022A  // Sel         15.16
#define CONSUMER__AC_History                          0x022B  // Sel         15.16
#define CONSUMER__AC_Subscriptions                    0x022C  // Sel         15.16
#define CONSUMER__AC_ZoomIn                           0x022D  // Sel         15.16
#define CONSUMER__AC_ZoomOut                          0x022E  // Sel         15.16
#define CONSUMER__AC_Zoom                             0x022F  // Sel         15.16
#define CONSUMER__AC_FullScreenView                   0x0230  // Sel         15.16
#define CONSUMER__AC_NormalView                       0x0231  // Sel         15.16
#define CONSUMER__AC_ViewToggle                       0x0232  // Sel         15.16
#define CONSUMER__AC_ScrollUp                         0x0233  // Sel         15.16
#define CONSUMER__AC_ScrollDown                       0x0234  // Sel         15.16
#define CONSUMER__AC_Scroll                           0x0235  // Sel         15.16
#define CONSUMER__AC_PanLeft                          0x0236  // Sel         15.16
#define CONSUMER__AC_PanRight                         0x0237  // Sel         15.16
#define CONSUMER__AC_Pan                              0x0238  // Sel         15.16
#define CONSUMER__AC_NewWindow                        0x0239  // Sel         15.16
#define CONSUMER__AC_TileHorizontally                 0x023A  // Sel         15.16
#define CONSUMER__AC_TileVertically                   0x023B  // Sel         15.16
#define CONSUMER__AC_Format                           0x023C  // Sel         15.16
#define CONSUMER__AC_Edit                             0x023D  // Sel         15.14
#define CONSUMER__AC_Bold                             0x023E  // Sel         15.16
#define CONSUMER__AC_Italics                          0x023F  // Sel         15.16
#define CONSUMER__AC_Underline                        0x0240  // Sel         15.16
#define CONSUMER__AC_Strikethrough                    0x0241  // Sel         15.16
#define CONSUMER__AC_Subscript                        0x0242  // Sel         15.16
#define CONSUMER__AC_Superscript                      0x0243  // Sel         15.16
#define CONSUMER__AC_AllCaps                          0x0244  // Sel         15.16
#define CONSUMER__AC_Rotate                           0x0245  // Sel         15.16
#define CONSUMER__AC_Resize                           0x0246  // Sel         15.16
#define CONSUMER__AC_Fliphorizontal                   0x0247  // Sel         15.16
#define CONSUMER__AC_FlipVertical                     0x0248  // Sel         15.16
#define CONSUMER__AC_MirrorHorizontal                 0x0249  // Sel         15.16
#define CONSUMER__AC_MirrorVertical                   0x024A  // Sel         15.16
#define CONSUMER__AC_FontSelect                       0x024B  // Sel         15.16
#define CONSUMER__AC_FontColor                        0x024C  // Sel         15.16
#define CONSUMER__AC_FontSize                         0x024D  // Sel         15.16
#define CONSUMER__AC_JustifyLeft                      0x024E  // Sel         15.16
#define CONSUMER__AC_JustifyCenterH                   0x024F  // Sel         15.16
#define CONSUMER__AC_JustifyRight                     0x0250  // Sel         15.16
#define CONSUMER__AC_JustifyBlockH                    0x0251  // Sel         15.16
#define CONSUMER__AC_JustifyTop                       0x0252  // Sel         15.16
#define CONSUMER__AC_JustifyCenterV                   0x0253  // Sel         15.16
#define CONSUMER__AC_JustifyBottom                    0x0254  // Sel         15.16
#define CONSUMER__AC_JustifyBlockV                    0x0255  // Sel         15.16
#define CONSUMER__AC_IndentDecrease                   0x0256  // Sel         15.16
#define CONSUMER__AC_IndentIncrease                   0x0257  // Sel         15.16
#define CONSUMER__AC_NumberedList                     0x0258  // Sel         15.16
#define CONSUMER__AC_RestartNumbering                 0x0259  // Sel         15.16
#define CONSUMER__AC_BulletedList                     0x025A  // Sel         15.16
#define CONSUMER__AC_Promote                          0x025B  // Sel         15.16
#define CONSUMER__AC_Demote                           0x025C  // Sel         15.16
#define CONSUMER__AC_Yes                              0x025D  // Sel         15.16
#define CONSUMER__AC_No                               0x025E  // Sel         15.16
#define CONSUMER__AC_Cancel                           0x025F  // Sel         15.16
#define CONSUMER__AC_Catalog                          0x0260  // Sel         15.16
#define CONSUMER__AC_Buy_Checkout                     0x0261  // Sel         15.16
#define CONSUMER__AC_AddtoCart                        0x0262  // Sel         15.16
#define CONSUMER__AC_Expand                           0x0263  // Sel         15.16
#define CONSUMER__AC_ExpandAll                        0x0264  // Sel         15.16
#define CONSUMER__AC_Collapse                         0x0265  // Sel         15.16
#define CONSUMER__AC_CollapseAll                      0x0266  // Sel         15.16
#define CONSUMER__AC_PrintPreview                     0x0267  // Sel         15.16
#define CONSUMER__AC_PasteSpecial                     0x0268  // Sel         15.16
#define CONSUMER__AC_InsertMode                       0x0269  // Sel         15.16
#define CONSUMER__AC_Delete                           0x026A  // Sel         15.16
#define CONSUMER__AC_Lock                             0x026B  // Sel         15.16
#define CONSUMER__AC_Unlock                           0x026C  // Sel         15.16
#define CONSUMER__AC_Protect                          0x026D  // Sel         15.16
#define CONSUMER__AC_Unprotect                        0x026E  // Sel         15.16
#define CONSUMER__AC_AttachComment                    0x026F  // Sel         15.16
#define CONSUMER__AC_DeleteComment                    0x0270  // Sel         15.16
#define CONSUMER__AC_ViewComment                      0x0271  // Sel         15.16
#define CONSUMER__AC_SelectWord                       0x0272  // Sel         15.16
#define CONSUMER__AC_SelectSentence                   0x0273  // Sel         15.16
#define CONSUMER__AC_SelectParagraph                  0x0274  // Sel         15.16
#define CONSUMER__AC_SelectColumn                     0x0275  // Sel         15.16
#define CONSUMER__AC_SelectRow                        0x0276  // Sel         15.16
#define CONSUMER__AC_SelectTable                      0x0277  // Sel         15.16
#define CONSUMER__AC_SelectObject                     0x0278  // Sel         15.16
#define CONSUMER__AC_Redo_Repeat                      0x0279  // Sel         15.16
#define CONSUMER__AC_Sort                             0x027A  // Sel         15.16
#define CONSUMER__AC_SortAscending                    0x027B  // Sel         15.16
#define CONSUMER__AC_SortDescending                   0x027C  // Sel         15.16
#define CONSUMER__AC_Filter                           0x027D  // Sel         15.16
#define CONSUMER__AC_SetClock                         0x027E  // Sel         15.16
#define CONSUMER__AC_ViewClock                        0x027F  // Sel         15.16
#define CONSUMER__AC_SelectTimeZone                   0x0280  // Sel         15.16
#define CONSUMER__AC_EditTimeZones                    0x0281  // Sel         15.16
#define CONSUMER__AC_SetAlarm                         0x0282  // Sel         15.16
#define CONSUMER__AC_ClearAlarm                       0x0283  // Sel         15.16
#define CONSUMER__AC_SnoozeAlarm                      0x0284  // Sel         15.16
#define CONSUMER__AC_ResetAlarm                       0x0285  // Sel         15.16
#define CONSUMER__AC_Synchronize                      0x0286  // Sel         15.16
#define CONSUMER__AC_Send_Receive                     0x0287  // Sel         15.16
#define CONSUMER__AC_SendTo                           0x0288  // Sel         15.16
#define CONSUMER__AC_Reply                            0x0289  // Sel         15.16
#define CONSUMER__AC_ReplyAll                         0x028A  // Sel         15.16
#define CONSUMER__AC_ForwardMsg                       0x028B  // Sel         15.16
#define CONSUMER__AC_Send                             0x028C  // Sel         15.16
#define CONSUMER__AC_AttachFile                       0x028D  // Sel         15.16
#define CONSUMER__AC_Upload                           0x028E  // Sel         15.16
#define CONSUMER__AC_Download_SaveTargetAs            0x028F  // Sel         15.16
#define CONSUMER__AC_SetBorders                       0x0290  // Sel         15.16
#define CONSUMER__AC_InsertRow                        0x0291  // Sel         15.16
#define CONSUMER__AC_InsertColumn                     0x0292  // Sel         15.16
#define CONSUMER__AC_InsertFile                       0x0293  // Sel         15.16
#define CONSUMER__AC_InsertPicture                    0x0294  // Sel         15.16
#define CONSUMER__AC_InsertObject                     0x0295  // Sel         15.16
#define CONSUMER__AC_InsertSymbol                     0x0296  // Sel         15.16
#define CONSUMER__AC_SaveandClose                     0x0297  // Sel         15.16
#define CONSUMER__AC_Rename                           0x0298  // Sel         15.16
#define CONSUMER__AC_Merge                            0x0299  // Sel         15.16
#define CONSUMER__AC_Split                            0x029A  // Sel         15.16
#define CONSUMER__AC_DisributeHorizontally            0x029B  // Sel         15.16
#define CONSUMER__AC_DistributeVertically             0x029C  // Sel         15.16

//      (Reserved)                            0x029D..0xFFFF  // -           -


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
#endif  // ERGODOX_FIRMWARE__SRC__LIB__USB__USAGE_PAGE__CONSUMER__H

