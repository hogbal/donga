// Parser.java
// Recursive descent parser for Expression Grammar
package 프로그래밍언어론;
import java.io.*;

public class Parser {
    Token token;          // current token from the input stream
    Lexer lexer;
    String funcId = "";

    public Parser(Lexer ts) throws IOException { // Open the Clite source program
        lexer = ts;				// as a token stream, and
        token = lexer.next(); // retrieve its first Token
    }
  
	private void getToken() throws IOException {
		token = lexer.next();
	}
	
	private void parse() throws IOException {
		command();
	}

	private void command() throws IOException {
		prgm();
	}
	
	private Expression aexp() throws IOException {
		Expression e = term();
		while(token.type() == TokenType.Plus || token.type() == TokenType.Minus) {
			Operator op = new Operator(token.value()); 
			System.out.print(" "+token.value());
			getToken();
			Expression e2 = term();
			e = new Binary(op, e, e2);
		}
		return e;
	}
	
	private Expression term() throws IOException {
		Expression e = factor();
		while(token.type() == TokenType.Multiply || token.type() == TokenType.Divide) {
			Operator op = new Operator(token.value()); 
			System.out.print(" "+token.value());
			getToken();
			Expression e2 = factor();
			e = new Binary(op, e, e2);
		}
		return e;
	}
	
	private Expression factor() throws IOException {
		Expression e = null;
		if (token.type() == TokenType.LeftParen) {
			System.out.print(" "+token.value());
			getToken();
			e = aexp();
			if(token.type() == TokenType.RightParen) {
				System.out.print(" "+token.value());
				getToken();
			}
			else {
				System.out.println("\n)is required");
				System.exit(0);
			}
		}
		else if (token.type() == TokenType.IntLiteral) {
			String s = token.value();
			System.out.print(" "+token.value());
			getToken();		
			return new IntValue(Integer.parseInt(s));
		} 
		else if (token.type() == TokenType.Identifier) {
			System.out.print(" "+token.value());
			Identifier v = new Identifier(token.value());
			e = v;
			getToken();		
		} 
		else if(token.type() == TokenType.Minus) {
			Operator op = new Operator(token.value());
			System.out.print(" "+token.value());
			getToken();
			e = factor();
			return new Unary(op,e);
		}
		else {
			System.out.println("\nSyntax ERROR");
			System.exit(-1);
		}
		
		return e;
	}
	
	private Expression expr() throws IOException {
		Expression e = null;
		if(token.type() == TokenType.True || token.type() == TokenType.False) {
			System.out.print(" "+token.value());
			e = new BoolValue(token.value());
			getToken();
		}
		else if(token.type() == TokenType.Not) {
			System.out.print(" "+token.value());
			Operator op = new Operator(token.value());
			getToken();
			Expression e2 = expr();
			e = new Unary(op,e2);
		}
		else {
			e = bexp();
			while(token.type() == TokenType.And || token.type() == TokenType.Or) {
				Operator op = new Operator(token.value()); 
				System.out.print(" "+token.value());
				getToken();
				Expression e2 = bexp();
				e = new Binary(op, e ,e2);
			}
		}
		return e;
	}
	
	private Expression bexp() throws IOException {
		Expression e = aexp();
		if(relop()) {
			System.out.print(" "+token.value());
			Operator op = new Operator(token.value()); 
			getToken();
			Expression e2 = aexp();
			e = new Binary(op, e, e2);
		}
		return e;
	}
	
	private boolean relop() throws IOException {
		if(token.type() == TokenType.Same || 
				token.type() == TokenType.Different ||
				token.type() == TokenType.Right ||
				token.type() == TokenType.Left ||
				token.type() == TokenType.Rightsame ||
				token.type() == TokenType.Leftsame) {
			return true;
		}
		return false;
	}
	
	private void prgm() throws IOException {
		Statement s = stmt();
		if(token.type() == TokenType.PrgmEnd) {
			if(lexer.getter_col()+1 >= lexer.getter_len()) {
				System.out.println("\nSyntax OK");
				System.out.println("\n-----AST-----");
				System.out.println("Program(AST):");
				s.display(1);
			}
			else {
				System.out.println("\nSyntax ERROR");
			}
		}
	}
	
	private Statement stmt() throws IOException {
		Statement s = null;
		if(token.type() == TokenType.Identifier || token.type() == TokenType.Assignment) {
			s = id();
		}
		else if(token.type() == TokenType.LeftBrace) {
			s = block();
		}
		else if(token.type() == TokenType.If) {
			s = if_fun();
		}
		else if(token.type() == TokenType.While) {
			s = while_fun();
		}
		else if(token.type() == TokenType.Read) {
			s = read();
		}
		else if(token.type() == TokenType.Print) {
			s = print();
		}
		else if(token.type() == TokenType.Let) {
			s = let();
		}
		else {
			System.out.println("\nSyntax ERROR");
			System.exit(-1);
		}
		return s;
	}
	
