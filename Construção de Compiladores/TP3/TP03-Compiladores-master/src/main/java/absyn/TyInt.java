package absyn;

import env.Env;
import io.vavr.collection.Tree;
import types.INT;
import types.Type;

public class TyInt extends Ty {

   public TyInt(Loc loc) {
      super(loc);
   }

   @java.lang.Override
   public Tree.Node<String> toTree() {
      return Tree.of("int");
   }

   @Override
   public Type semantic(Env env) {
      return INT.T;
   }
}
