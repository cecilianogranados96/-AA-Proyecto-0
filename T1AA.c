#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

///Variables
clock_t tInicio, tFin, tDecorrido;
int num_aleatorio[7], mat[4][4], n=10000000;


///Funciones para multiplicar
int f_vacia(int A, int B){
    return 0;
}

int f_estandar(int A,int B){
    return A*B;
}

int f_antigua(int A,int B){
    int P = 0;
    while(B != 0){
        if((B%2) != 0){
            P += A;
        }
        A += A;
        B = B >> 1;
    }
    return P;
}

extern int f_vaciaE(int, int);
extern int f_estandarE(int, int);
extern int f_antiguaE(int, int);



///Funciones para guardar datos en un archivo
void guardarTiempo(int ns){
	FILE *fp; 
	fp = fopen("/home/alejandro/Documentos/2018-ISemestre/Analisis_de_Algoritmos/T1AA/Datos/Tiempos.txt", "a");
	fprintf(fp, "%d\t", ns);
	fclose(fp);
}	

void nuevaLinea(){
	FILE *fp; 
	fp = fopen("/home/alejandro/Documentos/2018-ISemestre/Analisis_de_Algoritmos/T1AA/Datos/Tiempos.txt", "a");
	fprintf(fp, "\n");
	fclose(fp);
}

void guardarAleatorios(){
	FILE *fp; 
	fp = fopen("/home/alejandro/Documentos/2018-ISemestre/Analisis_de_Algoritmos/T1AA/Datos/Aleatorios.txt", "a");
	for( int i=0; i<8; i++){
		fprintf(fp, "%d\t", num_aleatorio[i]);
	}
	fprintf(fp, "\n");
	fclose(fp);
}



///Funciones para escribir en pantalla
void escribir_base(void){
	printf("\t PRESENTACION DE LA TABLA BASE:\n\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			printf("%4d X %-4d\t", num_aleatorio[i],num_aleatorio[j+4]);
			putchar('\n');
	}
	printf("\n--------------------------------------------------------\n");
	printf("\t PRESENTACION DE LA TABLA ALTERNA:\n\n");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			printf("%4d X %-4d\t", num_aleatorio[i+4],num_aleatorio[j]);
			putchar('\n');
	}
	printf("\n--------------------------------------------------------\n");
}

void escribir_num_aleatorio(void){
	printf("\n\t NUMEROS ALEATORIOS USADOS:\n\n");
	for (int i = 0; i < 8; i++) {
		printf("\t |%d -> %4d|\n", i,num_aleatorio[i]);
	}
	printf("--------------------------------------------------------\n");
}

void escribir(long unsigned int tiempo, int tipo){
	if(tipo == 1){
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				printf("%8d\t", mat[i][j]);
				putchar('\n');
		}	
		printf("\n\nTiempo de ejecución para la tabla base: %lu ms \n\n ", tiempo);
		printf("--------------------------------------------------------\n");
		printf("\t TABLA ALTERNA\n\n");
	}
	else{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				printf("%8d\t", mat[j][i]);
				putchar('\n');
		}	
		printf("\n\nTiempo de ejecución para la tabla alterna: %lu ms \n \n ",tiempo);
		printf("--------------------------------------------------------\n");
	}
}

void terminarBase(){
    tDecorrido = ((tFin - tInicio) / (CLOCKS_PER_SEC / 1000));
    guardarTiempo(tDecorrido);
    escribir(tDecorrido, 1);
}

void terminarAlterna(){
	tDecorrido = ((tFin - tInicio) / (CLOCKS_PER_SEC / 1000));
    guardarTiempo(tDecorrido);
    escribir(tDecorrido, 2);
    escribir_num_aleatorio();
}

void siguiente(char* version){
	printf("Precione enter para %s\n", version);
    getchar();
    system("clear");
}



