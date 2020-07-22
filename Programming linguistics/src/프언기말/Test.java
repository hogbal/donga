package 프언기말;

class Test {
	public static void main(String args[]) {
		try {
			m();
			System.out.print("0 ");
		}catch (Exception e) {
			System.out.print("1 ");
		}
	}
	static void m() throws Exception{
		try {
			try {
				if(true) throw new Exception();
				System.out.print("2 ");
			}catch(A e) {
				System.out.print("3 ");
			}catch(Exception e) {
				System.out.print("4 ");
				throw new B();
			}
		}catch(A e) {
			System.out.print("5 ");
		}catch(Exception e) {
			System.out.print("6 ");
			throw e;
		}
	}
}
