-------------------------------------------------------------------------------
-- Copyright (c) 2014 Ben Blazak <benblazak.dev@gmail.com> 
-- Released under The MIT License (see "doc/licenses/MIT.md")
-- Project located at <https://github.com/benblazak/ergodox-firmware>
-------------------------------------------------------------------------------

{-| Keyboard definitions
-}


module Boards where


-------------------------------------------------------------------------------
-- values
-------------------------------------------------------------------------------


{-| A list of the keyboards defined
-}
all : [Board]
all = [ ergodox ]


-------------------------------------------------------------------------------
-- types and default values
-------------------------------------------------------------------------------


{-| A type for keys in our keyboard

Fields:
- `name`: The name of the key (so we can reference it)
- `size`: The width of the key (in multiples of the standard 1x1 key, which
  takes up 1 grid block)
- `position`: The position of the center of the key on the grid, with `(0,0)`
  being the top left of the board, positive x extending right, and positive y
  extending down
- `rotation`: The rotation of the key (in degrees)
- `value`: A name corresponding to the assigned keycode for this key
- `configuration`: The configuration of the board to which this key belongs
    - 0: This key belongs to all configurations
-}
type Key = { name: String
           , size: Float
           , position: (Float,Float)
           , rotation: Float
           , value: String
           , configuration: Int
           }

defaultKey : Key
defaultKey = { name = ""
             , size = 1
             , position = (0,0)
             , rotation = 0
             , value = ""
             , configuration = 0
             }


{-| A type for keyboards (`Keyboard` is already used, in Elm)

Fields:
- `name`: The display name
- `size`: The horizontal and vertical size of the board, in grid squares
- `keys`: A list of keys, making up the keyboard
-}
type Board = { name: String
             , size: (Float,Float)
             , keys: [Key]
             }


-------------------------------------------------------------------------------
-- board definitions
-------------------------------------------------------------------------------


