package 프로그래밍언어론;

class IntValue extends Expression{
	protected boolean undef = true;
	boolean isUndef( ) { return undef; } 
	private int value = 0;
	
	IntValue (int v) { 
		value = v; 
		undef = false; 
	}
	public String toString( ) {
		if (undef) {
			return "undef";
		}
		return "" + value;
	}
	public void display(int levels) {
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("IntValue: "+value);
	}
}
