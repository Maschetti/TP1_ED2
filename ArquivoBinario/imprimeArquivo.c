#include "ArquivoBinario.h"

void imprimeArquivo(FILE* arquivo, int tamanho) {
  Registro registro;
  for (int i = 0; i < tamanho; i++) {
    fread(&registro, sizeof(Registro), 1, arquivo);
    imprimeRegistro(registro);
  } 
}