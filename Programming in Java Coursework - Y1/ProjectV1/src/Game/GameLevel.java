package Game;

import city.cs.engine.*;
import city.cs.engine.Shape;
import com.sun.tools.javac.Main;
import org.jbox2d.common.Vec2;

import javax.management.ValueExp;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import java.util.TimerTask;
import java.util.Timer;

public abstract class GameLevel extends World {
    private MainCharacter player;
    private Enemy[] enemy = new Enemy[enemyAmount()];
    private FinishSensor Sensor;

    public void populate(Game game) {
        //Sound
        Sounds.getBackground().loop();

        //Character
        player = new MainCharacter(this);
        player.setPosition(PlayerPosition());
        if(PlayerPosition().y < FinishPosition().y){
            game.Restart();
            player.setHealth(5);
        }

        // Enemy
        for(int i = 0; i < enemyAmount(); i++) {
            enemy[i] = new Enemy(this);
            //Adds a reference to the a collision listener
            enemy[i].setPosition(new Vec2(EnemyPosition().x+(i*20),EnemyPosition().y));
            enemy[i].setEnemyHealth(enemyHealth());
            enemy[i].removeAllImages();//Removes all images on this body
            enemy[i].addImage(new BodyImage("data/GunManRight.png", 5));//Adds an image to this body
            enemy[i].setWeaponDamage(damage());

            //FinishSensor
            Shape circle = new CircleShape(0.2f);
            Body sensor = new StaticBody(this, circle);
            sensor.addImage(new BodyImage("data/Flag.gif",10));
            Sensor Finish = new Sensor(sensor,circle);
            Sensor = new FinishSensor(getPlayer(),game);
            Finish.addSensorListener(Sensor);
            sensor.setPosition(new Vec2(FinishPosition().x,FinishPosition().y+5));
            Shape finishShape = new BoxShape(5,0.75f);
            Body finishPlatform = new StaticBody(this, finishShape);
            finishPlatform.setFillColor(Color.LIGHT_GRAY);
            finishPlatform.setPosition(FinishPosition());
        }
    }

    public MainCharacter getPlayer(){
        return player;
    }
    public Enemy[] getEnemy(){
        return enemy;//Used to add things to the enemy in the main class
    }
    public Boolean getFinished(){ return Sensor.getFinished();}
    public abstract Vec2 PlayerPosition();
    public abstract Vec2 EnemyPosition();
    public abstract boolean isComplete();
    public abstract int enemyAmount();
    public abstract int enemyHealth();
    public abstract int damage();
    public abstract Vec2 FinishPosition();
    public abstract int LevelNumber();
}
