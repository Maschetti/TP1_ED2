#include "tad.h"

void imprimeRegistro(Registro registro) {
  printf("Chave: %d - Dados %li | %s\n\n", registro.chave, registro.dado1, registro.dado2);
}