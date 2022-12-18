#include "Validation/validation.h"

int main(int argc, char **argv) {
  FILE* arquivo;
  if((arquivo = validation(argc, argv)) != NULL) {
    printf("%p\n", arquivo);
  }
  else {
    printf("ERRO: nao foi possivel abrir o arquivo\n");
  }
  return 1;
}