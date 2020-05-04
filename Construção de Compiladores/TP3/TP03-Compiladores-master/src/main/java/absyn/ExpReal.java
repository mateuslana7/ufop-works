package absyn;

import env.Env;
import env.Table;
import interpret.Value;
import interpret.ValueReal;
import io.vavr.collection.List;
import io.vavr.collection.Tree;
import types.REAL;
import types.Type;

public class ExpReal extends Exp {

    public final double value;

    public ExpReal(Loc loc, String value) {
        super(loc);
        this.value = new Double(value);
    }

    @Override
    public Tree.Node<String> toTree() {
        return Tree.of(annotateType("ExpReal: " + value));
    }

    @Override
    protected Type semantic_(Env env) {
        return REAL.T;
    }

    @Override
    public Value eval(Table<Value> memory, List<Fun> functions) {
        return new ValueReal(value);
    }
}
