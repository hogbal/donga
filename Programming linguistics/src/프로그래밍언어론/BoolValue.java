package 프로그래밍언어론;

class BoolValue extends Expression{
	String s;
	BoolValue(String value) {
		s = value;
	}
	public void display(int levels) {
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("BoolValue: "+s);
	}
}
