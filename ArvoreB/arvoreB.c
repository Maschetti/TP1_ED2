#include "arvoreB.h"

void pesquisaArvoreB() {

}

void insereIndice(Apontador paginaAtual, Indice item, int *cresceu, Indice *indiceRetorno, Apontador *paginaRetorno) {
  int i = 1, j;
  Apontador auxiliar;

  if(paginaAtual == NULL) {
    *cresceu = 1;
    *indiceRetorno = item;
    *paginaRetorno = NULL;

    return ;
  }

  while(i < paginaAtual->items && item.chave > paginaAtual->items->chave) i++;

  if(item.chave == paginaAtual->items[i - 1].chave) {
    *cresceu = 0;
    printf("ERRO: o item ja esta presente na arvore\n");

    return ;
  }

  return ;
}

void insereArvoreB(Apontador *arvore, Indice item) {
  int cresceu;
  Indice indiceRetorno;
  Pagina *paginaRetorno, *paginaAuxiliar;
  
  insereIndice(*arvore, item, &cresceu, &indiceRetorno, &paginaRetorno);

  if(cresceu) {
    paginaAuxiliar = malloc(sizeof(Pagina*));
    paginaAuxiliar->numeroItems = 1;
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