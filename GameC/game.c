#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int dificuldade;
	int valor1;
	int valor2;
	int operacao;
	int resultado;
}Calcular;

void jogar();
void mostrarInfo(Calcular calc);
int somar(int resposta, Calcular calc);
int diminuir(int resposta, Calcular calc);
int multiplicar(int resposta, Calcular calc);


int pontos=0;

int main(){
	srand(time(NULL));

	jogar();


	return 0;
}

void jogar(){
	Calcular calc;
	int dificuldade;

	printf("Informe o nivel de dificuldade desejado [1,2,3 ou 4]");
	fflush(stdout);
	scanf("%d", &dificuldade);

	calc.operacao=rand()%3;

	if(calc.dificuldade==1){
		calc.valor1=rand()%11;
		calc.valor2=rand()%11;
	}else if(calc.dificuldade==2){
		calc.valor1=rand()%101;
		calc.valor2=rand()%101;
	}else if(calc.dificuldade==3){
		calc.valor1=rand()%1001;
		calc.valor2=rand()%1001;
	}else if(calc.dificuldade==4){
		calc.valor1=rand()%10001;
		calc.valor2=rand()%10001;
	}else{
		calc.valor1=rand()%100001;
		calc.valor2=rand()%100001;
	}

	int resposta;
	printf("Informe o resultado para a seguinte operação: \n");

	if(calc.operacao==0){
		printf("%d + %d\n",calc.valor1,calc.valor2);
		fflush(stdout);
		scanf("%d", &resposta);

		if(somar(resposta, calc)){
			pontos+=1;
			printf("Você tem %d ponto(s).\n ", pontos);
		}

	}else if(calc.operacao==1){
		printf("%d - %d\n",calc.valor1,calc.valor2);
		fflush(stdout);
		scanf("%d", &resposta);

		if(diminuir(resposta, calc)){
			pontos+=1;
			printf("Você tem %d ponto(s).\n ", pontos);
		}
	}else if(calc.operacao==2){
		printf("%d X %d\n",calc.valor1,calc.valor2);
		fflush(stdout);
		scanf("%d", &resposta);

		if(multiplicar(resposta, calc)){
			pontos+=1;
			printf("Você tem %d ponto(s).\n ", pontos);
		}
	}else{
		printf("A operação %d não é reconecida.\n", calc.operacao);
	}
	printf("Deseja continuar jogando? [1-sim, 0-não]");
	int continuar;
	fflush(stdout);
	scanf("%d", &continuar);

	if(continuar){
		jogar();
	}else{
		printf("Você finalizou com %d ponto(s).\n", pontos);
		printf("Até a proxima");
		exit(0);
	}
}

void mostrarInfo(Calcular calc){
	char op[25];

	if(calc.operacao==0){
		sprintf(op,"Somar");
	}else if(calc.operacao==1){
		sprintf(op, "Diminuir");
	}else if(calc.operacao==2){
		sprintf(op,"Multiplicar");
	}else{
		sprintf(op, "Operação desconhecida!");
	}
	printf("Valor 1: %d \nValor 2: %d \nDificuldade: %d \nOperação: %s",
			calc.valor1, calc.valor2, calc.dificuldade, calc.operacao);

}

int somar(int resposta, Calcular calc){
	int resultado=calc.valor1+calc.valor2;
	calc.resultado= resultado;
	int certo=0;

	if(resposta==calc.resultado){
		printf("Resposa correta!\n");
	}else{
		printf("Resposta errada!\n");
	}
	printf("%d + %d= %d\n", calc.valor1,calc.valor2, calc.resultado);
	return certo;
}

int diminuir(int resposta, Calcular calc){
	int resultado=calc.valor1-calc.valor2;
		calc.resultado= resultado;
		int certo=0;

		if(resposta==calc.resultado){
			printf("Resposa correta!\n");
		}else{
			printf("Resposta errada!\n");
		}
		printf("%d - %d= %d\n", calc.valor1,calc.valor2, calc.resultado);
		return certo;
	}

int multiplicar(int resposta, Calcular calc){
	int resultado=calc.valor1*calc.valor2;
		calc.resultado= resultado;
		int certo=0;

		if(resposta==calc.resultado){
			printf("Resposa correta!\n");
		}else{
			printf("Resposta errada!\n");
		}
		printf("%d X %d= %d\n", calc.valor1,calc.valor2, calc.resultado);
		return certo;
	}


