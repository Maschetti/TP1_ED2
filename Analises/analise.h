#ifndef analise_h
#define analise_h

#include <time.h>

//a analise eh dormado por numero de transferencias, comparacoes e o tempo
typedef struct{
  int tranferencias_criacao, tranferencias_pesquisa;
  int comparacoes_criacao, comparacoes_pesquisa;
  double tempo_pesquisa, tempo_criacao;

  clock_t iniTempo, fimTempo;
} Analise;


//funcao que inicia as analises
void iniciaAnalise(Analise *analise);

//funcao que imprime os dados obtidos na analise 
void imprimirDados(Analise *analise);

//funcoes para contagem do tempo 
void iniciaContagemTempo(Analise *analise);
void finalizaContagemTempo(Analise *analise);

//funcoes para numero de transfencias
void atualizaTransferencias_criacao(Analise *analise, int qtd);
void atualizaTransferencias_pesquisa(Analise *analise, int qtd);

//funcoes para numero de comparacoes
void atualizaComparacoes_criacao(Analise *analise, int qtd);
void atualizaComparacoes_pesquisa(Analise *analise, int qtd);

//funcoes para atualizacao do tempo de contagem
void atualizaTempo_criacao(Analise *analise);
void atualizaTempo_pesquisa(Analise *analise);

#endif