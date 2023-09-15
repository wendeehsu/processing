int colors[] = {#FF0000, #FFA500, #FFFF00, #008000, #0000FF, #4B0082, #EE82EE};

void setup() {
  size(500,500);
  
  for (int i = 0; i < 7; i++) {
    drawCircle(200 - i*200/7, colors[i]);
  }
}

void draw() {
  line(0,0,mouseX, mouseY);
  println(mouseX);
}

void drawCircle(int radius, int colorHex) {
  fill(colorHex);
  noStroke();
  ellipse(250,250,radius,radius);}
