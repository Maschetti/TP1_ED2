#ifndef TAD_H
#define TAD_H
#include <stdio.h>

typedef struct {
  int chave;
  long int dado1;
  char dado2[5000];
} Registro;

typedef struct {
  int chave;
  int posicaoArquivo;
} Indice;

void imprimeRegistro(Registro registro);

#endif