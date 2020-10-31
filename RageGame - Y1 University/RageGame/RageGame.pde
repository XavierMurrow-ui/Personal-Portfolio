import processing.video.*;
import processing.sound.*;

Square s;
Line[] l;
Score me;
Death[] d;
Lives L;

Start b = new Start(435, 325, 100);
Quit p = new Quit(885, 20, 100);

Movie myVideo;
Movie Cat;

SoundFile theme;

boolean left, right, up, down;

Boolean Score = false;
Boolean Life = false;

int currentScreen;

void setup() {
  size(1000, 700);
  myVideo = new Movie(this, "Rick.mp4");
  Cat = new Movie(this, "NyanCat.mp4");
  theme = new SoundFile(this, "theme.mp3");
  
  if(!theme.isPlaying()) theme.play();
  

  left = false;
  right = false;
  up = false;
  down = false;

  s= new Square();
  me = new Score();
  d = new Death[60];
  l = new Line[6];
  L = new Lives();

  l[0] = new Line(465, 100, 100);
  l[1] = new Line(random(20, 980), 200, random(50, 200));
  l[2] = new Line(random(20, 980), 300, random(50, 200));
  l[3] = new Line(random(20, 980), 400, random(50, 200));
  l[4] = new Line(random(20, 980), 500, random(50, 200));
  l[5] = new Line(random(20, 980), 600, random(50, 200));

  d[0] = new Death(150);
  d[1] = new Death(150);
  d[2] = new Death(150);
  d[3] = new Death(150);
  d[4] = new Death(150);
  d[5] = new Death(150);
  d[6] = new Death(150);
  d[7] = new Death(150);
  d[8] = new Death(150);
  d[9] = new Death(150);

  d[10] = new Death(250);
  d[11] = new Death(250);
  d[12] = new Death(250);
  d[13] = new Death(250);
  d[14] = new Death(250);
  d[15] = new Death(250);
  d[16] = new Death(250);
  d[17] = new Death(250);
  d[18] = new Death(250);
  d[19] = new Death(250);

  d[20] = new Death(350);
  d[21] = new Death(350);
  d[22] = new Death(350);
  d[23] = new Death(350);
  d[24] = new Death(350);
  d[25] = new Death(350);
  d[26] = new Death(350);
  d[27] = new Death(350);
  d[28] = new Death(350);
  d[29] = new Death(350);

  d[30] = new Death(450);
  d[31] = new Death(450);
  d[32] = new Death(450);
  d[33] = new Death(450);
  d[34] = new Death(450);
  d[35] = new Death(450);
  d[36] = new Death(450);
  d[37] = new Death(450);
  d[38] = new Death(450);
  d[39] = new Death(450);

  d[40] = new Death(550);
  d[41] = new Death(550);
  d[42] = new Death(550);
  d[43] = new Death(550);
  d[44] = new Death(550);
  d[45] = new Death(550);
  d[46] = new Death(550);
  d[47] = new Death(550);
  d[48] = new Death(550);
  d[49] = new Death(550);

  d[50] = new Death(650);
  d[51] = new Death(650);
  d[52] = new Death(650);
  d[53] = new Death(650);
  d[54] = new Death(650);
  d[55] = new Death(650);
  d[56] = new Death(650);
  d[57] = new Death(650);
  d[58] = new Death(650);
  d[59] = new Death(650);
}

void draw() {
  startScreen();
}

boolean rectangleIntercept(Square r1, Line r2) {
  //distance on x-axis
  float distanceX = (r1.x + r1.w/2) - (r2.x + r2.w/2);//dist(r1.x, 0, r2.x, 0);
  //distance on y-axis
  float distanceY = (r1.y + r1.h/2) - (r2.y + r2.h/2);//dist(0, r1.y, 0, r2.y); works but only for whole shape collision
  //combined half widths
  float halfWidth = r1.w/2 + r2.w/2 ;
  //combined half heights
  float halfHeight = r1.h/2 + r2.h/2;

  //check x-axis
  if (abs(distanceX) < halfWidth) {
    if (abs(distanceY) < halfHeight) {
      return true;
    }
  }
  return false;
}

