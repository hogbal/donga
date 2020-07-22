package 프로그래밍언어론;

class Operator {
	final static String PLUS = "+";
	final static String MINUS = "-";
	final static String TIMES = "*";
	final static String DIV = "/";
	
	final static String SAME = "==";
	final static String Different = "!=";
	final static String Right = "<";
	final static String Left = ">";
	final static String Rightsame = ">=";
	final static String Leftsame = ">=";
	
	final static String AND = "&";
	final static String OR = "|";
	final static String NOT = "!";
	
	String val;
	
	Operator(String s) {
		val = s;
	}
	
	public String toString() {
		return val;
	}
	public boolean equals(Object obj) {
		return val.equals(obj);
	}
	
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Operator: "+val);
	}
}
