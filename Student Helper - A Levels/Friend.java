/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import java.awt.*;
import java.awt.event.*;
import java.util.regex.Pattern;
import javax.swing.*;

/**
 *
 * @author xavmu
 */
public class Friend extends JFrame{
    
    private final JTextArea Area;
    private final JScrollPane Pane;
    private final JTextField Field, Field1;
    private final JButton Button,Home;
    private final JComboBox Box = new JComboBox();
    private double Output, number, numBer;
    
    public Friend(){
    
        super("Friend");
        setLayout(new FlowLayout());
        setResizable(false);
        
        Area = new JTextArea(200, 700);
        Area.setEditable(false);
        Area.setText("Hello, please enter the first number in box one.\n Then choose what operation you want and type the other number into the "
                + "other box.\n If you are using on of the operations that only use one number,\n enter that number in the first field and 0 into the other.\n Now press the enter button.");
        Pane = new JScrollPane(Area);
        Pane.setPreferredSize(new Dimension(700, 200));
        add(Pane, Area);
        
        Field = new JTextField(30);
        Field.setEditable(true);
        Field.setToolTipText("number");
        add(Field);
        
        Field1 = new JTextField(30);
        Field1.setEditable(true);
        Field1.setToolTipText("numBer");
        add(Field1);
        
        Box.setEditable(false);
        Box.addItem("-");
        Box.addItem("+");
        Box.addItem("x");
        Box.addItem("Square Root");
        Box.addItem("Power");
        Box.addItem("cos(x)");
        Box.addItem("sin(x)");
        Box.addItem("tan(x)");
        Box.addItem("cos-1");
        Box.addItem("sin-1");
        Box.addItem("tan-1");
        add(Box);
        
        Button = new JButton("Enter");
        add(Button);
        
        Home = new JButton("Home");
        add(Home);
        
        A_button DAction = new A_button();
        Button.addActionListener(DAction);
        Home.addActionListener(DAction);
        
    }
        
    private class A_button implements ActionListener {
            
            @Override
        public void actionPerformed(ActionEvent e){
            if(e.getSource() == Button){
                String question = Field.getText();
                number = Double.parseDouble(question);
                String Other = Field1.getText();
                numBer = Double.parseDouble(Other);
                Area.setText("");
                
                if(Box.getSelectedItem()== "-"){
                    Output = number - numBer;
                } else if(Box.getSelectedItem()== "+"){
                    Output = number + numBer;
                } else if(Box.getSelectedItem()=="x"){
                    Output = number * numBer;
                } else if(Box.getSelectedItem()=="Square Root"){
                    Output = Math.sqrt(number);
                } else if(Box.getSelectedItem()=="Power"){
                    Output = Math.pow(number, numBer);
                } else if(Box.getSelectedItem()=="cos(x)"){
                    double Rads = number * (Math.PI/180);
                    Output = Math.cos(Rads);
                } else if(Box.getSelectedItem()=="sin(x)"){
                    double Rads = number * (Math.PI/180);
                    Output = Math.sin(Rads);
                } else if (Box.getSelectedItem()== "tan(x)"){
                    double Rads = number * (Math.PI/180);
                    Output = Math.tan(Rads);
                } else if(Box.getSelectedItem()== "cos-1"){
                    double Rads = number * (Math.PI/180);
                    Output = Math.acos(Rads);
                } else if(Box.getSelectedItem()== "sin-1"){
                    double Rads = number * (Math.PI/180);
                    Output = Math.asin(Rads);
                } else if(Box.getSelectedItem()== "tan-1"){
                    double Rads = number * (Math.PI/180);
                    Output = Math.atan(Rads);
                }
                Area.setText("The answer is: " +Output);
                
            } else if(e.getSource()==Home){
                dispose();
                MainInterface Home = new MainInterface();
                Home.setSize(400,180);
                Home.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Home.setVisible(true);
            }
        }
    }
}