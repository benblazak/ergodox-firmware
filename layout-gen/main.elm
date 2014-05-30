import Window


lightLightBlue : Color
lightLightBlue = rgba 114 159 207 0.5  -- lightBlue with alpha=0.5


main : Signal Element
main = background <~ Window.dimensions


background : (Int, Int) -> Element
background (w,h) =
    let (xMax, yMax) = (toFloat w / 2, toFloat h / 2)
        vtLine color = segment (0, -yMax) (0, yMax) |> traced (dashed color)
        htLine color = segment (-xMax, 0) (xMax, 0) |> traced (dashed color)
        vLineOffsets space = [floor (-xMax/space)..floor (xMax/space)]
        hLineOffsets space = [floor (-yMax/space)..floor (yMax/space)]
    in color lightGray <| collage w h (
        vtLine black :: htLine black ::
        (map (\x -> vtLine (if mod x 2 == 1 then lightBlue else lightLightBlue)
                    |> move (toFloat x * 35, 0))
             (vLineOffsets 35)) ++
        (map (\y -> htLine (if mod y 2 == 1 then lightBlue else lightLightBlue)
                    |> move (0, toFloat y * 35))
             (hLineOffsets 35))
    )

