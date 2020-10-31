package Game;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class GameLoader {
    private  String fileName, Username;
    private Game Game;
    private int Level;
    private int score;
    private int Health;

    public GameLoader(String fileName,Game game, String username) {
        this.fileName = fileName;
        this.Game = game;
        this.Username = username;

    }

    /**
     * Read the high-score data from the high-score file and print it to
     * the terminal window.
     */
    public void loadGame() throws IOException {
        FileReader fr = null;
        BufferedReader reader = null;
        try {
            fr = new FileReader(fileName);
            reader = new BufferedReader(fr);
            String line = reader.readLine();
                //retrieve data
            String[] tokens = line.split(",");
            String name = tokens[0];
            score = Integer.parseInt(tokens[1]);
            Level = Integer.parseInt(tokens[2]);
            Health = Integer.parseInt(tokens[3]);

            if(name.equals(Username)) {
                Game.levelSelect(Level);
                Game.setTotalScore(score);
                System.out.println(score);
                Game.setContinueHealth(Health);
            }
            System.out.println("Name: " + name + ", Score: " + score + ", Level: " + Level + ", Health: " + Health);
        } finally {
            if (reader != null) {
                reader.close();
            }
            if (fr != null) {
                fr.close();
            }
        }
    }

    public int getScore() {
        return score;
    }

    public int getHealth() {
        return Health;
    }
}
