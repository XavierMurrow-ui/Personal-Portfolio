class Death {
  float x, y, w, h;

  Death(float destY) {
    x = random(10, 990);
    y = destY;
    w = 10;
    h = 10;
  }

  void show() {
    fill(#030303);
    rect(x, y, w, h);
  }
}
