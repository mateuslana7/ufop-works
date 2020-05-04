package absyn;

import env.Env;
import io.vavr.collection.Tree;
import types.BOOL;
import types.INT;
import types.Type;

import static error.ErrorHelper.typeMismatch;

public class ExpIf extends Exp {

   public final Exp test;
   public final Exp alt1;
   public final Exp alt2;

   public ExpIf(Loc loc, Exp test, Exp alt1, Exp alt2) {
      super(loc);
      this.test = test;
      this.alt1 = alt1;
      this.alt2 = alt2;
   }

   @Override
   public Tree.Node<String> toTree() {
      return Tree.of(annotateType("ExpIf"),
                     test.toTree(),
                     alt1.toTree(),
                     alt2.toTree());
   }

   @Override
   protected Type semantic_(Env env) {
      // check the test
      test.semantic(env);
      if (! test.type.is(BOOL.T))
         throw typeMismatch(test.loc, test.type, BOOL.T);
      // check the alternatives
      alt1.semantic(env);
      alt2.semantic(env);
      if (alt1.type.is(alt2.type))
         return alt2.type;
      if (alt2.type.is(alt1.type))
         return alt1.type;
      throw typeMismatch(alt2.loc, alt2.type, alt1.type);
   }

}
