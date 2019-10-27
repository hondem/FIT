package ija.ija2018.homework2;

import ija.ija2018.homework2.game.*;
import ija.ija2018.homework2.common.Figure;
import ija.ija2018.homework2.common.Game;

public abstract class GameFactory extends Object{

    public static Game createChessGame(Board board){
        for (int i = 1; i < board.getSize() + 1; i++){
            board.getField(i, 2).put((Figure) new ChessPawn(true));
            board.getField(i, board.getSize()-1).put((Figure) new ChessPawn(false));

            if (i == 1 || i == board.getSize()) {
                board.getField(i, 1).put((Figure) new Rook(true));
                board.getField(i, board.getSize()).put((Figure) new Rook(false));
            }
        }

        GameInstance gm_board = new GameInstance(board);
        return gm_board;
    }

    public static Game createCheckersGame(Board board){
        for (int col = 1; col < board.getSize() + 1; col++){
            if(col % 2 == 0){
                board.getField(col, 2).put((Figure) new CheckersPawn(true));
            } else {
                board.getField(col, 1).put((Figure) new CheckersPawn(true));
            }
        }

        GameInstance gm_board = new GameInstance(board);
        return gm_board;
    }
}
