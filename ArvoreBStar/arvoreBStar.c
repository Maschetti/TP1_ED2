#include "arvoreBStar.h"
#include "../Analises/analise.h"

Analise analiseStar;

void pesquisaArvoreBStar(ApontadorStar *paginaAtual, Indice *indicePesquisa, int *achou) {
  int i;
  ApontadorStar paginaAuxiliar;
  paginaAuxiliar = *paginaAtual;

  if((*paginaAtual)->tipoDaPagina == INTERNA) {
    i = 1;
    while (i < paginaAuxiliar->UU.interna.numeroChaves && indicePesquisa->chave > paginaAuxiliar->UU.interna.chaves[i - 1]){
      atualizaComparacoes_pesquisa(&analiseStar,1);
      i++;
    }
    
    atualizaComparacoes_pesquisa(&analiseStar,2);
    if(indicePesquisa->chave <= paginaAuxiliar->UU.interna.chaves[i - 1]) {
      pesquisaArvoreBStar(&paginaAuxiliar->UU.interna.paginasFilhas[i - 1], indicePesquisa, achou);
    }
    else {
      pesquisaArvoreBStar(&paginaAuxiliar->UU.interna.paginasFilhas[i], indicePesquisa, achou);
    }

    return ;
  }
 
  i = 1;
  while (i <= paginaAuxiliar->UU.externa.numeroIndices && indicePesquisa->chave >  paginaAuxiliar->UU.externa.indices[i - 1].chave) i++;
  
  atualizaComparacoes_pesquisa(&analiseStar,1);
  if(indicePesquisa->chave == paginaAuxiliar->UU.externa.indices[i - 1].chave) {
    *indicePesquisa = paginaAuxiliar->UU.externa.indices[i - 1];
    *achou = 1;
  }

  return ;
}

