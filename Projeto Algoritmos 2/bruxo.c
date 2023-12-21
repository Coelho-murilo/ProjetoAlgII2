#include "Bruxo.h"
#include <stdio.h>
#include <string.h>

FILE* arquivoBruxos = NULL;

int InicializarBruxos() {
    arquivoBruxos = fopen("bruxos.bin", "rb+"); // Modificado para manipular um arquivo binário
    if (arquivoBruxos == NULL)
        return 0;

    return 1;
}

int EncerraBruxos() {
    fclose(arquivoBruxos);
    return 1;
}

int SalvarBruxo(Bruxo b) {
    if (arquivoBruxos == NULL)
        return 0;

    fseek(arquivoBruxos, 0, SEEK_END);
    fwrite(&b, sizeof(Bruxo), 1, arquivoBruxos);

    return 1;
}

int QuantidadeBruxos() {
    if (arquivoBruxos == NULL)
        return 0;

    fseek(arquivoBruxos, 0, SEEK_END);
    return ftell(arquivoBruxos) / sizeof(Bruxo);
}

Bruxo* ObterBruxoPeloIndice(int indice) {
    if (arquivoBruxos == NULL || indice < 0 || indice >= QuantidadeBruxos())
        return NULL;

    fseek(arquivoBruxos, indice * sizeof(Bruxo), SEEK_SET);

    Bruxo* b = (Bruxo*)malloc(sizeof(Bruxo));
    if (b == NULL)
        return NULL;

    fread(b, sizeof(Bruxo), 1, arquivoBruxos);

    return b;
}

Bruxo* ObterBruxoPeloCodigo(int codigo) {
    if (arquivoBruxos == NULL || codigo < 0)
        return NULL;

    fseek(arquivoBruxos, 0, SEEK_SET);

    Bruxo* b = (Bruxo*)malloc(sizeof(Bruxo));
    if (b == NULL)
        return NULL;

    while (fread(b, sizeof(Bruxo), 1, arquivoBruxos) == 1) {
        if (b->codigoBruxo == codigo)
            return b;
    }

    free(b);
    return NULL;
}

int AtualizarBruxo(Bruxo b) {
    if (arquivoBruxos == NULL)
        return 0;

    fseek(arquivoBruxos, 0, SEEK_SET);

    Bruxo temp;
    while (fread(&temp, sizeof(Bruxo), 1, arquivoBruxos) == 1) {
        if (temp.codigoBruxo == b.codigoBruxo) {
            fseek(arquivoBruxos, -sizeof(Bruxo), SEEK_CUR);
            fwrite(&b, sizeof(Bruxo), 1, arquivoBruxos);
            return 1;
        }
    }

    return 0;
}

int ApagarBruxoPeloCodigo(int codigo) {
    if (arquivoBruxos == NULL || codigo < 0)
        return 0;

    fseek(arquivoBruxos, 0, SEEK_SET);

    FILE* tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL)
        return 0;

    Bruxo temp;
    while (fread(&temp, sizeof(Bruxo), 1, arquivoBruxos) == 1) {
        if (temp.codigoBruxo != codigo) {
            fwrite(&temp, sizeof(Bruxo), 1, tempFile);
        }
    }

    fclose(arquivoBruxos);
    fclose(tempFile);

    remove("bruxos.bin");
    rename("temp.bin", "bruxos.bin");

    arquivoBruxos = fopen("bruxos.bin", "ab+");

    return 1;
}

