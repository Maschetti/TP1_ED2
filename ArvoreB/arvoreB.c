#include "arvoreB.h"
#include "../Analises/analise.h"

Analise analiseB;

void pesquisaArvoreB(Apontador paginaAtual, Indice *itemPesquisa, int *achou) {

  long i = 1;
  
  if(paginaAtual == NULL) {
    return ;
  }

  while (i < paginaAtual->numeroItems && itemPesquisa->chave > paginaAtual->items[i - 1].chave) i++;

  atualizaComparacoes_pesquisa(&analiseB,1);
  if(itemPesquisa->chave == paginaAtual->items[i - 1].chave) {
    *itemPesquisa = paginaAtual->items[i - 1];
    *achou = 1;
    return  ;
  }

  if(itemPesquisa->chave < paginaAtual->items[i - 1].chave) {
    pesquisaArvoreB(paginaAtual->paginasFilhas[i - 1], itemPesquisa, achou);
  }
  else {
    pesquisaArvoreB(paginaAtual->paginasFilhas[i], itemPesquisa, achou);
  }

  return ;
}

void insereNaPagina(Apontador paginaAtual, Indice item, Apontador paginaDireita) {
  int naoAchouPosicao, k;
  k = paginaAtual->numeroItems;
  naoAchouPosicao = (k > 0) ? 1 : 0;

  while (naoAchouPosicao) {
    atualizaComparacoes_criacao(&analiseB, 1);
    if(item.chave >= paginaAtual->items[k - 1].chave) {
      naoAchouPosicao = 0;
      break;
    }

    paginaAtual->items[k] = paginaAtual->items[k - 1];
    paginaAtual->paginasFilhas[k + 1] = paginaAtual->paginasFilhas[k];
    k--;

    if(k < 1) {
      naoAchouPosicao = 0;
    }
  }

  paginaAtual->items[k] = item;
  paginaAtual->paginasFilhas[k + 1] = paginaDireita;
  paginaAtual->numeroItems++;
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

  while(i < paginaAtual->numeroItems && item.chave > paginaAtual->items[i - 1].chave) {
    atualizaComparacoes_criacao(&analiseB, 1);
    i++;
  }

  atualizaComparacoes_criacao(&analiseB, 2);
  if(item.chave == paginaAtual->items[i - 1].chave) {
    *cresceu = 0;
    printf("ERRO: o item ja esta presente na arvore\n");

    return ;
  }

  atualizaComparacoes_criacao(&analiseB, 1);
  if(item.chave < paginaAtual->items[i - 1].chave) i--;

  insereIndice(paginaAtual->paginasFilhas[i], item, cresceu, indiceRetorno, paginaRetorno);

  if(!*cresceu) return ;

  if(paginaAtual->numeroItems < 2 * M) {
    insereNaPagina(paginaAtual, *indiceRetorno, *paginaRetorno);
    *cresceu = 0;
    return ;
  }

  paginaAuxiliar = (Apontador) malloc(sizeof(Pagina));
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

  for (j = M + 2; j <= 2 * M; j++) { 
    insereNaPagina(paginaAuxiliar, paginaAtual->items[j - 1], paginaAtual->paginasFilhas[j]);
  }

  paginaAtual->numeroItems = M;
  paginaAuxiliar->paginasFilhas[0] = paginaAtual->paginasFilhas[M + 1];
  *indiceRetorno = paginaAtual->items[M];
  *paginaRetorno = paginaAuxiliar;

  return ;
} 

void insereNaArvoreB(Apontador *paginaRaiz, Indice item) {
  int cresceu;
  Indice indiceRetorno;
  Pagina *paginaRetorno, *paginaAuxiliar;
  
  insereIndice(*paginaRaiz, item, &cresceu, &indiceRetorno, &paginaRetorno);

  if(cresceu) {
    paginaAuxiliar = (Pagina *) malloc(sizeof(Pagina));
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
  iniciaAnalise(&analiseB);
  iniciaContagemTempo(&analiseB);
  for (int i = 0; i < tamanhoArquivo; i++) {
    fread(&auxiliar, sizeof(Registro), 1, arquivo);
    atualizaTransferencias_criacao(&analiseB,1);
    item.chave = auxiliar.chave;
    item.posicaoArquivo = i;
    insereNaArvoreB(&paginaRaiz, item);
  }
  finalizaContagemTempo(&analiseB);
  atualizaTempo_criacao(&analiseB);

  item.chave = registroPesquisa->chave;
  
  int achou = 0;

  iniciaContagemTempo(&analiseB);
  pesquisaArvoreB(paginaRaiz, &item, &achou);
  
  if(achou) {
    fseek(arquivo, item.posicaoArquivo * sizeof(Registro), SEEK_SET);
    atualizaDeslocamentos_pesquisa(&analiseB,1);
    fread(registroPesquisa, sizeof(Registro), 1, arquivo);
    atualizaTransferencias_pesquisa(&analiseB,1);
  }
  finalizaContagemTempo(&analiseB);
  atualizaTempo_pesquisa(&analiseB);

  imprimirDados(&analiseB);

  return ;
}