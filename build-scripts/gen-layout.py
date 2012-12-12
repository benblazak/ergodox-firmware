#! /usr/bin/env python3
# -----------------------------------------------------------------------------
# Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
# Released under The MIT License (MIT) (see "license.md")
# Project located at <https://github.com/benblazak/ergodox-firmware>
# -----------------------------------------------------------------------------

"""
Generate a depiction of the layout (in html + svg)

Depends on:
- the UI info file (in JSON)
"""

# -----------------------------------------------------------------------------

import argparse
import json
import os
import re
import sys

# -----------------------------------------------------------------------------

class Namespace():
	pass

template = Namespace()
doc = Namespace()
info = Namespace()

# -----------------------------------------------------------------------------

def main():
	arg_parser = argparse.ArgumentParser(
			description = "Generate a picture of the firmware's "
			            + "keyboard layout" )

	arg_parser.add_argument(
			'--ui-info-file',
			required = True )

	args = arg_parser.parse_args(sys.argv[1:])

	# constant file paths
	args.template_svg_file = './build-scripts/gen_layout/template.svg'
	args.template_js_file = './build-scripts/gen_layout/template.js'

	# normalize paths
	args.ui_info_file = os.path.abspath(args.ui_info_file)
	args.template_svg_file = os.path.abspath(args.template_svg_file)
	args.template_js_file = os.path.abspath(args.template_js_file)

	# set vars
	doc.main = ''  # to store the html document we're generating
	template.svg = open(args.template_svg_file).read()
	template.js = open(args.template_js_file).read()
	info.all = json.loads(open(args.ui_info_file).read())

	info.matrix_positions = info.all['mappings']['matrix-positions']
	info.matrix_layout = info.all['mappings']['matrix-layout']

	# prefix
	doc.prefix = ("""
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<html>

<head>
  <script>
"""
+ template.js +
""" </script>
</head>

<body>

<h1>Firmware Layout</h1>

<ul>
  <li>git commit date:
  <code>""" + info.all['miscellaneous']['git-commit-date'] + """</code></li>
  <li>git commit id:
  <code>""" + info.all['miscellaneous']['git-commit-id'] + """</code></li>
</ul>

<h2>Notes</h2>

<ul>
  <li>Layer keys are labeled e.g. <code>la 2 +- 2</code>
  <ul>
	<li><code>la</code> is for "layer"</li>
	<li><code>2</code> indicates that the second pair of push|pop functions is
	being used (differently numbered pairs won't interfere with each
	other)</li>
	<li><code>+</code> indicates that the layer is being "pushed" onto the
	stack at some point, either when the key is pressed or when it is
	released</li>
	<li><code>-</code> indicates that the layer is being "popped" off of the
	stack at some point</li>
	<li>the last <code>2</code> indicates the layer-number that will be
	activated on "push".</li>
  </ul>
  See the project 'readme.md' file on <a
  href='https://github.com/benblazak/ergodox-firmware'>the github page</a> as a
  starting point for learning more about how this firmware implements
  layers.</li>
  <br>
  <li>Shifted keys are labeled with an <code>sh</code> at the beginning.  This
  indicates that a 'Shift' is generated with that keypress, the same as if you
  had held down 'Shift', and pressed that key.</li>
  <br>
  <li><code>(null)</code> indicates that no keypress or keyrelease will be
  generated for that key, on that layer.</li>
  <br>
  <li>Blank keys indicate "transparency": if you press that key on that layer,
  the key will act as if it was on whatever layer is active below the current
  one.</li>
  <br>
  <li>Some keys may be labled with special functions (like
  <code>[btldr]</code>, which tells the Teensy to wait for the host to send it
  a new firmware).</li>
</ul>

<br>

""")[1:-1]

	# suffix
	doc.suffix = ("""
</body>
</html>

""")[1:-1]

	# substitute into template
	# -------
	# note: this is not general enough to handle any possible layout well, at
	# the moment.  but it should handle more standard ones well.  (hopefully
	# minor) modifications may be necessary on a case by case basis
	# -------
	layer_number = -1
	for (layout, layer) in zip( info.matrix_layout,
								range(len(info.matrix_layout))):
		layer_number += 1
		svg = template.svg
		for (name, (code, press, release)) \
				in zip(info.matrix_positions, layout):
			replace = ''
			if press == 'kbfun_transparent':
				replace = ''
			elif press == 'kbfun_shift_press_release':
				replace = 'sh ' + keycode_to_string.get(code, '[n/a]')
			elif press == 'kbfun_jump_to_bootloader':
				replace = '[btldr]'
			elif press == 'NULL' and release == 'NULL':
				replace = '(null)'
			elif re.search(r'numpad', press+release):
				replace = '[num]'
			elif re.search(r'layer', press+release):
				replace = 'la ' + re.findall(r'\d+', press+release)[0] + ' '
				if re.search(r'push', press+release):
					replace += '+'
				if re.search(r'pop', press+release):
					replace += '-'
				replace += ' ' + str(code)
			else:
				replace = keycode_to_string.get(code, '[n/a]')

			svg = re.sub(
					'>'+name+'<', '>'+replace+'<', svg )
			svg = re.sub(
					r"\('(" + name + r".*)'\)",
					r"('\1', " + str(layer) + r")",
					svg )

		doc.main += '<h2>Layer ' + str(layer_number) + '</h2>\n' + svg

	# change the font size
	doc.main = re.sub(r'22.5px', '15px', doc.main)

	print(doc.prefix + doc.main + doc.suffix)

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

