import error.CompilerError;
import io.vavr.collection.List;
import java_cup.runtime.Symbol;
import org.assertj.core.api.JUnitSoftAssertions;
import org.junit.Rule;
import org.junit.Test;
import parse.Lexer;
import parse.Terminals;

import java.io.IOException;
import java.io.StringReader;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.Assert.assertArrayEquals;

public class LexerTest {

   private String run(String input) throws IOException {
      Lexer lexer = new Lexer(new StringReader(input), "unknown");
      Symbol token;
      StringBuilder builder = new StringBuilder();
      List<String> list = List.empty();
      do {
         token = lexer.next_token();
         builder.append(Terminals.dumpTerminal(token)).append('\n');
         list = list.append(Terminals.dumpTerminal(token));
      } while (token.sym != Terminals.EOF);
      return builder.toString();
      //return list;
   }

   //METODO PARA TESTE AUTOMATIZADO SEM MENSAGEM DE ERRO
   private void trun(String input, String... output) throws IOException {
      StringBuilder builder = new StringBuilder();
      for (String x : output)
         builder.append(x).append('\n');
      softly.assertThat(run(input))
         .as("%s", input)
         .isEqualTo(builder.toString());
   }

   //METODO PARA TESTE AUTOMATIZADO COM MENSAGEM ERRO
   private void erun(String input, String message) throws IOException {
      softly.assertThatThrownBy(() -> run(input))
         .as("%s", input)
         .isInstanceOf(CompilerError.class)
         .hasMessage(message);
   }

   @Rule
   public final JUnitSoftAssertions softly = new JUnitSoftAssertions();

   @Test
   public void lexerTest1() throws IOException {
      // DELIMITADORES DE ESPAÇOS E QUEBRA DE LINHA
      trun("    \t\n\n\n\t\r\n\r\n  ", "6:3-6:3 EOF");

      // COMENTARIOS DE LINHA
      trun("-- a line comment\n", "2:1-2:1 EOF");
      trun("-- a line comment", "1:18-1:18 EOF");

      // COMENTARIOS DE BLOCO E BLOCO ANINHADO
      trun("/- a block comment -/", "1:22-1:22 EOF");
      trun("/- a\nmultiline\ncomment -/", "3:11-3:11 EOF");
      trun("/- begin ----/", "1:15-1:15 EOF");
      trun("/- outer /- inner -/ outer -/", "1:30-1:30 EOF");
      erun("/- a /- ab /- abc -/ ba", "1:24-1:24 lexical error: unclosed comment");

      // SINAIS DE PONTUACAO
      trun("(", "1:1-1:2 PARENTESE_ESQ", "1:2-1:2 EOF");
      trun(")", "1:1-1:2 PARENTESE_DIR", "1:2-1:2 EOF");
      trun(",", "1:1-1:2 VIRGULA", "1:2-1:2 EOF");

      // OPERADORES
      trun("+", "1:1-1:2 MAIS", "1:2-1:2 EOF");
      trun("=", "1:1-1:2 IGUAL", "1:2-1:2 EOF");

      // LITERAIS INTEIROS
      trun("26342", "1:1-1:6 LIT_INTEIRO(26342)", "1:6-1:6 EOF");
      trun("0", "1:1-1:2 LIT_INTEIRO(0)", "1:2-1:2 EOF");
      //trun("+75"    , "1:1-1:4 LIT_INTEIRO(75)"    , "1:4-1:4 EOF");
      //trun("-75"    , "1:1-1:4 LIT_INTEIRO(-75)"   , "1:4-1:4 EOF");

      // PALAVRAS RESERVADAS
      trun("bool", "1:1-1:5 BOOLEANO", "1:5-1:5 EOF");
      trun("int", "1:1-1:4 INTEIRO", "1:4-1:4 EOF");
      trun("if", "1:1-1:3 IF", "1:3-1:3 EOF");
      trun("then", "1:1-1:5 THEN", "1:5-1:5 EOF");
      trun("else", "1:1-1:5 ELSE", "1:5-1:5 EOF");
      trun("let", "1:1-1:4 LET", "1:4-1:4 EOF");
      trun("in", "1:1-1:3 IN", "1:3-1:3 EOF");

      // IDENTIFICADORES
      trun("nome", "1:1-1:5 ID(nome)", "1:5-1:5 EOF");
      trun("variavel", "1:1-1:9 ID(variavel)", "1:9-1:9 EOF");
      trun("menorMaior", "1:1-1:11 ID(menorMaior)", "1:11-1:11 EOF");
      trun("LETRAMAIUSCULA", "1:1-1:15 ID(LETRAMAIUSCULA)", "1:15-1:15 EOF");
      trun("com_sublinhado", "1:1-1:15 ID(com_sublinhado)", "1:15-1:15 EOF");
      trun("comNumeros123", "1:1-1:14 ID(comNumeros123)", "1:14-1:14 EOF");
      trun("A1b2C33", "1:1-1:8 ID(A1b2C33)", "1:8-1:8 EOF");

      //OUTROS
      trun("set+", "1:1-1:4 ID(set)", "1:4-1:5 MAIS", "1:5-1:5 EOF");
      trun("45let", "1:1-1:3 LIT_INTEIRO(45)", "1:3-1:6 LET", "1:6-1:6 EOF");
      erun("_invalid", "1:1-1:2 lexical error: invalid character '_'");
      trun("if (x=1) then x=x+1 else x=0",
              "1:1-1:3 IF",
              "1:4-1:5 PARENTESE_ESQ",
              "1:5-1:6 ID(x)",
              "1:6-1:7 IGUAL",
              "1:7-1:8 LIT_INTEIRO(1)",
              "1:8-1:9 PARENTESE_DIR",
              "1:10-1:14 THEN",
              "1:15-1:16 ID(x)",
              "1:16-1:17 IGUAL",
              "1:17-1:18 ID(x)",
              "1:18-1:19 MAIS",
              "1:19-1:20 LIT_INTEIRO(1)",
              "1:21-1:25 ELSE",
              "1:26-1:27 ID(x)",
              "1:27-1:28 IGUAL",
              "1:28-1:29 LIT_INTEIRO(0)",
              "1:29-1:29 EOF");
   }

}
