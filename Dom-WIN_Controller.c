#include "DOM-WIN_Controller.h"
#include "DOM-WIN_View.cpp"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void fIniciarPecas() // Funcao que fornecera valor para os lados da peca.
{
    int j, i;
    int k = 0;
    int g;

    for (i = 0; i <= 6; i++)
        for (j = 0; j <= i; j++)
        {
            peca[k].lado1 = i; // O lado 1 correspondera o valor crescente de i
            peca[k].lado2 = j; // O lado 2 correspondera o valor crescente de j
            peca[k].status = '0'; // Situacao do jogo inicializado como 'O'
            k++;
        }
}

void fEmbaralhar() // Funcao que embaralha as pecas de domino
{
    int i, aux;
    int ran;

    srand(time(NULL));

    for (i = 0; i < 28; i++)
    {
        ran = rand() % 28; // Determina o resto de 28 como indice da posicao dos lados de forma aleatoria

        aux = peca[i].lado1; // Armazena o valor de cada posicao
        peca[i].lado1 = peca[ran].lado1; // Troca o valor pela posicao aleatoria de ran
        peca[ran].lado1 = aux; // Troca o valor pelo valor armazenado

        aux = peca[i].lado2;
        peca[i].lado2 = peca[ran].lado2;
        peca[ran].lado2 = aux;
    }
}

void fDistribuirPecas()//contador das pecas para ambos jogadores
{
    int k;

    for (k = 0; k < 7; k++)//contador de pecas do jogador 1
    {
        peca[k].status = '1';
    }

    for (k = 7; k < 14; k++) //contador de pecas do jogador 2
    {
        peca[k].status = '2';
    }
}

void fPrimeiraJogada() // joga a primeira peca na mesa 
{
    int i, pj, dupla;

    pj = -1;
    dupla = -1;
	//identifica qual a peca  mais alta de ladosa iguais para ser jogada na mesa 
    for (i = 0; i < 14; i++)
    {
        if (peca[i].lado1 == peca[i].lado2)
        {
            if (peca[i].lado1 > dupla)
            {
                dupla = peca[i].lado1;
                pj = i;
            }
        }
    }

    if (pj == -1)
    {
        dupla = 0;
        for (i = 0; i < 14; i++)
        {
            if (peca[i].lado1 + peca[i].lado2 > dupla)
            {
                dupla = peca[i].lado1 + peca[i].lado2;
                pj = i;
            }
        }
    }
    jvez = peca[pj].status;
    mesa[0].ladoE = peca[pj].lado1;
    mesa[0].ladoD = peca[pj].lado2;
    peca[pj].status = 'M';
    tamanho = 1; // Atualiza o tamanho para indicar que ha uma peca na mesa
    // Se estiver jogando contra o computador (jogador 2), garanta que o jogador 1 jogue a primeira peça da mesa
}

void fTrocaJogador() //funcao para trocar o jogador
{
    if (jvez == '1')
        jvez = '2';
    else
        jvez = '1';
}

