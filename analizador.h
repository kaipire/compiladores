//LIBRERIAS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//CONSTANTES
#define COD_FALSE	    1
#define COD_TRUE	    2
#define COD_NULL        3
#define COD_STRING      4
#define COD_NUMBER      5
#define COD_LLLAVE      6
#define COD_RLLAVE      7
#define COD_LCORCHETE   8
#define COD_RCORCHETE   9
#define COD_DOSPUNTOS   10
#define COD_COMA        11

#define LINEA           12

#define TAM 500

// prototipos de funciones
int* copiar(int tokens[]);
void parser(int tokens[]);
void jsonml();
void element(int sinc[]);
void object(int sinc[]);
void array(int sinc[]);
void pr_object(int sinc[]);
void pr_array(int sinc[]);
void ele_list(int sinc[]);
void pr_elelist(int sinc[]);
void attribute(int sinc[]);
void att_list(int sinc[]);
void pr_attlist(int sinc[]);
void att_name(int sinc[]);
void att_value(int sinc[]);

//metodos de validacion
void match(int);
void get_token();
//recuperacion de errores
void scanto(int sinc[]);
void checkinput(int pro[], int sgte[]);
void error(const char*);
//auxiliares
int buscar(int sinc[]);
int* volcar(int pro[], int sgte[]);

