package absyn;

import env.Entry;
import env.Env;
import env.FunEntry;
import env.Table;
import interpret.Value;
import io.vavr.collection.List;
import io.vavr.collection.Tree;
import io.vavr.render.ToTree;

import static error.ErrorHelper.noMain;

public class Program extends AST {

   public final List<Fun> functions;

   public Program(Loc loc, List<Fun> functions) {
      super(loc);
      this.functions = functions;
   }

   @java.lang.Override
   public Tree.Node<String> toTree() {
      return Tree.of("Program",
                     functions.map(ToTree::toTree));
   }

   // A program is a sequence of one or more mutually recursive
   // function declarations. There should be at least one function
   // named main returning an integer and with an integer argument.

   // Semantic analysis of the program should check each function
   // declaration, adding it to the environment, as well as check the
   // main function existence.

   // Do semantic analysis of the program.
   public void semantic(Env env) {
      functions.forEach(f -> f.checkSignature(env));
      functions.forEach(f -> f.checkBody(env));

      // check main
      Entry entry = env.venv.get("main".intern());
      if (! (entry instanceof FunEntry))
         throw noMain(loc);
   }

   public void execute() {
      Exp prg = new ExpCall(null, "main", List.of(new ExpInt(null, "0")));
      Table<Value> memory = new Table<>();
      prg.eval(memory, functions);
   }

}
