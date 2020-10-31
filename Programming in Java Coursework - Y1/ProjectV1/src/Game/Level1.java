package Game;

import city.cs.engine.*;
import city.cs.engine.Shape;
import org.jbox2d.common.Vec2;

import java.awt.*;

public class Level1 extends GameLevel {

    public void populate(Game game){
        super.populate(game);

        //Ground
        Shape groundShape = new BoxShape(50, 0.75f);//Creates the shape for the ground
        Body ground = new StaticBody(this, groundShape);//This adds the shape to a body so that physical properties can be added
        ground.setFillColor(Color.LIGHT_GRAY);
        //ground.addImage(new BodyImage("data/GroundLong2.png"));
        ground.setPosition(new Vec2(0, -12.5f));

        //Enemy Platform
        Shape platformShape = new BoxShape(5,0.75f);
        Body platform1 = new StaticBody(this, platformShape);
        Body platform2 = new StaticBody(this, platformShape);
        platform1.setPosition(new Vec2(-10, -5));
        platform2.setPosition(new Vec2(10,-5));
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
        return 2;
    }

    @Override
    public int enemyHealth() {
        return 50;
    }

    @Override
    public int damage() {
        return 50;
    }

    @Override
    public Vec2 FinishPosition() {
        return new Vec2(50,-12.5f);
    }

    @Override
    public int LevelNumber() {
        return 1;
    }
}
