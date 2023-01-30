#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include <stdio.h>
#include <stdlib.h>
#include "../Tad/tad.h"

typedef struct {
  Indice indice;
  int filhoEsquerda;
  int filhoDireita;
} ArvoreExterna;

void arvoreBinaria(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa, int ordemArquivo);

#endif