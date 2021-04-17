%{
#include <string.h>
#include <stdio.h>
%}

NUM [0-9]+\.?[0-9]*
VARS [a-zA-Z_]+[a-zA-Z0-9_]*
INI "(U-u)>>"
FIM "<<(U-u)"	
STRING "lad_string"
INT "lad_int"
FLOAT "lad_float"
SQRT "lad_sqrt"
IF "lad"
ELSE "gelson"
WHILE "lad_while"
PRINT "lad_out"
IN "lad_in"
STR ["][^"]*["]
ENDL "lad_line"
DI "[i::]"
DF "[f::]"
DS "[s::]"

COMENTARIO "//"
IGNORE [\s\t\n" "]


%%
{INI} { return INI;	}
{FIM} {	return FIM;	}
{IF} { return IF; }
{ELSE} { return ELSE; }
{WHILE} { return WHILE;	}
{PRINT} { return PRINTT; }
{IN} { return IN; }
{STRING} { return STRING; }
{INT} { return INT; }
{FLOAT} { return FLOAT; }
{SQRT} { return SQRT; }
{ENDL} { return ENDL; }
{DI} { return DI; }
{DF} { return DF; }
{DS} { return DS; }
{VARS} {
	strcpy(yylval.str,yytext);
	return VARS;
	}

{STR} {
    char aux[50];
    strncpy ( aux, &yytext[1], strlen(yytext)-2);
    aux[strlen(yytext)-2]='\0';
    strcpy (yylval.str, aux);
	return STR;  
}


{NUM} {
	yylval.flo = atof(yytext);
	return NUM;
	}

[-+()=%/*^,{};:\[\]] {return *yytext;
			}
{COMENTARIO}..*|"/**"(..*|{IGNORE})*"*/" { ; }

">" {yylval.fn = 1; return CMP; }
"<" {yylval.fn = 2; return CMP; }
"!=" {yylval.fn = 3; return CMP; }
"==" {yylval.fn = 4; return CMP; }
">=" {yylval.fn = 5; return CMP; }
"<=" {yylval.fn = 6; return CMP; }
{IGNORE} {;}
. {
	// printf("(%s) Ingonrado\n",yytext);
}

%%

int yywrap() {
   return 1;
}