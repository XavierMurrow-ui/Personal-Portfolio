class Square {
  float x, y, w, h;

  float speedX, speedY;

  boolean connected;
  float g;

  Square() {
    x = width/2;
    y = 40;
    w = 32;
    h = 32;

    speedX = 0;
    speedY = 0;

    connected = false;
    g = 0.6;
  }

  void land(float destY) {
    speedY = 0;
    connected = true;
    y = destY - h;
  }

  void collision() {
    x = width/2;
    y = 40;
    life--;
    //me.lose();
  }

  void update() {
    if (left) {
      speedX = -5;
    }
    if (right) {
      speedX = 5;
    }
    if (!left && !right) {
      speedX = 0;
    } else if (left && right) {
      speedX = 0;
    }
    if (up && connected == true) {
      speedY = -10;
      connected = false;
    }
    if (connected == false) {
      speedY += g;
    }
    if (y > height) {
      y =0;
      speedY = 0;
      score++;
      theme.stop();
      setup();
      mainScreen();
    }

    if (x > width || x + w < 0) {
      life --;
      theme.stop();
      setup();
    }

    x += speedX;
    y += speedY;
  }

  void show() {
    fill(255, 100, 0);
    rect(x, y, w, h);
  }
}
