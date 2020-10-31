package Game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Options extends JFrame {
    private Font font;
    private JLabel title;
    private JButton Sound;
    private JButton Instructions;
    private JButton Credits;
    private JButton Back;
    private StartFrame Start;

    public Options(){
        super("Options");
        this.setSize(1000,500);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new FlowLayout());

        /** Background **/
        JLabel background = new JLabel();
        background.setIcon(new ImageIcon("data/Background.png"));
        this.add(background);
        background.setLayout(null);

        /** Title **/
        title = new JLabel("Options");
        title.setFont(PixelFont());
        title.setBounds(450,30,500,75);
        background.add(title);

        /** Buttons **/
        Sound = new JButton("Sound");
        Sound.setFont(PixelFont());
        Sound.setBounds(440,140,130,50);
        background.add(Sound);

        Instructions = new JButton("Instructions");
        Instructions.setFont(PixelFont());
        Instructions.setBounds(390,220,245,50);
        background.add(Instructions);

        Credits = new JButton("Credits");
        Credits.setFont(PixelFont());
        Credits.setBounds(430,300,150,50);
        background.add(Credits);

        Back = new JButton("Back");
        Back.setFont(PixelFont());
        Back.setBounds(10,10,110,35);
        background.add(Back);

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

        Instructions.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Instructions New = new Instructions();
                New.pack();
                New.setVisible(true);
            }
        });

        Credits.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Credits New = new Credits();
                New.pack();
                New.setVisible(true);
            }
        });

        Back.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                new Game(Start);
            }
        });
    }

    public Font PixelFont(){
        try {
            font = Font.createFont(Font.TRUETYPE_FONT, new File("data/Pixel.ttf")).deriveFont(30f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(font);
        }catch(IOException | FontFormatException e){}
        return font;
    }
}
