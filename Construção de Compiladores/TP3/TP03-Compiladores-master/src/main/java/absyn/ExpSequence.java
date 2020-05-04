package absyn;

import env.Env;
import io.vavr.collection.List;
import io.vavr.collection.Tree;
import types.Type;
import types.VOID;

public class ExpSequence extends Exp {
    public final List<Exp> sequence;

    public ExpSequence(Loc loc, List<Exp> sequence) {
        super(loc);
        this.sequence = sequence;
    }

    @Override
    public Tree.Node<String> toTree() {
        return Tree.of(annotateType("ExpSequence"), sequence.map(Exp::toTree));
    }

    @Override
    protected Type semantic_(Env env) {
        sequence.forEach(exp -> exp.semantic(env));
        return sequence.isEmpty() ? VOID.T : sequence.last().type;
    }
}