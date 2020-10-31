package Game;

import city.cs.engine.UserView;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class EnterName extends JFrame {
    private Font font;
    private JLabel title;
    private JTextField Text;
    private JButton enter;
    private String Username = "";

    public EnterName(){
        super("EnterName");
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
        title = new JLabel("Username");
        title.setFont(PixelFont());
        title.setBounds(400,10,500,75);
        background.add(title);

        /** Text Field**/
        Text = new JTextField();
        Text.setFont(PixelFont());
        Text.setBounds(320,150,300,50);
        background.add(Text);

        /** Button **/
        enter = new JButton("Enter");
        enter.setFont(PixelFont());
        enter.setBounds(650,150,150,50);
        background.add(enter);

        /** ActionListeners **/
        enter.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Username = Text.getText();
                System.out.println(Username);
                dispose();
                new Game(Username);
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

    public String getUsername() {
        return Username;
    }

    public String getText() {
        return Text.getText();
    }
}
