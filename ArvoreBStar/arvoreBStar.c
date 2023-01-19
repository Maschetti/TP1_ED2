#include "arvoreBStar.h"

void pesquisaArvoreBStar(Indice *indicePesquisa, Apontador *paginaAtual) {
  int i;
  Apontador paginaAuxiliar;
  paginaAuxiliar = *paginaAtual;

  if((*paginaAtual)->tipoDaPagina == Interna) {
    i = 1;
    while (i < paginaAuxiliar->UU.U0.numeroIndices && indicePesquisa->chave > paginaAuxiliar->UU.U0.chaves[i - 1]) i++;
    
    if(indicePesquisa->chave < paginaAuxiliar->UU.U0.chaves[i - 1]) {
      pesquisaArvoreBStar(indicePesquisa, &paginaAuxiliar->UU.U0.paginasFilhas[i - 1]);
    }
    else {
      pesquisaArvoreBStar(indicePesquisa, &paginaAuxiliar->UU.U0.paginasFilhas[i]);
    }

    return ;
  }
  else {
    i = 1;
    while (i < paginaAuxiliar->UU.U1.numeroIndices && indicePesquisa->chave >  paginaAuxiliar->UU.U1.indices[i - 1].chave) i++;

    if(indicePesquisa->chave == paginaAuxiliar->UU.U1.indices[i - 1].chave) {
      *indicePesquisa = paginaAuxiliar->UU.U1.indices[i - 1];
    }
  }

  return ;
}

void arvoreBStar() {
  
}