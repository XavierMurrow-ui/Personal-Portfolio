/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import javax.swing.*;

/**
 *
 * @author 5403Murrow
 */
public class Main extends JFrame{
    
    private static final int FRAME_WIDTH = 400;
    private static final int FRAME_HEIGHT = 180;
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args){
        // TODO code application logic here
        
        MainInterface Main = new MainInterface();
        Main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Main.setSize(FRAME_WIDTH, FRAME_HEIGHT);
        Main.setVisible(true);
    }
}
        