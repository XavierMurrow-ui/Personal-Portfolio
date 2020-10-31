package Game;

import city.cs.engine.CollisionEvent;
import city.cs.engine.CollisionListener;

public class BulletCollision implements CollisionListener {
    private MainCharacter body;
    private Enemy enemy;

    public BulletCollision(MainCharacter body, Enemy enemy){
        this.body = body;
        this.enemy = enemy;
    }
    @Override
    public void collide(CollisionEvent e) {
        if(e.getOtherBody() == body){
            body.decreaseHealth();//decreases character life
            e.getReportingBody().destroy();//destroy bullet
        }
            if (e.getOtherBody() != enemy) {
                e.getReportingBody().destroy();
            }
    }
}
