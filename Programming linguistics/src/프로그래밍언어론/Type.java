package 프로그래밍언어론;

class Type {
	String left;
	Identifier right;
	Type(String s, Identifier id) {
		left = s;
		right = id;
	}
	
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Declaration:");
		
		levels++;
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Type: "+left);
		
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Identifier: "+right);
	}
}