boolean rectangleIntercept(Square r1, Death r2) {
  //distance on x-axis
  float distanceX = (r1.x + r1.w/2) - (r2.x + r2.w/2);//dist(r1.x, 0, r2.x, 0);
  //distance on y-axis
  float distanceY = (r1.y + r1.h/2) - (r2.y + r2.h/2);//dist(0, r1.y, 0, r2.y); works but only for whole shape collision
  //combined half widths
  float halfWidth = r1.w/2 + r2.w/2 ;
  //combined half heights
  float halfHeight = r1.h/2 + r2.h/2;

  //check x-axis
  if (abs(distanceX) < halfWidth) {
    if (abs(distanceY) < halfHeight) {
      return true;
    }
  }
  return false;
}

void keyPressed() {
  switch(keyCode) {
  case 37: //left
    left = true;
    break;
  case 39: // right
    right = true;
    break;
  case 38: //up
    up = true;
    break;
  case 40: //down
    down = true;
    break;
  }
}

void keyReleased() {
  switch(keyCode) {
  case 37: //left
    left = false;
    break;
  case 39: // right
    right = false;
    break;
  case 38: //up
    up = false;
    break;
  case 40: //down
    down = false;
    break;
  }
}

void lines() {
  for (int i = 0; i < l.length; i++ ) {
    if (i <= 0) {
      TEXT();
      fill(0, 0, 255, 150);
    } else {
      fill(255, 0, 0, 150);
    }
    l[i].show();// creates obsticles
    if (i % 2 != 0) {
      l[i].move();
    }
  }
  for (int i = 0; i < l.length; i++ ) {
    if (rectangleIntercept(s, l[i])) {
      s.land(l[i].y);//allows you to land
      break;
    } else {
      s.connected = false;
    }
  }
}

void TEXT() {
  textSize(25);
  fill(0);
  text("START", 475, 122);
}

void kill() {
  for (int i = 0; i < d.length; i++ ) {
    d[i].show();// creates obsticles
  }
  for (int i = 0; i < d.length; i++ ) {
    if (rectangleIntercept(s, d[i])) {
      s.collision();
      break;
    } else {
      s.connected = false;
    }
  }
}

void movieEvent(Movie videoBuffer)
{
  videoBuffer.read();
}

void startScreen() {
  background(255);
  fill(0);
  textSize(100);
  text("RAGEGAME", 230, 90);
  textSize(30);
  fill(0);
  text("Start", 450, 350);
  textSize(50);
  fill(0);
  text("Just get to the bottom", 250, 600);
  noStroke();
  fill(255, 0);
  b.show();
  quit();
}

void mainScreen() {
  background(255);
  s.show();
  s.update();
  lines();
  me.show();
  kill();
  L.show();
  me.win();
  L.GameOver();
  quit();
}

void quit() {
  fill(255,0,0);
  textSize(25);
  text("Quit", 900, 40);
  fill(255, 0);
  p.show();
}


void mouseClicked() {
  if (b.contains(mouseX, mouseY)) {
    b.on = true;
    theme.stop();
    theme.play();
  }
  if (p.contains(mouseX, mouseY)) {
    p.on = true;
  }
  if (life < 0) {
    theme.stop();
    myVideo.stop();
    setup();
    draw();
    myVideo.stop();
    theme.play();
    Score = true;
    Life = true;
  } 
  if (score == 10) {
    theme.stop();
    Cat.stop();
    setup();
    draw();
    Cat.stop();
    theme.play();
    Score = true;
    Life = true;
  } 
  if (Score == true) {
    score = 0;
  } 
  if (Life == true) {
    life = 3;
  } else {
  }
}
