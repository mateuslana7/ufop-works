package parse;

import error.ErrorHelper;

import java_cup.runtime.Symbol;
import java_cup.runtime.SymbolFactory;
import java_cup.runtime.ComplexSymbolFactory.Location;
import java_cup.runtime.ComplexSymbolFactory;

%%

%public
%final
%class Lexer
%implements Terminals
%cupsym Terminals
%cup
%line
%column
%char

%eofval{
    return tok(EOF);
%eofval}

%ctorarg String unitName

%init{
   this.unit = unitName;
%init}

%{
   private String unit;

   private ComplexSymbolFactory complexSymbolFactory = new ComplexSymbolFactory();

   public SymbolFactory getSymbolFactory() {
      return complexSymbolFactory;
   }

   // auxiliary methods to construct terminal symbols at current location

   private Location locLeft() {
      return new Location(unit, yyline + 1, yycolumn + 1, yychar);
   }

   private Location locRight() {
      return new Location(unit, yyline + 1, yycolumn + 1 + yylength(), yychar + yylength());
   }

   private java_cup.runtime.Symbol tok(int type, Object value, Location left, Location right) {
      return complexSymbolFactory.newSymbol(yytext(), type, left, right, value);
    }

   private Symbol tok(int type, String lexeme, Object value) {
      return complexSymbolFactory.newSymbol(lexeme, type, locLeft(), locRight(), value);
   }

   private Symbol tok(int type, Object value) {
      return tok(type, yytext(), value);
   }

   private Symbol tok(int type) {
      return tok(type, null);
   }

   // Error handling
   private void error(String format, Object... args) {
      throw ErrorHelper.error(
         Loc.loc(new Location(unit, yyline+1, yycolumn+1),
                 new Location(unit, yyline+1, yycolumn+1+yylength())),
         "lexical error: " + format,
         args);
   }

   // Auxiliary variables
   private int commentLevel;
   private StringBuilder builder = new StringBuilder();
   private Location strLeft;
%}

%state COMMENT
%state STR

litint    = [0-9]+ //ER QUE DEFINE OS LITERAIS INTEIROS
id        = [a-zA-Z][a-zA-Z0-9_]* // ER QUE DEFINE OS IDENTIFICADORES

%%

<YYINITIAL>{
[ \t\f\n\r]+ { /* IGNORA */ }
"--" .*       { /* IGNORA */ }
"/-"         { yybegin(COMMENT); commentLevel = 1; }

//CLASSIFICACAO DOS LITERAIS INTEIROS
{litint}     { return tok(LIT_INTEIRO, yytext()); }

//CLASSIFICACAO DAS PALAVRAS RESERVADAS
bool         { return tok(BOOLEANO); }
int          { return tok(INTEIRO); }
if           { return tok(IF); }
then         { return tok(THEN); }
else         { return tok(ELSE); }
let          { return tok(LET); }
in           { return tok(IN); }

//CLASSIFICACAO DOS IDENTIFICADORES
{id}         { return tok(ID, yytext().intern()); }

//CLASSIFICACAO DOS OPERADORES
"+"          { return tok(MAIS); }
"="          { return tok(IGUAL); }

//CLASSIFICACAO DOS SINAIS DE PONTUACAO
"("          { return tok(PARENTESE_ESQ); }
")"          { return tok(PARENTESE_DIR); }
","          { return tok(VIRGULA); }
}

//TRATAMENTO DOS COMENTARIOS DE BLOCOS E BLOCOS ANINHADOS
<COMMENT>{
"/-"         { ++commentLevel; }
"-/"         { if (--commentLevel == 0) yybegin(YYINITIAL); }
[^]          { }
<<EOF>>      { yybegin(YYINITIAL); error("unclosed comment"); }
}

.            { error("invalid character '%s'", yytext()); }
