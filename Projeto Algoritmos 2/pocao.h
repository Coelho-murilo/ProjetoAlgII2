#define TAM_STRING 20
#ifndef POCAO_H
#define POCAO_H

typedef struct {
	int codigoPocao;
	char nomePocao[TAM_STRING];
	char tipoPocao[TAM_STRING];
} Pocao;

int InicializarPocoes();
int EncerraPocoes();
int SalvarPocao(Pocao b);
int QuantidadePocoes();
Pocao* ObterPocaoPeloIndice(int indice);
Pocao* ObterPocaoPeloCodigo(int codigo);
int AtualizarPocao(Pocao b);
int ApagarPocaoPeloCodigo(int codigo);
int ApagarPocaoPeloNome(char* nome);

#endif
