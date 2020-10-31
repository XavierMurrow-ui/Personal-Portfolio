package Game;

import city.cs.engine.*;
import org.jbox2d.common.Vec2;

import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;

public class MouseHandler extends MouseAdapter {

    private WorldView view;
    private MainCharacter body;
    private Enemy[] enemy;
    private GameLevel world;
    private Bullets bullet;
    private Game game;
    private Vec2 Mouse;

    public MouseHandler(WorldView view, MainCharacter body) {
        this.view = view;
        this.body = body;
    }

    public MouseHandler(WorldView view){
        this.view = view;
    }

    public MouseHandler(WorldView view, GameLevel world, MainCharacter Player, Enemy[] Enemy, Game game){
        this.view = view;
        this.world = world;
        this.body = Player;
        this.enemy = Enemy;
        this.game = game;
    }

    @Override
    public void mousePressed(MouseEvent e) {
        Sounds.getShot().play();
        Mouse = view.viewToWorld(e.getPoint());
       bullet = new Bullets(world,body,enemy,Mouse,game,0);
       if(Mouse.x > body.getPosition().x) {
           bullet.setPosition(new Vec2(body.getPosition().x + 5, body.getPosition().y));
       }else if(Mouse.x < body.getPosition().x){
           bullet.setPosition(new Vec2(body.getPosition().x -5, body.getPosition().y));
       }
    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    public Vec2 getMouse() {
        return Mouse;
    }
}
