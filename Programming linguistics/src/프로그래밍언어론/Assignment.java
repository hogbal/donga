package 프로그래밍언어론;

class Assignment extends Statement{
	// Assignment = Identifier target; Expression source
	Identifier target;
	Expression source;
	Assignment (Identifier t, Expression e) {
		target = t;
		source = e; 
	}
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Assignment:");
		levels++;
		target.display(levels);
		source.display(levels);
	}
}
