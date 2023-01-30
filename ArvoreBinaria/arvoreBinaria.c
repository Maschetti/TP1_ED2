#include "arvoreBinario.h"

void imprimeArvore(int tamanhoArvore) {
  ArvoreExterna auxiliar;
  FILE *arvore = fopen("arvoreBinaria.bin", "rb");
  fseek(arvore, 0, SEEK_SET);

  for(int i = 0; i < tamanhoArvore; i++) {
    fread(&auxiliar, sizeof(ArvoreExterna), 1, arvore);
    printf("%d, %d, %d\n", auxiliar.indice.chave, auxiliar.filhoEsquerda, auxiliar.filhoDireita);
  }
  fclose(arvore);
};

void insereArvoreBinariaOrdenada(FILE *arvore, Indice indiceInsere, int posicaoFilho, int ordemArquivo, int fimArquivo) {
  ArvoreExterna folha;
  folha.indice = indiceInsere;
  folha.filhoEsquerda = -1;
  folha.filhoDireita = -1;
  if(ordemArquivo == 1 && !fimArquivo) {
    folha.filhoDireita = posicaoFilho;
  }
  else if(ordemArquivo == 2 && !fimArquivo) {
    folha.filhoEsquerda = posicaoFilho;
  }
  fwrite(&folha, sizeof(ArvoreExterna), 1, arvore);
  return ;
}

int insereArvoreBinaria(FILE *arvore, Indice indiceFilho) {
  
  ArvoreExterna indicePai;
  int ehArvoreVazia = fread(&indicePai, sizeof(ArvoreExterna), 1, arvore);

  ArvoreExterna folha;
  folha.indice = indiceFilho;
  folha.filhoDireita = -1;
  folha.filhoEsquerda = -1;


  if(ehArvoreVazia == 0) {
    fwrite(&folha, sizeof(ArvoreExterna), 1, arvore);
    return 1;
  }

  if(indicePai.indice.chave == indiceFilho.chave) {
    return 0;
  }

  int temFilhoEsquerda = (indicePai.filhoEsquerda != -1) ? 1 : 0;
  int filhoMenorPai = (indiceFilho.chave < indicePai.indice.chave) ? 1 : 0;
  int temFilhoDireita = (indicePai.filhoDireita != -1) ? 1 : 0;
  int filhoMaiorPai = (indiceFilho.chave > indicePai.indice.chave) ? 1 : 0;

  if(filhoMenorPai && temFilhoEsquerda) {
    fseek(arvore, indicePai.filhoEsquerda * sizeof(ArvoreExterna), SEEK_SET);
    insereArvoreBinaria(arvore, indiceFilho);
    return 1;
  }

  
  if(filhoMaiorPai && temFilhoDireita) {
    fseek(arvore, indicePai.filhoDireita * sizeof(ArvoreExterna), SEEK_SET);
    insereArvoreBinaria(arvore, indiceFilho);
    return 1;
  }

  int posicaoPai = (ftell(arvore) / sizeof(ArvoreExterna)) -1;
  fseek(arvore, 0, SEEK_END);

  if(filhoMenorPai) {
    indicePai.filhoEsquerda = ftell(arvore) / sizeof(ArvoreExterna);
  }
  else {
    indicePai.filhoDireita = ftell(arvore) / sizeof(ArvoreExterna);
  }

  fwrite(&folha, sizeof(ArvoreExterna), 1, arvore);

  fseek(arvore, posicaoPai * sizeof(ArvoreExterna), SEEK_SET);
  fwrite(&indicePai, sizeof(ArvoreExterna), 1, arvore);
  
  return 1;
};

void procuraArvoreBinaria(FILE *arvore, int chave, Indice *index, int *achou) {
  ArvoreExterna folha;
  fread(&folha, sizeof(ArvoreExterna), 1, arvore);

  int temFilhoEsquerda = (folha.filhoEsquerda != -1) ? 1 : 0;
  int chaveMenorPai = (chave < folha.indice.chave) ? 1 : 0;
  int temFilhoDireita = (folha.filhoDireita != -1) ? 1 : 0;
  int chaveMaiorPai = (chave > folha.indice.chave) ? 1 : 0;

  if(folha.indice.chave == chave) {
    *index = folha.indice;
    *achou = 1;
    return ;
  }

  if(chaveMenorPai && temFilhoEsquerda) {
    fseek(arvore, folha.filhoEsquerda * sizeof(ArvoreExterna), SEEK_SET);
    procuraArvoreBinaria(arvore, chave, index, achou);
  }

  if(chaveMaiorPai && temFilhoDireita) {
    fseek(arvore, folha.filhoDireita * sizeof(ArvoreExterna), SEEK_SET);
    procuraArvoreBinaria(arvore, chave, index, achou);
  }

  return ;
};

void arvoreBinaria(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa, int ordemArquivo) {
  Registro registroAuxiliar;
  Indice index;
  FILE *arvore;
  if((arvore = fopen("arvoreBinaria.bin", "w+b")) != NULL) {

    for (int i = 0; i < tamanhoArquivo; i++) {

      fread(&registroAuxiliar, sizeof(Registro), 1, arquivo);
      index.chave = registroAuxiliar.chave;
      index.posicaoArquivo = i;
      if(ordemArquivo == 1 || ordemArquivo == 2) {
        insereArvoreBinariaOrdenada(arvore, index, i + 1, ordemArquivo, i + 1 == tamanhoArquivo);
      }
      else {
        if(insereArvoreBinaria(arvore, index) == 0)
          return ;
        else
          fseek(arvore, 0, SEEK_SET);
      }
    }
    int achou = 0;
    fseek(arvore, 0, SEEK_SET);
    procuraArvoreBinaria(arvore, registroPesquisa->chave, &index, &achou);

    if(achou == 1) {
      fseek(arquivo, index.posicaoArquivo * sizeof(Registro), SEEK_SET);
      fread(registroPesquisa, sizeof(Registro), 1, arquivo);
    }

    fclose(arvore);
  }
  else {
    printf("ERRO: nao foi possivel criar arvoreBinaria\n");
  }
  
  return ;
}