{-| Definition for the ErgoDox Keyboard

From the firmware source:

    /* left hand, spatial positions */
    k50,k51,k52,k53,k54,k55,k56,      
    k40,k41,k42,k43,k44,k45,k46,      
    k30,k31,k32,k33,k34,k35,          
    k20,k21,k22,k23,k24,k25,k26,      
    k10,k11,k12,k13,k14,              
                            k05,k06,  
                        k15,k16,k04,  
                        k03,k02,k01,  
                                      
    /* right hand, spatial positions *
        k57,k58,k59,k5A,k5B,k5C,k5D,  
        k47,k48,k49,k4A,k4B,k4C,k4D,  
            k38,k39,k3A,k3B,k3C,k3D,  
        k27,k28,k29,k2A,k2B,k2C,k2D,  
                k19,k1A,k1B,k1C,k1D,  
    k07,k08,                          
    k09,k17,k18,                      
    k0C,k0B,k0A )                     
-}


ergodox : Board
ergodox = { name = "ErgoDox", size = (18,8), keys = [

    -- left hand, roughly from upper left to bottom right

    { defaultKey | name <- "k50", position <- (0.25,0), size <- 1.5 }
  , { defaultKey | name <- "k51", position <- (1.5,0) }
  , { defaultKey | name <- "k52", position <- (2.5,0) }
  , { defaultKey | name <- "k53", position <- (3.5,0) }
  , { defaultKey | name <- "k54", position <- (4.5,0) }
  , { defaultKey | name <- "k55", position <- (5.5,0) }
  , { defaultKey | name <- "k56", position <- (6.5,0) }

  , { defaultKey | name <- "k40", position <- (0.25,1), size <- 1.5 }
  , { defaultKey | name <- "k41", position <- (1.5,1) }
  , { defaultKey | name <- "k42", position <- (2.5,1) }
  , { defaultKey | name <- "k43", position <- (3.5,1) }
  , { defaultKey | name <- "k44", position <- (4.5,1) }
  , { defaultKey | name <- "k45", position <- (5.5,1) }
  , { defaultKey | name <- "k46", position <- (6.5,1.25), size <- 1.5, rotation <- 90 }

  , { defaultKey | name <- "k30", position <- (0.25,2), size <- 1.5 }
  , { defaultKey | name <- "k31", position <- (1.5,2) }
  , { defaultKey | name <- "k32", position <- (2.5,2) }
  , { defaultKey | name <- "k33", position <- (3.5,2) }
  , { defaultKey | name <- "k34", position <- (4.5,2) }
  , { defaultKey | name <- "k35", position <- (5.5,2) }

  , { defaultKey | name <- "k20", position <- (0.25,3), size <- 1.5 }
  , { defaultKey | name <- "k21", position <- (1.5,3) }
  , { defaultKey | name <- "k22", position <- (2.5,3) }
  , { defaultKey | name <- "k23", position <- (3.5,3) }
  , { defaultKey | name <- "k24", position <- (4.5,3) }
  , { defaultKey | name <- "k25", position <- (5.5,3) }
  , { defaultKey | name <- "k26", position <- (6.5,2.75), size <- 1.5, rotation <- 90 }

  , { defaultKey | name <- "k10", position <- (0.5,4) }
  , { defaultKey | name <- "k11", position <- (1.5,4) }
  , { defaultKey | name <- "k12", position <- (2.5,4) }
  , { defaultKey | name <- "k13", position <- (3.5,4) }
  , { defaultKey | name <- "k14", position <- (4.5,4) }

  , { defaultKey | name <- "k05", position <- (6.5,5) }
  , { defaultKey | name <- "k06", position <- (7.5,5) }

  , { defaultKey | name <- "k15", position <- (5.5,6), configuration <- 2 }
  , { defaultKey | name <- "k16", position <- (6.5,6), configuration <- 2 }
  , { defaultKey | name <- "k04", position <- (7.5,6) }

  , { defaultKey | name <- "k03", position <- (5.5,6.5), size <- 2, rotation <- 90, configuration <- 1 }
  , { defaultKey | name <- "k02", position <- (6.5,6.5), size <- 2, rotation <- 90, configuration <- 1 }
  , { defaultKey | name <- "k03", position <- (5.5,7), configuration <- 2 }
  , { defaultKey | name <- "k02", position <- (6.5,7), configuration <- 2 }
  , { defaultKey | name <- "k01", position <- (7.5,7) }
  
    -- right hand, roughly from upper left to bottom right

  , { defaultKey | name <- "k57", position <- (10.5,0) }
  , { defaultKey | name <- "k58", position <- (11.5,0) }
  , { defaultKey | name <- "k59", position <- (12.5,0) }
  , { defaultKey | name <- "k5A", position <- (13.5,0) }
  , { defaultKey | name <- "k5B", position <- (14.5,0) }
  , { defaultKey | name <- "k5C", position <- (15.5,0) }
  , { defaultKey | name <- "k5D", position <- (16.75,0), size <- 1.5 }

  , { defaultKey | name <- "k47", position <- (10.5,1.25), size <- 1.5, rotation <- -90 }
  , { defaultKey | name <- "k48", position <- (11.5,1) }
  , { defaultKey | name <- "k49", position <- (12.5,1) }
  , { defaultKey | name <- "k4A", position <- (13.5,1) }
  , { defaultKey | name <- "k4B", position <- (14.5,1) }
  , { defaultKey | name <- "k4C", position <- (15.5,1) }
  , { defaultKey | name <- "k4D", position <- (16.75,1), size <- 1.5 }

  , { defaultKey | name <- "k38", position <- (11.5,2) }
  , { defaultKey | name <- "k39", position <- (12.5,2) }
  , { defaultKey | name <- "k3A", position <- (13.5,2) }
  , { defaultKey | name <- "k3B", position <- (14.5,2) }
  , { defaultKey | name <- "k3C", position <- (15.5,2) }
  , { defaultKey | name <- "k3D", position <- (16.75,2), size <- 1.5 }

  , { defaultKey | name <- "k27", position <- (10.5,2.75), size <- 1.5, rotation <- -90 }
  , { defaultKey | name <- "k28", position <- (11.5,3) }
  , { defaultKey | name <- "k29", position <- (12.5,3) }
  , { defaultKey | name <- "k2A", position <- (13.5,3) }
  , { defaultKey | name <- "k2B", position <- (14.5,3) }
  , { defaultKey | name <- "k2C", position <- (15.5,3) }
  , { defaultKey | name <- "k2D", position <- (16.75,3), size <- 1.5 }

  , { defaultKey | name <- "k19", position <- (12.5,4) }
  , { defaultKey | name <- "k1A", position <- (13.5,4) }
  , { defaultKey | name <- "k1B", position <- (14.5,4) }
  , { defaultKey | name <- "k1C", position <- (15.5,4) }
  , { defaultKey | name <- "k1D", position <- (16.5,4) }

  , { defaultKey | name <- "k07", position <- (9.5,5) }
  , { defaultKey | name <- "k08", position <- (10.5,5) }

  , { defaultKey | name <- "k09", position <- (9.5,6) }
  , { defaultKey | name <- "k17", position <- (10.5,6), configuration <- 2 }
  , { defaultKey | name <- "k18", position <- (11.5,6), configuration <- 2 }

  , { defaultKey | name <- "k0C", position <- (9.5,7) }
  , { defaultKey | name <- "k0B", position <- (10.5,6.5), size <- 2, rotation <- -90, configuration <- 1 }
  , { defaultKey | name <- "k0A", position <- (11.5,6.5), size <- 2, rotation <- -90, configuration <- 1 }
  , { defaultKey | name <- "k0B", position <- (10.5,7), configuration <- 2 }
  , { defaultKey | name <- "k0A", position <- (11.5,7), configuration <- 2 }

  ]}

