# picnic-java

*Picnic* is a toy programming language, implemented in Java. It is an
_easy understanding_ programming language based on the book
Introduction to Compiler Design, by Torben Ægidius Mogensen.


# Grammar

- The syntax of the language is given by a context free grammar.
- Only the production rules are explicitly given.
- The sets of terminals and non-terminals are obtained from the rules.
- The initial symbol is the non-terminal on the left side of the first production rule.

Production rule                               | Internal representation
----------------------------------------------|---------------------------------
_Program_ → _Funs_                            | Program
_Funs_ → _Fun_                                | Sequence of Function definitions
_Funs_ → _Fun_ _Funs_                         |
_Fun_ → _TypeId_ `(` _TypeIds_ `)` `=` _Exp_  | Function definition
_TypeId_ → `bool` `id`                        | Type and identififier
_TypeId_ → `int` `id`                         |
_TypeIds_ → _TypeId_                          | Sequence of types and identifiers
_TypeIds_ → _TypeId_ _TypeIds_                |
_Exp_ → `num`                                 | Expressions
_Exp_ → `id`                                  |
_Exp_ → _Exp_ `+` _Exp_                       |
_Exp_ → _Exp_ `<` _Exp_                       |
_Exp_ →  `id` `(` _Exps_ `)`                  |
_Exp_ →  `if` _Exp_ `then` _Exp_ `else` _Exp_ |
_Exp_ →  `let` `id` `=` _Exp_ `in` _Exp_      |
_Exps_ → _Exp_                                | Sequence of expressions
_Exps_ → _Exp_ `,` _Exps_                     |
