package Game;

import city.cs.engine.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Game {

    private GameLevel world;
    private UserView view;
    private int LevelNumber, totalScore, continueHealth;
    private Controller controller;
    private NewView MyView;
    private MyView Tracker;
    private DebugViewer VIEW;
    private JPanel panel;
    private ControlPanel menu;
    private static StartFrame Start;
    private String username;
    //private Target set;

    public Game(String Username){
        this.username = Username;
        final JFrame frame = new JFrame("Test");//Instance of the JFrame or GUI

        LevelNumber = 1;
        world = new Level1();//Creates new instance of the GameLevel
        world.populate(this);
        Tracker = new MyView(world,1000,500,world.getPlayer(),world.getEnemy(),world);
        view = Tracker;//Adds background image to the view and sets the width and height of this

        MyView = new NewView(view,world.getPlayer());
        world.addStepListener(MyView);//Allows the users view to be primarily the character

        //Listeners
        controller = new Controller(world.getPlayer(),world, world.getEnemy(),this,username);
        frame.addKeyListener(controller);//Initials key listeners so character can be moved with keys
        view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));

        //VIEW = new DebugViewer(world, 1000,500);
        //JFrame debugView = VIEW;
        //debugView.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);


        //Frame Stuff


        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//Makes the program stop if the window is closed
        frame.setLocationByPlatform(true);

        frame.add(view);//Adds the userview to the frame
        frame.setResizable(false);//User cannot resize window
        frame.pack();
        frame.setVisible(true);//Makes the frame visible

        //Buttons/Panel
        panel = new JPanel();
        panel.add(Tracker);
        menu = new ControlPanel(Tracker,world,this,username);
        frame.add(menu.getMainPanel(),BorderLayout.SOUTH);
        //frame.setLocationByPlatform(true);
        frame.add(panel);




        world.start();//Starts world
    }

    public Game(StartFrame start){
        this.Start = start;
        world = new Level();
       start = new StartFrame(this);
        start.setResizable(false);
        start.pack();
        start.setVisible(true);
        world.start();
    }

    public static void main(String[] args){

        new Game(Start);
    }

    public void nextLevel(){
        totalScore = world.getPlayer().getScore();
        continueHealth = world.getPlayer().getHealth();

        if (LevelNumber == 4) {
            System.out.println(LevelNumber);
            world.stop();
            System.exit(0);
        } else if(world.isComplete() && LevelNumber == 1){
            System.out.println(LevelNumber);
            world.stop();
            LevelNumber++;
            world = new Level2();
            world.populate(this);
            world.getPlayer().setScore(totalScore);
            world.getPlayer().setHealth(continueHealth);
            controller.setWorld(world);
            controller.setBody(world.getPlayer());
            controller.setEnemy(world.getEnemy());
            Tracker.setWorld(world);
            Tracker.setPlayer(world.getPlayer());
            Tracker.setEnemy(world.getEnemy());
            Tracker.setGame(world);
            MyView.setWorld(view);
            MyView.setBody(world.getPlayer());
            world.addStepListener(MyView);
            view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
            world.start();
        }else if(world.isComplete() && LevelNumber == 2){
            System.out.println(LevelNumber);
            world.stop();
            LevelNumber++;
            world = new Level3();
            world.populate(this);
            world.getPlayer().setScore(totalScore);
            world.getPlayer().setHealth(continueHealth);
            controller.setWorld(world);
            controller.setBody(world.getPlayer());
            controller.setEnemy(world.getEnemy());
            Tracker.setWorld(world);
            Tracker.setPlayer(world.getPlayer());
            Tracker.setGame(world);
            MyView.setWorld(view);
            MyView.setBody(world.getPlayer());
            world.addStepListener(MyView);
            view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
            world.start();
        }
    }

    public void Restart(){
        totalScore = world.getPlayer().getScore();
        continueHealth = world.getPlayer().getHealth();

        if (LevelNumber == 1) {
            world.stop();
            LevelNumber = 1;
            world = new Level1();
            world.populate(this);
            world.getPlayer().setScore(totalScore);
            world.getPlayer().setHealth(continueHealth);
            controller.setWorld(world);
            controller.setBody(world.getPlayer());
            controller.setEnemy(world.getEnemy());
            Tracker.setWorld(world);
            Tracker.setPlayer(world.getPlayer());
            Tracker.setEnemy(world.getEnemy());
            Tracker.setGame(world);
            MyView.setWorld(view);
            MyView.setBody(world.getPlayer());
            world.addStepListener(MyView);
            view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
            world.start();
        }else if(LevelNumber == 2){
            world.stop();
            LevelNumber = 2;
            world = new Level2();
            world.populate(this);
            world.getPlayer().setScore(totalScore);
            world.getPlayer().setHealth(continueHealth);
            controller.setWorld(world);
            controller.setBody(world.getPlayer());
            controller.setEnemy(world.getEnemy());
            Tracker.setWorld(world);
            Tracker.setPlayer(world.getPlayer());
            Tracker.setEnemy(world.getEnemy());
            Tracker.setGame(world);
            MyView.setWorld(view);
            MyView.setBody(world.getPlayer());
            world.addStepListener(MyView);
            view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
            world.start();
        }else if(LevelNumber == 3){
            world.stop();
             LevelNumber = 3;
            world = new Level3();
            world.populate(this);
            world.getPlayer().setScore(totalScore);
            world.getPlayer().setHealth(continueHealth);
            controller.setWorld(world);
            controller.setBody(world.getPlayer());
            controller.setEnemy(world.getEnemy());
            Tracker.setWorld(world);
            Tracker.setPlayer(world.getPlayer());
            Tracker.setEnemy(world.getEnemy());
            Tracker.setGame(world);
            MyView.setWorld(view);
            MyView.setBody(world.getPlayer());
            world.addStepListener(MyView);
            view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
            world.start();
        }
    }

    public void levelSelect(int Level){
        GameLoader Load = new GameLoader("data/Score.txt",this,username);
        world.getPlayer().setScore(Load.getScore());
        world.getPlayer().setHealth(Load.getHealth());

        switch (Level){
            case 2:
                world.stop();
                LevelNumber = 2;
                world = new Level2();
                world.populate(this);
                controller.setWorld(world);
                controller.setBody(world.getPlayer());
                controller.setEnemy(world.getEnemy());
                Tracker.setWorld(world);
                Tracker.setPlayer(world.getPlayer());
                Tracker.setEnemy(world.getEnemy());
                Tracker.setGame(world);
                MyView.setWorld(view);
                MyView.setBody(world.getPlayer());
                world.addStepListener(MyView);
                view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
                world.getPlayer().setScore(Load.getScore());
                world.getPlayer().setHealth(Load.getHealth());
                world.start();
                break;
            case 3:
                world.stop();
                LevelNumber = 3;
                world = new Level3();
                world.populate(this);
                controller.setWorld(world);
                controller.setBody(world.getPlayer());
                controller.setEnemy(world.getEnemy());
                Tracker.setWorld(world);
                Tracker.setPlayer(world.getPlayer());
                Tracker.setEnemy(world.getEnemy());
                Tracker.setGame(world);
                MyView.setWorld(view);
                MyView.setBody(world.getPlayer());
                world.addStepListener(MyView);
                view.addMouseListener(new MouseHandler(view,world,world.getPlayer(),world.getEnemy(),this));
                world.getPlayer().setScore(Load.getScore());
                world.getPlayer().setHealth(Load.getHealth());
                world.start();
                break;
        }
    }

    public void setContinueHealth(int continueHealth) {
        this.continueHealth = continueHealth;
    }

    public void setTotalScore(int totalScore) {
        this.totalScore = totalScore;
    }
}
