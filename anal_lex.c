
/*********** Librerias **************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/************* Variables globales **************/

char fin;

// variables para el analizador lexico

FILE *archivo;			// Fuente JSON

/**************** Funciones **********************/


// Rutinas del analizador lexico


void validar()
{
	char c=0;
	int acepto=0;
	int estado=0;
    int ban = 0;

	while((c=fgetc(archivo))!=EOF)
	{   //imprimi espacio y y continuar
        if (c == ' '){
            printf("%c",c);
            continue;
        }//imprimir tabulador y continuar
        else if (c == '\t'){
            printf("%c",c);
            continue;
        }
        //imprimir salto de linea y continuar
		else if(c=='\n')
		{
            printf("%c",c);			
			continue;
		}
        else if (c=='\"')
		{
            //validar string
			do
			{
				c=fgetc(archivo);
				if (c=='\"')
				{
                    ban=1;
                    printf("STRING ");
                    break;
                                    
				}
                else if(c==EOF || c==',' || c=='\n' || c==':')
		        {
			        while(c!='\n')
                        c=fgetc(archivo);
                                
                    printf("ERROR");
                    ungetc(c,archivo);
                    break;                       
		         }
             }while(isascii(c) || ban==0);
            break;
        }
        //validacion de signos
        else if (c == '{')
        {   
            printf("L_LLAVE ");
            break;
        }

        else if (c == '}')
        {   
            printf("R_LLAVE ");
            break;
        }

        else if (c == '[')
        {   
            printf("L_CORCHETE ");
            break;
        }

        else if (c == ']')
        {   
            printf("R_CORCHETE ");
            break;
        }

        else if (c == ':')
        {   
            printf("DOS_PUNTOS ");
            break;
        }

        else if (c == ',')
        {   
            printf("COMA ");
            break;
        }
        //fin validacion de signos
        else if (c == 'f' || c == 'F')
        {   //validar false
            estado = 0;
            acepto = 0;
            char aux = c;
            int cont = 0; 
            while(acepto == 0)
            {
                if (aux == 'f'){
                  switch (estado){
                        case 0:
                            c = fgetc(archivo);                        
                            if (c == 'a')
                                estado = 1;
                            else
                                estado = -1;
                            break;
                        case 1:
                            c = fgetc(archivo);                       
                            if (c == 'l')
                                estado = 2;
                            else
                                estado = -1;
                            break;
                        case 2:
                            c = fgetc(archivo);                        
                            if (c == 's')
                                estado = 3;
                            else
                                estado = -1;
                            break;
                        case 3:
                            c = fgetc(archivo);                        
                            if (c == 'e')
                                estado = 4;
                            else
                                estado = -1;
                            break;
                        case 4:
                            c = fgetc(archivo);
                            if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ':')
                                estado = 5;
                            else
                                estado = -1;
                            break;
                        case 5:
                            if (c!=EOF)
						        ungetc(c,archivo);
					        else
						        c=0;
				            printf("PR_FALSE ");
                            acepto=1;
                            break;

				       case -1:
				            if (c==EOF){
				        		printf("No se esperaba el fin de archivo");
                            }
					        else{
						        printf("error");
                                while (c != '\n'){
                                    c = fgetc(archivo);                                
                                }
                                ungetc(c,archivo);
                                acepto=1;
					            
					        }
                            break;
                    }
                }
                else{
                  switch (estado){
                        case 0:
                            c = fgetc(archivo);                      
                            if (c == 'A')
                                estado = 1;
                            else
                                estado = -1;
                            break;
                        case 1:
                            c = fgetc(archivo);                        
                            if (c == 'L')
                                estado = 2;
                            else
                                estado = -1;
                            break;
                        case 2:
                            c = fgetc(archivo);                        
                            if (c == 'S')
                                estado = 3;
                            else
                                estado = -1;
                            break;
                        case 3:
                            c = fgetc(archivo);                        
                            if (c == 'E')
                                estado = 4;
                            else
                                estado = -1;
                            break;
                        case 4:
                            c = fgetc(archivo);
                            if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ':')
                                estado = 5;
                            else
                                estado = -1;
                            break;
                        case 5:
                            if (c!=EOF)
						        ungetc(c,archivo);
					        else
						        c=0;
				            printf("PR_FALSE ");
                            acepto=1;
                            break;

				       case -1:
				            if (c==EOF){
				        		printf("No se esperaba el fin de archivo");
                            }
					        else{
						        printf("error");
                                while (c != '\n'){
                                    c = fgetc(archivo);                                
                                }
                                ungetc(c,archivo);
                                acepto=1;
					            
					        }
                            break;
                    }                
                }
            }
            break;
        }
        //fin validacion false
        else if (c == 't' || c == 'T')
        {   //validar true
            estado = 0;
            acepto = 0;
            char aux = c;
            while(acepto == 0)
            {
                if (aux == 't'){
                  switch (estado){
                        case 0:
                            c = fgetc(archivo);                        
                            if (c == 'r')
                                estado = 1;
                            else
                                estado = -1;
                            break;
                        case 1:
                            c = fgetc(archivo);                       
                            if (c == 'u')
                                estado = 2;
                            else
                                estado = -1;
                            break;
                        case 2:
                            c = fgetc(archivo);                        
                            if (c == 'e')
                                estado = 3;
                            else
                                estado = -1;
                            break;
                        case 3:
                            c = fgetc(archivo);
                            if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ':')
                                estado = 4;
                            else
                                estado = -1;
                            break;

                        case 4:
                            if (c!=EOF)
						        ungetc(c,archivo);
					        else
						        c=0;
				            printf("PR_TRUE ");
                            acepto=1;
                            break;

				       case -1:
				            if (c==EOF){
				        		printf("No se esperaba el fin de archivo");
                            }
					        else{
						        printf("error");
                                while (c != '\n'){
                                    c = fgetc(archivo);                                
                                }
                                ungetc(c,archivo);
                                acepto=1;
					            
					        }
                            break;
                    }
                }
                else{
                  switch (estado){
                        case 0:
                            c = fgetc(archivo);                      
                            if (c == 'R')
                                estado = 1;
                            else
                                estado = -1;
                            break;
                        case 1:
                            c = fgetc(archivo);                        
                            if (c == 'U')
                                estado = 2;
                            else
                                estado = -1;
                            break;
                        case 2:
                            c = fgetc(archivo);                        
                            if (c == 'E')
                                estado = 3;
                            else
                                estado = -1;
                            break;

                        case 3:
                            c = fgetc(archivo);
                            if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ':')
                                estado = 4;
                            else
                                estado = -1;
                            break;

                        case 4:
                            if (c!=EOF)
						        ungetc(c,archivo);
					        else
						        c=0;
				            printf("PR_TRUE ");
                            acepto=1;
                            break;

				       case -1:
				            if (c==EOF){
				        		printf("No se esperaba el fin de archivo");
                            }
					        else{
						        printf("error");
                                while (c != '\n'){
                                    c = fgetc(archivo);                                
                                }
                                ungetc(c,archivo);
                                acepto=1;
					            
					        }
                            break;
                    }                
                }
            }
            break;
        }
        //fin de validar true
        else if (c == 'n' || c == 'N')
        {   //validar null
            estado = 0;
            acepto = 0;
            char aux = c;
            while(acepto == 0)
            {
                if (aux == 'n'){
                  switch (estado){
                        case 0:
                            c = fgetc(archivo);                        
                            if (c == 'u')
                                estado = 1;
                            else
                                estado = -1;
                            break;
                        case 1:
                            c = fgetc(archivo);                       
                            if (c == 'l')
                                estado = 2;
                            else
                                estado = -1;
                            break;
                        case 2:
                            c = fgetc(archivo);                        
                            if (c == 'l')
                                estado = 3;
                            else
                                estado = -1;
                            break;
                        case 3:
                            c = fgetc(archivo);
                            if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ':')
                                estado = 4;
                            else
                                estado = -1;
                            break;

                        case 4:
                            if (c!=EOF)
						        ungetc(c,archivo);
					        else
						        c=0;
				            printf("PR_NULL ");
                            acepto=1;
                            break;

				       case -1:
				            if (c==EOF){
				        		printf("No se esperaba el fin de archivo");
                            }
					        else{
						        printf("error");
                                while (c != '\n'){
                                    c = fgetc(archivo);                                
                                }
                                ungetc(c,archivo);
                                acepto=1;
					            
					        }
                            break;
                    }
                }
                else{
                  switch (estado){
                        case 0:
                            c = fgetc(archivo);                      
                            if (c == 'U')
                                estado = 1;
                            else
                                estado = -1;
                            break;
                        case 1:
                            c = fgetc(archivo);                        
                            if (c == 'L')
                                estado = 2;
                            else
                                estado = -1;
                            break;
                        case 2:
                            c = fgetc(archivo);                        
                            if (c == 'L')
                                estado = 3;
                            else
                                estado = -1;
                            break;

                        case 3:
                            c = fgetc(archivo);
                            if (c == ' ' || c == '\t' || c == '\n' || c == ',' || c == ':')
                                estado = 4;
                            else
                                estado = -1;
                            break;

                        case 4:
                            if (c!=EOF)
						        ungetc(c,archivo);
					        else
						        c=0;
				            printf("PR_NULL ");
                            acepto=1;
                            break;

				       case -1:
				            if (c==EOF){
				        		printf("No se esperaba el fin de archivo");
                            }
					        else{
						        printf("error");
                                while (c != '\n'){
                                    c = fgetc(archivo);                                
                                }
                                ungetc(c,archivo);
                                acepto=1;
					            
					        }
                            break;
                    }                
                }
            }
            break;
        }
