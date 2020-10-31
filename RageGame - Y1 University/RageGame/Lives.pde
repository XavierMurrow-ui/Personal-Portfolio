int life = 3;

class Lives {
  PVector Pos;
  Lives() {
    Pos = new PVector(0, 90);
  }

  void show() {
    fill(0);
    text("Lives Left: "+life, Pos.x, Pos.y);
  }

  void GameOver() {
    if (life < 0) {
      theme.stop();
      background(0);
      fill(255, 0, 0);
      textSize(50);
      text("GAME OVER!", 340, 100);
      image(myVideo, 260, 150);
      myVideo.play();
      textSize(30);
      text("Click to retry", 400, 570);
      theme.stop();
    }
  }
}
