package 프로그래밍언어론;

class Print extends Statement{
	Expression test;
	Print(Expression e) {
		test = e;
	}
	
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Print:");
		levels++;
		test.display(levels);
	}
}
