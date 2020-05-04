package absyn;

import env.Entry;
import env.Env;
import env.FunEntry;
import env.Table;
import interpret.*;
import io.vavr.collection.List;
import io.vavr.collection.Tree;
import io.vavr.control.Option;
import io.vavr.render.ToTree;
import types.Type;

import static error.ErrorHelper.*;


public class ExpCall extends Exp {

   public final String name;
   public final List<Exp> arguments;

   public ExpCall(Loc loc, String name, List<Exp> arguments) {
      super(loc);
      this.name = name;
      this.arguments = arguments;
   }

   @Override
   public Tree.Node<String> toTree() {
      return Tree.of(annotateType("ExpCall: " + name),
                     arguments.map(ToTree::toTree));
   }

   @Override
   protected Type semantic_(Env env) {
      Entry entry = env.venv.get(name);
      if (entry == null)
         throw undefined(loc, "function", name);
      if (!(entry instanceof FunEntry))
         throw notAFunction(loc, name);
      FunEntry fentry = (FunEntry) entry;
      if (arguments.size() < fentry.formals.size())
         throw tooFewArguments(loc, name);
      if (arguments.size() > fentry.formals.size())
         throw tooMuchArguments(loc, name);
      fentry.formals.zipWith(arguments,
                             (f, a) -> {
                                if (!a.semantic(env).is(f))
                                   throw typeMismatch(a.loc, a.type, f);
                                return 0;
                             });
      return fentry.result;
   }

   @Override
   public Value eval(Table<Value> memory, List<Fun> functions) {
      List<Value> args = arguments.map(a -> a.eval(memory, functions));
      Option<Fun> option = functions.find(fun -> fun.name.id == name);
      if (option.isEmpty())
         return applyPrimitive(name, args);
      Fun f = option.get();
      memory.beginScope();
      f.parameters.zipWith(args, (p, v) -> {
         memory.put(p.id, v);
         return null; });
      Value x = f.body.eval(memory, functions);
      memory.endScope();
      return x;
   }

   private Value applyPrimitive(String name, List<Value> arguments) {

      double num, result;
      long x,y;
      String text = new String();
      String text1 = new String();
      char caract;

      switch (name) {
         case "print":
            System.out.println(((ValueText)arguments.get(0)).value);
            return new ValueVoid();
         case "printbool":
            System.out.println(((ValueBool)arguments.get(0)).value);
            return new ValueVoid();
         case "printint":
            System.out.println(((ValueInt)arguments.get(0)).value);
            return new ValueVoid();
         case "printreal":
            System.out.println(((ValueReal)arguments.get(0)).value);
            return new ValueVoid();
         case "real":
            num = (double)((ValueInt)arguments.get(0)).value;
            return new ValueReal(num);
         case "round":
            num = ((ValueReal)arguments.get(0)).value;
            return new ValueInt(Math.round(num));
         case "ceil":
            num = ((ValueReal)arguments.get(0)).value;
            num = Math.ceil(num);
            return new ValueInt((long)num);
         case "floor":
            num = ((ValueReal)arguments.get(0)).value;
            num = Math.floor(num);
            return new ValueInt((long)num);
         case "size":
            text = ((ValueText)arguments.get(0)).value;
            x = text.length();
            return new ValueInt(x);
         case "char":
            text = ((ValueText)arguments.get(0)).value;
            x = ((ValueInt)arguments.get(1)).value;
            caract = text.charAt((int)x);
            return new ValueText(caract+"");
         case "subtext":
            text = ((ValueText)arguments.get(0)).value;
            x = ((ValueInt)arguments.get(1)).value;
            y = ((ValueInt)arguments.get(2)).value;
            text = text.substring((int)x,(int)y);
            return new ValueText(text);
         case "concat":
            text = ((ValueText)arguments.get(0)).value;
            text1 = ((ValueText)arguments.get(1)).value;
            return new ValueText(text+text1);
         default:
            fatal("unknown primitive function");
            return new ValueVoid();
      }
   }
}
