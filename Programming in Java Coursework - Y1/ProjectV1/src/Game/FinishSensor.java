package Game;

import city.cs.engine.SensorEvent;
import city.cs.engine.SensorListener;
import com.sun.tools.javac.Main;

public class FinishSensor implements SensorListener {
    private MainCharacter Player;
    private Game Game;
    private Boolean Finished = false;

    public FinishSensor(MainCharacter player, Game game){
        this.Player = player;
        this.Game = game;
    }

    @Override
    public void beginContact(SensorEvent e) {
        if(e.getContactBody() == Player){
            Finished = true;
            Game.nextLevel();
        }else{
            Finished = false;
        }
    }

    @Override
    public void endContact(SensorEvent sensorEvent) {

    }

    public Boolean getFinished() {
        return Finished;
    }
}
