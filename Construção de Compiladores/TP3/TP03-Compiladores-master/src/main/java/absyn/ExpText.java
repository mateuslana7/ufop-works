package absyn;

import env.Env;
import env.Table;
import interpret.Value;
import interpret.ValueText;
import io.vavr.collection.List;
import io.vavr.collection.Tree;
import types.TEXT;
import types.Type;

public class ExpText extends Exp {

    public final String value;

    public ExpText(Loc loc, String value) {
        super(loc);
        this.value = new String(value);
    }

    @Override
    public Tree.Node<String> toTree() {
        return Tree.of(annotateType("ExpText: " + value));
    }

    @Override
    protected Type semantic_(Env env) {
        return TEXT.T;
    }

    @Override
    public Value eval(Table<Value> memory, List<Fun> functions) {
        return new ValueText(value);
    }
}
