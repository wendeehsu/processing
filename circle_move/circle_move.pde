int[] x = new int[100];
int[] y = new int[100];
int[] colors = new int[100];
int speed = 0;

void setup() {
  size(500,500);
  noStroke();
  for (int i = 0; i < 100; i++) {
    x[i] = int(random(0,500));
    y[i] = int(random(0,500));
    colors[i] = int(random(0,255));
  }
}

void draw() {
  background(255);
  for (int i = 0; i < 100; i++) {
    fill(colors[i], 50);
    circle(x[i] + speed * i/5,y[i],i+5);
  }
  speed += 1;
}
