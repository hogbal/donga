package 프로그래밍언어론;

class Conditional extends Statement{
	// Conditional = Expression test; Statement thenbranch, elsebranch
	Expression test;
	Statement thenbranch, elsebranch;
	Conditional (Expression t, Statement tp) {
		test = t; 
		thenbranch = tp; 
		elsebranch = null;
	}
	Conditional (Expression t, Statement tp, Statement ep) { 
		test = t; 
		thenbranch = tp; 
		elsebranch = ep;
	}
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Conditional:");
		levels++;
		test.display(levels);
		thenbranch.display(levels);
		if(elsebranch != null) {
			elsebranch.display(levels);
		}
	}
}
