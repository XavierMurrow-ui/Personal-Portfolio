/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mainproject;

import java.awt.FlowLayout;
import java.awt.event.*;
import java.sql.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.table.DefaultTableModel;
/**
 *
 * @author xavmu
 */
public class HomeFace extends JFrame{
    
//     private final DefaultTableModel Model = new DefaultTableModel() {
//
//        @Override
//        public boolean isCellEditable(int row, int col) {
//                    return true;
//                }
//};
    //
    private final JTable Table;
    private final JButton Button;
    private static final int Table_Width = 500,Table_Height = 180,Frame_Width = 500,Frame_Height = 180;
    String FirstnAme;
    String Surname;
    String DayOfWeek;
    
    public HomeFace(String Name, String Sname, String DAY) throws SQLException, InterruptedException{
        
        super("Homework");
        this.FirstnAme = Name;
        this.Surname = Sname;
        this.DayOfWeek = DAY;
        Statement st;
        ResultSet rs;
        
        System.out.println(Name + Sname+DAY);
        
        setLayout(new FlowLayout());
        setResizable(false);
        setSize(Frame_Width, Frame_Height);
        setVisible(true);
        
        DefaultTableModel model = new DefaultTableModel();
        Table = new JTable(model);
        model.addColumn("Day of the Week");//creates column
        model.addColumn("Period");
        model.addColumn("Subject");
        model.addRow(new String[] {"Day of the Week","Period","Subject"});
        add(Table);
        Table.setSize(Table_Width, Table_Height);
        Table.setVisible(true);

        try{
            Connection conn = DriverManager.getConnection("jdbc:derby://localhost:1527/StudentsTables","app","app");
            st = conn.createStatement();
            rs = st.executeQuery("SELECT Day_of_the_Week, Periods, Subjects.SubjectID\n" +
"	FROM Students, Subjects, Enrol\n" +
"	WHERE Day_of_the_Week = '"+DAY+"'\n" +
"	AND Students.Firstname = '"+Name+"'\n" +
"	AND Students.Surname = '"+Sname+"'\n" +
"	AND Students.StudentID = Enrol.StudentID\n" +
"	AND Subjects.SubjectID = Enrol.SubjectID\n" +
"	ORDER BY Periods");
            while(rs.next()){
                model.addRow(new String[] {rs.getString(1),rs.getString(2),rs.getString(3)});
            }
        } catch (SQLException e) {
           JOptionPane.showMessageDialog(null,e.getMessage());
        }
        
        Button = new JButton("Exit");
        Button.setToolTipText("Click to go home");
        add(Button);
        
        DButton Action = new DButton();
        Button.addActionListener(Action);
    }
    
    private class DButton implements ActionListener{
        
        @Override
        public void actionPerformed(ActionEvent e){
            if(e.getSource()==Button){
                dispose();
                MainInterface Face = new MainInterface();
                Face.setSize(400,180);
                Face.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                Face.setVisible(true);
                
            }
        }
    }
    
}

