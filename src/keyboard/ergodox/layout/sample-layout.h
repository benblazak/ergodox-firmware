/*
 * Ergodox layout: sample
 * Based on qwerty-kinesis-mod
 *
 * Created by lotem <chen.sst@gmail.com>
 */
ERGODOX_LAYOUT = {
  ERGODOX_LAYER( // L0: default
    // left hand
    _(_equal),      _(_1),          _(_2),          _(_3),          _(_4),          _(_5),          _(_esc),
    _(_backslash),  _(_Q),          _(_W),          _(_E),          _(_R),          _(_T),          PUSH(1),
    _(_tab),        _(_A),          _(_S),          _(_D),          _(_F),          _(_G),
    S2CAP(_shiftL), _(_Z),          _(_X),          _(_C),          _(_V),          _(_B),          CHORD(1),
    _(_guiL),       _(_grave),      _(_backslash),  _(_arrowL),     _(_arrowR),
                                                                                    _(_ctrlL),      _(_altL),
                                                                                                    _(_home),
                                                                    _(_bs),         _(_del),        _(_end),
    // right hand
    UNUSED,         _(_6),          _(_7),          _(_8),          _(_9),          _(_0),          _(_dash),
    _(_bracketL),   _(_Y),          _(_U),          _(_I),          _(_O),          _(_P),          _(_bracketR),
    /*_*/           _(_H),          _(_J),          _(_K),          _(_L),          _(_semicolon),  _(_quote),
    CHORD(1),       _(_N),          _(_M),          _(_comma),      _(_period),     _(_slash),      S2CAP(_shiftR),
                                    _(_arrowL),     _(_arrowD),     _(_arrowU),     _(_arrowR),     _(_guiR),
    _(_altR),       _(_ctrlR),
    _(_pageU),
    _(_pageD),      _(_enter),      _(_space)
  ),
  ERGODOX_LAYER( // L1: function and symbol keys
    // left hand
    __,             _(_F1),         _(_F2),         _(_F3),         _(_F4),         _(_F5),         _(_F11),
    __,             S(_bracketL),   S(_bracketR),   _(_bracketL),   _(_bracketR),   UNUSED,         POP(1),
    __,             _(_semicolon),  _(_slash),      _(_dash),       _(_0_kp),       S(_semicolon),
    __,             _(_6_kp),       _(_7_kp),       _(_8_kp),       _(_9_kp),       S(_equal),      __,
    __,             __,            __,             __,              __,
                                                                                    __,             __,
                                                                                                    __,
                                                                    __,             __,             __,
    // right hand
    _(_F12),        _(_F6),         _(_F7),         _(_F8),         _(_F9),         _(_F10),        _(_power),
    __,             UNUSED,         S(_dash),       S(_comma),      S(_period),     _(_currencyUnit), _(_volumeU),
                    _(_backslash),  _(_1_kp),       S(_9),          S(_0),          _(_equal),      _(_volumeD),
    __,             S(_8),          _(_2_kp),       _(_3_kp),       _(_4_kp),       _(_5_kp),       _(_mute),
                                    __,             __,             __,             __,             __,
    __,             __,
    __,
    __,             __,             __
  ),
};
