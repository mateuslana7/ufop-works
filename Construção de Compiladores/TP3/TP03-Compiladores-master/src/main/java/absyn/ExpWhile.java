package absyn;

import env.Env;
import io.vavr.collection.Tree;
import types.Type;
import types.VOID;

public class ExpWhile extends Exp {
    public final Exp test;
    public final Exp body;

    public ExpWhile(Loc loc, Exp test, Exp body) {
        super(loc);
        this.test = test;
        this.body = body;
    }

    @Override
    public Tree.Node<String> toTree() {
        return Tree.of(annotateType("ExpWhile"),
                test.toTree(),
                body.toTree());
    }

    @Override
    protected Type semantic_(Env env) {
        return VOID.T;
    }
}

