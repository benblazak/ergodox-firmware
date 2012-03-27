# Documentation : Keyboard Matrix

## Matrix [row.column] assignments

 * row and column numbers are in hex
 * coordinates without brackets are unused
 * left and right hands are mostly the same, except that `row += 6` for left
   hand rows

    .......           rows x columns = positions;  assigned,  unassigned .......
    ....... per hand:    6 x 7       = 42;         38,        4          .......
    .......    total:   12 x 7       = 84;         76,        8          .......
    ----------------------------------------------------------------------------
    [60][61][62][63][64][65][66]                [00][01][02][03][04][05][06]
    [70][71][72][73][74][75][76]                [10][11][12][13][14][15][16]
    [80][81][82][83][84][85] 86                  20 [21][22][23][24][25][26]
    [90][91][92][93][94][95][96]                [30][31][32][33][34][35][36]
    [A0][A1][A2][A3][A4] A5  A6                  40  41 [42][43][44][45][46]
                          [B0]     B6      50     [56]
                          [B1]    [B5]    [51]    [55]
                          [B2][B3][B4]    [52][53][54]

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")
Project located at <https://github.com/benblazak/ergodox-firmware>

