package ija.ija2018.homework1.board;

public interface Field{
	public enum Direction{
		D, L, LD, LU, R, RD, RU, U
	}

	public void addNextField(Field.Direction dirs, Field field);
	public Field nextField(Field.Direction dirs);
	public Disk get();
	public boolean isEmpty();
	public boolean put(Disk disk);
	public boolean remove(Disk disk);
}