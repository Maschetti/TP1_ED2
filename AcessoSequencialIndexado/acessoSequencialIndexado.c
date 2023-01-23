#include "acessoSequencialIndexado.h"
#include "../Analises/analise.h"
#include <stdlib.h>

Analise analise;

void pesquisa(FILE *arquivo, int *tabela, int tamanhoTabela, Registro *registroPesquisa, int tamanhoArquivo) {
  Registro pagina[TAMANHOPAGINA];

  int i, quantidadeItems;
  long desloc;
  iniciaContagemTempo(&analise);
  i = 0;
  while (i < tamanhoTabela && tabela[i] <= registroPesquisa->chave) i++;

  if(i == 0) return ;
  if(i < tamanhoTabela) quantidadeItems = TAMANHOPAGINA;
  else {
    fseek(arquivo, 0, SEEK_END);

    atualizaDeslocamentos_pesquisa(&analise, 1);
    quantidadeItems = tamanhoArquivo % TAMANHOPAGINA;
    if(quantidadeItems == 0) quantidadeItems = TAMANHOPAGINA;
  }

  desloc = (i - 1) * TAMANHOPAGINA * sizeof(Registro);
  fseek(arquivo, desloc, SEEK_SET);
  atualizaDeslocamentos_pesquisa(&analise, 1);
  fread(&pagina, sizeof(Registro), quantidadeItems, arquivo);
  atualizaTransferencias_pesquisa(&analise, 1);

  for(i = 0; i < quantidadeItems; i++) {
    atualizaComparacoes_pesquisa(&analise, 1);
    if(pagina[i].chave == registroPesquisa->chave) {
      *registroPesquisa = pagina[i];   
      break;
    }
  }
  finalizaContagemTempo(&analise);
  atualizaTempo_pesquisa(&analise);

  return ;
}

void acessoSequencialIndexado(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
  iniciaAnalise(&analise);
  iniciaContagemTempo(&analise);
  int tamanhoTabela = tamanhoArquivo / TAMANHOPAGINA;
  if(tamanhoTabela < ((double) tamanhoArquivo / (double) TAMANHOPAGINA)) {
    tamanhoTabela++;
  }
  int *tabela = malloc(sizeof(int) * (tamanhoTabela));

  int posicao = 0;
  Registro registro;
  while (posicao < tamanhoTabela) {
    fread(&registro, sizeof(registro), 1, arquivo);
    atualizaTransferencias_criacao(&analise, 1);

    fseek(arquivo, (sizeof(registro) * (TAMANHOPAGINA - 1)), SEEK_CUR);
    atualizaDeslocamentos_criacao(&analise, 1);    

    tabela[posicao] = registro.chave;
    posicao++;
    
  }
  fflush(stdout);

  finalizaContagemTempo(&analise);
  atualizaTempo_criacao(&analise);
  pesquisa(arquivo, tabela, tamanhoTabela, registroPesquisa, tamanhoArquivo);

  free(tabela);
  imprimirDados(&analise);
  return ;
}
