#include "arvoreBinario.h"
#include "../Analises/analise.h"

Analise analiseBinaria;

void imprimeArvore(int tamanhoArvore)
{
  ArvoreExterna auxiliar;
  FILE *arvore = fopen("arvoreBinaria.bin", "rb");
  fseek(arvore, 0, SEEK_SET);

  for (int i = 0; i < tamanhoArvore; i++)
  {
    fread(&auxiliar, sizeof(ArvoreExterna), 1, arvore);
    printf("%d, %d, %d\n", auxiliar.indice.chave, auxiliar.filhoEsquerda, auxiliar.filhoDireita);
  }
  fclose(arvore);
};

void insereArvoreBinariaOrdenada(FILE *arvore, Indice indiceInsere, int posicaoFilho, int ordemArquivo, int fimArquivo)
{
  ArvoreExterna folha;
  folha.indice = indiceInsere;
  folha.filhoEsquerda = -1;
  folha.filhoDireita = -1;
  if (ordemArquivo == 1 && !fimArquivo)
  {
    folha.filhoDireita = posicaoFilho;
  }
  else if (ordemArquivo == 2 && !fimArquivo)
  {
    folha.filhoEsquerda = posicaoFilho;
  }
  fwrite(&folha, sizeof(ArvoreExterna), 1, arvore);
  return;
}

int insereArvoreBinaria(FILE *arvore, Indice indiceInsere)
{
  ArvoreExterna folhaCaminhamento, folhaInsere, folhaPai;
  folhaInsere.indice = indiceInsere;
  folhaInsere.filhoEsquerda = -1;
  folhaInsere.filhoDireita = -1;

  int posicaoPai = 0;
  int naoAchouPosicaoFilho = 1;
  int arvoreVazia = (fread(&folhaCaminhamento, sizeof(ArvoreExterna), 1, arvore) == 0) ? 1 : 0;
  atualizaTransferencias_criacao(&analiseBinaria,1);

  if (arvoreVazia)
  {
    fwrite(&folhaInsere, sizeof(ArvoreExterna), 1, arvore);
    return 1;
  }

  while (naoAchouPosicaoFilho)
  {
    fseek(arvore, posicaoPai * sizeof(ArvoreExterna), SEEK_SET);
    atualizaDeslocamentos_criacao(&analiseBinaria,1);

    fread(&folhaCaminhamento, sizeof(ArvoreExterna), 1, arvore);
    atualizaTransferencias_criacao(&analiseBinaria,1);
    folhaPai = folhaCaminhamento;

    atualizaComparacoes_criacao(&analiseBinaria, 1);
    if (folhaInsere.indice.chave < folhaCaminhamento.indice.chave)
    {
      if (folhaCaminhamento.filhoEsquerda != -1)
      {
        posicaoPai = folhaCaminhamento.filhoEsquerda;
      }
      else
      {
        naoAchouPosicaoFilho = 0;
      }
    }
    else
    {
      atualizaComparacoes_pesquisa(&analiseBinaria,1);
      if (folhaInsere.indice.chave > folhaCaminhamento.indice.chave)
      {
        if (folhaCaminhamento.filhoDireita != -1)
        {
          posicaoPai = folhaCaminhamento.filhoDireita;
        }
        else
        {
          naoAchouPosicaoFilho = 0;
        }
      }
      else
      {
        return 0;
      }
    }
  }

  fseek(arvore, 0, SEEK_END);
  atualizaDeslocamentos_criacao(&analiseBinaria,1);

  atualizaComparacoes_criacao(&analiseBinaria,1);
  if (folhaInsere.indice.chave < folhaPai.indice.chave)
  {
    folhaPai.filhoEsquerda = ftell(arvore) / sizeof(ArvoreExterna);
  }
  else
  {
    folhaPai.filhoDireita = ftell(arvore) / sizeof(ArvoreExterna);
  }

  fwrite(&folhaInsere, sizeof(ArvoreExterna), 1, arvore);

  fseek(arvore, posicaoPai * sizeof(ArvoreExterna), SEEK_SET);
  atualizaDeslocamentos_criacao(&analiseBinaria,1);
  fwrite(&folhaPai, sizeof(ArvoreExterna), 1, arvore);
  return 1;
}

void procuraArvoreBinaria(FILE *arvore, int chave, Indice *index, int posicao, int *achou)
{
  ArvoreExterna folha;
  fseek(arvore, posicao * sizeof(ArvoreExterna), SEEK_SET);
  atualizaDeslocamentos_pesquisa(&analiseBinaria,1);

  fread(&folha, sizeof(ArvoreExterna), 1, arvore);
  atualizaTransferencias_pesquisa(&analiseBinaria,1);

  int temFilhoEsquerda = (folha.filhoEsquerda != -1) ? 1 : 0;
  int chaveMenorPai = (chave < folha.indice.chave) ? 1 : 0;
  int temFilhoDireita = (folha.filhoDireita != -1) ? 1 : 0;
  int chaveMaiorPai = (chave > folha.indice.chave) ? 1 : 0;

  atualizaComparacoes_pesquisa(&analiseBinaria,5);
  if (folha.indice.chave == chave)
  {
    *index = folha.indice;
    *achou = 1;
    return;
  }

  if (chaveMenorPai && temFilhoEsquerda)
  {
    procuraArvoreBinaria(arvore, chave, index, folha.filhoEsquerda, achou);
  }

  if (chaveMaiorPai && temFilhoDireita)
  {
    procuraArvoreBinaria(arvore, chave, index, folha.filhoDireita, achou);
  }

  return;
};

void arvoreBinaria(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa, int ordemArquivo)
{
  Registro registroAuxiliar;
  Indice index;
  FILE *arvore;
  iniciaAnalise(&analiseBinaria);

  iniciaContagemTempo(&analiseBinaria);
  if ((arvore = fopen("arvoreBinaria.bin", "w+b")) != NULL)
  {

    for (int i = 0; i < tamanhoArquivo; i++)
    {

      fread(&registroAuxiliar, sizeof(Registro), 1, arquivo);
      atualizaTransferencias_criacao(&analiseBinaria, 1);

      index.chave = registroAuxiliar.chave;
      index.posicaoArquivo = i;
      if (ordemArquivo == 1 || ordemArquivo == 2)
      {
        insereArvoreBinariaOrdenada(arvore, index, i + 1, ordemArquivo, i + 1 == tamanhoArquivo);
      }
      else
      {
        if (insereArvoreBinaria(arvore, index) == 0)
          return;
        else
          fseek(arvore, 0, SEEK_SET);
      }
    }
    int achou = 0;
    fseek(arvore, 0, SEEK_SET);
    atualizaDeslocamentos_criacao(&analiseBinaria, 1);

    finalizaContagemTempo(&analiseBinaria);
    atualizaTempo_criacao(&analiseBinaria);

    iniciaContagemTempo(&analiseBinaria);
    procuraArvoreBinaria(arvore, registroPesquisa->chave, &index, 0, &achou);

    if (achou == 1)
    {
      fseek(arquivo, index.posicaoArquivo * sizeof(Registro), SEEK_SET);
      atualizaDeslocamentos_pesquisa(&analiseBinaria,1);
      fread(registroPesquisa, sizeof(Registro), 1, arquivo);
      atualizaTransferencias_pesquisa(&analiseBinaria,1);
    }

    finalizaContagemTempo(&analiseBinaria);
    atualizaTempo_pesquisa(&analiseBinaria);

    fclose(arvore);
  }
  else
  {
    printf("ERRO: nao foi possivel criar arvoreBinaria\n");
  }

  imprimirDados(&analiseBinaria);

  return;
}