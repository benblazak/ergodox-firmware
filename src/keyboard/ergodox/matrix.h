/* ----------------------------------------------------------------------------
 * ergoDOX: keyboard matrix specific exports
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
 * Released under The MIT License (MIT) (see "license.md")
 * Project located at <https://github.com/benblazak/ergodox-firmware>
 * ------------------------------------------------------------------------- */


#ifndef MATRIX_h
	#define MATRIX_h

	#include "lib/data-types.h"

	#define KB_ROWS    12  // must match real life
	#define KB_COLUMNS  7  // must match real life

	extern bool (*kb_is_pressed)[KB_ROWS][KB_COLUMNS];
	extern bool (*kb_was_pressed)[KB_ROWS][KB_COLUMNS];


	#ifdef KEYBOARD_INCLUDE_PRIVATE

		/* mapping from spatial position to matrix position
		 * - spatial position: where the key is spatially, relative to
		 *   other keys both on the keyboard and in the layout
		 * - matrix position: the coordinate in the matrix to which
		 *   a key is scanned by the update functions
		 *
		 * - location numbers are in the format `row##column`, where
		 *   both 'row' and 'column' are single digit hex numbers
		 *   corresponding to the matrix position
		 * - coordinates not listed are unused
		 *
		 * --- other info ---------------------------------------------
		 *           rows x columns = positions;  assigned,  unassigned
		 * per hand:    6 x 7       = 42;         38,        4
		 *    total:   12 x 7       = 84;         76,        8
		 *
		 * left hand  : cols 0..6, rows 6..B
		 * right hand : cols 0..6, rows 0..5
		 * ------------------------------------------------------------
		 */
		#define LAYER(						\
				/* for unused positions */		\
				na,					\
									\
				/* left hand, spatial positions */	\
				kB6,kB5,kB4,kB3,kB2,kB1,kB0,		\
				kA6,kA5,kA4,kA3,kA2,kA1,kA0,		\
				k96,k95,k94,k93,k92,k91,		\
				k86,k85,k84,k83,k82,k81,k80,		\
				k76,k75,k74,k73,k72,			\
				                      k64,		\
				                      k63,  k60,	\
				                    k65,k62,k61,	\
									\
				/* right hand, spatial positions */	\
				    k50,k51,k52,k53,k54,k55,k56,	\
				    k40,k41,k42,k43,k44,k45,k46,	\
				        k31,k32,k33,k34,k35,k36,	\
				    k20,k21,k22,k23,k24,k25,k26,	\
				            k12,k13,k14,k15,k16,	\
				      k04,				\
				k00,  k03,				\
				k01,k02,k05 )				\
									\
			/* matrix positions */				\
			{ { k00,k01,k02,k03,k04,k05, na,},		\
			  {  na, na,k12,k13,k14,k15,k16,},		\
			  { k20,k21,k22,k23,k24,k25,k26,},		\
			  {  na,k31,k32,k33,k34,k35,k36,},		\
			  { k40,k41,k42,k43,k44,k45,k46,},		\
			  { k50,k51,k52,k53,k54,k55,k56,},		\
			  { k60,k61,k62,k63,k64,k65, na,},		\
			  {  na, na,k72,k73,k74,k75,k76,},		\
			  { k80,k81,k82,k83,k84,k85,k86,},		\
			  {  na,k91,k92,k93,k94,k95,k96,},		\
			  { kA0,kA1,kA2,kA3,kA4,kA5,kA6,},		\
			  { kB0,kB1,kB2,kB3,kB4,kB5,kB6 } }


		#define LAYER_SET_ALL(na, kxx)				\
			LAYER(						\
				na,					\
									\
				kxx,kxx,kxx,kxx,kxx,kxx,kxx,		\
				kxx,kxx,kxx,kxx,kxx,kxx,kxx,		\
				kxx,kxx,kxx,kxx,kxx,kxx,		\
				kxx,kxx,kxx,kxx,kxx,kxx,kxx,		\
				kxx,kxx,kxx,kxx,kxx,			\
				                      kxx,		\
				                      kxx,  kxx,	\
				                    kxx,kxx,kxx,	\
									\
				    kxx,kxx,kxx,kxx,kxx,kxx,kxx,	\
				    kxx,kxx,kxx,kxx,kxx,kxx,kxx,	\
				        kxx,kxx,kxx,kxx,kxx,kxx,	\
				    kxx,kxx,kxx,kxx,kxx,kxx,kxx,	\
				            kxx,kxx,kxx,kxx,kxx,	\
				      kxx,				\
				kxx,  kxx,				\
				kxx,kxx,kxx )

	#endif

#endif

