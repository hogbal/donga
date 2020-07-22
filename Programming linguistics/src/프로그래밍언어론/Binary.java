package 프로그래밍언어론;

class Binary extends Expression{
	Operator op;
	Expression term1, term2;
	Binary(Operator o, Expression l, Expression r) {
		op = o;
		term1 = l;
		term2 = r;
	}
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Binary:");
		levels++;
		term1.display(levels);
		op.display(levels);
		term2.display(levels);
	}
}