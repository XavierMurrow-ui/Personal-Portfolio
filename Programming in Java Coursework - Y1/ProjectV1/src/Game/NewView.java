package Game;

import city.cs.engine.StepEvent;
import city.cs.engine.StepListener;
import city.cs.engine.World;
import city.cs.engine.WorldView;
import org.jbox2d.common.Vec2;

public class NewView implements StepListener {
    private WorldView world;
    private MainCharacter body;

    public NewView(WorldView world, MainCharacter body){
        this.world = world;
        this.body = body;
    }

    @Override
    public void preStep(StepEvent stepEvent) {

    }

    @Override
    public void postStep(StepEvent e) {
        world.setView(new Vec2(body.getPosition().x,body.getPosition().y  + 15),10);
    }

    public void setBody(MainCharacter body) {
        this.body = body;
    }

    public void setWorld(WorldView world) {
        this.world = world;
    }
}
