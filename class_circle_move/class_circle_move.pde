Circle[] circles = new Circle[20];

void setup() {
  size(600,600);
  for (int i = 0; i < circles.length; i++) {
    circles[i] = new Circle();
  }
}

void draw() {
  background(255);
  for (int i = 0; i < circles.length; i++) {
    circles[i].display();
    circles[i].behaviour();
  }
}
