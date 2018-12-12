import java.util.*;

public class MiniMaxPlayer extends Player{

	public void play(){
		if(!isMyTurn()) return;
		Move m = minimaxDecision();
		mark(m);
	}
	
	public Move minimaxDecision(){
		Move result = null;
		int depth = 1;
		int max = Integer.MIN_VALUE;
		ArrayList<Move> moves = getAvailableMoves();
		for (Move bestMove: moves){
			int value = minValue(getNextState(getCurrentState(),bestMove),depth);
			System.out.println("move: " + bestMove + ", with " + value);
			if(value>max){
				result = bestMove;
				max = value;
			}
		}
		return result;
	}
	
	public int maxValue(Board b,int depth){
		int v = Integer.MIN_VALUE;
		if(isGameOver(b)) 
			return utility(b,depth);
		ArrayList <Move> moves = getAvailableMoves(b); 
		for(Move m: moves){
			v = max(v, minValue(getNextState(b,s), depth+1));
		}
		return v;
	}
	
	public int minValue(Board b,int depth){
		int v = Integer.MAX_VALUE;
		if(isGameOver(b)) 
			return utility(b,depth);
		ArrayList <Move> moves = getAvailableMoves(b); 
		for(Move m: moves){
			v = min(v, maxValue(getNextState(b,s), depth+1));
		}
		return v;
	}
	
	public int utility(Board b,int depth){
		if(getMarkTake() == getWinningMark(b))
			return 10-depth;
		else if(getMarkTake().getOppositeMark() == getWinningMark(b))
			return depth-10;
		else
			return 0;
	}
	
	public int max(){
		
	}
	
	public int min(){
		
	}
}