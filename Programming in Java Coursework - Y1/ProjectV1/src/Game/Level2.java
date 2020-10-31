package Game;

import city.cs.engine.Body;
import city.cs.engine.BoxShape;
import city.cs.engine.Shape;
import city.cs.engine.StaticBody;
import org.jbox2d.common.Vec2;

import java.awt.*;

public class Level2 extends GameLevel {
    private Body[] platforms = new Body[3];
    private Body[] grounds = new Body[15];
    private int x = 0;
    private Shape platformShape = new BoxShape(5, 0.75f);
    private Shape groundShape = new BoxShape(10,0.75f);
    private Vec2 temp;

    public void populate(Game game){
        super.populate(game);

        //Ground
        for(int i = 0; i < grounds.length; i++){
            grounds[i] = new StaticBody(this, groundShape);
            grounds[i].setFillColor(Color.LIGHT_GRAY);
            grounds[i].setPosition(new Vec2(-50+(i*10),-12.5f-(i*1.5f)));
        }

        //Enemy Platform
        for(int i = 0; i < platforms.length; i++) {
            platforms[i] = new StaticBody(this, platformShape);
            platforms[i].setFillColor(Color.LIGHT_GRAY);
            platforms[i].setLineColor(Color.LIGHT_GRAY);
            platforms[i].setPosition(new Vec2(-10+(i*20), -5));
        }

        //coin = new Coin(this);
        //coin.setPosition(platforms[2].getPosition());
    }
    @Override
    public Vec2 PlayerPosition() {
        return new Vec2(-50,-9.5f);
    }

    @Override
    public Vec2 EnemyPosition() {
        return new Vec2(-10,-1.9f);
    }

    @Override
    public boolean isComplete() {
        for(int i = 0; i<enemyAmount(); i++) {
            if (getEnemy()[i].getEnemyHealth() == 0 && getFinished() == true) {
                return true;
            }
        }
        return false;
    }

    @Override
    public int enemyAmount() {
        return 3;
    }

    @Override
    public int enemyHealth() {
        return 100;
    }

    @Override
    public int damage() {
        return 50;
    }

    @Override
    public Vec2 FinishPosition() {
        return new Vec2(120,-34f);
    }

    @Override
    public int LevelNumber() {
        return 2;
    }
}
