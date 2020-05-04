package env;

import io.vavr.collection.List;
import types.*;

public class Env {

  public Table<Type> tenv;
  public Table<Entry> venv;

  public Env() {
    tenv = new Table<Type>();
    venv = new Table<Entry>();
    put(venv, "print", new FunEntry(List.of(TEXT.T), VOID.T) );
    put(venv, "printbool", new FunEntry(List.of(BOOL.T), VOID.T) );
    put(venv, "printint", new FunEntry(List.of(INT.T), VOID.T) );
    put(venv, "printreal", new FunEntry(List.of(REAL.T), VOID.T) );
    put(venv, "real", new FunEntry(List.of(INT.T), REAL.T) );
    put(venv, "round", new FunEntry(List.of(REAL.T), INT.T) );
    put(venv, "ceil", new FunEntry(List.of(REAL.T), INT.T) );
    put(venv, "floor", new FunEntry(List.of(REAL.T), INT.T) );
    put(venv, "size", new FunEntry(List.of(TEXT.T), INT.T) );
    put(venv, "char", new FunEntry(List.of(TEXT.T,INT.T), TEXT.T) );
    put(venv, "subtext", new FunEntry(List.of(TEXT.T,INT.T,INT.T), TEXT.T) );
    put(venv, "concat", new FunEntry(List.of(TEXT.T,TEXT.T), TEXT.T) );

  }

  private static <E> void put(Table<E> table, String name, E value) {
    table.put(name.intern(), value);
  }

   @Override
   public String toString() {
      return "Env{" +
         "tenv=" + tenv +
         ", venv=" + venv +
         '}';
   }

}
