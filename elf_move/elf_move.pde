// second position
float X[] = new float[30];

// hour position
int hour_X[] = new int[24];
int hour_Y[] = new int[24];

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
  
  for (int i = 0; i < 24; i++) {
    hour_X[i] = 150 + (i % 6) * 60;
    hour_Y[i] = 150 + (i / 6)* 60;
  }
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

  fill(255);
  textSize(30);
  text(hour()+ ":"+ minute()+ ":"+ (second()), 250, 100);

  for (int i = second(); i < 60; i++) {
    circle(X[i % 30], 30 + 380* (i / 30),
          (i + 1) % 5 == 0 ? largeCircleRadius: circleRadius);
  }

  for (int i = 0; i < 24; i++) {
    if (i == hour()-1) {
      fill(255);
      arc(hour_X[i] , hour_Y[i], 50, 50, minute()*PI/30-2*QUARTER_PI, 2*(PI-QUARTER_PI), PIE);
    } else if (i > hour() -1) {
      fill(255);
      circle(hour_X[i], hour_Y[i], 50);      
    } else {
      // body
      fill(155);
      arc(hour_X[i] , hour_Y[i], 50, 50, PI, 2*PI, PIE);
      rect(hour_X[i]-25 , hour_Y[i], 50,25);
      
      // eye
      fill(0);
      textSize(18);
      text("> m <", hour_X[i]-20 , hour_Y[i]);
    }
  }


  // Yellow Elf
  fill(245, 245, 66);
  arc(X[(start_second) % 30] + (millis() - start_pos) * 595/30000 ,
      second() < 30 ? 30 : 410, 10 + 40*second()/60.0, 10 + 40*second()/60.0,
      QUARTER_PI - ((millis() - start_pos) % 1000)*QUARTER_PI/1000, // jaw
      2*PI-(QUARTER_PI- ((millis() - start_pos) % 1000)*QUARTER_PI/1000), // upper mouth
      PIE);
}
