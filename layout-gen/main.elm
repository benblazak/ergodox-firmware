-------------------------------------------------------------------------------
-- Copyright (c) 2014 Ben Blazak <benblazak.dev@gmail.com> 
-- Released under The MIT License (see "doc/licenses/MIT.md")
-- Project located at <https://github.com/benblazak/ergodox-firmware>
-------------------------------------------------------------------------------

{-| A web-based UI for generating keyboard layouts for the firmware
-}


import Window
import Dict

import Boards


-------------------------------------------------------------------------------
-- values and signals
-------------------------------------------------------------------------------

{-| The number of columns and rows in our grid

Notes:
- The list gives the aspect ratio (of width to height)
- The number gives the scale of the aspect ratio, relative to the window size
-}
[columns, rows] = map ((*) 5) [4,3]


{-| The edge length of a square in our grid
-}
edgeSignal : Signal Float
edgeSignal =
  let function = \(width,height) -> min (toFloat width / columns)
                                        (toFloat height / rows)
  in lift function Window.dimensions


-------------------------------------------------------------------------------
-- groups of forms
-------------------------------------------------------------------------------

background : (Int, Int) -> Float -> [Form]
background (width,height) edge =
  let (w,h) = (toFloat width, toFloat height)

      ruleLines = True
      lineStyle = dashed lightBlue
      ruleLineStyle = dotted charcoal

      -- x and y represent the horizontal and vertical scaling factors
      line (x,y) style offset =
        segment (-x*w/2,-y*h/2) (x*w/2,y*h/2)
                |> traced style
                |> move (y*offset*edge, x*offset*edge)

      lines (x,y) =
        let dimension = if x == 0 then w else h
        in map (\n -> line (x,y) lineStyle (toFloat n/2)
                      |> alpha (1 / (toFloat (mod (n+1) 2 + 1) * 3)))
               [floor (-dimension/edge)*2 .. floor (dimension/edge)*2]

      vLines = lines (0,1)
      hLines = lines (1,0)

      rLines =
        let boxLine (x,y) offset = line (x,y) ruleLineStyle offset
        in [ boxLine (0,1) (-columns/2), boxLine (1,0) (-rows/2)
--            , boxLine (0,1) 0,            boxLine (1,0) 0
           , boxLine (0,1) (columns/2),  boxLine (1,0) (rows/2)
           ]

  in hLines ++ vLines ++ if ruleLines then rLines else []


keyboardTestDraw : Float -> [Form]
keyboardTestDraw edge =
  let lineStyle =
        let temp = solid lightBlue
        in { temp | width <- 5, cap <- Round, join <- Smooth }

      -- grab just 1 Board, and use only 1 configuration
      keyboard = head <| filter (\n -> n.name == "ErgoDox") Boards.all
      configuration = 1

      -- s = scaling factor (from 1 square of the grid)
      -- p = position of the center of the rectangle on the grid
      formKey k =
        let (sizeX, sizeY) = (k.size*edge, edge)
            (posX, posY) = ((fst k.position)*edge, (snd k.position)*edge)
        in map (move (posX, posY) . rotate (degrees k.rotation))
               [ rect sizeX sizeY |> outlined lineStyle
               , toForm <| plainText k.name
               ]

      -- convert positions to be relative to center of the page
      keys =
        let convertPosition (x,y) = (  x - (fst keyboard.size) / 2,
                                      -y + (snd keyboard.size) / 2 )
        in map (\n -> { n | position <- convertPosition n.position })
               keyboard.keys
           |> filter ( \n ->    n.configuration == 0
                             || n.configuration == configuration )

  in foldl1 (++) (map formKey keys)

--       leftHand =    (map (\n -> ((1.5,1),(-8.25,8-n)))[0..3])     -- left 1.5x
--                  ++ (map (\n -> ((1,1),(-7+n,8)))[0..5])          -- top  1x
--                  ++ (map (\n -> ((1,1),(-7+n,7)))[0..4])          -- next 1x
--                  ++ (map (\n -> ((1,1),(-7+n,6)))[0..4])          -- next 1x
--                  ++ (map (\n -> ((1,1),(-7+n,5)))[0..4])          -- next 1x
--                  ++ (map (\n -> ((1,1),(-8+n,4)))[0..4])          -- bottom 1x
--                  ++ (map (\n -> ((1,1.5),(-2,6.75-n*1.5)))[0..1]) -- right 1.5x
--                  ++ (map (\n -> ((1,2),(-3+n,1.5)))[0..1])        -- thumb 2x
--                  ++ (map (\n -> ((1,1),(-2+n,3)))[0..1])          -- t thumb 1x
--                  ++ (map (\n -> ((1,1),(-1-n,2)))[0..0])          -- m thumb 1x
--                  ++ (map (\n -> ((1,1),(-1-n,1)))[0..0])          -- b thumb 1x
-- 
--       rightHand = map (\((a,b),(c,d)) -> ((a,b),(-c,d))) leftHand
-- 
--   in map (\((a,b),(c,d)) -> key (a,b) (c-0.5,d-3)) (leftHand ++ rightHand)


-------------------------------------------------------------------------------
-- putting it all together
-------------------------------------------------------------------------------

scene : (Int, Int) -> Float -> Element
scene (width,height) edge =
  let backgroundColor = lightGray
  in layers [ collage width height [] |> color backgroundColor
            , collage width height (background (width,height) edge)
            , collage width height (keyboardTestDraw edge)
            ]


main : Signal Element
main = scene <~ Window.dimensions ~ edgeSignal

