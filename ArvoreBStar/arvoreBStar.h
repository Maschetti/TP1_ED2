#ifndef ARVOREBSTAR_H
#define ARVOREBSTAR_H
#include "../Tad/tad.h"
#include <stdlib.h>

#define M 4

typedef enum { INTERNA, EXTERNA } IntExt;

typedef struct PaginaStar *ApontadorStar;

typedef struct PaginaStar {
  IntExt tipoDaPagina;

  union {
    struct {
      int numeroChaves;
      int chaves[2 * M];
      ApontadorStar paginasFilhas[2 * M + 1];
    } interna;
    
    struct {
      int numeroIndices;
      Indice indices[2 * M];
    } externa;
  } UU;
} PaginaStar;

void arvoreBStar(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa);

#endif