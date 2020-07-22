package 프로그래밍언어론;

class Identifier extends Expression{
	private String id;
	
	Identifier (String s) { id = s; }
	
	public String id() { return id; }
	public String toString() { return id; }
	public boolean equals(Object obj) {
		String s = ((Identifier) obj).id;
		return id.equals(s);
	}
	public void display(int levels) {
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Identifier: "+id);
	}
}
