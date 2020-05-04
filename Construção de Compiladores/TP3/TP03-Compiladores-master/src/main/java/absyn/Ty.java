package absyn;

import env.Env;
import types.Type;

public abstract class Ty extends AST {

   public Ty(Loc loc) {
      super(loc);
   }

   // Check the type constructor
   public abstract Type semantic(Env env);
}
