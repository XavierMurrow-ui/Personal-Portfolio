package Game;

import city.cs.engine.CollisionEvent;
import city.cs.engine.CollisionListener;
import city.cs.engine.Walker;

public class KillCollision implements CollisionListener {
    private MainCharacter player;
    private Enemy[] enemy;

    public KillCollision(MainCharacter Player, Enemy[] Enemy){
        this.player = Player;
        this.enemy = Enemy;
    }
    @Override
    public void collide(CollisionEvent e) {
        for(int i = 0; i<enemy.length;i++){
            if (e.getOtherBody() == enemy[i]) {
                enemy[i].Damage();
                player.Score();
                e.getReportingBody().destroy();
                if (enemy[i].getEnemyHealth() <= 0) {
                    e.getOtherBody().destroy();
                    e.getReportingBody().destroy();
                }
            } else if (e.getOtherBody() != enemy[i]) {
                e.getReportingBody().destroy();
            }
        }
    }
}