void insereNaInterna(ApontadorStar paginaAtual, int chave, ApontadorStar paginaDireita) {
  int k = paginaAtual->UU.interna.numeroChaves;
  int naoAchouPosicao = (k > 0);

  while (naoAchouPosicao) {
    atualizaComparacoes_criacao(&analiseStar,1);
    if(chave >= paginaAtual->UU.interna.chaves[k - 1]) {
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

  paginaAtual->UU.interna.chaves[k] = chave;
  paginaAtual->UU.interna.paginasFilhas[k + 1] = paginaDireita;
  paginaAtual->UU.interna.numeroChaves++;
}

void insereNaExterna(ApontadorStar paginaAtual, Indice indice) {
  int k = paginaAtual->UU.externa.numeroIndices;
  int naoAchouPosicao = (k > 0);

  while (naoAchouPosicao) {
    atualizaComparacoes_criacao(&analiseStar,1);
    if(indice.chave >= paginaAtual->UU.externa.indices[k - 1].chave) {
      naoAchouPosicao = 0;
      break;
    }

    paginaAtual->UU.externa.indices[k] = paginaAtual->UU.externa.indices[k - 1];
    k--;

    if(k < 1) {
      naoAchouPosicao = 0;
    }
  }

  paginaAtual->UU.externa.indices[k] = indice;
  paginaAtual->UU.externa.numeroIndices++;
}

void insereIndiceStar(ApontadorStar paginaAtual, Indice indiceInserir, int *cresceu, Indice *indiceRetorno, ApontadorStar *paginaRetorno) {
  int i = 1, j;
  ApontadorStar paginaAuxiliar;

  if(paginaAtual == NULL) {
    *cresceu = 1;
    (*indiceRetorno) = indiceInserir;
    (*paginaRetorno) = NULL;

    return ;
  }

  if(paginaAtual->tipoDaPagina == INTERNA) {
    while(i < paginaAtual->UU.interna.numeroChaves && indiceInserir.chave > paginaAtual->UU.interna.chaves[i - 1]) {
      i++;
      atualizaComparacoes_criacao(&analiseStar,1);
      }

    atualizaComparacoes_criacao(&analiseStar,2);
    if(indiceInserir.chave < paginaAtual->UU.interna.chaves[i - 1]) i--;

    insereIndiceStar(paginaAtual->UU.interna.paginasFilhas[i], indiceInserir, cresceu, indiceRetorno, paginaRetorno);

    if(!*cresceu) return ;

    if(paginaAtual->UU.interna.numeroChaves < 2 * M) {
      insereNaInterna(paginaAtual, indiceRetorno->chave, *paginaRetorno);
      *cresceu = 0;

      return ;
    }

    paginaAuxiliar = (ApontadorStar) malloc(sizeof(PaginaStar));
    paginaAuxiliar->tipoDaPagina = INTERNA;
    paginaAuxiliar->UU.interna.numeroChaves = 0;
    paginaAuxiliar->UU.interna.paginasFilhas[0] = NULL;

    if(i < M + 1) {
      insereNaInterna(paginaAuxiliar, paginaAtual->UU.interna.chaves[2 * M - 1], paginaAtual->UU.interna.paginasFilhas[2 * M]);
      paginaAtual->UU.interna.numeroChaves--;
      insereNaInterna(paginaAtual, indiceRetorno->chave, *paginaRetorno);
    }
    else {
      insereNaInterna(paginaAuxiliar, indiceRetorno->chave, *paginaRetorno);
    }

    for(j = M + 2; j <= 2 * M; j++) {
      insereNaInterna(paginaAuxiliar, paginaAtual->UU.interna.chaves[j - 1], paginaAtual->UU.interna.paginasFilhas[j]);
    }

    paginaAtual->UU.interna.numeroChaves = M;
    paginaAuxiliar->UU.interna.paginasFilhas[0] = paginaAtual->UU.interna.paginasFilhas[M + 1];
    indiceRetorno->chave = paginaAtual->UU.interna.chaves[M];
    *paginaRetorno = paginaAuxiliar;
  }
  else {
    (*indiceRetorno) = indiceInserir;

    while (i < paginaAtual->UU.externa.numeroIndices && indiceInserir.chave > paginaAtual->UU.externa.indices[i - 1].chave){
      i++;
      atualizaComparacoes_criacao(&analiseStar,1);
    }

    atualizaComparacoes_criacao(&analiseStar,2);
    if(indiceInserir.chave == paginaAtual->UU.externa.indices[i - 1].chave && paginaAtual->UU.externa.numeroIndices != 0) {
      *cresceu = 0;
      return ;
    }

    if(!*cresceu) return ;

    if(paginaAtual->UU.externa.numeroIndices < 2 * M) {
      insereNaExterna(paginaAtual, *indiceRetorno);
      *cresceu = 0;
      return ;
    }

    paginaAuxiliar = (ApontadorStar) malloc(sizeof(PaginaStar));
    paginaAuxiliar->tipoDaPagina = EXTERNA;
    paginaAuxiliar->UU.externa.numeroIndices = 0;
    

    if(i < M + 1) {
      insereNaExterna(paginaAuxiliar, paginaAtual->UU.externa.indices[2 * M - 1]);
      paginaAtual->UU.externa.numeroIndices--;
      insereNaExterna(paginaAtual, *indiceRetorno);
    }
    else {
      insereNaExterna(paginaAuxiliar, *indiceRetorno);
    }

    for (j = M + 2; j <= 2 * M; j++) {
      insereNaExterna(paginaAuxiliar, paginaAtual->UU.externa.indices[j - 1]);
    }
    
    paginaAtual->UU.externa.numeroIndices = M + 1;
    *indiceRetorno = paginaAtual->UU.externa.indices[M];
    *paginaRetorno = paginaAuxiliar;
  }

  return ;
}

void insereNaArvoreBStar(ApontadorStar *paginaRaiz, Indice indiceInserir) {
  int cresceu = 1;
  Indice indiceRetorno;
  PaginaStar *paginaRetorno, *paginaAuxiliar;

  if(*paginaRaiz == NULL) {
    paginaAuxiliar = (PaginaStar*) malloc(sizeof(PaginaStar));
    paginaAuxiliar->tipoDaPagina = EXTERNA;
    paginaAuxiliar->UU.externa.numeroIndices = 0;
    *paginaRaiz = paginaAuxiliar;
  }

  insereIndiceStar(*paginaRaiz, indiceInserir, &cresceu, &indiceRetorno, &paginaRetorno);

  if(cresceu) {
    paginaAuxiliar = (PaginaStar *) malloc(sizeof(PaginaStar));
    paginaAuxiliar->tipoDaPagina = INTERNA;
    paginaAuxiliar->UU.interna.numeroChaves = 1;
    paginaAuxiliar->UU.interna.chaves[0] = indiceRetorno.chave;
    paginaAuxiliar->UU.interna.paginasFilhas[1] = paginaRetorno;
    paginaAuxiliar->UU.interna.paginasFilhas[0] = *paginaRaiz;
    *paginaRaiz = paginaAuxiliar;
  }
}

void arvoreBStar(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
  ApontadorStar paginaRaiz = NULL;
  Registro registroAuxiliar;
  Indice indice;

  iniciaAnalise(&analiseStar);

  iniciaContagemTempo(&analiseStar);
  for (int i = 0; i < tamanhoArquivo; i++) {
    fread(&registroAuxiliar, sizeof(Registro), 1, arquivo);
    atualizaTransferencias_criacao(&analiseStar,1);
    indice.chave = registroAuxiliar.chave;
    indice.posicaoArquivo = i;
    insereNaArvoreBStar(&paginaRaiz, indice);
  }
  finalizaContagemTempo(&analiseStar);
  atualizaTempo_criacao(&analiseStar);
  indice.chave = registroPesquisa->chave;

  int achou = 0;

  iniciaContagemTempo(&analiseStar);
  pesquisaArvoreBStar(&paginaRaiz, &indice, &achou);

  if(achou) {
    fseek(arquivo, indice.posicaoArquivo * sizeof(Registro), SEEK_SET);
    atualizaDeslocamentos_pesquisa(&analiseStar,1);
    fread(registroPesquisa, sizeof(Registro), 1, arquivo);
    atualizaTransferencias_pesquisa(&analiseStar,1);
  }
  finalizaContagemTempo(&analiseStar);
  atualizaTempo_pesquisa(&analiseStar);

  return ;
}