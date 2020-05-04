package parse;

import absyn.Loc;
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
      throw ErrorHelper.error(Loc.loc(locLeft(), locRight()),
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

litint    = [0-9]+
litbool   = true | false
id        = [a-zA-Z][a-zA-Z0-9_]*
real      = [0-9]+ "."[0-9]* | [0-9]* "." [0-9]+

%%

<YYINITIAL>{
[ \t\f\n\r]+ { /* skip */ }
"#" .*       { /* skip */ }
"{#"         { yybegin(COMMENT); commentLevel = 1; }

{litint}     { return tok(LITINT, yytext()); }
{litbool}    { return tok(LITBOOL, yytext()); }


void         { return tok(VOID); }
bool         { return tok(BOOL); }
real         {return tok(REAL);}
text         {return tok(TEXT);}
int          { return tok(INT); }
if           { return tok(IF); }
then         { return tok(THEN); }
else         { return tok(ELSE); }
let          { return tok(LET); }
in           { return tok(IN); }
while        { return tok(WHILE); }
do           { return tok(DO); }
nil          { return tok(NIL); }


{id}         { return tok(ID, yytext().intern()); }
{real}         { return tok(LITREAL, yytext().intern()); }


":="         { return tok(ASSIGN); }
"="          { return tok(EQ); }
"~="         { return tok(NE); }
"<"          { return tok(LT); }
"<="         { return tok(LE); }
">"          { return tok(GT); }
">="         { return tok(GE); }
"&&"         { return tok(AND); }
"||"         { return tok(OR); }
"+"          { return tok(PLUS); }
"-"          { return tok(MINUS); }
"*"          { return tok(TIMES); }
"/"          { return tok(DIV); }
"^"          { return tok(POWER); }
"("          { return tok(LPAREN); }
")"          { return tok(RPAREN); }
","          { return tok(COMMA); }
}

<COMMENT>{
"{#"         { ++commentLevel; }
"#}"         { if (--commentLevel == 0) yybegin(YYINITIAL); }
[^]          { }
<<EOF>>      { yybegin(YYINITIAL); error("unclosed comment"); }
}

<STR>{
\"           { yybegin(YYINITIAL); return tok(LITTEXT, builder.toString(), strLeft, locRight()); }
\\ b         { builder.append('\b'); }
\\ t         { builder.append('\t'); }
\\ n         { builder.append('\n'); }
\\ r         { builder.append('\r'); }
\\ f         { builder.append('\f'); }
\\ \\        { builder.append('\\'); }
\\ \"        { builder.append('"'); }
\\ [0-9]{3}  { builder.append((char)(Integer.parseInt(yytext().substring(1)))); }
\\ .         { error("invalid escape arguments in string literal"); }
[^\"\n\\]+   { builder.append(yytext()); }
\n           { error("invalid newline in string literal"); }
<<EOF>>      { yybegin(YYINITIAL); error("unclosed string literal"); }
}

.            { error("invalid character '%s'", yytext()); }
