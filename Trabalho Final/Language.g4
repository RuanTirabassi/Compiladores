Program      ::= StatementList

StatementList::= Statement (Statement)*

Statement    ::= VariableDeclaration
               | Assignment
               | IfStatement
               | WhileStatement
               | ReturnStatement

VariableDeclaration ::= Type IDENTIFIER SEMICOLON
                      | Type IDENTIFIER ASSIGN_OP Expression SEMICOLON

Assignment   ::= IDENTIFIER ASSIGN_OP Expression SEMICOLON

IfStatement  ::= IF LEFT_PAREN Expression RIGHT_PAREN Block
               | IF LEFT_PAREN Expression RIGHT_PAREN Block ELSE Block

WhileStatement ::= WHILE LEFT_PAREN Expression RIGHT_PAREN Block

ReturnStatement ::= RETURN Expression SEMICOLON

Expression   ::= SimpleExpression (RelationalOperator SimpleExpression)?
SimpleExpression ::= Term (AddOp Term)*
Term         ::= Factor (MulOp Factor)*
Factor       ::= LEFT_PAREN Expression RIGHT_PAREN
               | IDENTIFIER
               | INTEGER_LITERAL
               | FLOAT_LITERAL

Type         ::= "int" | "float"

RelationalOperator ::= "==" | "!=" | "<" | ">"
AddOp        ::= "+" | "-"
MulOp        ::= "*" | "/"

Block        ::= "{" StatementList "}"
