import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class Main {
   private static void run(String[] args) throws IOException {
      java.io.Reader input;
      String fileName;

      if (args.length == 0) {
         fileName = "stdin";
         input = new java.io.InputStreamReader(System.in);
      }
      else {
         fileName = args[0];
         input = new java.io.FileReader(fileName);
      }

      Lexer lex = new Lexer(input);
      Parser p = new Parser(lex);

      p.parse();
   }

   public static void main(String[] args) {
      /*Scanner in = new Scanner(System.in);
      String input = "";

      System.out.println("Insira o programa: ");

      do{

      }while();*/

      try {
         run(args);
      }
      catch (FileNotFoundException e) {
         System.err.printf("file not found: %s\n", args[0]);
         System.exit(1);
      }
      catch (IOException e) {
         System.err.println("I/O error");
         System.exit(2);
      }
   }
}
