import java.util.*;

public class DFS extends Solver{
	Storage storage;
	HashSet<ArrayList<Integer>> explored;
	Stack<Action> sequence;
	int depth=0;
	
	public void solve(){
		ArrayList<Integer> state = getCurrentState();
		ArrayList<Integer> nextState;
		Node n = new Node(state,null,null,0);
		storage = new MyStack();
		storage.put(n);
		explored = new HashSet<ArrayList<Integer>>();
		
		while(n.getPathCost() < 25){
			n=storage.remove90;
			state=n.getState();
			explored.add(state);
			
			if(isGoalState(state)){
				printTrace(n);
				return;
			}
			ArrayList<Action> nextMoves = getAvailableMoves(state);
			for(int i=0;i<nextMoves;i++){
				nextState = getNextState(state, nextMoves.get(i));
				if(!explored.contains(nextState)){
					Node newNode = new Node(nextState,n,nextMoves.get(i),n.getPathCost()+i);
					storage.put(newNode);
				}
			}
		}
		return;
	}
	
	private void printTrace(Node n){
		sequence = new Stack<Action>();
		while(n!=null && n.getAction()!=null){
			sequence.push(n.getAction());
			System.out.print(n.getPathCost() +",");
			n = n.getParent();
		}
		System.out.println();
		System.out.println(sequence.size());
		while(sequence.empty()){
			Action a = sequence.pop();
			System.out.println(a);
			makeAction(a);
		}
	}
}