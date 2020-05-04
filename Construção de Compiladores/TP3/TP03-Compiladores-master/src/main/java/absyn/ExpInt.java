package absyn;

import env.Env;
import env.Table;
import interpret.Value;
import interpret.ValueInt;
import io.vavr.collection.List;
import io.vavr.collection.Tree;
import types.INT;
import types.Type;

public class ExpInt extends Exp {

   public final long value;

   public ExpInt(Loc loc, String value) {
      super(loc);
      this.value = new Long(value);
   }

   @Override
   public Tree.Node<String> toTree() {
      return Tree.of(annotateType("ExpInt: " + value));
   }

   @Override
   protected Type semantic_(Env env) {
      return INT.T;
   }

   @Override
   public Value eval(Table<Value> memory, List<Fun> functions) {
      return new ValueInt(value);
   }
}
