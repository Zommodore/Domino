#include "DOM-WIN_Model.h"
#include <stdio.h>


typedef struct stpeca //Estrutura de dados contendo os lados do domino e a situacao atual do jogo.
{
    int lado1;
    int lado2;
    char status;//Representa diferentes estados do jogo

} tipoPeca;

tipoPeca peca[28];//Define a quantidade de pecas 
tipoPeca aux;

struct mesa //cria a mesa
{
    int ladoE; //lado esquerdo da mesa
    int ladoD;//lado direito da mesa
    char status;
} mesa[28]; 


struct Jogo //cria a estrutura jogo 
{
int tamanhoJogo; 
int jogadorJogo; 
int jogadorComp;
} sitJogo;
