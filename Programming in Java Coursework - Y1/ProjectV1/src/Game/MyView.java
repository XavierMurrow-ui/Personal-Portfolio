package Game;

import city.cs.engine.BoxShape;
import city.cs.engine.UserView;
import city.cs.engine.World;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class MyView extends UserView {
    private Image background;
    private Font font;
    private MainCharacter Player;
    private Enemy[] Enemy;
    private GameLevel Game;
    public MyView(World w, int width, int height, MainCharacter player, Enemy[] enemy, GameLevel game) {
        super(w, width, height);
        this.Game = game;
        this.Player = player;
        this.Enemy = enemy;
        this.background = new ImageIcon("data/Background.png").getImage();
    }

    @Override
    protected void paintBackground(Graphics2D g){
        g.drawImage(background,0,0,this);
    }

    @Override
    protected void paintForeground(Graphics2D g) {
        g.setFont(PixelFont());
        g.drawString("HP: "+Player.getHealth(),40,40);
        g.drawString("SCORE: "+Player.getScore(), 450,40);
         for(int i = 0; i <Enemy.length; i++) {
            int health = Enemy[(Enemy.length-1) - i].getEnemyHealth() + Enemy[i].getEnemyHealth();
            g.drawString("ENEMY HP: " + (health), 750, 40);
        }
    }

    public Font PixelFont(){
        try {
            font = Font.createFont(Font.TRUETYPE_FONT, new File("data/Pixel.ttf")).deriveFont(30f);
            GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
            ge.registerFont(font);
        }catch(IOException | FontFormatException e){}
        return font;
    }

    public void setPlayer(MainCharacter player) {
        Player = player;
    }

    public void setEnemy(Enemy[] enemy) {
        Enemy = enemy;
    }

    public void setGame(GameLevel game) {
        Game = game;
    }
}