	private Statement id() throws IOException {
		Statement s = null;
		if(token.type() == TokenType.Identifier) {
			Identifier v = new Identifier(token.value());
			System.out.print(" "+token.value());
			getToken();
			if(token.type() == TokenType.Assignment) {
				System.out.print(" "+token.value());
				getToken();
				Expression e = expr();
				s = new Assignment(v,e);
				if(token.type() == TokenType.Semicolon) {
					System.out.print(" "+token.value());
					getToken();	
				}
				else {
					System.out.println("\nSyntax ERROR");	
					System.exit(0);
				}
			}
			else {
				System.out.println("\nSyntax ERROR");	
				System.exit(0);
			}	
		}
		else {
			System.out.println("\nSyntax ERROR");
			System.exit(0);
		}
		return s;
	}
	
	private Statement block() throws IOException {
		Block s = new Block();
		System.out.print(" "+token.value());
		getToken();
		while(token.type() != TokenType.RightBrace) {
			Statement temp = stmt();
			s.members.add(temp);
		}
		System.out.print(" "+token.value());
		getToken();
		return s;
	}
	
	private Statement if_fun() throws IOException{
		Statement s = null;
		System.out.print(" "+token.value());
		getToken();
		if(token.type() == TokenType.LeftParen) {
			System.out.print(" "+token.value());
			getToken();
			Expression e = expr();
			if(token.type() == TokenType.RightParen) {
				System.out.print(" "+token.value());
				getToken();
				if(token.type() == TokenType.Then) {
					System.out.print(" "+token.value());
					getToken();
					Statement s1 = stmt();
					if(token.type() == TokenType.Else) {
						System.out.print(" "+token.value());
						getToken();
						Statement s2 = stmt();
						s =  new Conditional(e, s1, s2);
					}
					else {
						s =  new Conditional(e, s1);	
					}
				}
				else {
					System.out.println("\nSyntax ERROR");	
					System.exit(0);
				}
			}
			else {
				System.out.println("\nSyntax ERROR");	
				System.exit(0);
			}
		}
		else {
			System.out.println("\nSyntax ERROR");	
			System.exit(0);
		}
		return s;
	}
	
	private Statement while_fun() throws IOException {
		Statement s = null;
		System.out.print(" "+token.value());
		getToken();
		if(token.type() == TokenType.LeftParen) {
			System.out.print(" "+token.value());
			getToken();
			Expression e = expr();
			if(token.type() == TokenType.RightParen) {
				System.out.print(" "+token.value());
				getToken();
				Statement s1 = stmt();
				s = new While(e,s1);
			}
			else {
				System.out.println("\nSyntax ERROR");	
				System.exit(0);
			}
		}
		else {
			System.out.println("\nSyntax ERROR");	
			System.exit(0);
		}
		return s;
	}
	
	private Statement read() throws IOException{
		Statement s = null;
		System.out.print(" "+token.value());
		getToken();
		if(token.type() == TokenType.Identifier) {
			Identifier id = new Identifier(token.value());
			System.out.print(" "+token.value());
			getToken();
			System.out.print(" "+token.value());
			getToken();
			s = new Read(id);
		}
		else {
			System.out.println("\nSyntax ERROR");	
			System.exit(0);
		}
		return s;
	}
	
	private Statement print() throws IOException{
		Statement s = null;
		System.out.print(" "+token.value());
		if(token.type() != TokenType.Semicolon) {
			getToken();
			Expression e = expr();	
			System.out.print(" "+token.value());
			getToken();
			s = new Print(e);
		}
		else {
			System.out.println("\nSyntax ERROR");	
			System.exit(0);
		}
		return s;
	}
	
	private Statement let() throws IOException{
		Let l = null;
		System.out.print(" "+token.value());
		getToken();
		Declarations ds = decls();
		if(token.type() == TokenType.In) {
			System.out.print(" "+token.value());
			getToken();
			Block s = new Block();
			while(token.type() != TokenType.End) {
				Statement temp = stmt();
				s.members.add(temp);
			}
			l = new Let(ds,s);
			System.out.print(" "+token.value());
			getToken();
		}
		else {
			System.out.println("\nSyntax ERROR");
			System.exit(-1);
		}
		return l;
	}
	
	private Declarations decls() throws IOException {
		Declarations ds = new Declarations();
		while(token.type() == TokenType.Int || token.type() == TokenType.Bool) {
			String s = token.value();
			System.out.print(" "+token.value());
			getToken();
			if(token.type() == TokenType.Identifier) {
				Identifier id = new Identifier(token.value());
				System.out.print(" "+token.value());
				getToken();
				Type temp = new Type(s,id);
				ds.members.add(temp);
				if(token.type() == TokenType.Semicolon) {
					System.out.print(" "+token.value());
					getToken();
				}
				else {
					System.out.println("\nSyntax ERROR");
					System.exit(-1);
				}
			}
			else {
				System.out.println("\nSyntax ERROR");
				System.exit(-1);
			}
		}
		return ds;
	}
	/*
    public static void main(String args[]) throws IOException {
		Parser parser;
		if (args.length == 0) {
            System.out.println("Begin parsing… ");
		    parser  = new Parser(new Lexer());
		    parser.parse();
		}
    	else {
			System.out.println("Begin parsing… " + args[0]);
			parser  = new Parser(new Lexer(args[0]));
		    parser.parse();
	    }
    } //main
    */
} // Parser