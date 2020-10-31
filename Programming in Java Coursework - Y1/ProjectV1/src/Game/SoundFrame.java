package Game;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class SoundFrame extends JFrame {
    private JLabel title, master,Music,SFX;
    private Font font;
    private JSlider Master, music, sfx;
    private JButton mute, Back;
    private float sfxVolume;

    public SoundFrame(){
        super("StarMenu");
        this.setSize(1000,500);
        this.setLocationRelativeTo(null);
        this.setLayout(new GridLayout());

        /** Background **/
        JLabel background = new JLabel();
        background.setIcon(new ImageIcon("data/Background.png"));
        this.add(background);
        background.setLayout(null);

        /** Titles **/
        title = new JLabel("Sound");
        title.setFont(PixelFont());
        title.setBounds(430,-13,500,75);
        background.add(title);

        master = new JLabel("Master Sound");
        master.setFont(PixelFont());
        master.setBounds(360,50,500,75);
        background.add(master);

        Music = new JLabel("Music Sound");
        Music.setFont(PixelFont());
        Music.setBounds(380,150,500,75);
        background.add(Music);

        SFX = new JLabel("SFX Sound");
        SFX.setFont(PixelFont());
        SFX.setBounds(400,240,500,75);
        background.add(SFX);

        /** Buttons/sliders **/
        Master = new JSlider();
        Master.setFont(PixelFont());
        Master.setBounds(350,120,300,25);
        background.add(Master);

        music = new JSlider();
        music.setFont(PixelFont());
        music.setBounds(350,210,300,25);
        background.add(music);

        sfx = new JSlider();
        sfx.setFont(PixelFont());
        sfx.setBounds(350,300,300,25);
        background.add(sfx);

        mute = new JButton("Mute");
        mute.setFont(PixelFont());
        mute.setBounds(430,350,140,50);
        background.add(mute);

        Back = new JButton("Back");
        Back.setFont(PixelFont());
        Back.setBounds(10,10,110,35);
        background.add(Back);

        /** Action Listeners **/
        Back.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                Options New = new Options();
                New.pack();
                New.setVisible(true);
            }
        });

        Master.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                float mastVolume = scale((float) Master.getValue(), 1.0f,100.0f,0.0001f,2.0f);
                Sounds.getShot().setVolume(mastVolume);
                Sounds.getBackground().setVolume(mastVolume);
            }
        });

        music.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                float musVolume = scale((float) music.getValue(), 1.0f,100.0f,0.0001f,2.0f);
                Sounds.getBackground().setVolume(musVolume);
            }
        });

        sfx.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                sfxVolume = scale((float) sfx.getValue(), 1.0f,100.0f,0.0001f,2.0f);
                Sounds.getShot().setVolume(sfxVolume);
            }
        });

        mute.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Sounds.getShot().setVolume(0.0001);
                Sounds.getBackground().setVolume(0.0001);
                Master.setValue(1);
                music.setValue(1);
                sfx.setValue(1);
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

    public float scale(float value, float minInput, float maxInput, float minRange, float maxRange){
        return ((maxRange - minRange)*(value - minInput) / (maxInput - minInput)) + minRange;
    }

    public float getSfxVolume() {
        return sfxVolume;
    }
}
