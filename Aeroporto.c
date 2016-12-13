/*PROJECTO IADE*/

/*BIBLIOTECAS*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*CONSTANTES*/
#define STRINGMAX	4
#define AEROMAX		1000

/*ESTRUTURAS DE DADOS*/
typedef struct{
	int capacidade;
	char nome[STRINGMAX];
	int estado;
}aeroporto;

/*PROTOTIPOS*/
void executa_A();
void executa_I();
void executa_F();
void executa_G();
void executa_R();
void executa_S();
void executa_N();
void executa_P();
void executa_Q();
void executa_V();
void executa_C();
void executa_O();
void executa_L();
void executa_L0();
void executa_L1();
void executa_L2();
void executa_X();
void inicializa_aeroporo_zeros(int indice);
int procura_indice(char SIGLA[]);
int soma_voos_aero(int indice);
int soma_voos_outgoing(int indice);
int soma_voos_incoming(int indice);
void cria_vetor_indices(int vector[]);
void selectionsort(int vector[], int l, int r);
void selectionsort_int(int vector[], int l, int r);

/*VARIAVEIS GLOBAIS*/
aeroporto aeroportos[AEROMAX]; /*vetor que contem os aerportos*/
int controlador = 0; /*variavel que controla o numero de aeroportos atual e a proxima posicao de um novo aerporto*/
int voos[AEROMAX][AEROMAX]; /*vetor bidemension que contem todos os voos entre os aeroportos, o primeiro indice corresponde ao indeice de partida e o segundo ao de chegada*/

/*FUNCOES AUXILIARES*/
void inicializa_aeroporo_zeros(int indice){
	int naero;
	for(naero = 0; naero < controlador; naero++){
		voos[indice][naero] = 0;
		voos[naero][indice] = 0;
	}
}

int procura_indice(char SIGLA[]){
	int naero;
	for(naero = 0; naero < controlador;	naero++){
		if (strcmp(SIGLA, aeroportos[naero].nome) == 0){ /*Compara a string fornecida com todos os nomes de aeroportos*/
			return naero;
		}
	}
	return -1; /*Aeroporto inexistente*/
}

int soma_voos_aero(int indice){
	int soma = 0, naero;
	for (naero = 0; naero < controlador; naero++){
		soma += voos[naero][indice];
		soma += voos[indice][naero];
	}
	return soma;
}

int soma_voos_outgoing(int indice){/*voos outgoing correspondem a todos os voos que tem como primeiro indice o indice do aeroporto*/
	int soma = 0, naero;
	for (naero = 0; naero < controlador; naero++){
		soma += voos[indice][naero];
	}
	return soma;
}

int soma_voos_incoming(int indice){/*voos incoming correspondem a todos os voos que tem como segundo indice o indice do aeroporto*/
	int soma = 0, naero;
	for (naero = 0; naero < controlador; naero++){
		soma += voos[naero][indice];
	}
	return soma;
}

void cria_vetor_indices(int vector[]){/*Cria um novo vetor com todos os indices de aeroportos de maneira a que possam ser ordenados*/
	int i;
	for(i=0;i<controlador;i++){
		vector[i] = i;
	}
}

void selectionsort(int vector[], int l, int r){
	int i, j;
	for (i=l; i < r; i++){
		int ind_aux, min = i;
		for (j = i + 1; j < r; j++){/*Procura o valor minimo do vector*/
			if (strcmp(aeroportos[vector[j]].nome, aeroportos[vector[min]].nome) < 0) (min = j); /*Faz uso da biblioteca string.h e caso o primeiro
			argumento seja menor que o segundo, atribui como novo minimo o j*/
		}
	ind_aux = vector[i];/*Troca o valor da posicao i com o valor do minimo*/
	vector[i] = vector[min];
	vector[min] = ind_aux;
	}
}

void selectionsort_int(int vector[], int l, int r){ /*Analogo a selectionsort mas para um vetor de inteiros*/
	int i, j;
	for(i = l; i < r; i++){
		int ind_aux, min = i;
		for (j = i + 1; j < r; j++){
			if (vector[j] < vector[min]) (min = j);
		}
	ind_aux = vector[i];
	vector[i] = vector[min];
	vector[min] = ind_aux;
	}
}

