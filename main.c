#include "AcessoSequencialIndexado/acessoSequencialIndexado.h"
#include "ArvoreBinaria/arvoreBinario.h"
#include "ArvoreB/arvoreB.h"
#include "ArvoreBStar/arvoreBStar.h"
#include "Validation/validation.h"
#include "Analises/analise.h"

int main(int argc, char **argv) {
  FILE* arquivo;
  if((arquivo = validation(argc, argv)) != NULL) {
    int metodo = atoi(argv[1]);
    int tamanhoArquivo = atoi(argv[2]);
    Registro registroPesquisa;
    registroPesquisa.chave = atoi(argv[4]);

    if(metodo == 1) {
      acessoSequencialIndexado(arquivo, tamanhoArquivo, &registroPesquisa);
    } else if(metodo == 2) {
      arvoreBinaria(arquivo, tamanhoArquivo, &registroPesquisa);
    }
    else if (metodo == 3) {
      arvoreB(arquivo, tamanhoArquivo, &registroPesquisa);
    }
    else {
      arvoreBStar(arquivo, tamanhoArquivo, &registroPesquisa);
    }

    imprimeRegistro(registroPesquisa);

    fclose(arquivo);
  }
  else {
    printf("ERRO: nao foi possivel abrir o arquivo\n");
  }
  
  return 1;
}