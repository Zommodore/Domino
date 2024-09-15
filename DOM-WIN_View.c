#include "DOM-WIN_View.h"
#include <stdio.h>
#include <stdlib.h>

void fJogoContraDois() //funcao para jogos de dois jogadores 
{
    int indice;
    char lado = 'V';
    
    printf("\nForneca a peca(-1 para voltar): "); 
    scanf("%d", &indice);
    fClear();
    //if criado para o usuario jogar a peca de mesmo numero em ambos lados, caso sejam iguais 
    if (peca[indice].lado1 == mesa[0].ladoE && peca[indice].lado1 == mesa[tamanho-1].ladoD || peca[indice].lado2 == mesa[0].ladoE && peca[indice].lado2 == mesa[tamanho-1].ladoD||peca[indice].lado1 == mesa[0].ladoE && peca[indice].lado2 == mesa[tamanho-1].ladoD || peca[indice].lado2 == mesa[0].ladoE && peca[indice].lado1 == mesa[tamanho-1].ladoD)
    {
    	printf("\nForneca o lado (E|D): ");
    	scanf(" %c", &lado); // Usar "%c" para ler um único caractere
    	fClear();
    	system("cls");
	}
	
	
	/*	if (indice == -1 && compcontra == 1)
	{	
	fMenuComputador();
	}
	else if (multiplayer == 1)
	{
	fMenuDois();
	}*/
	    

    fJogar(indice, lado);
}

void fApresentaPeca() //funcao para apresentar pecas de tal jogador
{
    int cont = 0, k;
    printf("Jogador(%c)   ", jvez);

    for (k = 0; k < 28; k++)
    {
	
	
        if (peca[k].status ==jvez) 
		{
        
            printf("  %d.[%d|%d]", k, peca[k].lado1, peca[k].lado2);
        }
	}
    printf("\n");
}

/*void fApresentaPeca() 
{
    printf("Jogador(1)   ");
    for (int k = 0; k < 28; k++) 
    {
        if (peca[k].status == '1') 
        {
            printf("  %d.[%d|%d]", k, peca[k].lado1, peca[k].lado2);
        }
    }
    printf("\n");

    printf("Jogador(2)   ");
    for (int k = 0; k < 28; k++) 
    {
        if (peca[k].status == '2') 
        {
            printf("  %d.[%d|%d]", k, peca[k].lado1, peca[k].lado2);
        }
    }
    printf("\n");
}
*/


void fRegras()// mostra aos usuarios inexperientes, como se joga domino 
{
	printf ("Os jogadores comecam com sete pecas aleatorias e podem comprar mais quando necessario. A partida comeca com o jogador que possui a peca seis-seis ou a peca com os numeros repetidos mais altos. O jogo ocorre no sentido anti-horario, e os jogadores deve combinar os numeros de suas peca com os das extremidades da mesa.O jogador que comeca tem vantagem.\n\nA cada turno, os jogadores colocam uma peca na mesa e, se nao puderem jogar, precisam comprar do estoque. Se nao houver pecas no estoque, passam a vez. A partida continua ate que o estoque esteja vazio e alguem coloque sua ultimo peca, tornando-se vencedor. Caso nenhum jogador possa continuar, e o estoque tambem esteja vazio, a partida se fecha, e vence quem tiver menos pecas. Em caso de empate, os jogadores somam os pontos das pecas restantes, e o jogador com menos pontos vence.\nEm resumo o vencedor geralmente e quem tem menos pecas ou menos pontos quando a partida termina.\n\n");
}

void fApresentaMesa() // apresenta a mesa do jogo e as pecas jogadas dentro dela
{
	printf ("==============================================\n");
	printf ("MESA:");
	for(int i=0;i<tamanho;i++) 
		printf ("[%d|%d]",mesa[i].ladoE,mesa[i].ladoD);
	printf ("\n==============================================\n");
}

void fApresentaMensagem(char mens[100]) 
{
	printf("%s\n",mens);
}

int fMenuGeral() // Função para exibir o menu do jogo.
{
    int opc;

    do
    {
        printf("1) Iniciar jogo (2 jogadores)\n");
        printf("2) Iniciar jogo (contra o computador)\n");
        printf("3) Retornar ao jogo interrompido\n");
        printf("4) Regras gerais do jogo\n");
        printf("5) Salvar o jogo\n");
        printf("6) Recuperar o jogo salvo\n");
        printf("0) Sair do jogo\n"); // Adicione a opção de sair (opcão 0)

        printf("Opcao: ");
        scanf("%d", &opc);

        if (opc == 0)
        {
            // Sair do jogo (você pode adicionar aqui qualquer código de encerramento que for necessário)
            printf("Saindo do jogo...\n");
            exit(0); // Encerra o programa
        }

        //fClear(); - Se necessário, adicione uma função para limpar a tela aqui

    } while (opc > 6 || opc < 1);

    return opc;
}


int fMenuDois()//menu para dois jogadores
{	
	int multiplayer = 1; 
	int opc;
	do
	{
		fApresentaMesa();
		fApresentaPeca();
		
		printf ("\n\n1)Jogar");
		printf ("\n2)Comprar");
		printf ("\n3)Passar");
		printf ("\n4)Sair");
		printf ("\nOpcao:");
		scanf  ("%d",&opc);
	}while (opc>4 ||opc<1);
	
	return opc;
}

int fMenuComputador()//menu de jogo contra a maquina
{	
		int compcontra = 1; 
		int opc;
	do
	{
		fApresentaMesa();
		fApresentaPeca();
		
		printf ("\n\n1)Jogar");
		printf ("\n2)Comprar");
		printf ("\n3)Passar");
		printf ("\n4)Sair");
		printf ("\nOpcao:");
		scanf  ("%d",&opc);
		
	}while (opc>4 ||opc<1);
	
	return opc;
}
