package ija.ija2018.homework2.common;

public interface Field{
	public enum Direction{
		D, L, LD, LU, R, RD, RU, U
	}

	public void addNextField(Field.Direction dirs, Field field);
	public Field nextField(Field.Direction dirs);
	public Figure get();
	public boolean isEmpty();
	public boolean put(Figure figure);
    public boolean remove(Figure figure);
    
    abstract int getRow();
    abstract int getCol();
}