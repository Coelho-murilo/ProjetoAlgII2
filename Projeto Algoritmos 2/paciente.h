#define TAM_STRING 20
#ifndef PACIENTE_H
#define PACIENTE_H

typedef struct {
	int codigoPaciente;
	char nomePaciente[TAM_STRING];
	int idadePaciente;
	float alturaPaciente;
} Paciente;

int InicializarPacientes();
int EncerraPacientes();
int SalvarPaciente(Paciente b);
int QuantidadePacientes();
Paciente* ObterPacientePeloIndice(int indice);
Paciente* ObterPacientePeloCodigo(int codigo);
int AtualizarPaciente(Paciente b);
int ApagarPacientePeloCodigo(int codigo);
int ApagarPacientePeloNome(char* nome);

#endif
