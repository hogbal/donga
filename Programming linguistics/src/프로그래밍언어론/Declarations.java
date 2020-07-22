package 프로그래밍언어론;

import java.util.ArrayList;

class Declarations {
	public ArrayList<Type> members= new ArrayList<Type>();
	
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Declarations:");
		levels++;
		for(Type s : members) {
			s.display(levels);
		}
	}
}
