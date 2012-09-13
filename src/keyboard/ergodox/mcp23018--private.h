/* ----------------------------------------------------------------------------
 * ergoDOX controller: MCP23018 specific exports : private
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef MCP23018_h_PRIVATE
	#define MCP23018_h_PRIVATE

	#include "lib/data-types.h"
	#include "matrix.h"

	#define MCP23018_TWI_ADDRESS 0b0100000

	uint8_t mcp23018_init(void);
	uint8_t mcp23018_update_matrix( bool matrix[KB_ROWS][KB_COLUMNS] );

#endif

