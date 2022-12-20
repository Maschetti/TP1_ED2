#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Tad/tad.h"

// como executar:
// gcc ArquivoBinario/cria.c -o cria -Wall
// ./cria int
// 
// int faz referencia a ordem do arquivo:
// (1) ascendente
// (2) descendente
// (3) aleatorio

void criaAscendente() {
  FILE *arquivo = fopen("ascendente.bin", "wb");

  if(arquivo != NULL) {
    Registro registro;
    srand(time(NULL));

    for (int i = 0; i < 2000000; i++) {
      registro.chave = i + 1;
      printf("%d\n", registro.chave);
      
      registro.dado1 = i * 2;

      for (int j = 0; j < 4999; j++) {
        registro.dado2[j] = (rand() % 26) + 65;
      }
      registro.dado2[4999] = '\0';
      
      fwrite(&registro, sizeof(Registro), 1, arquivo);
    }

    fclose(arquivo);
  }
  else {
    printf("ERRO: nao foi possivel criar o arquivo");
  }
}

void criaDescendente() {
  FILE *arquivo = fopen("descendente.bin", "wb");

  if(arquivo != NULL) {
    Registro registro;
    srand(time(NULL));

    for (int i = 2000000; i > 0; i--) {
      registro.chave = i;
      printf("%d\n", registro.chave);
      
      registro.dado1 = i * 2;

      for (int j = 0; j < 4999; j++) {
        registro.dado2[j] = (rand() % 26) + 65;
      }
      registro.dado2[4999] = '\0';
      
      fwrite(&registro, sizeof(Registro), 1, arquivo);
    }

    fclose(arquivo);
  }
  else {
    printf("ERRO: nao foi possivel criar o arquivo");
  }
}

void criaAleatorio() {
  FILE *arquivo = fopen("aleatorio.bin", "wb");

  if(arquivo != NULL) {
    Registro registro;
    int *vetor = calloc(2000000, sizeof(int));
    srand(time(NULL));
    
    int valido = 0;
    for (int i = 0; i < 2000000; i++)
    {
      valido = 0;
      while (valido == 0)
      {
        registro.chave = (rand() % 2000000);
        if(vetor[registro.chave] == 0) {
          vetor[registro.chave] = 1;
          valido = 1;
        }
      }
      registro.chave++;
      
      registro.dado1 = i * 2;

      for (int j = 0; j < 4999; j++) {
        registro.dado2[j] = (rand() % 26) + 65;
      }
      registro.dado2[4999] = '\0';
      
      fwrite(&registro, sizeof(Registro), 1, arquivo);
    }
    
    free(vetor);
    fclose(arquivo);
  }
  else {
    printf("ERRO: nao foi possivel criar o arquivo");
  }
}

int main(int argc, char **argv) {
  int situacao = atoi(argv[1]);

  if(argc != 2) {
    printf("ERRO: a linha de comando aceita apenas 1 parametro\n");
  }
  else if(situacao < 1 || situacao > 3) {
    printf("ERRO: o parametro deve ir de 1 a 3\n");
  }
  else if(situacao == 1) {
    criaAscendente();
  }
  else if(situacao == 2) {
    criaDescendente();
  }
  else {
    criaAleatorio();
  }

  return 1;
}