package 프로그래밍언어론;

class While extends Statement {
	// While = Expression test; Statement body
	Expression test;
	Statement body;
	While (Expression t, Statement b) {
		test = t; 
		body = b; 
	}
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("While:");
		levels++;
		test.display(levels);
		body.display(levels);
	}
}