//fin de validacion null
        else if (isdigit(c))
        {//validar numero
            estado = 0;
            acepto = 0;
				
			while(acepto == 0)
			{
			    switch(estado){
				    case 0: //una secuencia netamente de digitos, puede ocurrir . o e
				        c=fgetc(archivo);
				        if (isdigit(c))
					    {
						    estado=0;
					    }
					    else if(c=='.'){
						    estado=1;
					    }
					    else if(tolower(c)=='e'){
						    estado=3;
					    }
					    else{
						    estado=6;
					    }
					    break;
					
				    case 1://un punto, debe seguir un digito
				        c=fgetc(archivo);						
					    if (isdigit(c)){
						    estado=2;
					    }
                        else{
						    estado=-1;
					    }
					    break;
					
                   case 2://la fraccion decimal, pueden seguir los digitos o e
					    c=fgetc(archivo);
					    if (isdigit(c))
					    {
						    estado=2;
					    }
					    else if(tolower(c)=='e')
					    {
						    estado=3;
					    }
					    else
						    estado=6;
					    break;
					
                   case 3://una e, puede seguir +, - o una secuencia de digitos
				        c=fgetc(archivo);
					    if (c=='+' || c=='-')
					    {
						    estado=4;
					    }
                        else if(isdigit(c))
					    {
						    estado=5;
					    }
					    else{
						    estado=-1;
						}
						break;
					
                   case 4://necesariamente debe venir por lo menos un digito
				        c=fgetc(archivo);
					    if (isdigit(c))
					    {
						    estado=5;
					    }
					    else{
						    estado=-1;
					    }
					    break;
					
                   case 5://una secuencia de digitos correspondiente al exponente
					    c=fgetc(archivo);
					    if (isdigit(c))
					    {
						    estado=5;
					    }
					    else{
						    estado=6;
					    }
                        break;
                    case 6://al finalizar un numero puede venir una coma, espacion o salgo de linea
                        if(c == ',' || c == '\n' || c == '\t' || c == ' ')
                            estado = 7;
                        else
                            estado = -1;
                        break;

                    case 7://estado de aceptacion, devolver el caracter correspondiente a otro componente lexico
                        if (c!=EOF)
						    ungetc(c,archivo);
					    else
						    c=0;
				        printf("NUMBER ");
                        acepto=1;
                        break;
    
				    case -1:
				        if (c==EOF){
				            printf("No se esperaba el fin de archivo");
                        }
					    else{
						    printf("error");
                            while (c != '\n'){
                                c = fgetc(archivo);                                
                            }
                            ungetc(c,archivo);
                            acepto=1;
					            
					    }
                        break;
                        
				}
            }
            break;
        }//si no reconoce ningun de los token permitidos es un error
        else if (c != EOF){
            printf("error");
            while (c != '\n'){
                c = fgetc(archivo);            
            }
            ungetc(c, archivo);
        }
    }    
    if (c == EOF){
        fin = EOF;
    }

}			

int main(int argc,char* args[])
{
	// inicializar analizador lexico
	
	if(argc > 1)
	{
		if (!(archivo=fopen(args[1],"rt")))
		{
			printf("Archivo no encontrado.\n");
			exit(1);
		}
		while (fin!=EOF){
			validar();
		}
		fclose(archivo);
	}else{
		printf("Debe pasar como parametro el path al archivo fuente.\n");
		exit(1);
	}

	return 0;
}
