import Window


-- our grid's aspect ratio
aspectRatio : (Int, Int)
aspectRatio = (3,2)
-- to scale our aspect ratio
aspectScale : Int
aspectScale = 7

-- the number of columns in our grid
columns : Int
columns = aspectScale * (fst aspectRatio)
-- the number of rows in our grid
rows : Int
rows = aspectScale * (snd aspectRatio)

-- to generate various transparencies of lightBlue
lightBlueN : Float -> Color
lightBlueN n = rgba 114 159 207 (1/n)


-- TODO: document what i mean by (x,y) (after i figure it out)
background : (Int, Int) -> Element
background (width,height) =
  let (w,h) = (toFloat width, toFloat height)
      (r,c) = (toFloat rows, toFloat columns)

      step = min (w/c) (h/r)

      line (x,y) color offset =
        segment (-x*w,-y*h) (x*w,y*h) |> traced (dashed color)
                                      |> move (y*offset*step, x*offset*step)
      lines (x,y) =
        let dimension = if x == 0 then w else h
        in map (\n -> line (x/2,y/2)
                           (lightBlueN <| toFloat (mod (n+1) 2 + 1) * 3)
                           (toFloat n))
               [floor (-dimension/step) .. floor (dimension/step)]
      crossBox = [ line (0,1) charcoal 0,      line (1,0) charcoal 0, 
                   line (0,1) charcoal ( c/2), line (0,1) charcoal (-c/2),
                   line (1,0) charcoal ( r/2), line (1,0) charcoal (-r/2) ]

  in color lightGray <| collage width height (
       crossBox ++
       lines (0,1) ++ lines (1,0)
     )


main : Signal Element
main = background <~ Window.dimensions