void fJogar(int indice, char lado) //funcao para  jogar a peca na mesa
{
	if(indice == -1)
	{
		return; 
	}
    if ((jvez == '1' && peca[indice].status == '1') || (jvez == '2' && peca[indice].status == '2')) 
    {
        if ((lado == 'V' && (peca[indice].lado1 == mesa[0].ladoE || peca[indice].lado2 == mesa[0].ladoE))) 
        {
            for (int i = tamanho - 1; i >= 0; i--)
            {
                mesa[i + 1] = mesa[i]; 
            }

            if (peca[indice].lado1 == mesa[1].ladoE)
            {
                mesa[0].ladoD = peca[indice].lado1;
                mesa[0].ladoE = peca[indice].lado2;
            }
            else if (peca[indice].lado2 == mesa[1].ladoE)
            {
                mesa[0].ladoD = peca[indice].lado2;
                mesa[0].ladoE = peca[indice].lado1;
            }

            peca[indice].status = 'M';
            peca[indice].lado1 = -1;
            peca[indice].lado2 = -1; // Marca a peca como jogada 
            tamanho++;
            fTrocaJogador();//usado para trocar de jogador apos a peca ser jogada
        }
        else if ((lado == 'V' && (peca[indice].lado1 == mesa[tamanho - 1].ladoD || peca[indice].lado2 == mesa[tamanho - 1].ladoD)))
        {
            if (peca[indice].lado1 == mesa[tamanho - 1].ladoD)
            {
                mesa[tamanho].ladoD = peca[indice].lado2;
                mesa[tamanho].ladoE = peca[indice].lado1;
            }
            else if (peca[indice].lado2 == mesa[tamanho - 1].ladoD) 
            {
                mesa[tamanho].ladoD = peca[indice].lado1;
                mesa[tamanho].ladoE = peca[indice].lado2;
            }

            peca[indice].status = 'M';
            peca[indice].lado1 = -1;
            peca[indice].lado2 = -1; // Marca a peca como jogada
            tamanho++;
            fTrocaJogador();
        }
        else if ((lado == 'E' || lado == 'e') && (peca[indice].lado1 == mesa[0].ladoE || peca[indice].lado2 == mesa[0].ladoE))
        {
            for (int i = tamanho - 1; i >= 0; i--)
            {
                mesa[i + 1] = mesa[i];
            }

            if (peca[indice].lado1 == mesa[1].ladoE)
            {
                mesa[0].ladoD = peca[indice].lado1;
                mesa[0].ladoE = peca[indice].lado2;
            }
            else if (peca[indice].lado2 == mesa[1].ladoE)
            {
                mesa[0].ladoD = peca[indice].lado2;
                mesa[0].ladoE = peca[indice].lado1;
            }

            peca[indice].status = 'M';
            peca[indice].lado1 = -1;
            peca[indice].lado2 = -1; // Marca a peca como jogada
            tamanho++;
            fTrocaJogador(); // Alternar para o proximo jogador
        }
        else if ((lado == 'D' || lado == 'd') && (peca[indice].lado1 == mesa[tamanho - 1].ladoD || peca[indice].lado2 == mesa[tamanho - 1].ladoD))
        {
            if (peca[indice].lado1 == mesa[tamanho - 1].ladoD)
            {
                mesa[tamanho].ladoD = peca[indice].lado2;
                mesa[tamanho].ladoE = peca[indice].lado1;
            }
            else if (peca[indice].lado2 == mesa[tamanho - 1].ladoD)
            {
                mesa[tamanho].ladoD = peca[indice].lado1;
                mesa[tamanho].ladoE = peca[indice].lado2;
            }

            peca[indice].status = 'M';
            peca[indice].lado1 = -1;
            peca[indice].lado2 = -1; // Marca a peca como jogada
            tamanho++;
            fTrocaJogador(); // Alternar para o proximo jogador
        }
        else
        {
            fApresentaMensagem("\n \n A peca escolhida nao pode ser jogada nesse lado da mesa.\n"); //caso a peca jogada nao seja coincidente com o lado da mesa.
        }
    }
    else
    {
        fApresentaMensagem("Essa peca nao pertence ao jogador atual.\n"); 
    }

    int resultadoDesempate = fDesempate();  
    if (resultadoDesempate != 0) //informa quem ganhou a partida 
    {
        if (resultadoDesempate == 1)
        {
            fApresentaMensagem("O jogador 2 venceu.\n");//seja o jgador 2 
            fExecutarMenu();
        }
        else if (resultadoDesempate == 2)
        {
            fApresentaMensagem("O jogador 1 venceu.\n"); //seja o jogador 1 
            fExecutarMenu();
        }
    }
}



void fComprar(char jvez) // funcao  para comprar mais pecas 
{
    int i = 14; // as 14 primeiras pecas ja nao estao mais livres
    while (i < 28)
    {
        if (peca[i].status == '0')
        {
            peca[i].status = jvez;
            break;
        }
        i++;
    }
    if (i >= 28) // caso tenha acabado as pecas no deposito
    {
        fApresentaMensagem("Nada a comprar"); 
    }
}