keycode_to_string = {
		0x01: "Error",  # ErrorRollOver
		0x02: "POSTFail",
		0x03: "Error",  # ErrorUndefined
		0x04: "a A",
		0x05: "b B",
		0x06: "c C",
		0x07: "d D",
		0x08: "e E",
		0x09: "f F",
		0x0A: "g G",
		0x0B: "h H",
		0x0C: "i I",
		0x0D: "j J",
		0x0E: "k K",
		0x0F: "l L",
		0x10: "m M",
		0x11: "n N",
		0x12: "o O",
		0x13: "p P",
		0x14: "q Q",
		0x15: "r R",
		0x16: "s S",
		0x17: "t T",
		0x18: "u U",
		0x19: "v V",
		0x1A: "w W",
		0x1B: "x X",
		0x1C: "y Y",
		0x1D: "z Z",
		0x1E: "1 !",
		0x1F: "2 @",
		0x20: "3 #",
		0x21: "4 $",
		0x22: "5 %",
		0x23: "6 ^",
		0x24: "7 &",
		0x25: "8 *",
		0x26: "9 (",
		0x27: "0 )",
		0x28: "Return",
		0x29: "Esc",
		0x2A: "Backspace",
		0x2B: "Tab",
		0x2C: "Space",
		0x2D: "- _",
		0x2E: "= +",
		0x2F: "[ {",
		0x30: "] }",
		0x31: "\ |",
		0x32: "# ~",
		0x33: "; :",
		0x34: "\' \"",
		0x35: "` ~",
		0x36: ", <",
		0x37: ". >",
		0x38: "/ ?",
		0x39: "Caps",
		0x3A: "F1",
		0x3B: "F2",
		0x3C: "F3",
		0x3D: "F4",
		0x3E: "F5",
		0x3F: "F6",
		0x40: "F7",
		0x41: "F8",
		0x42: "F9",
		0x43: "F10",
		0x44: "F11",
		0x45: "F12",
		0x46: "PrintScreen",
		0x47: "ScrollLock",
		0x48: "Pause",
		0x49: "Ins",  # Insert
		0x4A: "Hm",  # Home
		0x4B: "Pg\u2191",  # up arrow
		0x4C: "Delete",
		0x4D: "End",
		0x4E: "Pg\u2193",  # down arrow
		0x4F: "\u2192",  # right arrow
		0x50: "\u2190",  # left arrow
		0x51: "\u2193",  # down arrow
		0x52: "\u2191",  # up arrow

		0x53: "Num",
		0x54: "/",
		0x55: "*",
		0x56: "-",
		0x57: "+",
		0x58: "Enter",
		0x59: "1 End",
		0x5A: "2 \u2193",  # down arrow
		0x5B: "3 Pg\u2193",  # down arrow
		0x5C: "4 \u2190",  # left arrow
		0x5D: "5",
		0x5E: "6 \u2192",  # right arrow
		0x5F: "7 Hm",  # Home
		0x60: "8 \u2191",  # up arrow
		0x61: "9 Pg\u2191",  # up arrow
		0x62: "0 Ins",  # Insert
		0x63: ". Del",

		0x64: "\ |",
		0x65: "App",
		0x66: "Power",

		0x67: "=",

		0x68: "F13",
		0x69: "F14",
		0x6A: "F15",
		0x6B: "F16",
		0x6C: "F17",
		0x6D: "F18",
		0x6E: "F19",
		0x6F: "F20",
		0x70: "F21",
		0x71: "F22",
		0x72: "F23",
		0x73: "F24",
		0x74: "Exec",
		0x75: "Help",
		0x76: "Menu",
		0x77: "Select",
		0x78: "Stop",
		0x79: "Again",
		0x7A: "Undo",
		0x7B: "Cut",
		0x7C: "Copy",
		0x7D: "Paste",
		0x7E: "Find",
		0x7F: "Mute",
		0x80: "VolUp",
		0x81: "VolDown",
		0x82: "LockingCapsLock",
		0x83: "LockingNumLock",
		0x84: "LockingScrollLock",

		0x85: ",",
		0x86: "=",

		0x87: "Int1",
		0x88: "Int2",
		0x89: "Int3",
		0x8A: "Int4",
		0x8B: "Int5",
		0x8C: "Int6",
		0x8D: "Int7",
		0x8E: "Int8",
		0x8F: "Int9",
		0x90: "LANG1",
		0x91: "LANG2",
		0x92: "LANG3",
		0x93: "LANG4",
		0x94: "LANG5",
		0x95: "LANG6",
		0x96: "LANG7",
		0x97: "LANG8",
		0x98: "LANG9",
		0x99: "AlternateErase",
		0x9A: "SysReq_Attention",
		0x9B: "Cancel",
		0x9C: "Clear",
		0x9D: "Prior",
		0x9E: "Return",
		0x9F: "Separator",
		0xA0: "Out",
		0xA1: "Oper",
		0xA2: "Clear_Again",
		0xA3: "CrSel_Props",
		0xA4: "ExSel",

		0xB0: "00",
		0xB1: "000",

		0xB2: "Thousands_Sep",
		0xB3: "Decimal_Sep",
		0xB4: "$",
		0xB5: "Currency_Subunit",

		0xB6: "(",
		0xB7: ")",
		0xB8: "{",
		0xB9: "}",

		0xBA: "Tab",
		0xBB: "Backspace",
		0xBC: "A",
		0xBD: "B",
		0xBE: "C",
		0xBF: "D",
		0xC0: "E",
		0xC1: "F",
		0xC2: "XOR",
		0xC3: "^",
		0xC4: "%",
		0xC5: "<",
		0xC6: ">",
		0xC7: "&",
		0xC8: "&&",
		0xC9: "|",
		0xCA: "||",
		0xCB: ":",
		0xCC: "#",
		0xCD: "Space",
		0xCE: "@",
		0xCF: "!",
		0xD0: "Mem_Store",
		0xD1: "Mem_Recall",
		0xD2: "Mem_Clear",
		0xD3: "Mem_+",
		0xD4: "Mem_-",
		0xD5: "Mem_*",
		0xD6: "Mem_/",
		0xD7: "+-",
		0xD8: "Clear",
		0xD9: "ClearEntry",
		0xDA: "Binary",
		0xDB: "Octal",
		0xDC: ".",
		0xDD: "Hexadecimal",

		0xE0: "L-Ctrl",
		0xE1: "L-Shift",
		0xE2: "L-Alt",
		0xE3: "L-GUI",
		0xE4: "R-Ctrl",
		0xE5: "R-Shift",
		0xE6: "R-Alt",
		0xE7: "R-GUI",
		}

# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

if __name__ == '__main__':
	main()

