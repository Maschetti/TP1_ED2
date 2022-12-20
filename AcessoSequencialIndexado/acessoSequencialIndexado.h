#ifndef ACESSOSEQUENCIALINDEXADO_H
#define ACESSOSEQUENCIALINDEXADO_H
#include <stdio.h>
#include <stdlib.h>
#include "../Tad/tad.h"

#define TAMANHOPAGINA 10

void acessoSequencialIndexado(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa);

#endif