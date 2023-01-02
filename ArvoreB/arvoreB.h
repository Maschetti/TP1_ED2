#ifndef ARVOREB_H
#define ARVOREB_H
#include <stdio.h>
#include <stdlib.h>
#include "../Tad/tad.h"

#define M 4

typedef struct Pagina *Apontador;

typedef struct Pagina {
  short n;
  Indice items[2 * M];
  Apontador paginasFilhas[2 * M + 1];
} Pagina;

void arvoreB(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa);

#endif