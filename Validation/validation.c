#include "validation.h"
#include "../ArquivoBinario/ArquivoBinario.h"

void argumentsToInt(int numberArguments, char** arguments, int *metodo, int *quantidade, int *situacao, int *chave, int *P) {
  *metodo = atoi(arguments[1]);
  *quantidade = atoi(arguments[2]);
  *situacao = atoi(arguments[3]);
  *chave = atoi(arguments[4]);

  if(numberArguments == 6) {
    if(strcmp(arguments[5], "-P") == 0) {
      *P = 1;
    }
  }
}

FILE* validation(int numberArguments, char **arguments) {
  // printf("number of arguments = %d\n", numberArguments);
  // printf("arguments = %s\n", arguments[1]);
  FILE* arquivo = NULL;
  int metodo, quantidade, situacao, chave, P = 0, valido = 1;

  if(numberArguments >= 5 && numberArguments < 7) {
    argumentsToInt(numberArguments, arguments, &metodo, &quantidade, &situacao, &chave, &P);
    
    if(metodo < 1 || metodo > 4) {
      printf("ERRO: metodo invalido\n");
      printf("OBS: metodo deve ser de 1 a 4\n\n");
      valido = 0;
    }

    if(quantidade < 1 || quantidade > 2000000) {
      printf("ERRO: quantidade invalida\n");
      printf("OBS: o arquivo deve conter de 1 a 2.000.000 de registros\n\n");
      valido = 0;
    }

    if(situacao < 1 || situacao > 3) {
      printf("ERRO: situacao invalida\n");
      printf("OBS: a situacao do arquivo pode ser (1)ascendente (2)descendente (3)desordenado\n\n");
      valido = 0;
    }

    if(chave < 1 || chave > 2000000) {
      printf("ERRO: chave invalida\n");
      printf("OBS: a chave deve ser de 1 a 2.000.000 de registros\n\n");
      valido = 0;
    }

    if(numberArguments == 6 && (P < 0 || P > 1)) {
      printf("ERRO: P invalida\n");
      printf("OBS: P deve ser de 1 ou 0\n\n");
      valido = 0;
    }

    if(metodo == 1 && situacao != 1) {
      printf("ERRO: situacao invalida\n");
      printf("OBS: ser o metodo for 1 a situacao deve ser (1)ascendente\n\n");
      valido = 0;
    }

    if(valido == 1) {
      if(situacao == 1) {
        arquivo = fopen("ascendente.bin", "rb");
      }
      else if(situacao == 2) {
        arquivo = fopen("descendente.bin", "rb");
      }
      else {
        arquivo = fopen("aleatorio.bin", "rb");
      }
    }

    if(P == 1) {
      imprimeArquivo(arquivo, quantidade);
    }

  } else {
    printf("ERRO: Numero de argumentos invalidos\n");
    printf("Entrada: pesquisa <metodo> <quantidade> <situacao> <chave> [-P]\n");
    printf("OBS: apenas o parametro [-P] e opcional");  
  }

  return arquivo;
}