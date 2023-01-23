#include "arvoreBStar.h"

void pesquisaArvoreBStar(Indice *indicePesquisa, ApontadorStar *paginaAtual) {
  int i;
  ApontadorStar paginaAuxiliar;
  paginaAuxiliar = *paginaAtual;

  if((*paginaAtual)->tipoDaPagina == INTERNA) {
    i = 1;
    while (i < paginaAuxiliar->UU.interna.numeroChaves && indicePesquisa->chave > paginaAuxiliar->UU.interna.chaves[i - 1]) i++;
    
    if(indicePesquisa->chave < paginaAuxiliar->UU.interna.chaves[i - 1]) {
      pesquisaArvoreBStar(indicePesquisa, &paginaAuxiliar->UU.interna.paginasFilhas[i - 1]);
    }
    else {
      pesquisaArvoreBStar(indicePesquisa, &paginaAuxiliar->UU.interna.paginasFilhas[i]);
    }

    return ;
  }
  else {
    i = 1;
    while (i < paginaAuxiliar->UU.externa.numeroIndices && indicePesquisa->chave >  paginaAuxiliar->UU.externa.indices[i - 1].chave) i++;

    if(indicePesquisa->chave == paginaAuxiliar->UU.externa.indices[i - 1].chave) {
      *indicePesquisa = paginaAuxiliar->UU.externa.indices[i - 1];
    }
  }

  return ;
}

void insereNaPaginaStar(ApontadorStar paginaAtual, Indice indiceInserir, ApontadorStar paginaDireita) {
  int naoAchouPosicao, k;
  if(paginaAtual->tipoDaPagina == INTERNA) {
    k = paginaAtual->UU.interna.numeroChaves;
    naoAchouPosicao = (k > 0) ? 1 : 0;

    while(naoAchouPosicao) {
      if(indiceInserir.chave >= paginaAtual->UU.interna.chaves[k - 1]) {
        naoAchouPosicao = 0;
        break;
      }

      paginaAtual->UU.interna.chaves[k] = paginaAtual->UU.interna.chaves[k - 1];
      paginaAtual->UU.interna.paginasFilhas[k + 1] = paginaAtual->UU.interna.paginasFilhas[k];
      k--;

      if(k < 1) {
        naoAchouPosicao = 0;
      }
    }

    paginaAtual->UU.interna.chaves[k] = indiceInserir.chave;
    paginaAtual->UU.interna.paginasFilhas[k + 1] = paginaDireita;
    paginaAtual->UU.interna.numeroChaves++;
  }
  else {
    k = paginaAtual->UU.externa.numeroIndices;
    naoAchouPosicao = (k > 0) ? 1 : 0;

    while(naoAchouPosicao) {
      if(indiceInserir.chave >= paginaAtual->UU.externa.indices[k - 1].chave) {
        naoAchouPosicao = 0;
        break;
      }

      paginaAtual->UU.externa.indices[k] = paginaAtual->UU.externa.indices[k - 1];
      k--;

      if(k < 1) {
        naoAchouPosicao = 0;
      }
    }

    paginaAtual->UU.externa.indices[k] = indiceInserir;
    paginaAtual->UU.externa.numeroIndices++;
  }
}

void insereIndiceStar(ApontadorStar paginaAtual, Indice indiceInserir, int *cresceu, Indice *indiceRetorno, ApontadorStar *paginaRetorno) {
  int i = 1;
  ApontadorStar paginaAuxiliar;

  if(paginaAtual->tipoDaPagina == INTERNA) {
    while(i < paginaAtual->UU.interna.numeroChaves && indiceInserir.chave > paginaAtual->UU.interna.chaves[i - 1]) i++;
    
    if(indiceInserir.chave == paginaAtual->UU.interna.chaves[i - 1]) {
      *cresceu = 0;
      printf("ERRO: o item ja esta presente na arvore\n");

      return ;
    }

    if(indiceInserir.chave > paginaAtual->UU.interna.chaves[i - 1]) i--;

    insereIndiceStar(paginaAtual->UU.interna.paginasFilhas[i], indiceInserir, cresceu, indiceRetorno, paginaRetorno);

    if(!*cresceu);

    if(paginaAtual->UU.interna.numeroChaves < 2 * M) {
      insereNaPaginaStar(paginaAtual, *indiceRetorno, *paginaRetorno);
      *cresceu = 0;

      return ;
    }

    paginaAuxiliar = (ApontadorStar) malloc(sizeof(PaginaStar));
    paginaAuxiliar->UU.interna.numeroChaves = 0;
    paginaAuxiliar->UU.interna.paginasFilhas[0] = NULL;
  }

  return ;
}

void insereNaArvoreBStar(ApontadorStar *paginaRaiz, Indice indiceInserir) {
  int cresceu;
  Indice indiceRetorno;
  PaginaStar *paginaRetorno, *paginaAuxiliar;

  if(*paginaRaiz == NULL) {
    paginaAuxiliar = (PaginaStar*) malloc(sizeof(PaginaStar));
    paginaAuxiliar->tipoDaPagina = EXTERNA;
    paginaAuxiliar->UU.externa.indices[0] = indiceInserir;
    paginaAuxiliar->UU.externa.numeroIndices = 1;

    return ;
  }

  insereIndiceStar(*paginaRaiz, indiceInserir, &cresceu, &indiceRetorno, &paginaRetorno);

  if(cresceu) {

  }
}

void arvoreBStar(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
  ApontadorStar paginaRaiz = NULL;
  Registro registroAuxiliar;
  Indice indice;

  for (int i = 0; i < tamanhoArquivo; i++) {
    fread(&registroAuxiliar, sizeof(Registro), 1, arquivo);
    indice.chave = registroAuxiliar.chave;
    indice.posicaoArquivo = i;
    insereNaArvoreBStar(&paginaRaiz, indice);
  }

  return ;
}