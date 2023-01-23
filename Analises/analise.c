#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "analise.h"

//funcoes para analises solicitadas
// aqui faz-se a analise para as etapas de criacao dos indices 
// e a analise para a pesquisa em si
void iniciaAnalise(Analise *analise){
  //depois -> analise da pesquisa
  analise->tranferencias_pesquisa = 0; 
  analise->comparacoes_pesquisa = 0;
  analise->deslocamentos_pesquisa = 0;

  //antes -> analise da criacao 
  analise->tranferencias_criacao = 0;
  analise->comparacoes_criacao = 0;
  analise->deslocamentos_criacao = 0;
}

//funcoes para contagem do tempo de execucao
//inicia e finaliza o clock - reloginho
void iniciaContagemTempo(Analise *analise){
  analise->iniTempo = clock();
}

void finalizaContagemTempo(Analise *analise){
  analise->fimTempo = clock();
}

//funcoes para verificacao do numero de transferencias
void atualizaTransferencias_pesquisa(Analise *analise, int qtd){
  analise->tranferencias_pesquisa += qtd;
}

void atualizaTransferencias_criacao(Analise *analise, int qtd){
  analise->tranferencias_criacao += qtd;
}

//funcoes para verificacao do numero de comparacoes
void atualizaComparacoes_pesquisa(Analise *analise, int qtd){
  analise->comparacoes_pesquisa += qtd;
}

void atualizaComparacoes_criacao(Analise *analise, int qtd){
  analise->comparacoes_criacao += qtd;
}

//funcoes para verificacao do numero de deslocamentos
void atualizaDeslocamentos_pesquisa(Analise *analise, int qtd){
  analise->deslocamentos_pesquisa += qtd;
}

void atualizaDeslocamentos_criacao(Analise *analise, int qtd){
  analise->deslocamentos_criacao += qtd;
}

//funcoes para atualizacao do tempo
void atualizaTempo_criacao(Analise *analise){
  //calcula o tempo o converte para milissegundos
  analise->tempo_criacao = ((double)(analise->fimTempo - analise->iniTempo) * 1000 / CLOCKS_PER_SEC);
}

void atualizaTempo_pesquisa(Analise *analise){
  //calculando e convertendo tempo total para milissegundos
  analise->tempo_pesquisa = ((double)(analise->fimTempo - analise->iniTempo) * 1000 / CLOCKS_PER_SEC);
}

//funcao para impressao dos dados 
void imprimirDados(Analise *analise){

  int acessoDiscoCriacao = analise->tranferencias_criacao + analise->deslocamentos_criacao;
  int acessoDiscoPesquisa = analise->tranferencias_pesquisa + analise->deslocamentos_pesquisa;



  printf("Dados da execução para criação dos índices:\n");
  printf("⏰  - Tempo de execução: %.4lfms\n", analise->tempo_criacao);
  printf("📈  - Quantidade de comparação(ões): %d\n", analise->comparacoes_criacao);
  printf("📊  - Quantidade de transferencia(s): %d\n", analise->tranferencias_criacao); 
  printf("🔄- Quantidade de deslocamento(s): %d\n", analise->deslocamentos_criacao); 
  printf("📊  - Quantidade de acesso ao disco(s): %d\n\n", acessoDiscoCriacao); 

  printf("Dados da execução da pesquisa:\n");
  printf("⏰  - Tempo de execução: %.4lfms\n", analise->tempo_pesquisa);
  printf("📈  - Quantidade de comparação(ões): %d\n", analise->comparacoes_pesquisa);
  printf("📊  - Quantidade de transferencia(s): %d\n", analise->tranferencias_pesquisa);
  printf("🔄- Quantidade de deslocamento(s): %d\n", analise->deslocamentos_pesquisa);
  printf("📊  - Quantidade de acesso ao disco(s): %d\n\n", acessoDiscoPesquisa); 
}