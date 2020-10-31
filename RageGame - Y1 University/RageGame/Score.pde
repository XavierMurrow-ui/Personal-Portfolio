int score;
class Score {

  float x, y;

  Score() {
    x = 0;
    y = 40;
    textSize(25);
  }

  void show() {
    fill(0);
    text("Score: " + score +" / 10", x, y);
  }

  void win() {
    if (score == 10 && life >= 0) {
      theme.stop();
      fill(255);
      background(#E8CE05);
      textSize(100);
      text("YOU WIN!", 340, 100);
      image(Cat, 260, 150);
      Cat.play();
      textSize(30);
      text("Click to retry",400, 570);
      theme.stop();
    }
  }
}
