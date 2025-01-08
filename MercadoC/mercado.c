#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct{
	int codigo;
	char nome[30];
	float preco;
}Produto;

typedef struct{
	Produto produto;
	int quantidade;
}Carrinho;

void infoProduto(Produto p);
void menu();
void cadastrarProduto();
void listarProduto();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto=0;
static int contador_carrinho=0;
static Carrinho carrinho[50];
static Produto produto[50];

int main(){
	menu();

	return 0;
}

void infoProduto(Produto p){
	printf("Código: %d\nNome: %s\n Preço: %.2f\n",p.codigo,strtok(p.nome,"\n"),p.preco);

}

void menu(){
	printf("=======================================\n");
	printf("===============Bem-vindo===============\n");
	printf("=======================================\n");

	printf("Selecione uma opção abaixo: \n");
	printf("1 - Cadastrar produto\n");
	printf("2 - Listar Produtos\n");
	printf("3 - Comprar\n");
	printf("4 - Visualizar carrinho\n");
	printf("5 - Fechar pedido\n");
	printf("6 - Sair\n");

	int opcao;
	fflush(stdout);
	scanf("%d", &opcao);
	getchar();

	switch(opcao){
		case 1:
			cadastrarProduto();
			break;
		case 2:
			listarProduto();
			break;
		case 3:
			comprarProduto();
			break;
		case 4:
			visualizarCarrinho();
			break;
		case 5:
			fecharPedido();
			break;
		case 6:
			printf("Volte sempre!\n");
			Sleep(2);
			exit(0);
		default:
			printf("Opção invalida.\n");
			menu();
			break;
	}

}

void cadastrarProduto(){
	printf("Cadastro de produto\n");
	printf("====================\n");

	printf("Informe o nome do produto: \n");
	fflush(stdout);
	fgets(produto[contador_produto].nome,30,stdin);

	printf("Informe o preço do produto: \n");
	fflush(stdout);
	scanf("%f", &produto[contador_produto].preco);

	printf("O produto %s foi cadastrado com sucesso. \n",strtok(produto[contador_produto].nome,"\n"));

	produto[contador_produto].codigo=(contador_produto+1);
	contador_produto++;
	Sleep(2);
	menu();
}

void listarProduto(){
	if(contador_produto>0){
		printf("Listagem de produtos.\n");
		printf("---------------------\n");
		for(int i=0;i<contador_produto;i++){
			infoProduto(produto[i]);
			printf("---------------------\n");
			Sleep(1);
		}
		Sleep(2);
		menu();
	}else{
		printf("Não temos produtos cadastrados.\n");
		Sleep(2);
		menu();
	}

}
void comprarProduto(){
	if(contador_produto>0){
		printf("Informe o codigo do produto.\n");

		printf("=========Produtos disponiveis==========\n");
		for(int i =0;i<contador_produto;i++){
			infoProduto(produto[i]);
			printf("--------------------\n");
			Sleep(1);
		}
		int codigo;
		fflush(stdout);
		scanf("%d", &codigo);
		getchar();

		int tem_mercado=0;
		for(int i=0;i<contador_produto;i++){
			if(produto[i].codigo==codigo){
				tem_mercado=1;

				if(contador_carrinho>0){
					int * retorno=temNoCarrinho(codigo);

					if(retorno[0]==1){
						carrinho[retorno[1]].quantidade++;
						printf("Aumentei a quantidade do produto %s já existente no carrinho.\n",
								strtok(carrinho[retorno[1]].produto.nome,"\n"));
						Sleep(2);
						menu();
					}else{
						Produto p=pegarProdutoCodigo(codigo);
						carrinho[contador_carrinho].produto=p;
						carrinho[contador_carrinho].quantidade=1;
						contador_carrinho++;
						printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome,"\n"));
						Sleep(2);
						menu();
					}
				}else{
					Produto p=pegarProdutoCodigo(codigo);
					carrinho[contador_carrinho].produto=p;
					carrinho[contador_carrinho].quantidade=1;
					contador_carrinho++;
					printf("O produto %s foi adicionado ao carrinho.\n",strtok(p.nome,"\n"));
					Sleep(2);
					menu();
				}

			}

		}
		if(tem_mercado<1){
			printf("Não foi encontrado o produto com o codigo %d.\n", codigo);
			Sleep(2);
			menu();
		}


	}else{
		printf("Ainda não existem produtos para comprar.\n");
		Sleep(2);
		menu();
	}

}

void visualizarCarrinho(){
	if(contador_carrinho>0){
		printf("Produtos do carrinho\n");
		printf("---------------------\n");
		for(int i=0; i<contador_carrinho;i++){
			infoProduto(carrinho[i].produto);
			printf("Quantidade: %d\n",carrinho[i].quantidade);
			printf("---------------------\n");
			Sleep(1);
		}
		Sleep(2);
		menu();
	}else{
		printf("Não temos produtos no carrinho.\n");
		Sleep(2);
		menu();
	}

}
Produto pegarProdutoCodigo(int codigo){
	Produto prod;
	for(int i=0;i<contador_produto;i++){
		if(produto[i].codigo==codigo){
			prod=produto[i];
		}
	}
	return prod;



}

int * temNoCarrinho(int codigo){
	int static retorno[]= {0,0};
	for(int i=0;i<contador_carrinho;i++){
		if(carrinho[i].produto.codigo==codigo){
			retorno[0]=1;
			retorno[1]=i;
		}
	}
	return retorno;
}
void fecharPedido(){
	if(contador_carrinho>0){
		float valorTotal=0;
		printf("Produtos do carrinho\n");
		printf("---------------------\n");
		for(int i =0; i<contador_carrinho;i++){
			Produto prod=carrinho[i].produto;
			int quantidade=carrinho[i].quantidade;
			valorTotal+=prod.preco*quantidade;
			infoProduto(prod);
			printf("Quantidade: %d\n", quantidade);
			printf("---------------------\n");
			Sleep(1);
		}
		printf("Sua fatura é R$ %.2f\n",valorTotal);
		contador_carrinho=0;
		printf("Obrigado pela preferencia.\n");
		Sleep(5);
		menu();
	}else{
		printf("Você não tem nenhum produto no carrinho...\n");
		Sleep(2);
		menu();
	}

}
