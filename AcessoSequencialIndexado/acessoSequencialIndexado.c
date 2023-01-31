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

  //Procura a página do item desejado
  while (i < tamanhoTabela && tabela[i] <= registroPesquisa->chave) i++;

  if(i == 0) return ;

  //Verifica a quantidade de itens na página
  if(i < tamanhoTabela) quantidadeItems = TAMANHOPAGINA;
  else {
    quantidadeItems = tamanhoArquivo % TAMANHOPAGINA;
    if(quantidadeItems == 0) quantidadeItems = TAMANHOPAGINA;
  }

  //Carregando a página para a memória principal
  desloc = (i - 1) * TAMANHOPAGINA * sizeof(Registro);
  fseek(arquivo, desloc, SEEK_SET);
  atualizaDeslocamentos_pesquisa(&analise, 1);
  fread(&pagina, sizeof(Registro), quantidadeItems, arquivo);
  atualizaTransferencias_pesquisa(&analise, 1);

  //Varredura na página para encontrar o item
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

  //Leitura e armazenamento do menor item da página
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
