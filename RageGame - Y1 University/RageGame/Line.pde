class Line {

  float x, y, w, h;
  PVector Vel;
  Line(float startX, float startY, float W) {
    x = startX;
    y = startY;
    Vel = new PVector(random(-4, 4), random(-4, 4));
    w = W;
    h = 25;
  }

  void move() {
    x = x + Vel.x;

    if (x < 0 && Vel.x < 0) {
      Vel.x = -1*Vel.x;
    } else if (x + w > width && Vel.x > 0) {
      Vel.x = -1*Vel.x;
    }
  }
  void show() {
    noStroke();
    rect(x, y, w, h);
  }
}
