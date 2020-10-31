class Start {
  boolean on = false;
  float centreX, centreY, Length;

  Start(float startX, float startY, float L) {
    on = false;
    centreX = startX;
    centreY = startY;
    Length = L;
  }

  void show() {
    rect(centreX, centreY, Length, 30);
    if (on == true) {
      mainScreen();
    }
  }

  boolean contains(float x, float y) {
    if (dist(x, y, centreX, centreY) <= Length) {
      return true;
    } else {
      return false;
    }
  }
}
