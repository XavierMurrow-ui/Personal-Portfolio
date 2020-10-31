/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import java.util.Calendar;
import java.util.concurrent.TimeUnit;
import javax.swing.*;
import javax.swing.table.*;


/**
 *
 * @author 5403Murrow
 */
public class GUI extends JFrame{
    String Fullname,Surname;
    private final JTable Table;
    private final JButton Home;
    private static String DayWeek;
    
    public GUI(String name, String Sname) throws SQLException, InterruptedException{
      super("Timetable");
      setLayout(new FlowLayout());
      setResizable(false);
      setSize(550,200);
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      this.Fullname = name;
      this.Surname = Sname;
      String message = "Your table was not found, please re-enter your name.";
        
      Statement st;
      ResultSet rs;
      
       java.util.Date date = new java.util.Date();//Uses date method to get the date
        Calendar c = Calendar.getInstance();//uses date value
        c.setTime(date);//allows calendar to know the 
        int dayOfWeek = c.get(Calendar.DAY_OF_WEEK);//gives the day a number
        
        switch(dayOfWeek){
            case 2: 
                DayWeek = "Monday";
                break;
            case 3: 
                DayWeek = "Tuesday";
                break;
            case 4:
                DayWeek = "Wednesday";
                break;
            case 5: 
                DayWeek = "Thursday";
                break;
            case 6: 
                DayWeek = "Friday";
                break;
        }
        
        DefaultTableModel model = new DefaultTableModel();
        Table = new JTable(model);
        Table.setSize(550,150);
        add(Table);
        
        Home = new JButton("Home");
        Home.setToolTipText("This return you to the main menu");
        add(Home);
        
        model.addColumn("Day of the Week");//creates column
        model.addColumn("Period");
        model.addColumn("Subject");
        model.addColumn("Classroom");
        model.addRow(new String[] {"Day of the Week","Period","Subject","Classroom"});
        //This line above is so the the columns has titles
        
        try {
              Connection con = DriverManager.getConnection("jdbc:derby://localhost:1527/StudentsTables","app","app");//Connection to my database
              st = con.createStatement();
              rs = st.executeQuery("SELECT Day_of_the_Week, Periods, Subjects.SUBJECTID, ClassroomID\n" +
                    "FROM Students, Subjects, Enrol\n" +
                    "WHERE Day_of_the_Week = '"+DayWeek+ "'\n" +
                    "AND Students.Firstname = '"+name+"'\n"+
                    "AND Students.Surname = '"+Sname+"'\n"+
                    "AND Students.STUDENTID = enrol.STUDENTID\n" +
                    "AND subjects.SUBJECTID = enrol.SUBJECTID "
                            + "ORDER BY Periods");
            while(rs.next()){
                  model.addRow(new String [] {rs.getString(1), rs.getString(2), rs.getString(3), rs.getString(4)});
              }//The line above is how the data retrived from the database is inputted into the table and then displayed
              setVisible(true);
              Table.setVisible(true);
          }catch (SQLException err) {
              JOptionPane.showMessageDialog(null,message);
              TimeUnit.SECONDS.sleep(1);
          }
        
        Button Action = new Button();
        Home.addActionListener(Action);
    }

    private class Button implements ActionListener {
    
        @Override
        public void actionPerformed(ActionEvent e){
            if(e.getSource()==Home){
                dispose();
                MainInterface Face = new MainInterface();
                Face.setSize(400,180);
                Face.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Face.setVisible(true);
            }
        }

    }

}
