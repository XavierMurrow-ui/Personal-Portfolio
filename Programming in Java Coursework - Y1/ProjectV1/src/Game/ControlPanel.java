package Game;

import city.cs.engine.UserView;
import city.cs.engine.World;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ControlPanel {
    private UserView View;
    private JButton Pause,Restart,Exit;
    private JPanel Menu = new JPanel();
    private GameLevel World;
    private Game Game;
    private String username;

    public ControlPanel(UserView view, GameLevel world, Game game, String Username){
        this.View = view;
        this.World = world;
        this.Game = game;
        this.username = Username;

        Menu.setSize(1000,35);

        /** Background **/
        JLabel background = new JLabel();
        background.setIcon(new ImageIcon("data/PanelBackground.png"));
        Menu.add(background);
        background.setSize(1000,35);
        background.setLayout(new FlowLayout());

        //Pause Button
        Pause = new JButton("Pause");
        Pause.setFocusable(false);
        background.add(Pause);

        //Restart Button
        Restart = new JButton("Restart");
        Restart.setFocusable(false);
        background.add(Restart);

        //Exit Button
        Exit = new JButton("Exit");
        Exit.setFocusable(false);
        background.add(Exit);

        Pause.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                PauseMenu menu = new PauseMenu(username,World,Game);

                if (View.getWorld().isRunning()) {
                    View.getWorld().stop();
                    Pause.setText("  Play ");
                    //Sound
                    Sounds.getShot().setVolume(0.0001);
                    Sounds.getBackground().setVolume(0.3);

                    //Menu
                    menu.setVisible(true);
                } else {
                    View.getWorld().start();
                    Pause.setText("Pause");

                    //Sound
                    Sounds.getBackground().setVolume(1);
                    Sounds.getShot().setVolume(1);

                    //Menu
                    menu.setVisible(false);
                }
            }
        });

        Exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        Restart.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Game.Restart();
            }
        });
    }

    public JPanel getMainPanel(){
        return Menu;
    }
}
