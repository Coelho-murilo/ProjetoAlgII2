#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Bruxo.h"
#include "Pocao.h"
#include "Paciente.h"
#include "Tratamento.h"

int main(int argc, char *argv[]) {

// variáveis do menu	
int menu = -1;
int subMenuB = -1;
int subMenuP = -1;
int subMenuPc = -1;
int subMenuT = -1;
	
// variáveis do bruxo
Bruxo b;
Bruxo* Bb;

// variáveis do paciente
Paciente p;
Paciente* Pp;

// variáveis da poção
Pocao Pc;
Pocao* Pcp;

// variáveis tratamento
int checkTratamento;
Tratamento t;
Tratamento* Tt;

// demais variáveis
int check;
int codigo;


// inicializando 
check = InicializarBruxos();
if(!check){
	printf("Erro ao alocar memoria!");
}
check = InicializarPacientes();
if(!check){
	printf("Erro ao alocar memoria!");
}
check = InicializarPocoes();
if(!check){
	printf("Erro ao alocar memoria!");
}

check = InicializarTratamento();
if(!check){
	printf("Erro ao alocar memoria!");
}

while(menu != 0) //menu geral
{
	printf("\n------- Menu -------\n");
	printf("\n\n0 - Sair \n");
	printf("1 - Bruxo \n");
	printf("2 - Paciente \n");
	printf("3 - Pocao \n");
	printf("4 - Tratamento \n");
	
	printf("\nDigite o codigo do que voce quer fazer: ");
	scanf("%d", &menu);
	
	switch (menu){
		case 0:
			printf("\nSistema finalizado!\n");
			break;
		case 1: 
			while(subMenuB != 0) //menu do bruxo
			{
				printf("\n------- Menu Bruxo -------\n");
				printf("\n\n0 - Sair \n");
				printf("1 - Listar Bruxo \n");
				printf("2 - Cadastrar Bruxo \n");
				printf("3 - Alterar Bruxo \n");
				printf("4 - Excluir Bruxo \n");	
				
				printf("\nDigite o codigo do que voce quer fazer: ");
				scanf("%d", &subMenuB);
				
				switch (subMenuB){
					case 1: 
						//Listando bruxos
						printf("\n--- Listando Bruxo! ---\n");
						//verificando bruxo cadastrado
						if(QuantidadeBruxos() == 0)
							printf("\nSem bruxo cadastrado!!\n");	
						for(int i = 0; i < QuantidadeBruxos(); i++){
							Bb = ObterBruxoPeloIndice(i);
							if (Bb != NULL) //verificando se tem bruxo cadastrado
								printf ("\nCodigo do bruxo: %d - Nome do bruxo: %s - Especialidade do bruxo: %s\n", Bb->codigoBruxo, Bb->nomeBruxo, Bb->especialidadeBruxo);
							else
								printf("Erro!");
							free(Bb);								
						}
						break;
					case 2: 
						//cadastrando bruxo						
						printf("\n--- Cadastrando Bruxo! ---\n");
						printf("\nCodigo do bruxo: ");
						scanf("%d", &b.codigoBruxo);
						printf("\nNome do Bruxo: ");
						scanf(" %[^\n]s", b.nomeBruxo);
						fflush(stdin);						
						printf("Especialidade do Bruxo: ");
						scanf(" %[^\n]s", b.especialidadeBruxo);
						fflush(stdin);
						// função para salvar as info do bruxo
						check = SalvarBruxo(b);
						if(check) //verificando se salvou
							printf("\nBruxo cadastrado com sucesso!\n");
						else
							printf("\nErro ao cadastrar bruxo!!\n");
						break;
					case 3:
						//Alterando bruxo						
						printf("\n--- Alterando Bruxo! ---\n");
						if(QuantidadeBruxos() == 0) //verificando se tem bruxo cadastrado
							printf("\nSem bruxo cadastrado!!\n");
						else{ //listando o bruxo cadastrado e impedindo de alterar caso não tenha bruxo cadastrado
							for(int i = 0; i < QuantidadeBruxos(); i++){						
								Bb = ObterBruxoPeloIndice(i);	
								if (Bb != NULL)
									printf ("\nCodigo do bruxo: %d - Nome do bruxo: %s - Especialidade do bruxo: %s\n", Bb->codigoBruxo, Bb->nomeBruxo, Bb->especialidadeBruxo);
								else
									printf("Erro!");
							}// alterando o bruxo
							printf("\nQual o codigo do Bruxo? ");
							scanf("%d", &codigo);					
							Bb = ObterBruxoPeloCodigo(codigo);
							if(Bb == 0){//verificando o erro
								printf("\nErro!!\n");
								break;
							}
							b.codigoBruxo = Bb->codigoBruxo;
							strcpy(b.nomeBruxo, Bb->nomeBruxo);
							strcpy(b.especialidadeBruxo, Bb->especialidadeBruxo);
							printf("\nQuer alterar o nome do Bruxo? (1-sim / 2-nao) " );
							scanf("%d", &check);
							if(check == 1){
								printf("Qual o novo nome? ");
								scanf(" %[^\n]s", b.nomeBruxo);
								fflush(stdin);
							}
							printf("\nQuer alterar a especialidade do Bruxo? (1-sim / 2-nao) ");
							scanf("%d", &check);
							if(check == 1){
								printf("Qual a especialidade do bruxo? ");
								scanf(" %[^\n]s", b.especialidadeBruxo);
								fflush(stdin);
							}
							if(AtualizarBruxo(b))
								printf("\nAlteracoes realizadas com sucesso!!\n");
						}
						break;
					case 4:
						//Excluindo bruxo
						printf("\n--- Apagando Bruxo! ---\n");
						if(QuantidadeBruxos() == 0)
							printf("\nSem bruxo cadastrado!!\n");
						else{//verificando se tem bruxo cadastrado e excluindo
							for(int i = 0; i < QuantidadeBruxos(); i++){
								Bb = ObterBruxoPeloIndice(i);
								if (Bb != NULL)
									printf ("\nCodigo do bruxo: %d - Nome do bruxo: %s - Especialidade do bruxo: %s\n", Bb->codigoBruxo, Bb->nomeBruxo, Bb->especialidadeBruxo);
								else
									printf("Erro!");
							}
							printf("\nQual o codigo do Bruxo? ");
							scanf("%d", &codigo);
							
							for(int i = 0; i < QuantidadeTratamento(); i++){
								
								if((Tt = ObterTratamentoPeloCodigodoBruxo(codigo, i)) != 0){
									
									printf("\nERRO: Bruxo presente no tratamento '%i'.\n", Tt->codigo);
									checkTratamento = 1;
									free(Tt);
									break;

								} else 
									checkTratamento = 0;
								
								free(Tt);
							}
							
							if(checkTratamento) 
								break;
							
							if(ApagarBruxoPeloCodigo(codigo))
								printf("\nBruxo excluido com sucesso\n");
							else 
								printf("\nErro ao excluir bruxo\n");				
						}
						break;
				}	
			}
			break;	
		case 2:
			while(subMenuP != 0)
			{
				printf("\n------- Menu Paciente -------\n");
				printf("\n\n0 - Sair \n");
				printf("1 - Listar Paciente \n");
				printf("2 - Cadastrar Paciente \n");
				printf("3 - Alterar Paciente \n");
				printf("4 - Excluir Paciente \n");		
				
				printf("\nDigite o codigo do que voce quer fazer: ");
				scanf("%d", &subMenuP);
				
				switch (subMenuP){
					case 1: 
						//Listar		 
						printf("\n--- Listando Paciente! ---\n");
						if(QuantidadePacientes() == 0)
							printf("\nSem paciente cadastrado!!\n");
						for(int i = 0; i < QuantidadePacientes(); i++){
							Pp = ObterPacientePeloIndice(i);
							if (Pp != NULL)
								printf ("\nCodigo do paciente: %d - Nome do paciente: %s - Idade do paciente: %d - Altura do paciente: %.2f\n", Pp->codigoPaciente, Pp->nomePaciente, Pp->idadePaciente, Pp->alturaPaciente);
							else
								printf("Erro!");
						}
						break;
					case 2: 
						//cadastrar
						printf("\n--- Cadastrando Paciente! ---\n");
						printf("\nCodigo do Paciente: ");
						scanf("%d", &p.codigoPaciente);
						printf("\nNome do Paciente: ");
						scanf(" %[^\n]s", p.nomePaciente);
						fflush(stdin);						
						printf("Idade do Paciente: ");
						scanf("%d", &p.idadePaciente);
						printf("Altura do Paciente: ");
						scanf("%f", &p.alturaPaciente);						
						check = SalvarPaciente(p);
						if(check)
							printf("\nPaciente cadastrado com sucesso!\n");
						else
							printf("\nErro ao cadastrar paciente!!\n");
						break;
					case 3:
						//Alterar
						printf("\n--- Alterando Paciente! ---\n");
						if(QuantidadePacientes() == 0)
							printf("\nSem paciente cadastrado!!\n");
						else{
							for(int i = 0; i < QuantidadePacientes(); i++){
								Pp = ObterPacientePeloIndice(i);
								if (Pp != NULL)
									printf ("\nCodigo do paciente: %d - Nome do paciente: %s - Idade do paciente: %d - Altura do paciente: %.2f\n", Pp->codigoPaciente, Pp->nomePaciente, Pp->idadePaciente, Pp->alturaPaciente);
								else
									printf("Erro!");
							}
							printf("\nQual o codigo do Paciente? ");
							scanf("%d", &codigo);
							Pp = ObterPacientePeloCodigo(codigo);
							if(Pp == 0){
								printf("\nErro!!\n");
								break;
							}
							p.codigoPaciente = Pp->codigoPaciente;
							strcpy(p.nomePaciente, Pp->nomePaciente);
							p.idadePaciente = Pp->idadePaciente;
							p.alturaPaciente = Pp->alturaPaciente;
							printf("\nQuer alterar o nome do Paciente? (1-sim / 2-nao) " );
							scanf("%d", &check);
							if(check == 1){
								printf("Qual o novo nome? ");
								scanf(" %[^\n]s", p.nomePaciente);
								fflush(stdin);
							}
							printf("\nQuer alterar a idade do Paciente? (1-sim / 2-nao) ");
							scanf("%d", &check);
							if(check == 1){
								printf("Qual a idade do Paciente? ");
								scanf("%d", &p.idadePaciente );
							}
							printf("\nQuer alterar a altura do Paciente? (1-sim / 2-nao) ");
							scanf("%d", &check);
							if(check == 1){
								printf("Qual a altura do Paciente? ");
								scanf("%f", &p.alturaPaciente );
							}
							if(AtualizarPaciente(p))
								printf("\nAlteracoes realizadas com sucesso!!\n");
							break;
						}
						break;	
					case 4:
						//Excluir
						printf("\n--- Apagando Paciente! ---\n");
						if(QuantidadePacientes() == 0)
							printf("\nSem paciente cadastrado!!\n");
						else{
							for(int i = 0; i < QuantidadePacientes(); i++){
								Pp = ObterPacientePeloIndice(i);					
								if (Pp != NULL)
									printf ("\nCodigo do paciente: %d - Nome do paciente: %s - Idade do paciente: %d - Altura do paciente: %.2f\n", Pp->codigoPaciente, Pp->nomePaciente, Pp->idadePaciente, Pp->alturaPaciente);
								else
									printf("Erro!");
							}
							printf("\nQual o codigo do Paciente? ");
							scanf("%d", &codigo);
							for(int i = 0; i < QuantidadeTratamento(); i++){
								
								if((Tt = ObterTratamentoPeloCodigodoPaciente(codigo, i)) != 0){
									
									printf("\nERRO: Paciente presente no tratamento '%i'.\n", Tt->codigo);
									checkTratamento = 1;
									free(Tt);
									break;

								} else 
									checkTratamento = 0;
								
								free(Tt);
							}
							
							if(checkTratamento) 
								break;
							if(ApagarPacientePeloCodigo(codigo))
								printf("\nPaciente excluido com sucesso\n");
							else 
								printf("\nErro ao excluir paciente\n");
								break;
						}
						break;
				}
			}
			break;
		case 3:
			while(subMenuPc != 0)
			{
				printf("\n------- Menu Pocao -------\n");
				printf("\n\n0 - Sair \n");
				printf("1 - Listar Pocao \n");
				printf("2 - Cadastrar Pocao \n");
				printf("3 - Alterar Pocao \n");
				printf("4 - Excluir Pocao \n");	
				
				printf("\nDigite o codigo do que voce quer fazer: ");
				scanf("%d", &subMenuPc);
				
				switch (subMenuPc){
					case 1: 
						//Listar
						printf("\n--- Listando Pocao! ---\n");
						if(QuantidadePocoes() == 0)
							printf("\nSem pocao cadastrado!!\n");
						for(int i = 0; i < QuantidadePocoes(); i++){
							Pcp = ObterPocaoPeloIndice(i);
							if (Pcp != NULL)
								printf ("\nCodigo da pocao: %d - Nome da pocao: %s - tipo da pocao: %s\n", Pcp->codigoPocao, Pcp->nomePocao, Pcp->tipoPocao);
							else
								printf("Erro!");
						}
						break;
					case 2: 
						//cadastrar
						printf("\n--- Cadastrando Pocao! ---\n");
						printf("\nCodigo da Pocao: ");
						scanf("%d", &Pc.codigoPocao);
						printf("\nNome da Pocao: ");
						scanf(" %[^\n]s", Pc.nomePocao);
						fflush(stdin);						
						printf("Tipo da pocao: ");
						scanf(" %[^\n]s", Pc.tipoPocao);
						fflush(stdin);
						check = SalvarPocao(Pc);
						if(check)
							printf("\nPocao cadastrada com sucesso!\n");
						else
							printf("\nErro ao cadastrar Pocao!!\n");
						break;
					case 3:
						//Alterar
						printf("\n--- Alterando Pocao! ---\n");
						if(QuantidadePocoes() == 0)
							printf("\nSem pocao cadastrado!!\n");
						else{
							for(int i = 0; i < QuantidadePocoes(); i++){
								Pcp = ObterPocaoPeloIndice(i);
								if (Pcp != NULL)
									printf ("\nCodigo da pocao: %d - Nome da pocao: %s - tipo da pocao: %s\n", Pcp->codigoPocao, Pcp->nomePocao, Pcp->tipoPocao);
								else
									printf("Erro!");
							}
							printf("\nQual o codigo da Pocao? ");
							scanf("%d", &codigo);
							Pcp = ObterPocaoPeloCodigo(codigo);
							if(Pcp == 0){
								printf("\nErro!!\n");
								break;
							}
							Pc.codigoPocao = Pcp->codigoPocao;
							strcpy(Pc.nomePocao, Pcp->nomePocao);
							strcpy(Pc.tipoPocao, Pcp->tipoPocao);
							printf("\nQuer alterar o nome da Pocao? (1-sim / 2-nao) " );
							scanf("%d", &check);
							if(check == 1){
								printf("Qual o novo nome? ");
								scanf(" %[^\n]s", Pc.nomePocao);
								fflush(stdin);
							}
							printf("\nQuer alterar o tipo da Pocao? (1-sim / 2-nao) ");
							scanf("%d", &check);
							if(check == 1){
								printf("Qual o tipo da Pocao ");
								scanf(" %[^\n]s", Pc.tipoPocao);
								fflush(stdin);
							}
							if(AtualizarPocao(Pc))
								printf("\nAlteracoes realizadas com sucesso!!\n");
						}	
						break;
					case 4:
						//Excluir
						printf("\n--- Apagando Pocao! ---\n");
						if(QuantidadePocoes() == 0)
							printf("\nSem pocao cadastrado!!\n");
						else{
							for(int i = 0; i < QuantidadePocoes(); i++){
								Pcp = ObterPocaoPeloIndice(i);
								if (Pcp != NULL)
									printf ("\nCodigo da pocao: %d - Nome da pocao: %s - tipo da pocao: %s\n", Pcp->codigoPocao, Pcp->nomePocao, Pcp->tipoPocao);
								else
									printf("Erro!");
							}
							printf("\nQual o codigo da Pocao? ");
							scanf("%d", &codigo);
							for(int i = 0; i < QuantidadeTratamento(); i++){
								
								if((Tt = ObterTratamentoPeloCodigodaPocao(codigo, i)) != 0){
									
									printf("\nERRO: Pocao presente no tratamento '%i'.\n", Tt->codigo);
									checkTratamento = 1;
									free(Tt);
									break;

								} else 
									checkTratamento = 0;
								
								free(Tt);
							}
							
							if(checkTratamento) 
								break;
							if(ApagarPocaoPeloCodigo(codigo))
								printf("\nPocao excluida com sucesso\n");
							else 
								printf("\nErro ao excluir Pocao\n");
							break;
						}	
						break;	
				}	
			}
			break;
		case 4:
			while(subMenuT != 0) 
				{
				printf("\n------- Menu Tratamento -------\n");
				printf("\n\n0 - Sair \n");
				printf("1 - Listar tratamento do paciente  \n");
				printf("2 - Listar tratamento do bruxo \n");
				printf("3 - Iniciar tratamento \n");
				printf("4 - Ampliar tratamento \n");	
				printf("5 - Excluir tratamento \n");
				
				printf("\nDigite o codigo do que voce quer fazer: ");
				scanf("%d", &subMenuT);
					
				switch (subMenuT){
					case 1: 
						//Listar Trat paciente		 
						printf("\n--- Listando Tratamento do Paciente! ---\n");
						if(QuantidadePacientes() == 0)
							printf("\nSem paciente cadastrado!!\n");
						
						printf("Digite o codigo do paciente: ");
						scanf("%d", &codigo);
						Pp = ObterPacientePeloCodigo(codigo);
						if (Pp == NULL){
							printf("Codigo invalido!");
							break;
						}
						
						
						free(Pp);

						for(int i = 0; i < QuantidadeTratamento(); i++){
							if ((Tt = ObterTratamentoPeloCodigodoPaciente(codigo, i)) != 0){
								printf ("\nCodigo do Tratamento: %d - Codigo do Bruxo: %d - Codigo da Pocao: %d - Quantidade de dias: %d - Dosagem: %d\n", Tt->codigo, Tt->codigoBruxo, Tt->codigoPocao, Tt->qtdDias, Tt->dosagem);
								free(Tt);
							}
							else
								printf("Erro!");
						}
						break;				
					case 2: 
						//Listar Trat bruxo
						printf("\n--- Listando Tratamento do Bruxo! ---\n");
						if(QuantidadeBruxos() == 0)
							printf("\nSem bruxo cadastrado!!\n");
						
						printf("Digite o codigo do bruxo: ");
						scanf("%d", &codigo);
						Bb = ObterBruxoPeloCodigo(codigo);
						if(Bb == NULL){
							printf("Codigo invalido!");
							break;
						}
						
						free(Bb);
						
						for(int i = 0; i < QuantidadeTratamento(); i++){
							if ((Tt = ObterTratamentoPeloCodigodoBruxo(codigo, i)) != 0){
								printf ("\nCodigo do Tratamento: %d - Codigo do Paciente: %d - Codigo da Pocao: %d - Quantidade de dias: %d - Dosagem: %d\n", Tt->codigo, Tt->codigoPaciente, Tt->codigoPocao, Tt->qtdDias, Tt->dosagem);
								free(Tt);
							}
							else
								printf("Erro!");
						}
						break;
					case 3:
						//Iniciar
						printf("\n--- Iniciando Tratamento ---");
							
						if(QuantidadeBruxos() == 0){
							printf("\n\nSem bruxos cadastrados!\n");								
						}
							
						if(QuantidadePacientes() == 0){
							printf("\n\nSem pacientes cadastrados!\n");
						}
							
						if(QuantidadePocoes() == 0){
							printf("\n\nSem pocoes cadastradas!\n");
						}
						printf("\n Codigo do Tratamento: ");
						scanf("%d", &t.codigo);	
						printf("\n\nCodigo do Bruxo: ");
						scanf("%d", &t.codigoBruxo);
						
						Bb = ObterBruxoPeloCodigo(t.codigoBruxo);	
						if(Bb == NULL){
							printf("\nERRO: Codigo Invalido!\n");
							break;		
						}
							
						free(Bb);
							
						printf("Codigo do Paciente: ");
						scanf("%d", &t.codigoPaciente);
						
						Pp = ObterPacientePeloCodigo(t.codigoPaciente);	
						if(Pp == NULL){
							printf("\nERRO: Codigo Invalido!\n");
									
							break;						
						}
							
						free(Pp);
							
						printf("Codigo da Pocao: ");
						scanf("%d", &t.codigoPocao);
						
						Pcp = ObterPocaoPeloCodigo(t.codigoPocao);	
						if(Pcp == NULL){
							printf("\nERRO: Codigo Invalido!\n");
									
							break;						
						}
							
						free(Pcp);
							
						printf("Quantidade de Dias: ");
						scanf("%d", &t.qtdDias);
						printf("Informe a dosagem: ");
						scanf("%i", &t.dosagem);
							
						if(SalvarTratamento(t)) 
							printf("\nTratamento iniciado com sucesso!\n");
						else 
							printf("\nRRO: Erro ao inciar tratamento!\n");
														
						break;		
					case 4:
						printf("\n--- Ampliando Tratamento ---");
							
						if(QuantidadeTratamento() == 0){
							printf("\n\nSem tratamentos cadastrados!\n");
						}
							
						printf("\n\nDigite o codigo do tratamento: ");
						scanf("%d", &codigo);

						Tt = ObterTratamentoPeloCodigo(codigo);
							
						if(Tt == 0){
							printf("\nERRO: Algum erro aconteceu!\n");											
						}
							
						t.codigo = Tt->codigo;
						t.codigoBruxo = Tt->codigoBruxo;
						t.codigoPaciente = Tt->codigoPaciente;
						t.codigoPocao = Tt->codigoPocao;
						t.qtdDias = Tt->qtdDias;
						t.dosagem = Tt->dosagem;
						
						free(Tt);

						printf("\n\nDeseja alterar os dias? (1-Sim / 2-Nao) ");
						scanf("%d", &check);
							
						if(check == 1){
							printf("\nQuantidade de Dias: ");
							scanf("%d", &t.qtdDias);		
						}
							
						printf("\n\nDeseja alterar a dosagem? (1-Sim / 2-Nao) ");
						scanf("%d", &check);
							
						if(check == 1){
								
						printf("\nDosagem atual: ");
						scanf("%d", &t.dosagem);
								
						}
														
						if(AtualizarTratamento(t)) 
							printf("\nTratamento ampliado com sucesso!\n");
						else 
							printf("\nERRO: Tratamento não ampliado!\n");
						break;	
					case 5:
						printf("\n--- Finalizando Tratamento ---");
						if(QuantidadeTratamento() == 0){
							printf("\n\nSem tratamentos cadastrados!\n");

						}
						printf("\n\nInforme o codigo do tratamento: ");
						scanf("%i", &codigo);
							
						if(ApagarTratamentoPeloCodigo(codigo)) 
							printf("\nTratamento finalizado com sucesso!\n");
						else 
							printf("\nERRO: Erro ao finalizar tratamento!\n");
						break;
				}	
			}
		break;
	}
}
	EncerraBruxos();
	EncerraPacientes();
	EncerraPocoes();
	EncerraTratamento();
	
	return 0;
}

