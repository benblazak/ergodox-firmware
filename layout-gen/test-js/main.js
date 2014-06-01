window.onload = function() {
  // Creates canvas 320 × 200 at 10, 50
  var paper = Raphael(0, 0, 320, 200);

  // Creates circle at x = 50, y = 40, with radius 10
  var circle = paper.circle(320, 200, 10);
  // Sets the fill attribute of the circle to red (#f00)
  circle.attr("fill", "#729fcf");

  // Sets the stroke attribute of the circle to white
  circle.attr("stroke", "#fff");
}

