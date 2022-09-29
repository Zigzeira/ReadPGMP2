//main
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main() {
  char nome_arquivo[255];
  scanf("%s", nome_arquivo);
  FILE *na = NULL;
  if(!(na = fopen(nome_arquivo,"rt"))){
      fprintf(stderr,"Erro: arquivo inexistente\n");
      return -1;
  }
  cabecalho(na);
  dados dadop2 = dados_pixel(na);
  impressao(dadop2.colunas,dadop2.linhas,dadop2.pixels);
  if (fclose (na)==EOF){
      perror("Arquivo não pode ser fechado\n");
      return -2;
  }
  free(dadop2.pixels);
  return 0;
}

//mylib.h
#include <stdio.h>

typedef struct {
  int colunas;
  int linhas;
  unsigned int maximo;
  unsigned int *pixels;
}dados;

int cabecalho(FILE *);

dados dados_pixel(FILE *);

void impressao(int ,int ,unsigned int*);

//mylib.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylib.h"

int cabecalho(FILE *arquivo){
    char verificap2[2];
    if(fscanf(arquivo,"%s",verificap2)!=1){
        fprintf(stderr,"Erro: arquivo corrompido\n");
        return -2;
    }
        
    if(strcmp(verificap2,"P2")){
        fprintf(stderr,"Erro: arquivo não é do formato P2\n");
        return -3;
    }
    
    char c[4],c1[4],c2[4],c3[4],c4[4],c5[4],c6[4],c7[4],c8[4],c9[4],c0[4];
    
    if(fscanf(arquivo,"%s %s %s %s %s %s %s %s %s %s %s",c,c1,c2,c3,c4,c5,c6,c7,c8,c9,c0)!=11){
        fprintf(stderr,"Erro: Não leu o comentário\n");
        return -4;
    }
    return 0;
    
}

dados dados_pixel(FILE *arquivo){
    dados dadosp2;
    int erro;
    
    int col,lin;
    if(fscanf(arquivo,"%d %d",&col, &lin)!=2){
      perror("Arquivo corrompido\n");
      erro = -4;
    }
    
    unsigned int *pix = malloc(col*lin*4);
    unsigned int *iterator = pix;
    unsigned int maxi;

    fscanf(arquivo, "%u", &maxi);
   
    for (int i = 0; i < lin; i++){
       for (int j = 0; j < col; j++, iterator++){
            if(fscanf(arquivo,"%u",iterator)!=1){
                 perror("Arquivo corrompido\n");
                 erro = -5; 
            }       
        }
    }
    

    if((erro == -4) || (erro == -5)){
      return dadosp2;
    }
    
    dadosp2.colunas = col;
    dadosp2.linhas = lin;
    dadosp2.maximo = maxi;
    dadosp2.pixels = pix;
    
    return dadosp2;
}

void impressao(int col, int lin, unsigned int* pix){
    for (int i = 0;i<lin;i++){
        for(int j = 0;j<col;j++, pix++){
            if(j==0){
                printf("%3X",*pix);
            }
            else{
                printf(" %3X",*pix);
            }
        }
        printf("\n");
    }
}
