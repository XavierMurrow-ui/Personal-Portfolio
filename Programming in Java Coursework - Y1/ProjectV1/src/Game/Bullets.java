package Game;

import city.cs.engine.*;
import org.jbox2d.common.Vec2;

import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

public class Bullets extends DynamicBody {
    private MainCharacter player;
    private Enemy[] enemies;
    private Vec2 mouse;
    private Game game;
    private Vec2 v;

    private static final Shape BulletShape = new BoxShape(0.3f, 0.2f);//Shape for the bullet
    private BodyImage Bullet = new BodyImage("data/Bullet.png", 0.2f);//Image for the bullet

    public Bullets(World world, MainCharacter Player, Enemy[] enemy, Vec2 Mouse,Game game, int i) {
        super(world, BulletShape);
        this.player = Player;
        this.enemies = enemy;
        this.mouse = Mouse;
        this.game = game;
        addImage(Bullet);
        setGravityScale(0);
        velocity(i);
    }

    public void velocity(int number) {
        if (number == 0) {
            addCollisionListener(new KillCollision(player, enemies));
            this.setLinearVelocity((mouse.sub(player.getPosition().add(new Vec2(5,0)))).mul(5));
        }else if(number == 1){
            for(int i = 0; i<enemies.length; i++) {
                addCollisionListener(new BulletCollision(player, enemies[i]));
                Vec2 e = enemies[i].getPosition();
                Vec2 p = player.getPosition();
                v = p.sub(e);
                v.normalize();
                v = v.mul(40.0f);
                setLinearVelocity(v);
            }
        }
    }
}
