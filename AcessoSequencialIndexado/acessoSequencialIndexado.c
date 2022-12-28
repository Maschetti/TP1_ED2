#include "acessoSequencialIndexado.h"

void pesquisa(FILE *arquivo, int *tabela, int tamanhoTabela, Registro *registroPesquisa) {
  Registro pagina[TAMANHOPAGINA];
  int i, quantidadeItems;
  long desloc;

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

  for(i = 0; i < quantidadeItems; i++) {
    if(pagina[i].chave == registroPesquisa->chave) {
      *registroPesquisa = pagina[i];
    }
  }

  return ;
}

void acessoSequencialIndexado(FILE *arquivo, int tamanhoArquivo, Registro *registroPesquisa) {

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
  }
  fflush(stdout);

  pesquisa(arquivo, tabela, tamanhoTabela, registroPesquisa);

  free(tabela);

  return ;
}
