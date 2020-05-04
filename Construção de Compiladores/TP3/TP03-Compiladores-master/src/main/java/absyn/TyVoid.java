package absyn;

import env.Env;
import io.vavr.collection.Tree;
import types.Type;
import types.VOID;

public class TyVoid extends Ty {

    public TyVoid(Loc loc) {
        super(loc);
    }

    @java.lang.Override
    public Tree.Node<String> toTree() {
        return Tree.of("void");
    }

    @Override
    public Type semantic(Env env) {
        return VOID.T;
    }
}