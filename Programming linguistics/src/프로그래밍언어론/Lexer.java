// Lexer.java
// Lexical analyzer for Clite, as discusssed in Chapter 3
// Lexical analyzer modified for S
package 프로그래밍언어론;
import java.io.*;

public class Lexer {

    private char ch = ' '; 
    private BufferedReader input;
    private String line = "";
    private int col = 1;
    private final String letters = "abcdefghijklmnopqrstuvwxyz"
        + "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private final String digits = "0123456789";
    private final char eolnCh = '\n';

    public Lexer (String fileName) { // source filename
        try {
            input = new BufferedReader (new FileReader(fileName));
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found: " + fileName);
            System.exit(1);
        }
    }

	public Lexer ( ) { // from standard input 
            input = new BufferedReader (new InputStreamReader(System.in));
            System.out.println(" . 입력시 입력 종료");
			System.out.print(">\n");
	}

    private char nextChar() { // Return next char
        col++;
        if (col >= line.length()) {
            try {
				do {
					System.out.print("    ");
					String temp = input.readLine( );
					line += temp;
					if(!line.contains(".")) line+=eolnCh;
				}while(!line.contains("."));
                //System.out.println(line);
            } catch (IOException e) {
                System.err.println(e);
                System.exit(1);
            } // try
            col = 0;
        } // if col
        return line.charAt(col);
    }
            

    public Token next( ) { // Return next token
        do {
            if (isLetter(ch)) { // ident 
                String spelling = concat(letters + digits);
                if(spelling.equals("true")) {
                	return Token.trueTok;
                }
                else if(spelling.equals("false")) {
                	return Token.falseTok;
                }
                else if(spelling.equals("if")) {
                	return Token.ifTok;
                }
                else if(spelling.equals("then")) {
                	return Token.thenTok;
                }
                else if(spelling.equals("else")) {
                	return Token.elseTok;
                }
                else if(spelling.equals("while")) {
                	return Token.whileTok;
                }
                else if(spelling.equals("read")) {
                	return Token.readTok;
                }
                else if(spelling.equals("print")) {
                	return Token.printTok;
                }
                else if(spelling.equals("int")) {
                	return Token.intTok;
                }
                else if(spelling.equals("bool")) {
                	return Token.boolTok;
                }
                else if(spelling.equals("let")) {
                	return Token.letTok;
                }
                else if(spelling.equals("in")) {
                	return Token.inTok;
                }
                else if(spelling.equals("end")) {
                	return Token.endTok;
                }
                return Token.mkIdentTok(spelling);
            } else if (isDigit(ch)) {
                String number = concat(digits);
                return Token.mkIntLiteral(number);
            } else 
			switch (ch) {
            case ' ': case '\t': case '\r': case eolnCh:
                ch = nextChar();
                break;
            
//            case eofCh:  case '.': 
//				return Token.eofTok;
            
            case '+': ch = nextChar();
                return Token.plusTok;
            case '-': ch = nextChar();
                return Token.minusTok;
            case '*': ch = nextChar();
                return Token.multiplyTok;
            case '/': ch = nextChar();
                return Token.divideTok;
            case '(': ch = nextChar();
                return Token.leftParenTok;
            case ')': ch = nextChar();
                return Token.rightParenTok;
            case '=': ch = nextChar();
            	if(ch == '=') {
            		ch = nextChar();
            		return Token.sameTok;
            	}
            	else {
            		return Token.assignmentTok;
            	}
            case '!': ch = nextChar();
            	if(ch == '=') {
            		ch = nextChar();
            		return Token.differentTok;
            	}
            	else {
            		return Token.notTok;
            	}
            case '<': ch = nextChar();
            	if(ch == '=') {
            		ch = nextChar();
            		return Token.rightsameTok;
            	}
            	else {
            		return Token.rightTok;
            	}
            case '>': ch = nextChar();
            	if(ch == '=') {
            		ch = nextChar();
            		return Token.leftsameTok;
            	}
            	else {
            		return Token.leftTok;
            	}
            case '&': ch = nextChar();
            	return Token.andTok;
            case '|': ch = nextChar();
            	return Token.orTok;
            case '{': ch = nextChar();
            	return Token.leftbraceTok;
            case '}': ch = nextChar();
            	return Token.rightbraceTok;
            case ';': ch = nextChar();
            	return Token.semicolonTok;
            case '.':
            	return Token.prgmendTok;
            } // switch
        } while (true);
    } // next

    private boolean isLetter(char c) {
        return (c>='a' && c<='z' || c>='A' && c<='Z');
    }
  
    private boolean isDigit(char c) {
        return (c>='0' && c<='9'); 
    }

    private String concat(String set) {
    	String r = "";
        do {
            r += ch;
            ch = nextChar();
        } while (set.indexOf(ch) >= 0);
        return r;
    }
    
    public int getter_col() {
    	return this.col;
    }
    
    public int getter_len() {
    	return this.line.length();
    }
    
    public void error (String msg) {
        System.err.print(line);
        System.err.println("Error: column " + col + " " + msg);
        System.exit(1);
    }

    static public void main ( String[] args ) {
        Lexer lexer;
		if (args.length == 0)
            lexer = new Lexer( );
		else
            lexer = new Lexer(args[0]);

        Token tok = lexer.next( );
        while (tok != Token.semicolonTok) {
            System.out.println(tok);
             tok = lexer.next( );
        } 
    } // main
}