package Game;

import java.io.FileWriter;
import java.io.IOException;

public class GameSaver {

    private String fileName;

    public GameSaver(String fileName) {
        this.fileName = fileName;
    }

    public void saveGame(String name, int score,int Level, int Health) throws IOException {
        boolean append = true;
        FileWriter writer = null;
        try {
            //if() {
                writer = new FileWriter(fileName);
            //}
            writer.write(name + "," + score + ","+ Level + "," + Health +"\n");
        } finally {
            if (writer != null) {
                writer.close();
            }
        }
    }
}
