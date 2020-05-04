import java.io.IOException;

public class Parser {
   private Lexer lex;
   private Token tok;

   public Parser(Lexer lex) throws IOException {
      this.lex = lex;
      this.tok = lex.getToken();
   }

   private void error(Token.T[] expected) {
      StringBuilder b = new StringBuilder();
      if (expected.length > 0) {
         b.append(expected[0]);
         for (int i = 1; i < expected.length; i++)
            b.append(", ").append(expected[i]);
      }
      ErrorMsg.error(tok.line, tok.col, "syntax error", "expecting " + b.toString() + ", found " + tok.type);
      System.exit(3);
   }

   private void advance() throws IOException {
      tok = lex.getToken();
   }

   private void eat(Token.T t) throws IOException {
      if (tok.type == t)
         advance();
      else
         error(new Token.T[]{t});
   }

   private void S() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            Program();
            break;
         case BOOLEANO:
            Program();
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO});
      }
   }

   private void Program() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            Funs();
            break;
         case BOOLEANO:
            Funs();
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO});
      }
   }

   private void Funs() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            Fun();
            FunsLinha();
            break;
         case BOOLEANO:
            Fun();
            FunsLinha();
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO});
      }
   }

   private void FunsLinha() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            Funs();
            break;
         case BOOLEANO:
            Funs();
            break;
         case EOF:
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO, Token.T.EOF});
      }
   }

   private void Fun() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            TypeId();
            eat(Token.T.PARENTESE_ESQ);
            TypeIds();
            eat(Token.T.PARENTESE_DIR);
            eat(Token.T.IGUAL);
            Exp();
            break;
         case BOOLEANO:
            TypeId();
            eat(Token.T.PARENTESE_ESQ);
            TypeIds();
            eat(Token.T.PARENTESE_DIR);
            eat(Token.T.IGUAL);
            Exp();
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO});
      }
   }

   private void TypeId() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            eat(Token.T.INTEIRO);
            eat(Token.T.ID);
            break;
         case BOOLEANO:
            eat(Token.T.BOOLEANO);
            eat(Token.T.ID);
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO});
      }
   }

   private void TypeIds() throws IOException {
      switch (tok.type) {
         case INTEIRO:
            TypeId();
            TypeIdsLinha();
            break;
         case BOOLEANO:
            TypeId();
            TypeIdsLinha();
            break;
         default:
            error(new Token.T[]{Token.T.INTEIRO, Token.T.BOOLEANO});
      }
   }

   private void TypeIdsLinha() throws IOException {
      switch (tok.type) {
         case PARENTESE_DIR:
            break;
         case VIRGULA:
            eat(Token.T.VIRGULA);
            TypeIds();
            break;
         default:
            error(new Token.T[]{Token.T.PARENTESE_DIR, Token.T.VIRGULA});
      }
   }

   private void Exp() throws IOException {
      switch (tok.type) {
         case ID:
            A();
            ExpLinha();
            break;
         case LET:
            eat(Token.T.LET);
            eat(Token.T.ID);
            eat(Token.T.IGUAL);
            Exp();
            eat(Token.T.IN);
            Exp();
            break;
         case IF:
            eat(Token.T.IF);
            Exp();
            eat(Token.T.THEN);
            Exp();
            eat(Token.T.ELSE);
            Exp();
            break;
         case NUM:
            A();
            ExpLinha();
            break;
         default:
            error(new Token.T[]{Token.T.ID, Token.T.LET, Token.T.IF, Token.T.NUM});
      }
   }

   private void ExpLinha() throws IOException {
      switch (tok.type) {
         case IGUAL:
            eat(Token.T.IGUAL);
            A();
            break;
         case INTEIRO:
         case BOOLEANO:
         case VIRGULA:
         case IN:
         case THEN:
         case ELSE:
         case PARENTESE_DIR:
         case EOF:
            break;
         default:
            error(new Token.T[]{Token.T.EOF, Token.T.PARENTESE_DIR,Token.T.IGUAL, Token.T.INTEIRO, Token.T.BOOLEANO,
                                Token.T.VIRGULA,Token.T.IN, Token.T.THEN, Token.T.ELSE });
      }
   }

   private void A() throws IOException {
      switch (tok.type) {
         case ID:
            T();
            ALinha();
            break;
         case NUM:
            T();
            ALinha();
         default:
            error(new Token.T[]{Token.T.ID, Token.T.NUM});
      }
   }

   private void ALinha() throws IOException {
      switch (tok.type) {
         case MAIS:
            eat(Token.T.MAIS);
            T();
            ALinha();
            break;
         case EOF:
         case PARENTESE_DIR:
         case IGUAL:
         case INTEIRO:
         case BOOLEANO:
         case VIRGULA:
         case IN:
         case THEN:
         case ELSE:
            break;
         default:
            error(new Token.T[]{Token.T.EOF, Token.T.PARENTESE_DIR,Token.T.IGUAL, Token.T.INTEIRO, Token.T.BOOLEANO,
                    Token.T.VIRGULA,Token.T.IN, Token.T.THEN, Token.T.ELSE, Token.T.MAIS });
      }
   }

   private void T() throws IOException {
      switch (tok.type) {
         case ID:
            eat(Token.T.ID);
            TLinha();
            break;
         case NUM:
            eat(Token.T.NUM);
            break;
         default:
            error(new Token.T[]{Token.T.ID, Token.T.NUM});
      }
   }

   private void TLinha() throws IOException {
      switch (tok.type) {
         case PARENTESE_ESQ:
            eat(Token.T.PARENTESE_ESQ);
            Exps();
            eat(Token.T.PARENTESE_DIR);
            break;
         case PARENTESE_DIR:
         case IGUAL:
         case INTEIRO:
         case BOOLEANO:
         case VIRGULA:
         case IN:
         case THEN:
         case ELSE:
         case MAIS:
         case EOF:
            break;
         default:
            error(new Token.T[]{Token.T.EOF, Token.T.PARENTESE_ESQ, Token.T.PARENTESE_DIR,Token.T.IGUAL, Token.T.INTEIRO, Token.T.BOOLEANO,
                    Token.T.VIRGULA,Token.T.IN, Token.T.THEN, Token.T.ELSE, Token.T.MAIS });
      }
   }

   private void Exps() throws IOException {
      switch (tok.type) {
         case ID:
            Exp();
            ExpsLinha();
            break;
         case LET:
            Exp();
            ExpsLinha();
            break;
         case IF:
            Exp();
            ExpsLinha();
            break;
         case NUM:
            Exp();
            ExpsLinha();
            break;
         default:
            error(new Token.T[]{Token.T.ID, Token.T.LET, Token.T.IF, Token.T.NUM});
      }
   }

   private void ExpsLinha() throws IOException {
      switch (tok.type) {
         case PARENTESE_DIR:
            break;
         case VIRGULA:
            eat(Token.T.VIRGULA);
            Exps();
         default:
            error(new Token.T[]{Token.T.PARENTESE_DIR, Token.T.VIRGULA});
      }
   }

   public void parse() throws IOException {
      S();
      eat(Token.T.EOF);
   }
}
