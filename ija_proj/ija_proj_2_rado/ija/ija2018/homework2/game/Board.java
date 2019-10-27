/*
 * IJA 2018/2019
 * Ukol 1
 */
package ija.ija2018.homework2.game;

import ija.ija2018.homework2.common.Field;

public class Board extends Object{

	// Board size
	private int size;

	// Array of all fields on board
	private Field[][] fields;

	/**
	 * Board constructor
	 * @param size Size of bard
	 */
	public Board(int size){
		this.size = size;
		this.initializeBoard();
	}

	/**
	 * Returns size of board
	 * @return Board size
	 */
	public int getSize(){
		return this.size;
	}

	/**
	 * Returns field from certain position
	 * @param int Column of field
	 * @param int Row of field
	 */
	public Field getField(int col, int row){
		return this.fields[col][row];
	}

	/**
	 * Init fields on board
	 */
	private void initializeBoard(){
		this.fields = new Field[this.size + 2][this.size + 2];
		
		for(int col = 0; col < this.size + 2; col++){
			for(int row = 0; row < this.size + 2; row++){
				if(row == 0 || col == 0 || row == this.size + 1 || col == this.size + 1){
					this.fields[col][row] = null;
				} else {
					this.fields[col][row] = new BoardField(col, row);
				}
			}
		}

		this.setNeighbors();
	}

	/**
	 * Sets neighbors of fields on board
	 */
	private void setNeighbors(){
		for(int col = 1; col < this.size + 1; col++){
			for(int row = 1; row < this.size + 1; row++){
				this.fields[col][row].addNextField(Field.Direction.U, this.fields[col][row + 1]);
				this.fields[col][row].addNextField(Field.Direction.D, this.fields[col][row - 1]);
				this.fields[col][row].addNextField(Field.Direction.L, this.fields[col - 1][row]);
				this.fields[col][row].addNextField(Field.Direction.R, this.fields[col + 1][row]);
				this.fields[col][row].addNextField(Field.Direction.LU, this.fields[col - 1][row + 1]);
				this.fields[col][row].addNextField(Field.Direction.LD, this.fields[col - 1][row - 1]);
				this.fields[col][row].addNextField(Field.Direction.RU, this.fields[col + 1][row + 1]);
				this.fields[col][row].addNextField(Field.Direction.RD, this.fields[col + 1][row - 1]);
			}
		}
	}
}