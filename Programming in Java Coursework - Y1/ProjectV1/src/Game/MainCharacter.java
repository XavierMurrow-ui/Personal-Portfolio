package Game;

import city.cs.engine.*;

public class MainCharacter extends Walker{
    private int Health = 10;//Character Health
    private int score;
    private static Shape hitBox = new PolygonShape(5*-0.11f,5*0.482f,5*0.134f,5*0.482f,5*0.222f,5*-0.01f,5*0.196f,5*-0.46f,5*-0.198f,5*-0.462f,5*-0.222f,5*-0.018f,5*-0.112f,5*0.482f);//Shape for character
    private BodyImage stickMan = new BodyImage("data/Stick3.png", 5);//image for character
    public MainCharacter(World world) {
        super(world, hitBox);
        addImage(stickMan);
    }

    public void decreaseHealth(){
        Health = Health - 1;
        System.out.println("Your health is: "+Health);
        if(Health <= 0){
            System.out.println("GAME OVER");
            System.exit(0);//stops program
        }

    }

    public void Score(){
        score+=10;
    }

    public int getHealth() {
        return Health;
    }

    public void setHealth(int health) {
        Health = health;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }
}
