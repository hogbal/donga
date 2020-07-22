// Token.java
// Tokens for Expression Grammar
package 프로그래밍언어론;
//import java.lang.Enum;
enum TokenType {
     Eof, Semicolon, 
     LeftParen, RightParen, 
     Plus, Minus, Multiply,
     Divide, Identifier, IntLiteral, 
     Same, Different, Right, Left, Rightsame, Leftsame,
     And, Or, Not,
     True, False,
     ID, Assignment,
     LeftBrace, RightBrace,
     If, Then, Else,
     While,
     Read,
     Print,
     ExitRightBrace,
     Int, Bool,
     Let, In, End,
     PrgmEnd
}

public class Token {

    public static final Token eofTok = new Token(TokenType.Eof, "<<EOF>>");
    public static final Token leftParenTok = new Token(TokenType.LeftParen, "(");
    public static final Token rightParenTok = new Token(TokenType.RightParen, ")");
	public static final Token semicolonTok = new Token(TokenType.Semicolon, ";");
    public static final Token plusTok = new Token(TokenType.Plus, "+");
    public static final Token minusTok = new Token(TokenType.Minus, "-");
    public static final Token multiplyTok = new Token(TokenType.Multiply, "*");
    public static final Token divideTok = new Token(TokenType.Divide, "/");
    public static final Token sameTok = new Token(TokenType.Same, "==");
    public static final Token differentTok = new Token(TokenType.Different, "!=");
    public static final Token rightTok = new Token(TokenType.Right, "<");
    public static final Token leftTok = new Token(TokenType.Left, ">");
    public static final Token rightsameTok = new Token(TokenType.Rightsame, "<=");
    public static final Token leftsameTok = new Token(TokenType.Leftsame, ">=");
    public static final Token andTok = new Token(TokenType.And, "&");
    public static final Token orTok = new Token(TokenType.Or, "|");
    public static final Token notTok = new Token(TokenType.Not, "!");
    public static final Token trueTok = new Token(TokenType.True, "true");
    public static final Token falseTok = new Token(TokenType.False, "false");
    public static final Token idTok = new Token(TokenType.ID, "id");
    public static final Token assignmentTok = new Token(TokenType.Assignment, "=");
    public static final Token leftbraceTok = new Token(TokenType.LeftBrace, "{");
    public static final Token rightbraceTok = new Token(TokenType.RightBrace, "}");
    public static final Token ifTok = new Token(TokenType.If,"if");
    public static final Token thenTok = new Token(TokenType.Then,"then");
    public static final Token elseTok = new Token(TokenType.Else, "else");
    public static final Token whileTok = new Token(TokenType.While, "while");
    public static final Token readTok = new Token(TokenType.Read, "read");
    public static final Token printTok = new Token(TokenType.Print, "print");
    public static final Token intTok = new Token(TokenType.Int, "int");
    public static final Token boolTok = new Token(TokenType.Bool, "bool");
    public static final Token letTok = new Token(TokenType.Let, "let");
    public static final Token inTok = new Token(TokenType.In, "in");
    public static final Token endTok = new Token(TokenType.End, "end");
    public static final Token prgmendTok = new Token(TokenType.PrgmEnd,".");

    private TokenType type;
    private String value = "";

    private Token (TokenType t, String v) {
        type = t;
        value = v;
    }

    public TokenType type( ) { return type; }

    public String value( ) { return value; }

    public static Token mkIdentTok (String name) {
        return new Token(TokenType.Identifier, name);
    }

    public static Token mkIntLiteral (String name) {
        return new Token(TokenType.IntLiteral, name);
    }

    public String toString ( ) {
        return value;
    } // toString

    public static void main (String[] args) {
        System.out.println(eofTok);
        System.out.println(divideTok);
        System.out.println(multiplyTok);
        System.out.println(rightParenTok);
    }
} // Token