int main(){
	char command;
	while (1) {
 		command = getchar();
 		switch (command){
 		case 'A':
			executa_A();
 		 	break;
 		case 'I':
 			executa_I();
 			break;
 		case 'F':
 			executa_F();
 			break;
 		case 'G':
 			executa_G();
 			break;
 		case 'R':
 			executa_R();
 			break;
 		case 'S':
 			executa_S();
 			break;
 		case 'N':
 			executa_N();
 			break;
 		case 'P':
 			executa_P();
 			break;
 		case 'Q':
 			executa_Q();
 			break;
 		case 'V':
 			executa_V();
 			break;
 		case 'C':
 			executa_C();
 			break;
 		case 'O':
 			executa_O();
 			break;
 		case 'L':
 			executa_L();
 			break;
 		case 'X':
 			executa_X();
 			return EXIT_SUCCESS;
		default:
 			printf("ERRO: Comando desconhecido\n");
 		}
 		getchar();
	}
	return EXIT_FAILURE;
}

void executa_A(){
	scanf("%s%d", aeroportos[controlador].nome, &aeroportos[controlador].capacidade); /*A variavel controlador guarda a posicao do novo aerporto*/
	aeroportos[controlador].estado = 1;
	inicializa_aeroporo_zeros(controlador);
	controlador ++;
	}

void executa_I(){
	char aero[STRINGMAX];
	int nova_capacidade, indice;
	scanf("%s%d", aero, &nova_capacidade);
	indice = procura_indice(aero);
	if (indice == -1 || aeroportos[indice].estado == 0 || (aeroportos[indice].capacidade + nova_capacidade) < soma_voos_aero(indice)) (printf("*Capacidade de %s inalterada\n", aero));
	else (aeroportos[indice].capacidade += nova_capacidade);
}

void executa_F(){ /*um voo de ida e volta, requer que a capacidade do aeroporto tenha pela menos dois slots disponiveis pois correpsonde a um voo de ida e volta*/
	char aero1[STRINGMAX], aero2[STRINGMAX];
	scanf("%s%s", aero1, aero2);
	int indice_partida = procura_indice(aero1), indice_chegada = procura_indice(aero2);
	if (indice_partida == -1 || aeroportos[indice_partida].estado ==0 || aeroportos[indice_partida].capacidade <
	 (soma_voos_aero(indice_partida) + 2) || indice_chegada == -1 || aeroportos[indice_chegada].estado == 0 || aeroportos[indice_chegada].capacidade <
	 (soma_voos_aero(indice_chegada) + 2)) (printf("*Impossivel adicionar voo RT %s %s\n", aero1, aero2));
	else{
		voos[indice_partida][indice_chegada] ++;
		voos[indice_chegada][indice_partida] ++;
	}
}

void executa_G(){
	char aero1[STRINGMAX], aero2[STRINGMAX];
	scanf("%s%s", aero1, aero2);
	int indice_partida = procura_indice(aero1), indice_chegada = procura_indice(aero2);
	if (indice_partida == -1 || aeroportos[indice_partida].estado ==0 || aeroportos[indice_partida].capacidade <
		(soma_voos_aero(indice_partida) + 1) || indice_chegada == -1 || aeroportos[indice_chegada].estado == 0 || aeroportos[indice_chegada].capacidade <
		(soma_voos_aero(indice_chegada) + 1)) (printf("*Impossivel adicionar voo %s %s\n", aero1, aero2));
	else{
		voos[indice_partida][indice_chegada] ++;
	}
}

void executa_R(){
	char aero1[STRINGMAX], aero2[STRINGMAX];
	scanf("%s%s", aero1, aero2);
	int indice_partida = procura_indice(aero1), indice_chegada = procura_indice(aero2);
	if (voos[indice_partida][indice_chegada] >= 1) (voos[indice_partida][indice_chegada] --);
	else printf("*Impossivel remover voo %s %s\n", aero1, aero2);
}

void executa_S(){
	char aero1[STRINGMAX], aero2[STRINGMAX];
	scanf("%s%s", aero1, aero2);
	int indice_partida = procura_indice(aero1), indice_chegada = procura_indice(aero2);
	if (voos[indice_partida][indice_chegada] >= 1 && voos[indice_chegada][indice_partida] >= 1){
		voos[indice_partida][indice_chegada] --;
		voos[indice_chegada][indice_partida] --;
	}
	else printf("*Impossivel remover voo RT %s %s\n", aero1, aero2);
}

void executa_N(){
	char aero1[STRINGMAX], aero2[STRINGMAX];
	scanf("%s%s", aero1, aero2);
	int indice_partida = procura_indice(aero1), indice_chegada = procura_indice(aero2);
	if (indice_partida != -1 && indice_chegada != -1) (printf("Voos entre cidades %s:%s:%d:%d\n", aero1, aero2, voos[indice_partida][indice_chegada], voos[indice_chegada][indice_partida]));
	else{
		if (indice_partida == -1) (printf("*Aeroporto %s inexistente\n",aero1));
		if (indice_chegada == -1) (printf("*Aeroporto %s inexistente\n",aero2));
	}
}

