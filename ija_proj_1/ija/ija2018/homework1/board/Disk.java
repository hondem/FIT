package ija.ija2018.homework1.board;

public class Disk extends Object{
	// Holds disk color
	private boolean isWhite;

	/**
	 * Constructor of Disk
	 * @param boolean Color of disk
	 */
	public Disk(boolean isWhite){
		this.isWhite = isWhite;
	}

	/**
	 * Checks whether disk is white
	 * @return true/false
	 */
	public boolean isWhite(){
		return this.isWhite;
	}

	/**
	 * Tries to move disk to certain position
	 * @return true/false - Depending on success of move
	 */
	public boolean move(Field moveTo){
		Field moveFrom = this.validatePath(moveTo);

		if(moveFrom != null){
			moveTo.put(this);
			moveFrom.remove(this);
		} else {
			return false;
		}

		return true;
	}

	/**
	 * Validates if disk can be moved to certain field
	 * @param moveTo Field to move disk to
	 * @return Starting point of path
	 */
	private Field validatePath(Field moveTo){
		if(!moveTo.isEmpty()) return null;

		Field tmp = moveTo;
		Field.Direction[] allowedDirections = { Field.Direction.L, Field.Direction.R, Field.Direction.D, Field.Direction.U};

		for(int i = 0; i < allowedDirections.length; i++){
			while(!(
				(tmp.get() != null) &&
				(tmp.get().equals(this))
			)){
				Field nextCandidate = tmp.nextField(allowedDirections[i]);

				if(
					(nextCandidate == null) ||
					(nextCandidate.get() != null && !nextCandidate.get().equals(this))
				){
					tmp = moveTo;
					break;
				} else {
					tmp = nextCandidate;
				};
			}

			if(!tmp.equals(moveTo)) break;
		}

		if(tmp.equals(moveTo)){
			return null;
		} else {
			return tmp;
		}
	}
}