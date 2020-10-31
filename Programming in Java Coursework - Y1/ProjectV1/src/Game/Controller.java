package Game;

import city.cs.engine.*;
import org.jbox2d.common.Vec2;

import javax.management.ValueExp;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.IOException;
import java.security.Key;
import java.util.TimerTask;
import java.util.concurrent.TimeUnit;

/**
 * Key handler to control an Walker.
 */
public class Controller extends KeyAdapter {
    private static final float JUMPING_SPEED = 10;//Jumping Speed of character
    private static final float WALKING_SPEED = 10;//Walking Speed of character
    private MainCharacter body;
    private Enemy[] enemy;
    private Bullets bullets;
    private GameLevel world;
    private Game game;
    private String username;
    private ActionListener taskPerformer = new ActionListener() {
        @Override
        public void actionPerformed(ActionEvent e) {
            Sounds.getShot().play();
            for(int i = 0; i < world.enemyAmount(); i++) {
                bullets = new Bullets(world, body, enemy,null, game,1);
                if(body.getPosition().x > enemy[i].getPosition().x) {
                    enemy[i].removeAllImages();
                    enemy[i].addImage(new BodyImage("data/GunManLeft.png",5));
                    bullets.setPosition(new Vec2(enemy[i].getPosition().x+5,enemy[i].getPosition().y));
                }else if(body.getPosition().x < enemy[i].getPosition().x){
                    enemy[i].removeAllImages();
                    enemy[i].addImage(new BodyImage("data/GunManRight.png",5));
                    bullets.setPosition(new Vec2(enemy[i].getPosition().x-5,enemy[i].getPosition().y));
                }if(enemy[i].getEnemyHealth() <= 0){
                    bullets.setLinearVelocity(new Vec2(0,0));
                    bullets.destroy();
                    Sounds.getShot().stop();
                }
            }
        }
    };
    private Timer timer = new Timer(1000,taskPerformer);

    // Constructor //
    public Controller(MainCharacter body, GameLevel world, Enemy[] enemy, Game game, String username) {
        this.username = username;
        this.body = body;
        this.world = world;
        this.enemy = enemy;
        this.game = game;
        timer.start();
    }
    
    /**
     * Handle key press events for walking and jumping.
     * @param e description of the key event
     */
    @Override
    public void keyPressed(KeyEvent e) {
        int code = e.getKeyCode();
        if (code == KeyEvent.VK_SPACE || code == KeyEvent.VK_W || code == KeyEvent.VK_UP) { // Space = jump
            Vec2 v = body.getLinearVelocity();
            // only jump if body is not already jumping
            if (Math.abs(v.y) < 0.01f) {
                body.setGravityScale(1);
                body.jump(JUMPING_SPEED);
            }
        } else if (code == KeyEvent.VK_A || code == KeyEvent.VK_LEFT) {
            body.startWalking(-WALKING_SPEED); // A or right arrow = walk left
            body.removeAllImages();//removes images from character
            body.addImage(new BodyImage("data/RUN3.gif", 5));//adds image to character
        } else if (code == KeyEvent.VK_D || code == KeyEvent.VK_RIGHT) {
            body.startWalking(WALKING_SPEED); // D or right arrow = walk right
            body.removeAllImages();
            body.addImage(new BodyImage("data/RUN2.gif", 5));
        }else if(code == KeyEvent.VK_S){
            GameSaver score = new GameSaver("data/Score.txt");
            try{
                score.saveGame(username,body.getScore(),world.LevelNumber(),body.getHealth());
            }catch(IOException ex){
                ex.printStackTrace();
            }
        }
    }
    
    /**
     * Handle key release events (stop walking).
     * @param e description of the key event
     */
    @Override
    public void keyReleased(KeyEvent e) {
        int code = e.getKeyCode();
        if (code == KeyEvent.VK_A || code == KeyEvent.VK_LEFT ) {
            body.stopWalking();
            body.removeAllImages();
            body.addImage(new BodyImage("data/Stick3.png", 5));
        } else if (code == KeyEvent.VK_D || code == KeyEvent.VK_RIGHT) {
            body.stopWalking();
            body.removeAllImages();
            body.addImage(new BodyImage("data/Stick3.png", 5));
        }
    }

    public void setWorld(GameLevel world) {
        this.world = world;
    }

    public void setBody(MainCharacter body) {
        this.body = body;
    }

    public void setEnemy(Enemy[] enemy) {
        this.enemy = enemy;
    }

    public Bullets getBullets() {
        return bullets;
    }
}