void executa_P(){
	int naero, soma = 0, soma_memoria = 0, indice_memoria = 0;
	for(naero = 0; naero < controlador; naero++){
		soma = soma_voos_aero(naero);
		if (soma > soma_memoria){
			indice_memoria = naero;
			soma_memoria = soma;
		}
	}
	printf("Aeroporto com mais rotas %s:%d:%d\n",aeroportos[indice_memoria].nome, soma_voos_outgoing(indice_memoria), soma_voos_incoming(indice_memoria));
}

void executa_Q(){
	int naero1, naero2, soma = 0, soma_memoria = 0, indice_memoria = 0;
	for(naero1 = 0; naero1 < controlador; naero1++, soma = 0){
		for(naero2 = 0; naero2 < controlador; naero2++){
			if (voos[naero1][naero2] > 0 || voos[naero2][naero1] > 0) (soma++);
		}
		if (soma > soma_memoria){
			soma_memoria = soma;
			indice_memoria = naero1;
		}
	}
	printf("Aeroporto com mais ligacoes %s:%d\n", aeroportos[indice_memoria].nome, soma_memoria);
}

void executa_V(){
	int naero1, naero2, soma = 0, soma_memoria = 0, indice_memoria_1 = 0, indice_memoria_2 = 0;
	for (naero1 = 0; naero1 < controlador; naero1++){
		for(naero2 = 0; naero2 < controlador; naero2++){
			soma = voos[naero1][naero2];
			if (soma > soma_memoria){
				soma_memoria = soma;
				indice_memoria_1 = naero1;
				indice_memoria_2 = naero2;
			}
		}
	}
	printf("Voo mais popular %s:%s:%d\n", aeroportos[indice_memoria_1].nome, aeroportos[indice_memoria_2].nome, soma_memoria);
}

void executa_C(){
	char aero[STRINGMAX];
	int indice;
	scanf("%s", aero);
	indice = procura_indice(aero);
	if (indice != -1){
		aeroportos[indice].estado = 0;
		inicializa_aeroporo_zeros(indice);
	}
	else{
		printf("*Aeroporto %s inexistente\n", aero);
	}
}

void executa_O(){
	char aero[STRINGMAX];
	int indice;
	scanf("%s", aero);
	indice = procura_indice(aero);
	if (indice != -1){
		aeroportos[indice].estado = 1;
	}
	else{
		printf("*Aeroporto %s inexistente\n", aero);
	}
}

void executa_L(){
	int tipo;
	scanf("%d", &tipo);
	if (tipo == 0) (executa_L0());
	else if (tipo == 1) (executa_L1());
	else if (tipo == 2) (executa_L2());
}

void executa_L0(){
	int naero;
	for(naero= 0; naero < controlador; naero++){
		printf("%s:%d:%d:%d\n", aeroportos[naero].nome, aeroportos[naero].capacidade, soma_voos_outgoing(naero), soma_voos_incoming(naero));
	}
}

void executa_L1(){
	int vetor_indices[AEROMAX], naero; /*Cria-se um vetor com os indices dos aeroportos*/
	cria_vetor_indices(vetor_indices);
	selectionsort(vetor_indices, 0, controlador);/*Ordena-se o vetor alfabeticamente segundo o nome do aeroporto,
	em que o indice do vetor corresponde `a sua posicao ordenada e o seu valor a posicao no vetor incial de aerportos para podermos aceder aos nomes*/
	for(naero= 0; naero < controlador; naero++){
		printf("%s:%d:%d:%d\n", aeroportos[vetor_indices[naero]].nome, aeroportos[vetor_indices[naero]].capacidade, soma_voos_outgoing(vetor_indices[naero]),
			soma_voos_incoming(vetor_indices[naero]));
	}
}

void executa_L2(){
	int vetor_histograma[AEROMAX], naero, i, contador = 0, controlo;
	for(naero = 0; naero < controlador; naero++){
		vetor_histograma[naero] = soma_voos_aero(naero);/*Cria-se um vetor com todos os voos*/
	}
	selectionsort_int(vetor_histograma, 0, controlador);/*Ordena-se esse mesmo vetor*/
	controlo = vetor_histograma[0];
	for(i = 0; i <= controlador; i++){
		if (i == controlador || vetor_histograma[i] != controlo){/*Percorre-se o vetor e enquanto o valor nao for diferente vai contando a frequencia desse numero de voos*/
			printf("%d:%d\n", controlo, contador);
			contador = 0;
			controlo = vetor_histograma[i];
		}
		contador ++;
	}
}

void executa_X(){
	int soma = 0, naero, naero2;
	for (naero = 0; naero < controlador; naero++){
		for(naero2 = 0; naero2 < controlador; naero2++){
			soma += voos[naero][naero2];
		}
	}
	printf("%d:%d\n", soma, controlador);
}
