package absyn;

import env.Env;
import io.vavr.collection.Tree;
import types.TEXT;
import types.Type;

public class TyText extends Ty {

    public TyText(Loc loc) {
        super(loc);
    }

    @java.lang.Override
    public Tree.Node<String> toTree() {
        return Tree.of("text");
    }

    @Override
    public Type semantic(Env env) {
        return TEXT.T;
    }
}
