#include "acessoSequencialIndexado.h"
#include "../Analises/analise.h"
#include <stdlib.h>

Analise analise;

void pesquisa(FILE *arquivo, int *tabela, int tamanhoTabela, Registro *registroPesquisa) {
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
    quantidadeItems = ((ftell(arquivo) / sizeof(Registro)) - 1) % TAMANHOPAGINA;
    if(quantidadeItems == 0) quantidadeItems = 4;
  }

  desloc = (i - 1) * TAMANHOPAGINA * sizeof(Registro);
  fseek(arquivo, desloc, SEEK_SET);
  fread(&pagina, sizeof(Registro), quantidadeItems, arquivo);
  atualizaTransferencias_pesquisa(&analise, 1);

  for(i = 0; i < quantidadeItems; i++) {
    if(pagina[i].chave == registroPesquisa->chave) {
      *registroPesquisa = pagina[i];
      atualizaComparacoes_pesquisa(&analise, 1);
      break;
    }
  }
  finalizaContagemTempo(&analise);
  atualizaTempo_pesquisa(&analise);

  return ;
}

void acessoSequencialIndexado(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {
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
    fseek(arquivo, (sizeof(registro) * (TAMANHOPAGINA - 1)), SEEK_CUR);
    tabela[posicao] = registro.chave;
    posicao++;
    //Atualiza Transferências antes 
    atualizaTransferencias_criacao(&analise, 1);
  }
  fflush(stdout);
  finalizaContagemTempo(&analise);
  atualizaTempo_criacao(&analise);
  pesquisa(arquivo, tabela, tamanhoTabela, registroPesquisa);

  free(tabela);
  imprimirDados(&analise);
  return ;
}
