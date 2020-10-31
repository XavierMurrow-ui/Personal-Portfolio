package Game;

import org.jbox2d.common.Vec2;

public class Level extends GameLevel {

    @Override
    public Vec2 PlayerPosition() {
        return new Vec2(05,50);
    }

    @Override
    public Vec2 EnemyPosition() {
        return new Vec2();
    }

    @Override
    public boolean isComplete() {
        return false;
    }

    @Override
    public int enemyAmount() {
        return 1;
    }

    @Override
    public int enemyHealth() {
        return 0;
    }

    @Override
    public int damage() {
        return 0;
    }

    @Override
    public Vec2 FinishPosition() {
        return new Vec2();
    }

    @Override
    public int LevelNumber() {
        return 0;
    }
}
