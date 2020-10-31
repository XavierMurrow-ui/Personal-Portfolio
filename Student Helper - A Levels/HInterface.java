/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;
/**
 *
 * @author xavmu
 */
public class HInterface extends JFrame {
    
    private final JTextArea Area;
    private final JTextField Field, Field1;
    private final JScrollPane Pane;
    private final JButton Enter,Home;
    private final JComboBox Box = new JComboBox();
    
    public HInterface(){
        
        super("Homework");
        setLayout(new FlowLayout());
        setResizable(false);
        
        Area = new JTextArea(100, 30);
        Area.setEditable(false);
        Area.setText(String.format("%s", "Hello, this is the homework function.\nPlease enter your name without spaces."));
        Pane = new JScrollPane(Area);
        Pane.setPreferredSize(new Dimension(350, 350));
        add(Pane, Area);
        
        Field = new JTextField(30);
        Field.setToolTipText("Enter name here");
        add(Field);
        
        Field1 = new JTextField(30);
        Field1.setToolTipText("Enter surname here");
        add(Field1,BorderLayout.CENTER);
        
        Box.setEditable(false);//so that the user cannot edit this
        Box.setToolTipText("Dropdown box");
        Box.addItem("Monday");//so that this is an option in the
        Box.addItem("Tuesday");//dropdown box
        Box.addItem("Wednesday");
        Box.addItem("Thursday");
        Box.addItem("Friday");
        add(Box, BorderLayout.CENTER);
        
        Enter = new JButton("Enter");
        Enter.setToolTipText("Enter");
        add(Enter, BorderLayout.CENTER);
        
        Home = new JButton("Home");
        Home.setToolTipText("This will return you to the main page");
        add(Home);
        
        HAction A_tion = new HAction();
        Box.addActionListener(A_tion);
        Enter.addActionListener(A_tion);
        Home.addActionListener(A_tion);
    }
    
    private class HAction implements ActionListener{
        
        @Override
        public void actionPerformed(ActionEvent e) {
            String FirstName = "";
            String Surname = "";
            String Day = "";
            
            if(e.getSource()==Enter){
                FirstName = Field.getText();
                Surname = Field1.getText();
                Day = (String) Box.getSelectedItem();
                Field.setText("");
                Field1.setText("");
                try {
                    HomeFace FullnAme = new HomeFace(FirstName,Surname,Day);
                } catch (SQLException ex) {
                    Logger.getLogger(HInterface.class.getName()).log(Level.SEVERE, null, ex);
                } catch (InterruptedException ex) {
                    Logger.getLogger(HInterface.class.getName()).log(Level.SEVERE, null, ex);
                }
                dispose();
            }else if(e.getSource()==Home){
                dispose();
                MainInterface face = new MainInterface();
                face.setSize(400,180);
                face.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                face.setVisible(true);
            }
            
            
            
            
                            
            
        }

    }
    
}
