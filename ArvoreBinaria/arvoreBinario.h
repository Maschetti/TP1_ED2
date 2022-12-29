#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Tad/tad.h"

typedef struct {
  Indice indice;
  int filhoEsquerda;
  int filhoDireita;
} ArvoreExterna;

#endif