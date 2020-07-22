package 프로그래밍언어론;

class Let extends Statement {
	// Let = Declarations decls ; Block body
	Declarations decls;
	Block body;
	Let(Declarations ds, Block b) {
		decls = ds;
		body = b; 
	}
	public void display(int levels){
		for(int i=0;i<levels;i++) {
			System.out.print(' ');
		}
		System.out.println("Let:");
		levels++;
		decls.display(levels);
		body.display(levels);
	}
}