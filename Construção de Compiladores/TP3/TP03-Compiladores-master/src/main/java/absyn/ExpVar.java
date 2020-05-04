package absyn;

import env.Entry;
import env.Env;
import env.VarEntry;
import io.vavr.collection.Tree;
import types.Type;

import static error.ErrorHelper.notAVariable;
import static error.ErrorHelper.undefined;

public class ExpVar extends Exp {

   public final String name;

   public ExpVar(Loc loc, String name) {
      super(loc);
      this.name = name;
   }

   @Override
   public Tree.Node<String> toTree() {
      return Tree.of(annotateType("ExpVar: " + name));
   }

   @Override
   protected Type semantic_(Env env) {
      // retrieve the variable from the environment
      Entry t = env.venv.get(name);
      if (t == null)
         throw undefined(loc, "variable", name);
      // check if the it is in fact a variable
      if (! (t instanceof VarEntry) )
         throw notAVariable(loc, name);
      // the final type
      return ((VarEntry) t).type;
   }

}
