package ija.ija2018.homework2.game;

import ija.ija2018.homework2.common.Field;
import ija.ija2018.homework2.common.Figure;

public abstract class Pawn implements Figure {

    public boolean color;

    private int col;
    private int row;

    protected Field position;

    public Pawn(boolean isWhite){
        this.color = isWhite;
    }

    @Override
    public boolean isWhite(){
        return this.color;
    }

    @Override
    public String getState(){
        String currentColor = (this.isWhite()) ? "[W]" : "[B]";
        return "P" + currentColor + this.col + ":" + this.row;
    }

    protected void setAttributesAfterMove(Field moveTo){
        
        this.position.remove(this);
        this.setRow(moveTo.getRow());
        this.setPosition(moveTo);
        this.setCol(moveTo.getCol());
        moveTo.put(this);

    }

    public void setCol(int col){
        this.col = col;
    }

    public void setRow(int row){
        this.row = row;
    }

    public void setPosition(Field field){
        this.position = field;
    }

    public Field getPosition(){ 
        return this.position; 
    }
}
