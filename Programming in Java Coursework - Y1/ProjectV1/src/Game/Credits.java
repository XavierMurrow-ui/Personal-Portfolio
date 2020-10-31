package Game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Credits extends JFrame {
    private Font font;
    private JLabel title,credits, extra;
    private JButton Back;

    public Credits(){
        super("Credits");
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
        title = new JLabel("Credits");
        title.setFont(PixelFont());
        title.setBounds(420,-10,500,75);
        background.add(title);

        /** Credits **/
        credits = new JLabel("EVERYTHING WAS DONE OR SOURCED BY XAVIER MURROW, OTHER THAN");
        credits.setFont(PixelFont());
        credits.setBounds(20,-70,1000,550);
        background.add(credits);

        extra = new JLabel(" THE ENGINE WHICH WAS CREATED BY CITY, UNIVERSITY OF LONDON.");
        extra.setFont(PixelFont());
        extra.setBounds(20,-10,1000,550);
        background.add(extra);

        /** Back Button **/
        Back = new JButton("Back");
        Back.setFont(PixelFont());
        Back.setBounds(10,10,110,35);
        background.add(Back);

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
            font = Font.createFont(Font.TRUETYPE_FONT, new File("data/Pixel.ttf")).deriveFont(27f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(font);
        }catch(IOException | FontFormatException e){}
        return font;
    }
}