///Funciones resumen
void versionVaciaC(){
	printf("\n\n  \t\t VERSIÓN VACIA\n");
    printf("--------------------------------------------------------\n");
    printf(" \n \t\t PROGRAMADO EN C\n\n");
    printf("--------------------------------------------------------\n");
    printf("\t TABLA BASE \n\n");

    /************* TABLA BASE ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_vacia(num_aleatorio[i],num_aleatorio[j+4]);
            }
        }
    }
    tFin = clock();
    terminarBase(tInicio, tFin, tDecorrido);
    /************* FORMA B X A ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_vacia(num_aleatorio[j+4],num_aleatorio[i]);
            }
        }
    }
    tFin = clock();
    terminarAlterna(tInicio, tFin, tDecorrido);
}

void versionVaciaASM(){
	printf("\n\n  \t\t VERSIÓN VACIA\n");
    printf("--------------------------------------------------------\n");
    printf(" \n \t\t PROGRAMADO EN ENSAMBLADOR\n\n");
    printf("--------------------------------------------------------\n");
    printf("\t TABLA BASE \n\n");
    /************* TABLA BASE ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_vaciaE(num_aleatorio[i],num_aleatorio[j+4]); //OJO CON ESTO EN ES LA RESPUESTA DEL ENSAMBLER
            }
        }
    }
    tFin = clock();
    terminarBase(tInicio, tFin, tDecorrido);
    
    /************* FORMA B X A ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_vaciaE(num_aleatorio[j+4],num_aleatorio[i]); //OJO CON ESTO EN ES LA RESPUESTA DEL ENSAMBLER
            }
        }
    }
    tFin = clock();
    terminarAlterna(tInicio, tFin, tDecorrido);
}

void versionEstandarC(){
	printf("\n\n  \t\t VERSIÓN ESTANDAR\n");
    printf("--------------------------------------------------------\n");
    printf(" \n \t\t PROGRAMADO EN C\n\n");
    printf("--------------------------------------------------------\n");
    printf("\t TABLA BASE \n\n");
    /************* TABLA BASE ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_estandar(num_aleatorio[i],num_aleatorio[j+4]);
            }
        }
    }
    tFin = clock();
    terminarBase(tInicio, tFin, tDecorrido);
    
    /************* FORMA B X A ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_estandar(num_aleatorio[j+4],num_aleatorio[i]);
            }
        }
    }
    tFin = clock();
    terminarAlterna(tInicio, tFin, tDecorrido);
}

void versionEstandarASM(){
	printf("\n\n  \t\t VERSIÓN ESTANDAR\n");
    printf("--------------------------------------------------------\n");
    printf(" \n \t\t PROGRAMADO EN ENSAMBLADOR\n\n");
    printf("--------------------------------------------------------\n");
    printf("\t TABLA BASE \n\n");
    /************* TABLA BASE ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_estandarE(num_aleatorio[i],num_aleatorio[j+4]);  //OJO CON ESTO EN ES LA RESPUESTA DEL ENSAMBLER
            }
        }
    }
    tFin = clock();
    terminarBase(tInicio, tFin, tDecorrido);
    
    /************* FORMA B X A ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_estandarE(num_aleatorio[j+4],num_aleatorio[i]);  //OJO CON ESTO EN ES LA RESPUESTA DEL ENSAMBLER
            }
        }
    }
    tFin = clock();
    terminarAlterna(tInicio, tFin, tDecorrido);
}

void versionAntiguaC(){
	printf("\n\n  \t\t VERSIÓN ANTIGUA\n");
    printf("--------------------------------------------------------\n");
    printf(" \n \t\t PROGRAMADO EN C\n\n");
    printf("--------------------------------------------------------\n");
    printf("\t TABLA BASE \n\n");
    /************* TABLA BASE ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_antigua(num_aleatorio[i],num_aleatorio[j+4]);
            }
        }
    }
    tFin = clock();
    terminarBase(tInicio, tFin, tDecorrido);
    
    /************* FORMA B X A ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_antigua(num_aleatorio[j+4],num_aleatorio[i]);
            }
        }
    }
    tFin = clock();
    terminarAlterna(tInicio, tFin, tDecorrido);
}

void versionAntiguaASM(){
	printf("\n\n  \t\t VERSIÓN ANTIGUA\n");
    printf("--------------------------------------------------------\n");
    printf(" \n \t\t PROGRAMADO EN ENSAMBLADOR\n\n");
    printf("--------------------------------------------------------\n");
    printf("\t TABLA BASE \n\n");
    /************* TABLA BASE ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_antiguaE(num_aleatorio[i],num_aleatorio[j+4]);  //OJO CON ESTO EN ES LA RESPUESTA DEL ENSAMBLER
            }
        }
    }
    tFin = clock();
    terminarBase(tInicio, tFin, tDecorrido);
    
    /************* FORMA B X A ****************/
    tInicio = clock();
    for (int r = 0; r < n; r++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++){
                mat[i][j] = f_antiguaE(num_aleatorio[j+4],num_aleatorio[i]);  //OJO CON ESTO EN ES LA RESPUESTA DEL ENSAMBLER
            }
        }
    }
    tFin = clock();
    terminarAlterna(tInicio, tFin, tDecorrido);
}
	


int main(void){
	//for(int repet=0; repet<75; repet++){
	srand(time(NULL));
    for( int i= 0; i<8; i++){
        num_aleatorio[i] = rand() % 9999;
	}
	
    /*printf("Digíte el numero N: ");
    scanf("%d",&n);
    getchar();
    system("clear");*/

	system("clear");
	escribir_base();
	siguiente("ver la solución vacía");

	escribir_base();
	versionVaciaC();
	siguiente("ver solucion en ensamblador");
	escribir_base();
	versionVaciaASM();
	siguiente("continuar con la solucion en la versión estándar");
	
	escribir_base();
	versionEstandarC();
	siguiente("ver solucion en ensamblador");
	escribir_base();
	versionEstandarASM();
	siguiente("continuar con la solucion en la versión antigua");
	
	escribir_base();
	versionAntiguaC();
    siguiente("ver solucion en ensamblador");
    escribir_base();
    versionAntiguaASM();
	siguiente("finalizar");
    
    nuevaLinea();
	guardarAleatorios();
	//}
	return 0;
}
