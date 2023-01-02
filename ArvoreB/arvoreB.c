#include "arvoreB.h"

void pesquisaArvoreB() {

}

void insereIndice(Indice item, Apontador arvore, int *cresceu, Indice *indiceRetorno, Apontador *paginaRetorno) {
  int i = 1, j;

  if(arvore == NULL) {
    
  }
}

void insereArvoreB(Apontador *arvore, Indice item) {
  int cresceu;
  Indice indiceRetorno;
  Pagina *paginaRetorno, *paginaAuxiliar;
  
  insereIndice();

  if(cresceu) {
    paginaAuxiliar = malloc(sizeof(Pagina*));
    paginaAuxiliar->n = 1;
    paginaAuxiliar->items[0] = indiceRetorno;
    paginaAuxiliar->paginasFilhas[1] = paginaRetorno;
    paginaAuxiliar->paginasFilhas[0] = *arvore;
    *arvore = paginaAuxiliar;
  }

  return ;
}

void arvoreB(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
  Apontador arvore = NULL;
  Registro auxiliar;
  Indice item;

  for (int i = 0; i < tamanhoArquivo; i++) {
    fread(&auxiliar, sizeof(Registro), 1, arquivo);
    item.chave = auxiliar.chave;
    item.posicaoArquivo = i;
    insereArvoreB(&arvore, item);
  }

  pesquisaArvoreB();
  
  return ;
}