package Game;

import city.cs.engine.*;
import city.cs.engine.Shape;
import org.jbox2d.common.Vec2;

import java.awt.*;

public class GameWorld extends World {
    private MainCharacter stick;//Instance of MainCharacter class
    private Enemy[] enemy = new Enemy[2];//Array instance of Enemy class

    public GameWorld() {
        super();

        //Ground
        Shape groundShape = new BoxShape(50, 0.75f);//Creates the shape for the ground
        Body ground = new StaticBody(this, groundShape);//This adds the shape to a body so that physical properties can be added
        ground.setFillColor(Color.LIGHT_GRAY);//Sets the fill colour
        ground.setLineColor(Color.LIGHT_GRAY);//Sets the line colour
        ground.setPosition(new Vec2(0, -12.5f));

        /*
        //Platforms
        Shape platformShape = new BoxShape(5,0.75f);
        Body platform = new StaticBody(this, platformShape);
        platform.setPosition(new Vec2(15, 0));

        Shape platformShape2 = new BoxShape(5,0.75f);
        Body platform2 = new StaticBody(this, platformShape2);
        platform2.setPosition(new Vec2(15, 0));
         */

        // Character
        stick = new MainCharacter(this);//Initialises the instance above
        stick.setPosition(new Vec2(0, -9.5f));//Sets the position of the shape within the world

        /* FUTURE CODE
        //Sensor
        Shape circle = new CircleShape(0.2f);
        Body sensor = new StaticBody(this, circle);
        Sensor test = new Sensor(sensor,circle);
        sensor.setPosition(new Vec2(-5,-9.5f));
        for(int i = 0; i<6; i++) {
            test.addSensorListener(new Target(enemy[i]));
        }
         */
    }

    public MainCharacter getPlayer() {
        return stick;//Used to add things to the character in the main class
    }

    public Enemy[] getEnemy(){
        return enemy;//Used to add things to the enemy in the main class
    }
}


