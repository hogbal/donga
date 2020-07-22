package 프로그래밍언어론;

class Read extends Statement{
	Identifier id;
	Read(Identifier temp) {
		id = temp;
	}
	
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Read:");
		levels++;
		id.display(levels);
	}
}
