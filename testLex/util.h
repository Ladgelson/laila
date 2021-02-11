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
        printf("evalString: internal error: bad node %c\n", a->nodetype);
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
            printf("Variável não é do tipo Numérico\n");
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
        printf("EVA varList: internal error: bad node %c\n", a->nodetype);
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
            printf("Variavel não é do tipo String %c\n", a->nodetype);
        break;
    default:
        printf("STRING: internal error: bad node %c\n", a->nodetype);
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
        printf("%.2f\n", v);
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
        scanf("%[^\n]s", v1);
        fflush(stdin);
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        strcpy(aux1->valors, v1);
        break;

    case 'Y':
        v2 = evalString(a->l);
        printf("%s\n", v2);
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
            printf("Variável não é do tipo String %c\n", a->nodetype);
        break;
    case 'z':
        aux1 =  srchVar( varList, ((Varval *)a)->var);
        if (aux1->nodetype == 2)
            printf("%s", aux1->valors);
        else
            printf("Variável não é do tipo String %c\n", a->nodetype);
        break;
    // endl
    case 'e':
        printf("\n");
        break;
    case 'f':
        eval(a->r);
        printf("\n");
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
            printf("Variável %s não é do tipo String \n", ((Symasgn *)a)->s);
        break;
    case '#':
        v2 = parseSTR(((Symasgn *)a)->v);
        aux1 =  srchVar( varList, ((Symasgn *)a)->s);
        if (aux1->nodetype == 2)
            strcat(aux1->valors, v2);
        else
            printf("Variável %s não é do tipo String \n", ((Symasgn *)a)->s);
        break;
    default:
        printf("(eval)internal error: bad node %c\n", a->nodetype);
        break;
    }
    return v;
}
