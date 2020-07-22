package 프로그래밍언어론;

import java.util.ArrayList;

class Block extends Statement { // Block = Statement*
	public ArrayList<Statement> members= new ArrayList<Statement>();
	
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Block:");
		levels++;
		for(Statement s : members) {
			s.display(levels);
		}
	}
}
