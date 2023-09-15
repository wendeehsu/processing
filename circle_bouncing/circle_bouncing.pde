int posX = 50;
int posY = 50;
int colorNo = 255;
boolean direction_right = true;
boolean direction_down = true;

void setup() {
  size(500,500);
  noStroke();
}

void draw() {
  fill(200,20);
  rect(0,0,500,500);
  fill(colorNo);
  
  // X
  if (posX > 450) {
    direction_right = false;
    colorNo = int(random(0,255));
  }
  else if (posX < 50) {
    direction_right = true;
    colorNo = int(random(0,255));
  }
  
  if (direction_right) {
    posX += 10;
  } else {
    posX -= 10;
  }
  
  // Y
  if (posY > 450) {
    direction_down = false;
    colorNo = int(random(0,255));
  }
  else if (posY < 50) {
    direction_down = true;
    colorNo = int(random(0,255));
  }
  
  if (direction_down) {
    posY += 5;
  } else {
    posY -= 5;
  }
  
  fill(colorNo);
  circle(posX,posY,100);
  fill(0);
  textSize(20);
  text("I want fika!", 250,250);
  
  
  // //trace mouse track
  //circle(mouseX, mouseY, 100);
  
  //// clock
  //line(second(), 0, second(), 100);
  //line(minute(), 100, minute(), 200);
  //line(hour(), 200, hour(), 300);
}
