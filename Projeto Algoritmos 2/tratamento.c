#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>

FILE* arquivoTratamentos = NULL;

int InicializarTratamento() {
    arquivoTratamentos = fopen("tratamentos.bin", "rb+");
    if (arquivoTratamentos == NULL)
        return 0;

    return 1;
}

int EncerraTratamento() {
    if (arquivoTratamentos != NULL) {
        fclose(arquivoTratamentos);
        arquivoTratamentos = NULL;
    }

    return 1;
}

int SalvarTratamento(Tratamento t) {
    if (arquivoTratamentos == NULL)
        return 0;

    fseek(arquivoTratamentos, 0, SEEK_END);
    fwrite(&t, sizeof(Tratamento), 1, arquivoTratamentos);

    return 1;
}

int QuantidadeTratamento() {
    if (arquivoTratamentos == NULL)
        return 0;

    fseek(arquivoTratamentos, 0, SEEK_END);
    long tamanho = ftell(arquivoTratamentos);

    return tamanho / sizeof(Tratamento);
}

Tratamento* ObterTratamentoPeloCodigo(int codigo) {
    if (arquivoTratamentos == NULL)
        return NULL;

    rewind(arquivoTratamentos);

    Tratamento* t = (Tratamento*)malloc(sizeof(Tratamento));
    if (t == NULL)
        return NULL;

    while (fread(t, sizeof(Tratamento), 1, arquivoTratamentos) == 1) {
        if (t->codigo == codigo)
            return t;
    }

    free(t);
    return NULL;
}

Tratamento* ObterTratamentoPeloCodigodoBruxo(int codigo, int indice) {
    if (arquivoTratamentos == NULL)
        return NULL;

    rewind(arquivoTratamentos);

    Tratamento* t = (Tratamento*)malloc(sizeof(Tratamento));
    if (t == NULL)
        return NULL;

    while (fread(t, sizeof(Tratamento), 1, arquivoTratamentos) == 1) {
        if (t->codigoBruxo == codigo && indice-- == 0)
            return t;
    }

    free(t);
    return NULL;
}

Tratamento* ObterTratamentoPeloCodigodoPaciente(int codigo, int indice) {
    if (arquivoTratamentos == NULL)
        return NULL;

    rewind(arquivoTratamentos);

    Tratamento* t = (Tratamento*)malloc(sizeof(Tratamento));
    if (t == NULL)
        return NULL;

    while (fread(t, sizeof(Tratamento), 1, arquivoTratamentos) == 1) {
        if (t->codigoPaciente == codigo && indice-- == 0)
            return t;
    }

    free(t);
    return NULL;
}

Tratamento* ObterTratamentoPeloCodigodaPocao(int codigo, int indice) {
    if (arquivoTratamentos == NULL)
        return NULL;

    rewind(arquivoTratamentos);

    Tratamento* t = (Tratamento*)malloc(sizeof(Tratamento));
    if (t == NULL)
        return NULL;

    while (fread(t, sizeof(Tratamento), 1, arquivoTratamentos) == 1) {
        if (t->codigoPocao == codigo && indice-- == 0)
            return t;
    }

    free(t);
    return NULL;
}

int AtualizarTratamento(Tratamento t) {
    if (arquivoTratamentos == NULL)
        return 0;

    rewind(arquivoTratamentos);

    Tratamento temp;
    while (fread(&temp, sizeof(Tratamento), 1, arquivoTratamentos) == 1) {
        if (temp.codigo == t.codigo) {
            fseek(arquivoTratamentos, -sizeof(Tratamento), SEEK_CUR);
            fwrite(&t, sizeof(Tratamento), 1, arquivoTratamentos);
            return 1;
        }
    }

    return 0;
}

int ApagarTratamentoPeloCodigo(int codigo) {
    if (arquivoTratamentos == NULL || codigo < 0)
        return 0;

    fseek(arquivoTratamentos, 0, SEEK_SET);

    FILE* tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
        return 0;

    Tratamento temp;
    while (fread(&temp, sizeof(Tratamento), 1, arquivoTratamentos) == 1) {
        if (temp.codigo != codigo) {
            fwrite(&temp, sizeof(Tratamento), 1, tempFile);
        }
    }

    fclose(arquivoTratamentos);
    fclose(tempFile);

    remove("tratamentos.bin");
    rename("temp.bin", "tratamentos.bin");

    arquivoTratamentos = fopen("tratamentos.bin", "ab+");

    return 1;
}

