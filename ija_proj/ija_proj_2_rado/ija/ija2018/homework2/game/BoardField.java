package ija.ija2018.homework2.game;

import ija.ija2018.homework2.common.Field;
import ija.ija2018.homework2.common.Figure;

public class BoardField implements Field {
    // Directions of field
	private int col, row;

	// Disk on field
	private Figure disk = null;

	// All neightbor fields
	private Field[] neighbors;

	/**
	 * Constructor of BoardField
	 * @param int Column of field
	 * @param int Row of field
	 */
	public BoardField(int col, int row){
		this.col = col;
		this.row = row;
		this.neighbors = new Field[8];

		for(int i = 0; i < 8; i++){
			this.neighbors[i] = null;
		}
	}

	/**
	 * Adds field in certain direction
	 * @param Direction Direction of field
	 * @param Field Field to be saved
	 */
	@Override
	public void addNextField(Field.Direction dirs, Field field) {
		this.neighbors[dirs.ordinal()] = field;
	}

	/**
	 * Get disk on field
	 * @return Disk put on field
	 */
	@Override
	public Figure get() {
		if(this.isEmpty()){
			return null;
		} else {
			return this.disk;
		}
	}

	/**
	 * Checks whether field is empty, or not
	 * @return true/false
	 */
	@Override
	public boolean isEmpty() {
		if(this.disk == null){
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Returns next field in direction
	 * @param Direction Direction of next field
	 * @return Field
	 */
	@Override
	public Field nextField(Direction dirs) {
		return this.neighbors[dirs.ordinal()];
	}

	/**
	 * Puts Disk on field
	 * @param Disk Disk to be put
	 * @return true/false depending if action is not forbidden
	 */
	@Override
	public boolean put(Figure disk) {
		if(this.isEmpty()){
            this.disk = disk;
            this.disk.setCol(this.col);
            this.disk.setRow(this.row);
            this.disk.setPosition(this);
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Removes disk from field
	 * @param Disk Disk to be removed
	 * @return true/false depending if action is not forbidden
	 */
	@Override
	public boolean remove(Figure disk) {
		if(this.isEmpty() || !disk.equals(this.disk)){
			return false;
		} else {
			this.disk = null;
			return true;
		}
    }
    
    @Override
    public int getCol(){
        return this.col;
    }

    @Override
    public int getRow(){
        return this.row;
    }
}
