package Game;

import city.cs.engine.Walker;
import city.cs.engine.World;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class PauseMenu extends JFrame {
    private Font font;
    private JLabel title;
    private JButton Sound, Save, Load, Exit;
    private String username;
    private GameLevel World;
    private Game Game;
    GameSaver Saver = new GameSaver("data/Score.txt");

    public PauseMenu(String Username, GameLevel world, Game game){
        super("PauseMenu");
        this.setSize(400,250);
        this.setLocationRelativeTo(null);
        this.setLayout(new FlowLayout());

        this.username = Username;
        this.World = world;
        this.Game = game;

        /** Titles **/
        title = new JLabel("Paused");
        title.setFont(PixelFont());
        this.add(title);

        /** Buttons **/
        Sound = new JButton("Sound");
        Sound.setFont(PixelFont());
        this.add(Sound);

        Save = new JButton("Save");
        Save.setFont(PixelFont());
        this.add(Save);

        Load = new JButton("Load");
        Load.setFont(PixelFont());
        this.add(Load);

        Exit = new JButton("Exit");
        Exit.setFont(PixelFont());
        this.add(Exit);

        /** Action Listeners **/
        Sound.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                SoundFrame New = new SoundFrame();
                New.pack();
                New.setVisible(true);
            }
        });

        Save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    Saver.saveGame(username,World.getPlayer().getScore(),World.LevelNumber(),World.getPlayer().getHealth());
                }catch(IOException ex){
                    ex.printStackTrace();
                }
            }
        });

        Load.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                GameLoader test = new GameLoader("data/Score.txt",Game,username);
                try {
                    dispose();
                    test.loadGame();
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        Exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try{
                    Saver.saveGame(username, World.getPlayer().getScore(),World.LevelNumber(),World.getPlayer().getHealth());
                }catch(IOException ex){
                    ex.printStackTrace();
                }
                System.exit(0);
            }
        });

    }

    public Font PixelFont(){
        try {
            font = Font.createFont(Font.TRUETYPE_FONT, new File("data/Pixel.ttf")).deriveFont(40f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(font);
        }catch(IOException | FontFormatException e){}
        return font;
    }
}
