//importaciones
#include "analizador.h"
//librerias
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
//variables globales
int combi[CONJ];//array que contiene los conjunto primero y siguiente
token t_actual; //en esta estructura se guarda el token leido del array de tokens
token auxiliar;//token auxiliar
token input[TOTAL];// array que contiene todos lo tokens del fuente
int poss = 0;//indice del array de tokens
int flag=0;
int numLinea = 0;//contador de saltos de linea
char lex_actual[TAMLEX]; //array que almacena el lexema actual
int k = -1; //contador de anidamiento de llamadas a la funcion attribute
token lex[TAMLEX]; //array que va almacenando los lexemas que se anidan

//funcion que copia el vector de tokens devuelto por el analizador lexico
token* copiar(token tokens[]){
    int i;
    for (i = 0; i < TOTAL; i++){
        input[i] = tokens[i];   
    }

}
//aqui inicia el analizador sintactico descendente recursivo
void parser(token input[])
{
    get_token();
    jsonml();
    if (flag == 0){
        printf("\nEURECA: No se encontro errores sintacticos\n");
    }
}

void jsonml(int sinc[])
{
    int ele_sig [CONJ]={EOF,COD_COMA, COD_RCORCHETE, COD_RLLAVE};
    if(t_actual.compLex== COD_LLLAVE || t_actual.compLex == COD_LCORCHETE){
        element(ele_sig);
    }else
    {
        error("Se esperaba L_LLAVE o L_CORCHETE");
    }
}

void element(int sinc[])
{
    int ele_pro[CONJ] = {COD_LLLAVE, COD_LCORCHETE};
    checkinput(ele_pro, sinc);
    switch(t_actual.compLex)
    {
        case COD_LLLAVE:
            object(sinc);
            break;
        case COD_LCORCHETE:
            array(sinc);
            break;
        default:
            error("Se esperaba L_LLAVE o L_CORCHETE");
            break;
    }
    checkinput(sinc,ele_pro);
}

void object(int sinc[])
{
    int obj_pro[CONJ]={COD_LLLAVE};
    checkinput(obj_pro,sinc);
    switch (t_actual.compLex)
    {
        case COD_LLLAVE:
            match(COD_LLLAVE);        
            pr_object(sinc);
            break;
        default:
            error("Se esperaba L_LLAVE");
            break;
    }   
    checkinput(sinc,obj_pro);
}

void array(int sinc[])
{
    int array_pro[CONJ]={COD_LCORCHETE};
    checkinput(array_pro,sinc);
    switch (t_actual.compLex)
    {
        case COD_LCORCHETE:
            match(COD_LCORCHETE);        
            pr_array(sinc);
            break;
        default:
            error("Se esperaba L_CORCHETE");
            break;
    }
    checkinput(sinc,array_pro);
}


void pr_object(int sinc[])
{
    int pr_objpro[CONJ]={COD_STRING,COD_RLLAVE};
    int attlist_sig[CONJ]={COD_RLLAVE};
    checkinput(pr_objpro,sinc);
    switch (t_actual.compLex)
    {
        case COD_STRING:
            att_list(attlist_sig);
            match(COD_RLLAVE);        
            break;
        case COD_RLLAVE:
            match(COD_RLLAVE);
            break;
        default:
            error("Se esperaba STRING o R_LLAVE");
            break;
    }
    checkinput(sinc,pr_objpro);
}

void pr_array(int sinc[])
{
    int pr_arpro[CONJ]={COD_LLLAVE, COD_LCORCHETE, COD_RCORCHETE};
    int elelist_sig[CONJ]={COD_RCORCHETE};
    checkinput(pr_arpro,sinc);
    switch (t_actual.compLex)
    {
        case COD_LLLAVE:
            ele_list(elelist_sig);
            match(COD_RCORCHETE);        
            break;
        case COD_LCORCHETE:
            ele_list(elelist_sig);
            match(COD_RCORCHETE);
            break;
        case COD_RCORCHETE:
            match(COD_RCORCHETE);
            break;
        default:
            error("Se esperaba L_LLAVE, L_CORCHETE o R_CORCHETE");
            break;
    }
    checkinput(sinc,pr_arpro);
}

void ele_list(int sinc[])
{
    int elelist_pro[CONJ]={COD_LLLAVE,COD_LCORCHETE};
    int ele_sig [CONJ]={EOF,COD_COMA, COD_RCORCHETE, COD_RLLAVE};
    checkinput(elelist_pro,sinc);
    if(t_actual.compLex == COD_LLLAVE || t_actual.compLex == COD_LCORCHETE){
        printf("<item>");
        element(ele_sig);
        printf("</item>");
        pr_elelist(sinc);
    }else{
        error("Se esperaba L_LLAVE, L_CORCHETE");
        checkinput(sinc,elelist_pro);
    }
}

void pr_elelist(int sinc[])
{
    int prlist_pro[CONJ]={COD_COMA};
    int ele_sig [CONJ]={EOF,COD_COMA, COD_RCORCHETE, COD_RLLAVE};
    if(t_actual.compLex==COD_RCORCHETE){
        checkinput(sinc,prlist_pro);
    }else{
        checkinput(prlist_pro,sinc);
    }
    switch(t_actual.compLex)
    {
        case COD_COMA:
            match(COD_COMA);
            printf("<item>");
            element(ele_sig);
            printf("</item>");
            pr_elelist(sinc);
            break;
    }
   checkinput(sinc,prlist_pro);
}

