%{
 
%}

OPARITMETICOS "+"|"-"|"*"|"/"|"**"
OPLOGICOS "&&"|"||"
LETRA[a-zA-Z]
DIGITO[0-9]
RECEBE"="
COMPARADORES"=="|"=>"|"<="|"!="|"<"|">"
LETRAMINUSCULA[a-z]+
LER"entrada>>"
SAIDA"saida<<"
INT"int"
FLOAT"float"
DOUBLE"double"
STRING"string"
PALAVRA\"[a-zA-Z0-9]*.*\"
COMENTARIO"#".*
VALORREAL{DIGITO}*\.{DIGITO}+
VALORINTEIRO{DIGITO}+
NOMEVAR{LETRAMINUSCULA}({LETRA}|{DIGITO})*
END";"
FIM"fim"
INI"ini"
IGNORE","|"("|")"|" "
IF"if"
ELSE"else"
FOR"for"
RETORNO"return"
INVALIDO .
%%

{FIM} {
	printf("FIM DO PROGRAMA: %s\n", yytext);
	}

{RETORNO} {
    printf("RETORNO: %s\n", yytext);
}

{IGNORE} {
        }


{INI} {
	printf("INICIO DO PROGRAMA: %s\n", yytext);

	}
{FOR} {
    printf("ESTRUTURA DE REPETICAO: %s\n", yytext);
}
{IF} {
    printf("ESTRUTURA CONDICIONAL: %s\n", yytext);
}
{ELSE} {
    printf("ESTRUTURA CONDICIONAL: %s\n", yytext);
}
{END} {
    printf("END: %s\n", yytext);
}
{COMPARADORES} {
    printf("COMPARAR: %s\n", yytext);
}
{RECEBE} {
	printf("RECEBE: %s\n", yytext);

	}
{PALAVRA} {
	printf("PALAVRA: %s\n", yytext);

	}
{INT} {
    printf("TIPO INTEIRO: %s\n", yytext);
}
{FLOAT} {
    printf("TIPO FLOAT: %s\n", yytext);
}
{DOUBLE} {
    printf("TIPO DOUBLE: %s\n", yytext);
}
{STRING} {
    printf("STRING: %s\n", yytext);
}
{SAIDA} {
    printf("OPERADOR DE SAIDA: %s\n", yytext);
}
{LER} {
    int a;
    scanf("%d",&a);
    printf("OPERADOR DE LEITURA: %s\n", yytext);
}
{NOMEVAR} {
    printf("NOME VARIÁVEL: %s\n",yytext);
}
{OPARITMETICOS} {

	printf("OPERADORES ARITMETICOS: %s\n", yytext);

}
{OPLOGICOS} {

	printf("OPERADORES LOGICOS: %s\n", yytext);

}

{COMENTARIO} {
    printf("COMENTARIO: %s\n", yytext);
}

{VALORREAL} {
    printf("VALOR REAL: %s\n", yytext);
}
{VALORINTEIRO} {
    printf("VALOR INTEIRO: %s\n", yytext);
}

{INVALIDO} {
    printf("caractere invalido: %s\n", yytext);
}

%%

int main(){
	yyin = fopen("code","r");
	yylex();
	fclose(yyin);
return 0;
}
