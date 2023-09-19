class Circle {
  float X, Y;
  float D;
  float Speed;
  int Red, Green, Blue;
  
  // Constructor
  Circle()
  {
    X = random(0, width-25);
    Y = random(0, height-25);
    D = random(10, 100);
    Speed = random(0.1, 2.5);
    Red = int(random(255));
    Green = int(random(255));
    Blue = int(random(255));
  }
  
  void display() {
    noStroke();
    fill(Red, Green, Blue, 50);
    circle(X, Y, D);
  }
  
  void behaviour() {
    X += Speed;
    if (X >= width + D) X = -D;
  }
}
