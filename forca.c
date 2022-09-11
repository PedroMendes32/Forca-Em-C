#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"forca.h"

int main(void)
{
    setlocale(LC_ALL,"Portuguese");
    char escolha;

    printf("\n");
    forca();
    
    printf("\n - Você deseja adicionar mais uma palavra? (S/N): ");
    scanf(" %c",&escolha);
    
    escolha = toupper(escolha);
    
    if ( escolha == 'S' )
	{
		adicionaPalavra();
	}

    printf("\n\n\n");
    system("pause");

    return 0;
}

void forca ( void )
{   
    char palavra[30];
    char letras[26];
    int tentativas = 0;

    escolhePalavra(palavra);

    while ( (!venceu(letras,tentativas,palavra)) && (!enforcou(letras,tentativas,palavra)) )
    {   
        mostraInicio();
        desenhaForca(letras,tentativas,palavra);
        exibeForca(palavra,letras,tentativas);
        joga ( &tentativas, letras );
        system("cls");
    }

    if ( venceu(letras,tentativas,palavra) == 1 )
    {
        printf("\n\n Parabéns, você acertou a palavra! \n");
        
        mostraVitoria();
        printf("\n\n");
        system("pause");
    }
    else if ( enforcou(letras,tentativas,palavra) == 1)
    {	
        printf("\n\n - Ops!, você perdeu, a palavra era %s\n",palavra);
        
        mostraDerrota();
        printf("\n\n");
        system("pause");
    }
}

void joga ( int *tentativas, char letras[26] )
{   
    char letra;
    printf("\n\n - Digite uma letra: ");
    scanf(" %c",&letra);

    letras[(*tentativas)] = letra;
    (*tentativas)++;
}

void mostraInicio ( void )
{
    printf("###################\n");
    printf("#  JOGO DE FORCA  #\n");
    printf("###################\n");
    printf("\n\n\n");
}

int achouLetra ( int tentativas, char letras[26], char letra )
{
    int achou = 0;
    int j;

    for ( j = 0; j < tentativas; j++ )
    {
        if ( letras[j] == letra )
        {
            achou = 1;
            break;
        }
    }

    return achou;
}

void exibeForca ( char palavra[30], char letras[26], int tentativas )
{
    int achou = 0;
    int i;

    for ( i = 0; i < strlen(palavra); i++ )
    {
        achou = achouLetra(tentativas,letras,palavra[i]);

        if ( achou )
        {
            printf("%c ",palavra[i]);
        }
        else
        {
            printf("_ ");
        }
    }
}

void escolhePalavra ( char palavra[30] )
{   
    int qntdPalavras;
    int numAleatorio;
    int i;
    FILE *arquivo;

    arquivo = fopen("palavras.txt","r");
    fscanf(arquivo,"%d",&qntdPalavras);

    srand(time(NULL));

    numAleatorio = rand() % qntdPalavras;

    for ( i = 0; i <= numAleatorio; i++ )
    {
        fscanf(arquivo,"%s",palavra);
    }
    
    fclose(arquivo);
}

int enforcou ( char letras[26], int tentativas, char palavra[30] )
{
    int i,j;
    int existe, erros = 0;

    for ( i = 0; i < tentativas; i++ )
    {   
        existe = 0;

        for ( j = 0; j < strlen(palavra); j++ )
        {
            if ( letras[i] == palavra[j] )
            {
                existe = 1;
                break;
            }
        }
        if ( existe != 1 )
        {
            erros++;
        }
    }

    return erros >= 5;
}

int venceu ( char letras[26], int tentativas, char palavra[30] )
{
    int i, j;
    int acertos = 0;

    for ( i = 0; i < tentativas; i++ )
	{
		for ( j = 0; j < strlen(palavra); j++ )
		{
			if ( letras[i] == palavra[j] )
			{
				acertos++;
			}
		}
	}
	
	if ( acertos == strlen(palavra) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void adicionaPalavra ( void )
{
	char palavra[30];
	int qntd;
	
	FILE * arquivo;	
	
	if (( arquivo = fopen("palavras.txt","r+") ) == NULL)
	{	
		printf("\n - Não foi possível abrir o arquivo!");
		exit(1);
	}
	else
	{
		printf("\n - Digite a nova palavra: ");
		scanf("%s",palavra);
		
		fscanf(arquivo,"%d",&qntd);
		qntd++;
		
		fseek(arquivo,0,SEEK_SET);
		fprintf(arquivo,"%d",qntd);
		
		fseek(arquivo,0,SEEK_END);
		fprintf(arquivo,"\n%s",palavra);
		
		fclose(arquivo);
	}
}

void mostraDerrota ( void )
{
	printf("    _______________         \n");
	printf("   /               \\       \n"); 
	printf("  /                 \\      \n");
	printf("//                   \\/\\  \n");
	printf("\\|   XXXX     XXXX   | /   \n");
	printf(" |   XXXX     XXXX   |/     \n");
	printf(" |   XXX       XXX   |      \n");
	printf(" |                   |      \n");
	printf(" \\__      XXX      __/     \n");
	printf("   |\\     XXX     /|       \n");
	printf("   | |           | |        \n");
	printf("   | I I I I I I I |        \n");
	printf("   |  I I I I I I  |        \n");
	printf("   \\_             _/       \n");
	printf("     \\_         _/         \n");
	printf("       \\_______/           \n");
}

void mostraVitoria ( void )
{
	printf("       ___________      \n");
	printf("      '._==_==_=_.'     \n");
	printf("      .-\\:      /-.    \n");
	printf("     | (|:.     |) |    \n");
	printf("      '-|:.     |-'     \n");
	printf("        \\::.    /      \n");
	printf("         '::. .'        \n");
	printf("           ) (          \n");
	printf("         _.' '._        \n");
	printf("        '-------'       \n\n");
}

void desenhaForca ( char letras[26], int tentativas, char palavra[30] )
{
	int i, j;
	int erros = 0;
	int existe;
	
	for ( i = 0; i < tentativas; i++ )
	{	
		existe = 0;
		
		for ( j = 0; j < strlen(palavra); j++ )
		{
			if ( letras[i] == palavra[j] )
			{
				existe = 1;
				break;
			}
		}
		if ( !existe )
		{
			erros++;
			printf("  _______       \n");
			printf(" |/      |      \n");
			printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
			printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
			printf(" |       %c     \n", (erros>=2?'|':' '));
			printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
			printf(" |              \n");
			printf("_|___           \n");
			printf("\n\n");
		}
	}
}