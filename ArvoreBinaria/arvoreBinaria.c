#include "arvoreBinario.h"

int insereArvoreBinaria(FILE *arvore, Indice index) {
  
  ArvoreExterna auxiliar;
  int ehArvoreVazia = fread(&auxiliar, sizeof(ArvoreExterna), 1, arvore);

  ArvoreExterna folha;
  folha.indice = index;
  folha.filhoDireita = -1;
  folha.filhoEsquerda = -1;


  if(ehArvoreVazia == 0) {
    fwrite(&folha, sizeof(ArvoreExterna), 1, arvore);
    return 1;
  }

  if(auxiliar.indice.chave == index.chave) {
    return 0;
  }

  if(index.chave < auxiliar.indice.chave && auxiliar.filhoEsquerda != -1) {
    fseek(arvore, auxiliar.filhoEsquerda * sizeof(ArvoreExterna), SEEK_SET);
    insereArvoreBinaria(arvore, index);
    return 1;
  }

  if(index.chave > auxiliar.indice.chave && auxiliar.filhoDireita != -1) {
    fseek(arvore, auxiliar.filhoDireita * sizeof(ArvoreExterna), SEEK_SET);
    insereArvoreBinaria(arvore, index);
    return 1;
  }

  int posicaoPai = (ftell(arvore) / sizeof(ArvoreExterna)) -1;
  fseek(arvore, 0, SEEK_END);

  if(index.chave < auxiliar.indice.chave) {
    auxiliar.filhoEsquerda = ftell(arvore) / sizeof(ArvoreExterna);
  }
  else {
    auxiliar.filhoDireita = ftell(arvore) / sizeof(ArvoreExterna);
  }

  fwrite(&folha, sizeof(ArvoreExterna), 1, arvore);

  fseek(arvore, posicaoPai * sizeof(ArvoreExterna), SEEK_SET);
  fwrite(&auxiliar, sizeof(ArvoreExterna), 1, arvore);
  
  return 1;
};

void procuraArvoreBinaria(FILE *arvore, int chave, Indice *index) {
  ArvoreExterna folha;
  fread(&folha, sizeof(ArvoreExterna), 1, arvore);

  if(folha.indice.chave == chave) {
    *index = folha.indice;
    return ;
  }

  if(chave < folha.indice.chave && folha.filhoEsquerda != -1) {
    fseek(arvore, folha.filhoEsquerda * sizeof(ArvoreExterna), SEEK_SET);
    procuraArvoreBinaria(arvore, chave, index);
  }

  if(chave > folha.indice.chave && folha.filhoDireita != -1) {
    fseek(arvore, folha.filhoDireita * sizeof(ArvoreExterna), SEEK_SET);
    procuraArvoreBinaria(arvore, chave, index);
  }

  return ;
};

void arvoreBinaria(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
  Registro registroAuxiliar;
  Indice index;
  FILE *arvore;
  if((arvore = fopen("arvoreBinaria.bin", "w+b")) != NULL) {

    for (int i = 0; i < tamanhoArquivo; i++) {

      fread(&registroAuxiliar, sizeof(Registro), 1, arquivo);
      index.chave = registroAuxiliar.chave;
      index.posicaoArquivo = i;
      fseek(arvore, 0, SEEK_SET);

      if(insereArvoreBinaria(arvore, index) == 0) {
        return ;
      }
    }

    fseek(arvore, 0, SEEK_SET);
    procuraArvoreBinaria(arvore, registroPesquisa->chave, &index);

    fseek(arquivo, index.posicaoArquivo * sizeof(Registro), SEEK_SET);
    fread(registroPesquisa, sizeof(Registro), 1, arquivo);

    fclose(arvore);
  }
  else {
    printf("ERRO: nao foi possivel criar arvoreBinaria\n");
  }
  
  return ;
}