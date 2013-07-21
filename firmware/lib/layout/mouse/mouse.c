/* ----------------------------------------------------------------------------
 * Copyright (c) 2013 Gyuri Horak <dyuri@horak.hu>
 * Released under The MIT License (see "doc/licenses/MIT.md")
 * Project located at <https://github.com/dyuri/ergodox-firmware>
 * ------------------------------------------------------------------------- */

#include <stdbool.h>
#include "../../../../firmware/lib/usb.h"
#include "../../../../firmware/keyboard.h"

// 
void key_functions__mouse_buttons(uint8_t left, uint8_t middle, uint8_t right)
{
	uint8_t mask=0;

	if (left) mask |= 1;
	if (middle) mask |= 4;
	if (right) mask |= 2;

  if (mask > 0) {
    kb__led__on(1);
  } else {
    kb__led__off(1);
  }

	usb__m__buttons(mask);
}

// single left click (?)
void key_functions__mouse_left_click(void) {
  usb__m__send(0, 0, 0, 0, MOUSE_BTN1);
  usb__m__send(0, 0, 0, 0, 0);
}

