export const API_URL = "http://localhost:5001/";

export const INITIAL_FLEX_CODE = `
/*

    Here you can put your Bison code.

*/

// the function main is required and cannot be changed
#include "lex.yy.c"

int main(){
	yyin=fopen("entrada.lad","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}


`