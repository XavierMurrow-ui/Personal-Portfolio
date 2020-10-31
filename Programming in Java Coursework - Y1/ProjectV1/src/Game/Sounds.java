package Game;

import city.cs.engine.SoundClip;

import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import java.io.IOException;

public class Sounds {

    private static SoundClip shot;
    private static SoundClip background;

    static{
        try {
            shot = new SoundClip("data/Shooting.wav");
            background = new SoundClip("data/Background.wav");
        } catch (UnsupportedAudioFileException | IOException | LineUnavailableException ex) {
            ex.printStackTrace();
        }
    }

    public static SoundClip getShot() {
        return shot;
    }

    public static SoundClip getBackground() {
        return background;
    }
}