void attribute(int sinc[])
{
    int att_pro[CONJ]={COD_STRING};
    int attname_sig[CONJ]={COD_DOSPUNTOS};
    checkinput(att_pro,sinc);
    switch(t_actual.compLex)
    {
        case COD_STRING:
            printf("<");
            att_name(attname_sig);//llama a la funcion que va a imprimir el nombre del tag
            printf(">");
            match(COD_DOSPUNTOS);
            att_value(sinc);
            break;
        default:
            error("Se esperaba STRING");
            break;
    }
    checkinput(sinc,att_pro);
    printf("</");
    auxiliar = lex[k];//se guarda el nombre de tag que corresponda
    printf("%s",sin_comilla(auxiliar.lexema));//se imprime nombre de tag de cierre
    k--;//se posiciona en el proximo nombre de tag
    printf(">");
}

void att_list(int sinc[])
{
    int attlist_pro[CONJ]={COD_STRING};
    int att_sig[CONJ] = {COD_COMA,COD_RLLAVE};
    checkinput(attlist_pro,sinc);
    if(t_actual.compLex==COD_STRING){
        attribute(att_sig);
        pr_attlist(sinc);
    }else{
        error("Se esperaba STRING");
    }
    checkinput(sinc,attlist_pro);
}

void pr_attlist(int sinc[])
{
    int prattlist_pro[CONJ]={COD_COMA};
    int att_sig[CONJ] = {COD_COMA,COD_RLLAVE};
    
    if(t_actual.compLex == COD_RLLAVE){
        checkinput(sinc,prattlist_pro);
    }else{        
        checkinput(prattlist_pro,sinc);
    }
    switch(t_actual.compLex)
    {
        case COD_COMA:
            match(COD_COMA);
            attribute(att_sig);
            pr_attlist(sinc);
            break;
    }
    checkinput(sinc,prattlist_pro);
}

void att_name(int sinc[])
{
    int attname_pro[CONJ]={COD_STRING};
    checkinput(attname_pro,sinc);
    switch(t_actual.compLex)
    {
        case COD_STRING:
            printf("%s",sin_comilla(t_actual.lexema));//imprime nombre del tag
            lex[++k] = t_actual;//guarda nombre del tag en caso de anidamiento
            match(COD_STRING);
            break;
        default:
            error("Se esperaba STRING");
            break;
    }
}

void att_value(int sinc[])
{
    int attval_pro[CONJ]={COD_LLLAVE, COD_LCORCHETE, COD_STRING, COD_NUMBER, COD_TRUE, COD_FALSE,COD_NULL};
    int ele_sig [CONJ]={EOF,COD_COMA, COD_RCORCHETE, COD_RLLAVE};
    checkinput(attval_pro,sinc);
    switch(t_actual.compLex)
    {
        case COD_LLLAVE:
            element(ele_sig);
            break;
        case COD_LCORCHETE:
            element(ele_sig);
            break;
        case COD_STRING:
            printf("%s",t_actual.lexema);//imprime nombre del tag
            match(COD_STRING);
            break;
        case COD_NUMBER:
            printf("%s",t_actual.lexema);//imprime nombre del tag
            match(COD_NUMBER);
            break;
        case COD_TRUE:
            printf("%s",t_actual.lexema);//imprime nombre del tag
            match(COD_TRUE);
            break;
        case COD_FALSE:
            printf("%s",t_actual.lexema);//imprime nombre del tag
            match(COD_FALSE);
            break;
        case COD_NULL:
            printf("%s",t_actual.lexema);//imprime nombre del tag
            match(COD_NULL);
            break;
        default:
            error("Se esperaba L_LLAVE, L_CORCHETE, STRING, NUMBER, TRUE,FALSE O NULL");
            break;
    }
    checkinput(sinc,attval_pro);
}

//funciones del analizador
void match(int t)
{
    if(t_actual.compLex == t){
        get_token();
    }
    else{
        flag = 1;
        printf("Match Error en linea %d.\n", numLinea);
    }
}

void get_token()
{
    t_actual = input[poss++];
    if (t_actual.compLex == LINEA){
        printf("%s",t_actual.lexema);
        numLinea++;
        t_actual = input[poss++];
    }
    if (t_actual.compLex == ESPACIO || t_actual.compLex == TAB ){
        printf("%s",t_actual.lexema);
        t_actual = input[poss++];
    }
}

//funciones del panic mode(recuperacion de errores)
void scanto(int sinc[])
{
    int i;
    while(buscar(sinc) != 1){
        get_token();
    }
}

void checkinput(int pro[], int sgte[])
{
    if (buscar(pro)==0){
        volcar(pro,sgte);
        scanto(volcar(pro,sgte));
    }
}

//funciones auxiliares
int buscar(int sinc[]){
    int ban = 0;
    int i = 0;
    for (i = 0; i<CONJ;i++){
        if (t_actual.compLex == sinc[i]){
            ban = 1;
        }    

    }
    return ban;
}

int* volcar(int pro[], int sgte[]){
    int i,j;
    int cont=0;
    
    //meter el primero
    for (i = 0; i < CONJ; i++){
        if(pro[i] != 0){
            combi[i] = pro[i];
            cont++;
        }
    }
    //meter el segundo
    for (j = 0; j < CONJ; j++){
        if(sgte[j] != 0){
            combi[cont++] = sgte[j];
        }
    }
    return combi;
}

char* sin_comilla(char vector[]){
    int i;
    int size = strlen(vector);
    for (i = 0; i < size; i++) {
        if(vector[i] =='\"'){
            vector[i] = ' ';
        }

    }
    return vector;
}
//impresion de errores
void error(const char* mensaje)
{
    flag = 1;
	printf("Lin %d: Sintax Error. %s.\n",numLinea,mensaje);	
}
