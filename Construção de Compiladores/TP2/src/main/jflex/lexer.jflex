/* -*-Mode: java-*- */

%%

%public
%class Lexer
%type Token
%function getToken
%line
%column

%{  
    private Token tok(Token.T typ, Object val) {
        return new Token(typ, val, yyline, yycolumn);
    }

    private Token tok(Token.T typ) {
        return tok(typ, null);
    }
    
    private void error(String msg) {
    	ErrorMsg.error(yyline, yycolumn, "lexical error", msg);
    }

    private int commentLevel;
%}

%state COMMENT
%state STR

num = [0-9]+

%%

<YYINITIAL>{
[ \t\f\n\r]+          { /* IGNORA */ }
"--" .*               { /* IGNORA */ }
"/-"                  { yybegin(COMMENT); commentLevel = 1; }

//LITERAL INTEIRO
{num}                {return tok(Token.T.NUM, yytext());}

//CLASSIFICACAO DAS PALAVRAS RESERVADAS
"bool"                { return tok(Token.T.BOOLEANO); }
"int"                 { return tok(Token.T.INTEIRO); }
"if"                  { return tok(Token.T.IF); }
"then"                { return tok(Token.T.THEN); }
"else"                { return tok(Token.T.ELSE); }
"let"                 { return tok(Token.T.LET); }
"in"                  { return tok(Token.T.IN); }

//CLASSIFICACAO DOS IDENTIFICADORES
[a-zA-Z][a-zA-Z0-9_]*         { return tok(Token.T.ID, yytext().intern()); }

//CLASSIFICACAO DOS OPERADORES
"="                   { return tok(Token.T.IGUAL); }
"+"                   { return tok(Token.T.MAIS); }

//CLASSIFICACAO SINAIS DE PONTUACAO
"("                   { return tok(Token.T.PARENTESE_ESQ); }
")"                   { return tok(Token.T.PARENTESE_DIR); }
","                   { return tok(Token.T.VIRGULA); }

<<EOF>>               { return tok(Token.T.EOF); }
}

//TRATAMENTO DOS COMENTARIOS DE BLOCOS E BLOCOS ANINHADOS
<COMMENT>{
"/-"         { ++commentLevel; }
"-/"         { if (--commentLevel == 0) yybegin(YYINITIAL); }
[^]          { }
<<EOF>>      { yybegin(YYINITIAL); error("unclosed comment"); }
}

.                     { error("illegal character: " + yytext()); }
