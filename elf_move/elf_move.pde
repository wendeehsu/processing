float X[] = new float[30];
boolean direction_right = true;
float circleRadius = 5;
float largeCircleRadius = circleRadius * 2;
int start_pos = -1;
int start_second = -1;

void setup() {
  size(600,450);
  noStroke();
  for (int i = 0; i < 30; i++) {
    X[i] = circleRadius + largeCircleRadius*2*i;
  }
  println(millis());
}

void draw() {
  if(start_pos == -1){
    start_pos = millis();
    start_second = second();
  } else if (second() == 30 || second() == 0) {
    start_pos = millis();
    start_second = 0;
  }

  background(0);
  text(second()+1, 5, 15);

  fill(255);
  for (int i = second(); i < 60; i++) {
    circle(X[i % 30],10 + 20*(1 + i / 30),
          (i + 1) % 5 == 0 ? largeCircleRadius: circleRadius);
  }

  // Yellow Elf
  fill(245, 245, 66);
  arc(X[(start_second) % 30] + (millis() - start_pos) * 595/30000 ,
      second() < 30 ? 30 : 50, 20, 20, QUARTER_PI, 2*PI-QUARTER_PI, PIE);

  //fill(200,20);
  //rect(0,0,500,500);
  //fill(colorNo);
  
  //// X
  //if (posX > 450) {
  //  direction_right = false;
  //  colorNo = int(random(0,255));
  //}
  //else if (posX < 50) {
  //  direction_right = true;
  //  colorNo = int(random(0,255));
  //}
  
  //if (direction_right) {
  //  posX += 10;
  //} else {
  //  posX -= 10;
  //}
  
  //// Y
  //if (posY > 450) {
  //  direction_down = false;
  //  colorNo = int(random(0,255));
  //}
  //else if (posY < 50) {
  //  direction_down = true;
  //  colorNo = int(random(0,255));
  //}
  
  //if (direction_down) {
  //  posY += 5;
  //} else {
  //  posY -= 5;
  //}
  
  //fill(colorNo);
  //circle(posX,posY,100);
  //fill(0);
  //textSize(20);
  //text("I want fika!", 250,250);
  
  
  // //trace mouse track
  //circle(mouseX, mouseY, 100);
  
  //// clock
  //line(second(), 0, second(), 100);
  //line(minute(), 100, minute(), 200);
  //line(hour(), 200, hour(), 300);
}
