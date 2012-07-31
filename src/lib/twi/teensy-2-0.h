/* ----------------------------------------------------------------------------
 * Very simple Teensy 2.0 TWI library : exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef TWI_h
	#define TWI_h

	// --------------------------------------------------------------------

	#ifndef TWI_FREQ
		#define TWI_FREQ 100000  // in Hz
	#endif

	// --------------------------------------------------------------------

	void    twi_init  (void);
	uint8_t twi_start (void);
	void    twi_stop  (void);
	uint8_t twi_send  (uint8_t data);
	uint8_t twi_read  (uint8_t * data);

#endif

