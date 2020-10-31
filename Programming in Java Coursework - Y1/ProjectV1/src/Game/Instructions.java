package Game;

import javax.swing.*;
import javax.swing.plaf.TextUI;
import javax.swing.text.JTextComponent;
import javax.swing.text.Style;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Instructions extends JFrame {
    private JLabel title;
    private Font font;
    private JLabel[] Instructions = new JLabel[3];
    private JButton Back;

    public Instructions(){
        super("Instructions");
        this.setSize(1000,500);
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new GridLayout());

        /** Background **/
        JLabel background = new JLabel();
        background.setIcon(new ImageIcon("data/Background.png"));
        this.add(background);
        background.setLayout(null);

        /** Titles **/
        title = new JLabel("Instructions");
        title.setFont(PixelFont());
        title.setBounds(430,-13,500,75);
        background.add(title);

        /** Buttons **/
        Back = new JButton("Back");
        Back.setFont(PixelFont());
        Back.setBounds(10,10,110,35);
        background.add(Back);

        /** Text **/
        for(int i = 0; i < Instructions.length; i++) {
            Instructions[0] = new JLabel("\u2022 USE AD OR LEFT AND RIGHT ARROW KEYS FOR MOVEMENT.");
            Instructions[1] = new JLabel("\u2022 USE SPACEBAR, W OR THE UP ARROW FOR JUMP.");
            Instructions[2] = new JLabel("\u2022 TO SAVE THE GAME PAUSE THE GAME AND PRESS THE SAVE BUTTON.");
            Instructions[i].setFont(PixelFont());
            Instructions[i].setBounds(10, -150 + (i*90), 1000, 500);
            background.add(Instructions[i]);
        }

        /** Action Listener **/
        Back.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                Options New = new Options();
                New.pack();
                New.setVisible(true);
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
