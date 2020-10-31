/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 *
 * @author xavmu
 */
public class MainInterface extends JFrame {//Class that contains the JFrame
    
    private static final int FRAME_WIDTH = 500,FRAME_HEIGHT = 180,HOME_HEIGHT = 500,
            HOME_WIDTH = 400,FACE_HEIGHT = 350,FACE_WIDTH = 850;
    private final JLabel Title, text;
    private final JButton Tbutton,Hbutton,Fbutton;
    
    public MainInterface(){//JFrame constuctor
        
        super("Student Helper");//Title of the frame
        setLayout(new FlowLayout());//layout of the internals of the frame
        setResizable(false);
        
        Title = new JLabel("Student Helper");//The programme title
        add(Title);//Adds the JLabel to the JFrame
        
        text = new JLabel("Hello, please click one of the buttons below. Thank you!");
        add(text);
        
        Tbutton = new JButton("Timetable");//A JButton for the timetable function
        Tbutton.setToolTipText("Click here to see timetable");
        add(Tbutton);
        
        Hbutton = new JButton("Homework");//A JButton for the Homework function
        Hbutton.setToolTipText("Click here to see homework");
        add(Hbutton);
        
        Fbutton = new JButton("Friend");
        Fbutton.setToolTipText("Click here to use Friend");
        add(Fbutton);
        
        Button FAction = new Button();//Calls the class to take this variable
        Tbutton.addActionListener(FAction);//How to implement an action listener
        Hbutton.addActionListener(FAction);
        Fbutton.addActionListener(FAction);
    }
    
    private class Button implements ActionListener{
        
        @Override
        public void actionPerformed(ActionEvent e){
            
            if(e.getSource()==Tbutton){
                Interface Table = new Interface();
                Table.setSize(FRAME_WIDTH, FRAME_HEIGHT);
                Table.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Table.setVisible(true);
                dispose();
            } else if(e.getSource()==Hbutton){   
                HInterface Home = new HInterface();
                Home.setSize(HOME_WIDTH, HOME_HEIGHT);
                Home.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Home.setVisible(true);
                dispose();
            } else if(e.getSource() == Fbutton){
                Friend Face = new Friend();
                Face.setSize(FACE_WIDTH, FACE_HEIGHT);
                Face.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Face.setVisible(true);
                dispose();
            }
        }
    }
    
    
}
