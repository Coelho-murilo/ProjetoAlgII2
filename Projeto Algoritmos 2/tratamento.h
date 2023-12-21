#define TAM_STRING 20
#ifndef TRATAMENTO_H
#define TRATAMENTO_H

typedef struct{
	int codigo;
	int codigoBruxo;
	int codigoPaciente;
	int codigoPocao;
	int dosagem;
	int qtdDias;
} Tratamento;

int InicializarTratamento();
int EncerraTratamento();
int SalvarTratamento(Tratamento t);
int QuantidadeTratamento();
Tratamento* ObterTratamentoPeloCodigo(int codigo);
Tratamento* ObterTratamentoPeloCodigodoBruxo(int codigo, int indice);
Tratamento* ObterTratamentoPeloCodigodoPaciente(int codigo, int indice);
Tratamento* ObterTratamentoPeloCodigodaPocao(int codigo, int indice);
int AtualizarTratamento(Tratamento t);
int ApagarTratamentoPeloCodigo(int codigo);

#endif

