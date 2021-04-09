<template>
    <div class="container-fluid">
        <codemirror 
            v-model="code"
            :options="cmOptions"
            @input="onCmCodeChange"
            @beforeChange="onCmBlockLastLines"
            style="CodeMirror"
            />
    </div>
</template>

<script>
import 'codemirror/mode/clike/clike'
// theme css
import 'codemirror/theme/dracula.css'
export default {
    props: {
        placeholder: String,
        codeType: String,
        type: String
    },
    methods: {
        onCmCodeChange(newCode) {
            this.code = newCode;
        },
        onCmBlockLastLines(cm, change){
            if(this.codeType == 'flex' || this.codeType == 'bison'){
                if(cm.lineCount()-11 <= change.from.line){
                    change.cancel();
                }
            }
        },
        selectInitialCode(codeType){
            if(codeType == 'flex') {
                if(this.type == 'lexical') {
                    return `%{
 
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
PALAVRA\\"[a-zA-Z0-9]*.*\\"
COMENTARIO"#".*
VALORREAL{DIGITO}*\\.{DIGITO}+
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
	printf("FIM DO PROGRAMA: %s\\n", yytext);
	}

{RETORNO} {
    printf("RETORNO: %s\\n", yytext);
}

{IGNORE} {
        }


{INI} {
	printf("INICIO DO PROGRAMA: %s\\n", yytext);

	}
{FOR} {
    printf("ESTRUTURA DE REPETICAO: %s\\n", yytext);
}
{IF} {
    printf("ESTRUTURA CONDICIONAL: %s\\n", yytext);
}
{ELSE} {
    printf("ESTRUTURA CONDICIONAL: %s\\n", yytext);
}
{END} {
    printf("END: %s\\n", yytext);
}
{COMPARADORES} {
    printf("COMPARAR: %s\\n", yytext);
}
{RECEBE} {
	printf("RECEBE: %s\\n", yytext);

	}
{PALAVRA} {
	printf("PALAVRA: %s\\n", yytext);

	}
{INT} {
    printf("TIPO INTEIRO: %s\\n", yytext);
}
{FLOAT} {
    printf("TIPO FLOAT: %s\\n", yytext);
}
{DOUBLE} {
    printf("TIPO DOUBLE: %s\\n", yytext);
}
{STRING} {
    printf("STRING: %s\\n", yytext);
}
{SAIDA} {
    printf("OPERADOR DE SAIDA: %s\\n", yytext);
}
{LER} {
    int a;
    scanf("%d",&a);
    printf("OPERADOR DE LEITURA: %s\\n", yytext);
}
{NOMEVAR} {
    printf("NOME VARIÁVEL: %s\\n",yytext);
}
{OPARITMETICOS} {

	printf("OPERADORES ARITMETICOS: %s\\n", yytext);

}
{OPLOGICOS} {

	printf("OPERADORES LOGICOS: %s\\n", yytext);

}

{COMENTARIO} {
    printf("COMENTARIO: %s\\n", yytext);
}

{VALORREAL} {
    printf("VALOR REAL: %s\\n", yytext);
}
{VALORINTEIRO} {
    printf("VALOR INTEIRO: %s\\n", yytext);
}

{INVALIDO} {
    printf("caractere invalido: %s\\n", yytext);
}

%%


/*

    The function main is required and cannot be changed

*/
int main(){
	yyin = fopen("code","r");
	yylex();
	fclose(yyin);
return 0;
}`;
                } else {
                    return `%{
#include <string.h>
#include <stdio.h>
%}

NUM [0-9]+\\.?[0-9]*
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
IGNORE [\\s\\t\\n" "]


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
    aux[strlen(yytext)-2]='\\0';
    strcpy (yylval.str, aux);
	return STR;  
}


{NUM} {
	yylval.flo = atof(yytext);
	return NUM;
	}

[-+()=%/*^,{};:\\[\\]] {return *yytext;
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
	// printf("(%s) Ingonrado\\n",yytext);
}

%%

/*

    The function yywrap is required and cannot be changed

*/



int yywrap() {
   return 1;
}`;
                }
            } 
            if(codeType == 'bison') return `%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>	
/*
TIPOS DE VARIAVEIS DENTRO DE LISTA DE VARIAVEIS
0 -> INTEIRO
1 -> PONTO FLUTUANTE
2 -> STRING
*/

// ESTRUTURA DA LISTA DE VARIAVEIS DO PROJETO
typedef struct vars{ 
    int nodetype;
    char name[100];
    double valor;
    char valors[2000];
    struct vars *prox;
} VARIAVEL;

/*
    Função que adiciona um float na lista de variaveis
    @param list - lista de variaveis do programa
    @param name - nome da variavel na lista
*/
VARIAVEL * push_back_float(VARIAVEL * list, char name[]){
    VARIAVEL *new = (VARIAVEL *)malloc(sizeof(VARIAVEL));
    strcpy(new->name, name);
    new->prox = list;
    new->nodetype = 1;
    return new;
}

/*
    Função que adiciona um inteiro na lista de variaveis
    @param list - lista de variaveis do programa
    @param name - nome da variavel na lista
*/
VARIAVEL * push_back_int(VARIAVEL * list, char name[]){
    VARIAVEL *new = (VARIAVEL *)malloc(sizeof(VARIAVEL));
    strcpy(new->name, name);
    new->prox =  list;
    new->nodetype = 0;
    return new;
}

/*
    Função que adiciona uma string na lista de variaveis
    @param list - lista de variaveis do programa
    @param name - nome da variavel na lista
*/
VARIAVEL * push_back_string(VARIAVEL *list, char name[]){
    VARIAVEL *new = (VARIAVEL *)malloc(sizeof(VARIAVEL));
    strcpy(new->name, name);
    new->prox = list;
    new->nodetype = 2;
    return new;
}

/*
    Função busca uma variavel na lista de variaveis do programa
    @param list - lista de variaveis do programa
    @param name - nome da variavel na lista
*/
VARIAVEL * srchVar(VARIAVEL *list, char name[]){
    VARIAVEL *aux = list;
    while (aux != NULL){
        if (strcmp(name, aux->name) == 0) return aux;
        aux = aux->prox;
    }
    return aux;
}

/*
    Estrutura de nó para a arvore de derivação
*/
typedef struct ast{ 
    int nodetype;
    struct ast *l; 
    struct ast *r;
} Ast;

/*Estrutura de um número*/
typedef struct numval{ 
    int nodetype;
    double valor;
} Numval;

/*Estrutura de um número*/
typedef struct endl{ 
    int nodetype;
} Endl;

/*Estrutura de um nome de variável*/
typedef struct varval{ 
    int nodetype;
    char var[50];
    int size;
    Ast *length;
} Varval;

/*Estrutura de um texto*/
typedef struct texto{ 
    int nodetype;
    char txt[50];
} TXT;

/*Estrutura de fluxo*/
typedef struct flow{ 
    int nodetype;
    Ast *cond; /*condição*/
    Ast *tl;   /*then, ou seja, verdade*/
    Ast *el;   /*else*/
} Flow;

/*Estrutura para um nó de atribuição na arvore de derivacao.*/
typedef struct symasgn{ 
    int nodetype;
    char s[50];
    Ast *v;
    int pos;
    Ast *indice;
} Symasgn;

/*Lista de variaveis da aplicação.*/
VARIAVEL * varList;
/*Variavel auxiliar .*/
VARIAVEL * aux;

/*
    Função cria um no de pular linha em string
    @param nodetype - tipo de nó para ser usado pelos eval's
*/
Ast *newendl(int nodetype){ 
    Endl *a = (Endl *)malloc(sizeof(Endl));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    return (Ast *)a;
}

/*
    Função cria um nó na arvore de derivação
    @param nodetype - tipo de nó para ser usado pelos eval's
    @param l - ponteiro para a esquerda na arvore
    @param r - ponteiro para a direita na arvore
*/
Ast * newast(int nodetype, Ast *l, Ast *r){ 
    Ast *a = (Ast *)malloc(sizeof(Ast));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

/*
    Função cria um nó na arvore de derivação
    @param nodetype - tipo de nó para ser usado pelos eval's
    @param l - ponteiro para a esquerda na arvore
    @param r - ponteiro para a direita na arvore
*/
Ast *newvari(int nodetype, char nome[50]){ 
    Varval *a = (Varval *)malloc(sizeof(Varval));
    if (!a)
    {
        printf("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    strcpy(a->var, nome);
    return (Ast *)a;
}

/*
    Função que cria um nó de ponto flutuante na arvore de derivação
    @param nodetype - tipo de nó para ser usado pelos eval's
*/
Ast *newnum(double d){ 
    Numval *a = (Numval *)malloc(sizeof(Numval));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->valor = d;
    return (Ast *)a;
}

/*
    Função que cria um nó de fluxo - if/else/while
    @param nodetype - tipo de nó para ser usado pelos eval's
    @param cond - condição para ir para o then ou para o else
    @param tl - ponteiro para lista de comandos do then
    @param el - ponteiro para lista de comandos do else
*/
Ast *newflow(int nodetype, Ast *cond, Ast *tl, Ast *el){ 
    Flow *a = (Flow *)malloc(sizeof(Flow));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (Ast *)a;
}

/*
    Função que cria um nó de comparação - if/else/while
    @param cmptype - tipo de comparação a ser relaizada
    @param l - ponteiro para a esquerda 
    @param r - ponteiro para a direita
*/
Ast *newcmp(int cmptype, Ast *l, Ast *r){ 
    Ast *a = (Ast *)malloc(sizeof(Ast));
    if (!a){
        printf("out of space");
        exit(0);
    }
    /*Para pegar o tipe de teste, definido no arquivo.l e utilizar na função eval()*/
    a->nodetype = '0' + cmptype; 
    a->l = l;
    a->r = r;
    return a;
}

/*
    Função que cria um nó de atribuição
    @param s - tipo de comparação a ser relaizada
    @param v - ponteiro do nó atual
*/
Ast *newasgn(char s[50], Ast *v){ 
    Symasgn *a = (Symasgn *)malloc(sizeof(Symasgn));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = '=';
    strcpy(a->s, s);
    a->v = v; 
    return (Ast *)a;
}

/*
    Função que recupera o nome/referência de uma variável, neste caso o número
    @param s - nome da variavel
*/
Ast *newValorVal(char s[]){ 
    Varval *a = (Varval *)malloc(sizeof(Varval));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = 'N';
    strcpy(a->var, s);
    return (Ast *)a;
}

/*
    Função que recupera o nome/referência de uma variável, neste caso o número
    @param s - nome da variavel
*/
Ast *newValorValS(char s[50]){ 
    Varval *a = (Varval *)malloc(sizeof(Varval));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = 'Q';
    strcpy(a->var, s);
    return (Ast *)a;
}

/*
    Função que cria um nó de busca na arvore de recursão 
    @param nodetype - tipo de nó 
    @param s - nome
*/
Ast *searchVar(int nodetype, char s[50]){
    Symasgn *a = (Symasgn *)malloc(sizeof(Symasgn));
    if (!a){
        printf("out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    strcpy(a->s, s);
    return (Ast *)a;
}

/*
    Função que executa arvore de recursão e recupera valor string
    @param a - nó atual da arvore
*/
char *evalString(Ast *a){
    VARIAVEL *aux1;
    char *v2;

    switch (a->nodetype){
    case 'Q':
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        return aux1->valors;
        break;

    default:
        printf("evalString: internal error: bad node %c \\n", a->nodetype);
        break;
    }

    return v2;
}

/*
    Função que executa arvore de recursão e recupera valor numerico
    @param a - nó atual da arvore
*/
double evalAux(Ast *a){
    double v;
    double value;
    char v1[50];
    char *v2;
    VARIAVEL *aux1;
    if (!a){
        printf("internal error, null eval");
        return 0.0;
    }
    switch (a->nodetype){
    case 'K':
        v = ((Numval *)a)->valor;
        break; 
    case 'N':
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        if (aux1->nodetype == 1 || aux1->nodetype == 0)
            v = aux1->valor;
        else
            printf("Variável não é do tipo Numérico \\n");
        break;
    case '+':
        v = evalAux(a->l) + evalAux(a->r);
        break;
    case '-':
        v = evalAux(a->l) - evalAux(a->r);
        break; 
    case '*':
        v = evalAux(a->l) * evalAux(a->r);
        break; 
    case '/':
        v = evalAux(a->l) / evalAux(a->r);
        break; 
    case '%':
        v = ((int)evalAux(a->l)) % ((int)evalAux(a->r));
        break; 
    case 'M':
        v = -evalAux(a->l);
        break; 

    case '1':
        v = (evalAux(a->l) > evalAux(a->r)) ? 1 : 0;
        break; 
    case '2':
        v = (evalAux(a->l) < evalAux(a->r)) ? 1 : 0;
        break;
    case '3':
        v = (evalAux(a->l) != evalAux(a->r)) ? 1 : 0;
        break;
    case '4':
        v = (evalAux(a->l) == evalAux(a->r)) ? 1 : 0;
        break;
    case '5':
        v = (evalAux(a->l) >= evalAux(a->r)) ? 1 : 0;
        break;
    case '6':
        v = (evalAux(a->l) <= evalAux(a->r)) ? 1 : 0;
        break;
    default:
        printf("EVA varList: internal error: bad node %c \\n", a->nodetype);
        break;
    }
    return v;
}

/*
    Função que realiza parse em valores para string
    @param a - nó atual da arvore
*/
char *parseSTR(Ast *a){
    char *v = (char *)malloc(1000 * sizeof(char));
    double value;
    VARIAVEL *aux1;
    if (!a){
        printf("Internal error, null eval");
        return NULL;
    }
    switch (a->nodetype){
    case '$':
        return ((Varval *)a->l)->var;
        break;
    case '7':
        value = evalAux(a->l);
        sprintf(v, "%.2lf", value);
        break;
    case '8':
        value = evalAux(a->l);
        sprintf(v, "%.0lf", value);
        break;
    case '9':
        aux1 =  srchVar( varList, ((Symasgn *)(a->l))->s);
        if (aux1->nodetype == 2)
            return aux1->valors;
        else
            printf("Variavel não é do tipo String %c \\n", a->nodetype);
        break;
    default:
        printf("STRING: internal error: bad node %c \\n", a->nodetype);
        break;
    }
    return v;
}

/*
    Função que executa todas as operações do programa recursivamente
    @param a - nó atual da arvore
*/
double eval(Ast *a){
    double v;
    double value;
    char v1[50];
    char *v2;
    VARIAVEL *aux1;
    if (!a){
        printf("internal error, null eval");
        return 0.0;
    }
    switch (a->nodetype)
    {
    case 'K':
        v = ((Numval *)a)->valor;
        break; 
    case 'N':
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        v = aux1->valor;
        break;
    case '+':
        v = eval(a->l) + eval(a->r);
        break; 
    case '-':
        v = eval(a->l) - eval(a->r);
        break; 
    case '*':
        v = eval(a->l) * eval(a->r);
        break; 
    case '/':
        v = eval(a->l) / eval(a->r);
        break;
    case '%':
        v = (int)eval(a->l) % (int)eval(a->r);
        break;
    case 'M':
        v = -eval(a->l);
        break; 
    case '1':
        v = (eval(a->l) > eval(a->r)) ? 1 : 0;
        break;
    case '2':
        v = (eval(a->l) < eval(a->r)) ? 1 : 0;
        break;
    case '3':
        v = (eval(a->l) != eval(a->r)) ? 1 : 0;
        break;
    case '4':
        v = (eval(a->l) == eval(a->r)) ? 1 : 0;
        break;
    case '5':
        v = (eval(a->l) >= eval(a->r)) ? 1 : 0;
        break;
    case '6':
        v = (eval(a->l) <= eval(a->r)) ? 1 : 0;
        break;

    case '=':
        v = eval(((Symasgn *)a)->v); 
        aux =  srchVar( varList, ((Symasgn *)a)->s);
        if (aux->nodetype == 1 || aux->nodetype == 0){ 
            aux->valor = v;
        }
        break;

    case 'I': 
        if (eval(((Flow *)a)->cond) != 0){
            if (((Flow *)a)->tl) v = eval(((Flow *)a)->tl); 
            else v = 0.0;
        } else {
            if (((Flow *)a)->el) v = eval(((Flow *)a)->el); 
            else v = 0.0;
        }
        break;

    case 'W':
        v = 0.0;
        if (((Flow *)a)->tl){
            while (eval(((Flow *)a)->cond) != 0){
                v = eval(((Flow *)a)->tl);
            }
        }
        break;

    case 'L':
        eval(a->l);
        v = eval(a->r);
        break; 

    case 'P':
        v = eval(a->l); 
        printf("%.2f\\n", v);
        break; 

    case 'S':
        fflush(stdin);
        scanf("%lf", &v);
        fflush(stdin);
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        aux1->valor = v;
        break;

    case 'T':
        fflush(stdin);
        scanf("%[^\\n]s", v1);
        fflush(stdin);
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        strcpy(aux1->valors, v1);
        break;

    case 'Y':
        v2 = evalString(a->l);
        printf("%s\\n", v2);
        break;

    // float
    case 'q':
        eval(a->r);
        eval(a->l);
        break;
    case 'p':
        value = eval(a->l);
        printf("%.2lf", value);
        break;

    // int
    case 'v':
        eval(a->r);
        eval(a->l);
        break; 
    case 'u':
        value = eval(a->l);
        printf("%d", (int)value);
        break;

    // "str"
    case 'r':
        eval(a->r);
        printf("%s", ((Varval *)a->l)->var);
        break;
    case 's':
        printf("%s", ((Varval *)a->l)->var);
        break;

    // string
    case 'y':
        eval(a->r);
        aux1 =  srchVar( varList, ((Symasgn *)(a->l))->s);
        if (aux1->nodetype == 2)
            printf("%s", aux1->valors);
        else
            printf("Variável não é do tipo String %c\\n", a->nodetype);
        break;
    case 'z':
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        if (aux1->nodetype == 2)
            printf("%s", aux1->valors);
        else
            printf("Variável não é do tipo String %c\\n", a->nodetype);
        break;
    // endl
    case 'e':
        printf("\\n");
        break;
    case 'f':
        eval(a->r);
        printf("\\n");
        break;
    //float
    case 'V': 
        varList = push_back_float( varList, ((Varval *)a)->var);
        break;
    //int
    case 'U': 
        varList = push_back_int( varList, ((Varval *)a)->var);
        break;
    //string
    case 'X': 
        varList = push_back_string( varList, ((Varval *)a)->var);
        break;
    //declarar e inserir float
    case 'D': 
        v = eval(a->r);
        varList = push_back_float( varList, ((Symasgn *)(a->l))->s);
        varList->valor = v;
        break;
    //declarar varios float
    case 'd': 
        varList = push_back_float( varList, ((Symasgn *)(a->l))->s);
        eval(a->r);
        break;
    //declarar e inserir int
    case 'G': 
        v = eval(a->r);
        varList = push_back_int( varList, ((Symasgn *)(a->l))->s);
        varList->valor = v;
        break;
    //declarar varios int
    case 'g': 
        varList = push_back_int( varList, ((Symasgn *)(a->l))->s);
        eval(a->r);
        break;

    //declarar e inserir string
    case 'H': 
        varList = push_back_string( varList, (((Symasgn *)(a->l))->s));
        strcpy( varList->valors, ((Varval *)a->r)->var);
        break;
    //declarar varios string
    case 'h': 
        varList = push_back_string( varList, ((Symasgn *)(a->l))->s);
        eval(a->r);
        break;
    case '@':
        v2 = parseSTR(((Symasgn *)a)->v);
        aux1 =  srchVar( varList, ((Symasgn *)a)->s);
        if (aux1->nodetype == 2)
            strcpy(aux1->valors, v2);
        else
            printf("Variável %s não é do tipo String \\n", ((Symasgn *)a)->s);
        break;
    case '#':
        v2 = parseSTR(((Symasgn *)a)->v);
        aux1 =  srchVar( varList, ((Symasgn *)a)->s);
        if (aux1->nodetype == 2)
            strcat(aux1->valors, v2);
        else
            printf("Variável %s não é do tipo String \\n", ((Symasgn *)a)->s);
        break;
    default:
        printf("(eval)internal error: bad node %c \\n", a->nodetype);
        break;
    }
    return v;
}

int yylex();
void yyerror (char *s){
	printf("%s\\n", s);
}

%}

%union{
	float flo;
	int fn;
	int inter;
	char str[50];
	Ast *a;
	}

%token <flo>NUM
%token <str>VARS
%token <str>STR
%token INI FIM IF ELSE WHILE OUT DECL STRING INT FLOAT IN PRINTT SCANS
%token DI DF DS ENDL
%token <fn> CMP

%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^' SQRT
%left CMP

%type <a> exp list stmt prog  multvarf multvari multvars multprint parsestr leitura

%nonassoc IFX VARPREC DECLPREC NEG VET PRECFLOAT PRINT MULTIPRINT

%%

val: INI prog FIM
	;

prog: stmt 		{eval($1);}
	| prog stmt {eval($2);}	
	;
	
stmt:
	 IF '(' exp ')' '{' list '}' %prec IFX {$$ = newflow('I', $3, $6, NULL);}
	| IF '(' exp ')' '{' list '}' ELSE '{' list '}' {$$ = newflow('I', $3, $6, $10);}
	| WHILE '(' exp ')' '{' list '}' {$$ = newflow('W', $3, $6, NULL);}
	| PRINTT '(' multprint ')' ';' 	{ $$ = $3; }
    | INT VARS '=' exp ';' { $$ = newast('G', newvari('U',$2) , $4); }
    | INT multvari ';'  %prec DECLPREC {  $$ =  $2; }
    | FLOAT multvarf ';' %prec DECLPREC {  $$ =  $2; }
    | FLOAT VARS '=' exp ';' { $$ = newast('D', newvari('V',$2) , $4); }
    | STRING multvars ';'  {  $$ =  $2; }
    | STRING VARS '=' STR ';' { $$ = newast('H', newvari('X',$2) , newValorValS($4)); }
	| VARS '=' exp ';' %prec VARPREC { $$ = newasgn($1,$3);}
	| IN '(' leitura ')'	';'	{  $$ = $3; }
    | ';' {;} // --> para nao bugar quando ler um ';'
    | { ;} // --> para poder rodar um prog sem nada
	;

list: stmt {$$ = $1;}
		| list stmt { $$ = newast('L', $1, $2);	}
		;
	
exp: 
	 exp '+' exp {$$ = newast('+',$1,$3);}
	|exp '-' exp {$$ = newast('-',$1,$3);}
	|exp '*' exp {$$ = newast('*',$1,$3);}
	|exp '/' exp {$$ = newast('/',$1,$3);}
    |exp '%' exp {$$ = newast('%',$1,$3);}
	|'(' exp ')' {$$ = $2;}
    |exp '^' exp { $$ = newast('^', $1, $3);  }
    |SQRT '(' exp ',' exp ')' { $$ = newast('~', $3, $5); }
	|exp CMP exp {$$ = newcmp($2,$1,$3);}
	|'-' exp %prec NEG {$$ = newast('M',$2,NULL);}
	|NUM 	{$$ = newnum($1);}				
	|VARS 	%prec VET {$$ = newValorVal($1);}

	;

leitura: DI VARS {$$ = newvari('S',$2);}
    | DF VARS {$$ = newvari('S',$2);}
    | DS VARS {$$ = newvari('T',$2);}
;
parsestr: STR  {  $$ = newast('$', newValorValS($1), NULL);}
        | DF exp { $$ = newast('7',$2,NULL);}
        | DI exp { $$ = newast('8',$2,NULL);}
        | DS VARS { $$ = newast('9', newValorValS($2), NULL);}
        ;


multvarf: VARS { $$ = newvari('V',$1); }
        | multvarf ',' VARS {  $$ = newast('d', newvari('V',$3) , $1); }
        ;
multvari: VARS { $$ = newvari('U',$1); }
        | multvari ',' VARS {  $$ = newast('g', newvari('U',$3) , $1); }
        ;
multvars: VARS { $$ = newvari('X',$1); }
        | multvars ',' VARS { $$ = newast('h', newvari('X',$3) , $1); }
        ;

multprint:  STR  {  $$ = newast('s', newValorValS($1), NULL);}
        | DF exp { $$ = newast('p',$2,NULL);}
        | DI exp { $$ = newast('u',$2,NULL);}
        | DS VARS { $$ = searchVar('z', $2); }
        | ENDL { $$ = newast('e', newendl('e'), NULL); }
        | multprint ',' STR { $$ = newast('r', newValorValS($3), $1); }
        | multprint ',' DF exp { $$ = newast('q', newast('p', $4,NULL), $1); }
        | multprint ',' DI exp { $$ = newast('v', newast('u', $4,NULL), $1); }
        | multprint ',' DS VARS { $$ = newast('y', searchVar('z', $4), $1); }
        | multprint ',' ENDL { $$ = newast('f', newendl('e'), $1);  }
        ;
%%


// The function main is required and cannot be changed

#include "lex.yy.c"

int main(){
	yyin=fopen("entrada.lad","r");
	yyparse();
	yylex();
	fclose(yyin);
return 0;
}`;     
            if(codeType == 'test')
                if(this.type == 'lexical'){
                    return `ini
saida<< a
entrada>> a
string a = "Fulano"
if
for 
return 
1
1.1
fim
`;
                } else {
                    return `(U-u)>>
    // teste comentario
    lad_out("BEM VINDO A LINGUAGEM LAD, LAD ONDE? DE GELSON! ", lad_line);
    lad_out("Quer saber se um número é primo? ", lad_line);
    lad_int a = 1;
    lad_while(a < 101){
        lad_out("Teste de while: ", [i::]a ,lad_line);
        a = a + 1;
    }
<<(U-u)          
`;
                }
            return '';
        }
    },
    data(){ 
        return {
            code: this.selectInitialCode(this.codeType),
            cmOptions: {
                // codemirror options
                tabSize: 4,
                mode: 'text/x-csrc',
                highlightDifferences: true,
                theme: 'dracula',
                lineNumbers: true,
                line: true,
                autoRefresh:true,
            }   
        }
    },
    watch: {
        code(val) {
            this.$emit('changeCode', {
                code: val,
                type: this.codeType
            });
        }, 
    }
}

</script>
<style>
.CodeMirror { 
    text-align: left!important;
    height: 500px
}
</style>