package 프로그래밍언어론;

class Unary extends Expression{
	Operator op;
	Expression term;
	Unary(Operator o, Expression e) {
		op = o;
		term = e;
	}
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Unary:");
		levels++;
		op.display(levels);
		term.display(levels);
	}
}
