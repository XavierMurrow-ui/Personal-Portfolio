import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.video.*; 
import processing.sound.*; 

import gifAnimation.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class RageGame extends PApplet {




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

public void setup() {
  
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

public void draw() {
  startScreen();
}

public boolean rectangleIntercept(Square r1, Line r2) {
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

public boolean rectangleIntercept(Square r1, Death r2) {
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

public void keyPressed() {
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

public void keyReleased() {
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

public void lines() {
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

public void TEXT() {
  textSize(25);
  fill(0);
  text("START", 475, 122);
}

public void kill() {
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

public void movieEvent(Movie videoBuffer)
{
  videoBuffer.read();
}

public void startScreen() {
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

public void mainScreen() {
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

public void quit() {
  fill(255,0,0);
  textSize(25);
  text("Quit", 900, 40);
  fill(255, 0);
  p.show();
}


public void mouseClicked() {
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
class Death {
  float x, y, w, h;

  Death(float destY) {
    x = random(10, 990);
    y = destY;
    w = 10;
    h = 10;
  }

  public void show() {
    fill(0xff030303);
    rect(x, y, w, h);
  }
}
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

  public void move() {
    x = x + Vel.x;

    if (x < 0 && Vel.x < 0) {
      Vel.x = -1*Vel.x;
    } else if (x + w > width && Vel.x > 0) {
      Vel.x = -1*Vel.x;
    }
  }
  public void show() {
    noStroke();
    rect(x, y, w, h);
  }
}
int life = 3;

class Lives {
  PVector Pos;
  Lives() {
    Pos = new PVector(0, 90);
  }

  public void show() {
    fill(0);
    text("Lives Left: "+life, Pos.x, Pos.y);
  }

  public void GameOver() {
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
class Quit {
  boolean on = false;
  float centreX, centreY, Length;
  Quit(float startX, float startY, float L) {
    on = false;
    centreX = startX;
    centreY = startY;
    Length = L;
  }
  public void show() {
    rect(centreX, centreY, Length, 30);
    if (on == true) {
      exit();
    }
  }

  public boolean contains(float x, float y) {
    if (dist(x, y, centreX, centreY) <= Length) {
      return true;
    } else {
      return false;
    }
  }
}
int score;
class Score {

  float x, y;

  Score() {
    x = 0;
    y = 40;
    textSize(25);
  }

  public void show() {
    fill(0);
    text("Score: " + score +" / 10", x, y);
  }

  public void win() {
    if (score == 10 && life >= 0) {
      theme.stop();
      fill(255);
      background(0xffE8CE05);
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
    g = 0.6f;
  }

  public void land(float destY) {
    speedY = 0;
    connected = true;
    y = destY - h;
  }

  public void collision() {
    x = width/2;
    y = 40;
    life--;
    //me.lose();
  }

  public void update() {
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

  public void show() {
    fill(255, 100, 0);
    rect(x, y, w, h);
  }
}
class Start {
  boolean on = false;
  float centreX, centreY, Length;

  Start(float startX, float startY, float L) {
    on = false;
    centreX = startX;
    centreY = startY;
    Length = L;
  }

  public void show() {
    rect(centreX, centreY, Length, 30);
    if (on == true) {
      mainScreen();
    }
  }

  public boolean contains(float x, float y) {
    if (dist(x, y, centreX, centreY) <= Length) {
      return true;
    } else {
      return false;
    }
  }
}
  public void settings() {  size(1000, 700); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "RageGame" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
