package Game;

import city.cs.engine.*;

public class Enemy extends StaticBody {
    private int enemyHealth;
    private int weaponDamage;

    private static Shape hitBox = new PolygonShape(5*-0.11f,5*0.482f,5*0.134f,5*0.482f,5*0.222f,5*-0.01f,5*0.196f,5*-0.46f,5*-0.198f,5*-0.462f,5*-0.222f,5*-0.018f,5*-0.112f,5*0.482f);//enemy shape
    private BodyImage stickMan = new BodyImage("data/Stick3.png", 5);//image for enemy

    public Enemy(World world){
        super(world, hitBox);
        addImage(stickMan);
    }

    public void setEnemyHealth(int enemyHealth) {
        this.enemyHealth = enemyHealth;
    }

    public void Damage(){
        enemyHealth -= weaponDamage;
    }

    public int getEnemyHealth() {
        return enemyHealth;
    }

    public void setWeaponDamage(int weaponDamage) {
        this.weaponDamage = weaponDamage;
    }
}
