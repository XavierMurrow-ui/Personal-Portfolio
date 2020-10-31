/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author xavmu
 */
public class Interface extends JFrame{
    
    private final JTextField Field,Field1;
    private final JLabel Title,Label;
    private final JButton Button,Enter; 
    private static final int FRAME_WIDTH = 400;
    private static final int FRAME_HEIGHT = 180;
    
    public Interface(){
        super("Timetable");
        setLayout(new FlowLayout());
        setResizable(false);
        
        Title = new JLabel("Timetable");
        add(Title);
        
        Label = new JLabel("Please enter your name below without spaces then press enter.");
        add(Label);
        
        Field = new JTextField(20);
        Field.setToolTipText("Enter firstname here");
        add(Field);
        
        Field1 = new JTextField(20);
        Field1.setToolTipText("Enter surname here");
        add(Field1);
        
        Button = new JButton("Home");
        Button.setToolTipText("Click to go home");
        add(Button);
        
        Enter = new JButton("Enter");
        Enter.setToolTipText("Press this to die");
        add(Enter);
        
        Enter Action = new Enter();
        Field.addActionListener(Action);
        Field1.addActionListener(Action);
        Button.addActionListener(Action);
        Enter.addActionListener(Action);
        
        
    }
    
    private class Enter implements ActionListener{
        
        @Override
        public void actionPerformed(ActionEvent event){
            String Message="Please press ok ";
            String Fullname = "";
            String Surname = "";
            
            if(event.getSource()==Button){
                MainInterface Main = new MainInterface();
                Main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Main.setSize(FRAME_WIDTH, FRAME_HEIGHT);
                Main.setVisible(true);
                dispose();
            }else if(event.getSource()==Enter){
                Fullname = Field.getText();
                Surname = Field1.getText();
                Field.setText("");
                JOptionPane.showMessageDialog(null,Message+Fullname);
                 try {
                     GUI fullname = new GUI(Fullname,Surname);
                } catch (SQLException ex) {
                     Logger.getLogger(Interface.class.getName()).log(Level.SEVERE, null, ex);
                } catch (InterruptedException ex) {
                     Logger.getLogger(Interface.class.getName()).log(Level.SEVERE, null, ex);
                }
                dispose();
            } 
            
            
            
        }
    }
}
