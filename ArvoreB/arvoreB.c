#include "arvoreB.h"

void pesquisaArvoreB() {

}

void insereNaPagina(Apontador paginaAtual, Indice item, Apontador paginaDireita) {
  int naoAchouPosicao, k;
  k = paginaAtual->items;
  naoAchouPosicao = (k > 0) ? 1 : 0;
}

void insereIndice(Apontador paginaAtual, Indice item, int *cresceu, Indice *indiceRetorno, Apontador *paginaRetorno) {
  int i = 1, j;
  Apontador paginaAuxiliar;

  if(paginaAtual == NULL) {
    *cresceu = 1;
    *indiceRetorno = item;
    *paginaRetorno = NULL;

    return ;
  }

  while(i < paginaAtual->numeroItems && item.chave > paginaAtual->items[i].chave) i++;

  if(item.chave == paginaAtual->items[i - 1].chave) {
    *cresceu = 0;
    printf("ERRO: o item ja esta presente na arvore\n");

    return ;
  }

  if(item.chave < paginaAtual->items[i].chave) i--;

  insereIndice(paginaAtual->paginasFilhas[i], item, cresceu, indiceRetorno, paginaRetorno);

  if(!*cresceu) return ;

  if(paginaAtual->numeroItems < 2 * M) {
    insereNaPagina(paginaAtual, *indiceRetorno, *paginaRetorno);
    *cresceu = 0;
  }

  paginaAuxiliar = malloc(sizeof(Apontador));
  paginaAuxiliar->numeroItems = 0;
  paginaAuxiliar->paginasFilhas[0] = NULL;

  if(i < M + 1) {
    insereNaPagina(paginaAuxiliar, paginaAtual->items[2 * M - 1], paginaAtual->paginasFilhas[2 * M]);
    paginaAtual->numeroItems--;
    insereNaPagina(paginaAtual, *indiceRetorno, *paginaRetorno);
  }
  else {
    insereNaPagina(paginaAuxiliar, *indiceRetorno, *paginaRetorno);
  }

  return ;
} 

void insereNaArvoreB(Apontador *paginaRaiz, Indice item) {
  int cresceu;
  Indice indiceRetorno;
  Pagina *paginaRetorno, *paginaAuxiliar;
  
  insereIndice(*paginaRaiz, item, &cresceu, &indiceRetorno, &paginaRetorno);

  if(cresceu) {
    paginaAuxiliar = malloc(sizeof(Pagina*));
    paginaAuxiliar->numeroItems = 1;
    paginaAuxiliar->items[0] = indiceRetorno;
    paginaAuxiliar->paginasFilhas[1] = paginaRetorno;
    paginaAuxiliar->paginasFilhas[0] = *paginaRaiz;
    *paginaRaiz = paginaAuxiliar;
  }

  return ;
}

void arvoreB(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
  Apontador paginaRaiz = NULL;
  Registro auxiliar;
  Indice item;

  for (int i = 0; i < tamanhoArquivo; i++) {
    fread(&auxiliar, sizeof(Registro), 1, arquivo);
    item.chave = auxiliar.chave;
    item.posicaoArquivo = i;
    insereArvoreB(&paginaRaiz, item);
  }

  pesquisaArvoreB();
  
  return ;
}