#include "Pocao.h"
#include <stdio.h>
#include <string.h>

FILE* arquivoPocoes = NULL;

int InicializarPocoes() {
    arquivoPocoes = fopen("pocoes.bin", "rb+"); // Modificado para manipular um arquivo binário
    if (arquivoPocoes == NULL)
        return 0;

    return 1;
}

int EncerraPocoes() {
    fclose(arquivoPocoes);
    return 1;
}

int SalvarPocao(Pocao Pc) {
    if (arquivoPocoes == NULL)
        return 0;

    fseek(arquivoPocoes, 0, SEEK_END);
    fwrite(&Pc, sizeof(Pocao), 1, arquivoPocoes);

    return 1;
}

int QuantidadePocoes() {
    if (arquivoPocoes == NULL)
        return 0;

    fseek(arquivoPocoes, 0, SEEK_END);
    return ftell(arquivoPocoes) / sizeof(Pocao);
}

Pocao* ObterPocaoPeloIndice(int indice) {
    if (arquivoPocoes == NULL || indice < 0 || indice >= QuantidadePocoes())
        return NULL;

    fseek(arquivoPocoes, indice * sizeof(Pocao), SEEK_SET);

    Pocao* Pc = (Pocao*)malloc(sizeof(Pocao));
    if (Pc == NULL)
        return NULL;

    fread(Pc, sizeof(Pocao), 1, arquivoPocoes);

    return Pc;
}

Pocao* ObterPocaoPeloCodigo(int codigo) {
    if (arquivoPocoes == NULL || codigo < 0)
        return NULL;

    fseek(arquivoPocoes, 0, SEEK_SET);

    Pocao* Pc = (Pocao*)malloc(sizeof(Pocao));
    if (Pc == NULL)
        return NULL;

    while (fread(Pc, sizeof(Pocao), 1, arquivoPocoes) == 1) {
        if (Pc->codigoPocao == codigo)
            return Pc;
    }

    free(Pc);
    return NULL;
}

int AtualizarPocao(Pocao Pc) {
    if (arquivoPocoes == NULL)
        return 0;

    fseek(arquivoPocoes, 0, SEEK_SET);

    Pocao temp;
    while (fread(&temp, sizeof(Pocao), 1, arquivoPocoes) == 1) {
        if (temp.codigoPocao == Pc.codigoPocao) {
            fseek(arquivoPocoes, -sizeof(Pocao), SEEK_CUR);
            fwrite(&Pc, sizeof(Pocao), 1, arquivoPocoes);
            return 1;
        }
    }

    return 0;
}

int ApagarPocaoPeloCodigo(int codigo) {
    if (arquivoPocoes == NULL || codigo < 0)
        return 0;

    fseek(arquivoPocoes, 0, SEEK_SET);

    FILE* tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
        return 0;

    Pocao temp;
    while (fread(&temp, sizeof(Pocao), 1, arquivoPocoes) == 1) {
        if (temp.codigoPocao != codigo) {
            fwrite(&temp, sizeof(Pocao), 1, tempFile);
        }
    }

    fclose(arquivoPocoes);
    fclose(tempFile);

    remove("pocoes.bin");
    rename("temp.bin", "pocoes.bin");

    arquivoPocoes = fopen("pocoes.bin", "ab+");

    return 1;
}

