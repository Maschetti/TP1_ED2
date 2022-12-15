#include "Validation/validation.h"

int main(int argc, char **argv) {
  if(validation(argc, argv) == 1) {
    printf("Rodando...\n");
  }
  return 1;
}