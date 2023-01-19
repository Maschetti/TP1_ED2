#ifndef ARVOREBSTAR_H
#define ARVOREBSTAR_H
#include "../Tad/tad.h"
#include <stdlib.h>

#define M 4

typedef enum { Interna, Externa } IntExt;

typedef struct Pagina *Apontador;

typedef struct Pagina {
  IntExt tipoDaPagina;

  union {
    struct {
      int numeroIndices;
      int chaves[2 * M];
      Apontador paginasFilhas[2 * M + 1];
    } U0;
    
    struct {
      int numeroIndices;
      Indice indices[2 * M];
    } U1;
  } UU;
} Pagina;

#endif