booleano fDepositoVazio() //pecas no deposito
{
    for (int i = 0; i < 28; i++)
    {
        if (peca[i].status == '0')
            return FALSE;
    }
    return TRUE;
}

booleano fPassar() //funcao para passar a vez ao outro jogador 
{
    if (fDepositoVazio() == FALSE)
    {
        fApresentaMensagem("Passagem bloqueada. O deposito nao esta vazio. Voce deve jogar e/ou comprar.");
        return FALSE;
    }
    else
    {
        booleano podePassar = TRUE; // Inicialmente, e possivel passar

        for (int i = 0; i < 28; i++)
        {
            if ((peca[i].lado1 == mesa[0].ladoE || peca[i].lado2 == mesa[tamanho - 1].ladoE ||
                 peca[i].lado1 == mesa[0].ladoD || peca[i].lado2 == mesa[tamanho - 1].ladoD) &&
                peca[i].status == jvez)
            {
                // Se uma peca valida do jogador atual for encontrada, nao e possivel passar
                podePassar = FALSE;
                break; // Saia do loop assim que encontrar uma peca valida
            }
        }

        if (podePassar)
        {
            if (jvez == '1')
                jvez = '2';
            else
                jvez = '1';
            return TRUE;
        }
        else
        {
            fApresentaMensagem("Passagem bloqueada. Voce tem pecas para jogar.");
            return FALSE;
        }
    }
}


int fDesempate() //funcao para identificar o ganhador da paritda 
{
    int jogadormesa = 0;
    int jogadorum = 0;
    int jogadordois = 0;
    int pontojogadorum = 0;
    int pontojogadordois = 0;

    for (int i = 0; i < 28; i++)
    {
        if (peca[i].status == '1')
        {
            jogadorum = 1;
            pontojogadorum += peca[i].lado1 + peca[i].lado2;
        }
        else if (peca[i].status == '2')
        {
            jogadordois = 1;
            pontojogadordois += peca[i].lado1 + peca[i].lado2;
        }
        else if (peca[i].status == '0')
        {
            jogadormesa = 1;
        }
    }

    if (!jogadormesa)
    {
        // Verifique se ambas as pecas dos jogadores não podem ser jogadas na mesa
        int ambasPecasNaoPodemSerJogadas = 1;
        for (int i = 0; i < 28; i++)
        {
            if ((peca[i].lado1 == mesa[0].ladoE || peca[i].lado2 == mesa[0].ladoE) ||
                (peca[i].lado1 == mesa[tamanho - 1].ladoD || peca[i].lado2 == mesa[tamanho - 1].ladoD))
            {
                ambasPecasNaoPodemSerJogadas = 0;
                break;
            }
        }

        if (ambasPecasNaoPodemSerJogadas) 
        {
            if (pontojogadorum < pontojogadordois)
            {
                return 1; // Jogador 1 vence
            }
            else if (pontojogadordois < pontojogadorum)
            {
                return 2; // Jogador 2 vence
            }
            else
            {
                // Se ambos têm a mesma quantidade de pontos,
                // verifique quem tem a menor peça
                int menorPecaJogador1 = 7; // Valor máximo de uma peça
                int menorPecaJogador2 = 7;

                for (int i = 0; i < 28; i++)
                {
                    if (peca[i].status == '1')
                    {
                        if (peca[i].lado1 < menorPecaJogador1)
                        {
                            menorPecaJogador1 = peca[i].lado1;
                        }
                        if (peca[i].lado2 < menorPecaJogador1)
                        {
                            menorPecaJogador1 = peca[i].lado2;
                        }
                    }
                    else if (peca[i].status == '2')
                    {
                        if (peca[i].lado1 < menorPecaJogador2)
                        {
                            menorPecaJogador2 = peca[i].lado1;
                        }
                        if (peca[i].lado2 < menorPecaJogador2)
                        {
                            menorPecaJogador2 = peca[i].lado2;
                        }
                    }
                }

                if (menorPecaJogador1 < menorPecaJogador2)
                {
                    return 1; // Jogador 1 vence
                }
                else if (menorPecaJogador2 < menorPecaJogador1)
                {
                    return 2; // Jogador 2 vence
                }
                else
                {
                    return 0; // Empate
                }
            }
        }
    }

    if (!jogadorum)
    {
        return 2; // Jogador 2 vence, pois o jogador 1 está sem peças
    }
    else if (!jogadordois)
    {
        return 1; // Jogador 1 vence, pois o jogador 2 está sem peças
    }

    // Se nenhum dos cenários de desempate ocorrer, retorne 0 ou outro valor apropriado
    return 0;
}


