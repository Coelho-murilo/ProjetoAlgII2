#include "Paciente.h"
#include <stdio.h>
#include <string.h>

FILE* arquivoPacientes = NULL;

int InicializarPacientes() {
    arquivoPacientes = fopen("pacientes.bin", "rb+"); // Modificado para manipular um arquivo binário
    if (arquivoPacientes == NULL)
        return 0;

    return 1;
}

int EncerraPacientes() {
    fclose(arquivoPacientes);
    return 1;
}

int SalvarPaciente(Paciente p) {
    if (arquivoPacientes == NULL)
        return 0;

    fseek(arquivoPacientes, 0, SEEK_END);
    fwrite(&p, sizeof(Paciente), 1, arquivoPacientes);

    return 1;
}

int QuantidadePacientes() {
    if (arquivoPacientes == NULL)
        return 0;

    fseek(arquivoPacientes, 0, SEEK_END);
    return ftell(arquivoPacientes) / sizeof(Paciente);
}

Paciente* ObterPacientePeloIndice(int indice) {
    if (arquivoPacientes == NULL || indice < 0 || indice >= QuantidadePacientes())
        return NULL;

    fseek(arquivoPacientes, indice * sizeof(Paciente), SEEK_SET);

    Paciente* p = (Paciente*)malloc(sizeof(Paciente));
    if (p == NULL)
        return NULL;

    fread(p, sizeof(Paciente), 1, arquivoPacientes);

    return p;
}

Paciente* ObterPacientePeloCodigo(int codigo) {
    if (arquivoPacientes == NULL || codigo < 0)
        return NULL;

    fseek(arquivoPacientes, 0, SEEK_SET);

    Paciente* p = (Paciente*)malloc(sizeof(Paciente));
    if (p == NULL)
        return NULL;

    while (fread(p, sizeof(Paciente), 1, arquivoPacientes) == 1) {
        if (p->codigoPaciente == codigo)
            return p;
    }

    free(p);
    return NULL;
}

int AtualizarPaciente(Paciente p) {
    if (arquivoPacientes == NULL)
        return 0;

    fseek(arquivoPacientes, 0, SEEK_SET);

    Paciente temp;
    while (fread(&temp, sizeof(Paciente), 1, arquivoPacientes) == 1) {
        if (temp.codigoPaciente == p.codigoPaciente) {
            fseek(arquivoPacientes, -sizeof(Paciente), SEEK_CUR);
            fwrite(&p, sizeof(Paciente), 1, arquivoPacientes);
            return 1;
        }
    }

    return 0;
}

int ApagarPacientePeloCodigo(int codigo) {
    if (arquivoPacientes == NULL || codigo < 0)
        return 0;

    fseek(arquivoPacientes, 0, SEEK_SET);

    FILE* tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
        return 0;

    Paciente temp;
    while (fread(&temp, sizeof(Paciente), 1, arquivoPacientes) == 1) {
        if (temp.codigoPaciente != codigo) {
            fwrite(&temp, sizeof(Paciente), 1, tempFile);
        }
    }

    fclose(arquivoPacientes);
    fclose(tempFile);

    remove("pacientes.bin");
    rename("temp.bin", "pacientes.bin");

    arquivoPacientes = fopen("pacientes.bin", "ab+");

    return 1;
}

