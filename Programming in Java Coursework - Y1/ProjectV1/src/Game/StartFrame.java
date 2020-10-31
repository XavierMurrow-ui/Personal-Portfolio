package Game;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.jar.JarEntry;

public class StartFrame extends JFrame {
    private Font font;
    private Game game;
    private JLabel title;
    private JButton Play;
    private JButton Options;
    private JButton Exit;

    public StartFrame(Game Game){
        super("StarMenu");
        this.game = Game;
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
        title = new JLabel("STICK SHOOTER");
        title.setFont(PixelFont());
        title.setBounds(320,50,500,75);
        background.add(title);

        /** Buttons **/
        Play = new JButton("Play");
        Play.setFont(PixelFont());
        Play.setBounds(420,200,150,50);
        background.add(Play);

        Options = new JButton("Options");
        Options.setFont(PixelFont());
        Options.setBounds(370,270,250,50);
        background.add(Options);

        Exit = new JButton("Exit");
        Exit.setFont(PixelFont());
        Exit.setBounds(420,340,150,50);
        background.add(Exit);

        /** Action Listeners**/
        Play.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                EnterName New = new EnterName();
                New.pack();
                New.setVisible(true);
            }
        });

        Options.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                Options New = new Options();
                New.pack();
                New.setVisible(true);
            }
        });

        Exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

    }

    public Font PixelFont(){
        try {
            font = Font.createFont(Font.TRUETYPE_FONT, new File("data/Pixel.ttf")).deriveFont(50f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(font);
        }catch(IOException | FontFormatException e){}
        return font;
    }
}