void fClear() // limpa tela
{
    int ch;
    while ((ch = fgetc(stdin)) != EOF&&ch != '\n');
}

void fGravaCadastro()//funcao para gravacao da partida
{
    if (tamanho == 0) 
    {
        fApresentaMensagem("Sem jogo a ser gravado");
        return;
    }

    // Verifique se o jogo terminou devido a um desempate
    int resultadoDesempate = fDesempate();

    // Verifique se um dos jogadores não tem mais peças na mão
    if (resultadoDesempate != 0)
    {
        fApresentaMensagem("O jogo terminou. Nao sera salvo.");
        return;
    }

    int i;

    FILE *fp;
    FILE *fpm;
    FILE *fps;

    sitJogo.tamanhoJogo = tamanho;
    sitJogo.jogadorJogo = jvez;
    sitJogo.jogadorComp = jogcomp;
		//mensagens para problemas na gravacao da partida
    if ((fp = fopen("CAD_DOMINO", "wb")) == NULL)
    {
        fApresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto para cadastrar");
        return;
    }

    if ((fpm = fopen("CAD_MESA", "wb")) == NULL)
    {
        fApresentaMensagem("O arquivo CAD_MESA nao pode ser aberto para cadastrar");
        return;
    }

    if ((fps = fopen("CAD_JOGO", "wb")) == NULL)
    {
        fApresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto para cadastrar");
        return;
    }

    for (i = 0; i < 28; i++)
    {
        if (fwrite(&peca[i], sizeof(tipoPeca), 1, fp) != 1)
        {
            fApresentaMensagem("Erro na gravacao do arquivo CAD_DOMINO");
            break;
        }
    }

    for (i = 0; i < 28; i++)
    {
        if (fwrite(&mesa[i], sizeof(struct mesa), 1, fpm) != 1)
        {
            fApresentaMensagem("Erro na gravacao do arquivo CAD_MESA");
            break;
        }
    }

    if (fwrite(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
        fApresentaMensagem("Erro na gravacao do arquivo CAD_JOGO");

    fclose(fps);
    fclose(fpm);
    fclose(fp);
    fApresentaMensagem("Gravados os arquivos CAD_DOMINO, CAD_MESA, CAD_JOGO");
}

// Funcao para verificar se um jogador nao tem mais pecas na mao
int fJogadorNaoTemPecas(int jogador)
{
    for (int i = 0; i < 28; i++)
    {
        if (peca[i].status == jogador)
        {
            // O jogador ainda tem pelo menos uma peca na mao
            return 0;
        }
    }
    // O jogador nao tem mais pecas na mao
    return 1;
}


void fRecuperaCadastro() // recupera a partida
{
    int i;

    FILE *fp;
    FILE *fpm;
    FILE *fps;
		//mensagens caso tenha problema na recuperacao de algum dos arquivos
    if ((fp = fopen("CAD_DOMINO", "rb")) == NULL)
    {
        fApresentaMensagem("O arquivo CAD_DOMINO nao pode ser aberto"); 
        return;
    }

    if ((fpm = fopen("CAD_MESA", "rb")) == NULL)
    {
        fApresentaMensagem("O arquivo CAD_MESA nao pode ser aberto");
        return;
    }

    if ((fps = fopen("CAD_JOGO", "rb")) == NULL)
    {
        fApresentaMensagem("O arquivo CAD_JOGO nao pode ser aberto");
        return;
    }

    for (i = 0; i < 28; i++)
    {
        if (fread(&peca[i], sizeof(tipoPeca), 1, fp) != 1)
        {
            fApresentaMensagem("Erro na leitura do arquivo CAD_DOMINO");
            break;
        }
    }

    for (i = 0; i < 28; i++)
    {
        if (fread(&mesa[i], sizeof(struct mesa), 1, fpm) != 1)
        {
            fApresentaMensagem("Erro na leitura do arquivo CAD_MESA");
            break;
        }
    }

    if (fread(&sitJogo, sizeof(struct Jogo), 1, fps) != 1)
        fApresentaMensagem("Erro na leitura do arquivo CAD_JOGO");

    fclose(fps);
    fclose(fpm);
    fclose(fp);

    jvez = sitJogo.jogadorJogo;
    tamanho = sitJogo.tamanhoJogo;
    jogcomp = sitJogo.jogadorComp;
    fApresentaMensagem("Retornando ao jogo recuperado");
}


void fComputador() 
{
    while (jvez == '2')
    {
        int pecaJogavel = -1;
        char ladoJogavel = 'V';

        // Verifique se o computador tem uma peca jogavel
        for (int i = 0; i < 28; i++)
        {
            if (peca[i].status == '2' &&
                (peca[i].lado1 == mesa[0].ladoE || peca[i].lado2 == mesa[0].ladoE ||
                 peca[i].lado1 == mesa[tamanho - 1].ladoD || peca[i].lado2 == mesa[tamanho - 1].ladoD))
            {
                pecaJogavel = i;
                break;
            }
        }

        if (pecaJogavel != -1)
        {
            // Encontrou uma peca jogavel, determine o lado e jogue
            if (peca[pecaJogavel].lado1 == mesa[0].ladoE)
            {
                ladoJogavel = 'E';
            }
            else if (peca[pecaJogavel].lado2 == mesa[0].ladoE)
            {
                ladoJogavel = 'E';
            }
            else if (peca[pecaJogavel].lado1 == mesa[tamanho - 1].ladoD)
            {
                ladoJogavel = 'D';
            }
            else if (peca[pecaJogavel].lado2 == mesa[tamanho - 1].ladoD)
            {
                ladoJogavel = 'D';
            }

            // Jogue a peca encontrada
            fJogar(pecaJogavel, ladoJogavel);
        }
        else
        {
            // Não encontrou uma peca jogavel, tente comprar uma
            int pecasDisponiveis = 0;

            for (int i = 0; i < 28; i++)
            {
                if (peca[i].status == '0')
                {
                    pecasDisponiveis = 1;
                    break;
                }
            }

            if (pecasDisponiveis)
            {
                fComprar(jvez);
            }
            else
            {
                // Se não houver pecas disponiveis para comprar, verifique se o jogador 1 tambem nao tem pecas jogaveis
                int jogador1SemPecasJogaveis = 1;
                for (int i = 0; i < 28; i++)
                {
                    if (peca[i].status == '1' &&
                        (peca[i].lado1 == mesa[0].ladoE || peca[i].lado2 == mesa[0].ladoE ||
                         peca[i].lado1 == mesa[tamanho - 1].ladoD || peca[i].lado2 == mesa[tamanho - 1].ladoD))
                    {
                        jogador1SemPecasJogaveis = 0;
                        break;
                    }
                }

                if (jogador1SemPecasJogaveis)
                {
                    int resultadoDesempate = fDesempate();
                    if (resultadoDesempate != 0)
                    {
                        if (resultadoDesempate == 1)
                        {
                            fApresentaMensagem("O jogador 1 venceu.\n");
                            fExecutarMenu();
                        }
                        else if (resultadoDesempate == 2)
                        {
                            fApresentaMensagem("O jogador 2 venceu.\n");
                            fExecutarMenu();
                        }
                    }
                }
                //fExecutarMenu(); // Ambos os jogadores nao tem pecas jogaveis, termine o jogo ou realize outra acao adequada
                // Voce pode adicionar o codigo apropriado aqui
                else
                {
                    // Passe o jogo para o jogador 1
                    jvez = '1';
                }

                break;
            }
        }
    }
}


void fExecutarMenu()
{
    int opc1;
    int modoDeJogo = 0; // 0 para modo de jogo contra o computador, 1 para modo de jogo de dois jogadores
			//opcoes do menu geral 
    do
    {
        opc1 = fMenuGeral();

        switch (opc1)
        {
        case 1:
            // Código para iniciar um novo jogo de dois jogadores
            modoDeJogo = 1;
            system("cls");
            fIniciarPecas();
            fEmbaralhar();
            fDistribuirPecas();
            fPrimeiraJogada();
            fTrocaJogador();
            fMenuJogo();
            break;

        case 2:
            // Código para iniciar um novo jogo contra o computador
            modoDeJogo = 0;
            system("cls");
            fIniciarPecas();
            fEmbaralhar();
            fDistribuirPecas();
            fPrimeiraJogada();
            fTrocaJogador();
            if (jvez == '2')
            {
                fComputador();
                fApresentaMensagem("O jogador 1 comecou jogando");
            }
            fMenuJogoComputador();
            break;

        case 3:
            system("cls");
			
			if (fDesempate()==0)
			{
				
            	if (modoDeJogo == 0)
            	{
                // Modo de jogo contra o computador
                	fMenuJogoComputador();
                	fApresentaMensagem("Modo de jogo: Contra o computador");
            	}
            	else if (modoDeJogo == 1)
            	{
                // Modo de jogo de dois jogadores
                	fMenuJogo();
                	fApresentaMensagem("Modo de jogo: Dois jogadores");
            	}
			}
			else
			{
				fApresentaMensagem("O jogo terminou.Nao sera recuperado");
				fExecutarMenu();
			}
            break;

        case 4: //mostra regras do jogo
            system("cls");
            fRegras();
            break;

        case 5: //salva a partida
            system("cls");
            fGravaCadastro();
            break;

        case 6: //recupera partida anteriormente salva 
            system("cls");
            fRecuperaCadastro();
            break;
        }

    } while (opc1 != 7);
}


void fMenuJogo()//menu do jogo entre dois jogadores
{
    int opc2, pj;

    do
    {
        opc2 = fMenuDois();
        switch (opc2)
        {
        case 1:		//case de jogar a peca 
        	
            system("cls");
            fApresentaMesa();
            fApresentaPeca();
            fJogoContraDois();
            break;
        case 2:		//Case de comprar  novas pecas 
            system("cls");
            fComprar(jvez);
            break;

        case 3: 	//case de passar a vez ao outro jogador 
            system("cls");
            fPassar();
            break;

        case 4: //case de sair da partida 
            system("cls");
            fExecutarMenu();
            break;
        }
    } while (opc2 != 4);
}

void fMenuJogoComputador() //menu do jogo contra computador
{
    int opc3;
    do
    {
        opc3 = fMenuComputador();

        switch (opc3)
        {
        case 1: //case de jogar a peca
    
            system("cls");
            fApresentaMesa();
            fApresentaPeca();
            fJogoContraDois(); 
            fComputador();
            break;
            
        case 2: // case de comprar novas pecas
            system("cls");
            fComprar(jvez);
            break;
            
		      
        case 4: //case de  sair da partida 
            system("cls");
            fExecutarMenu();
            break;
            
       	case 3: //case de passar a vez ao outro jogador 
       		system("cls");
       		fPassar();
       		break;
        }
    } while (opc3 != 4);
}
