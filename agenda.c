//Bianca Dias Barbosa e Henrique Marciano da Silva - BSI 2018
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

typedef struct reg *no;

typedef struct {
	int dia;
	int mes;
	int ano;
} d;

typedef struct {
	int hora;
	int minuto;
}h;

struct reg {
	d data;
	//h horario;
	//char compromisso[81];
	no prox;
};

void cria_lista(no *agenda) {
	*agenda = NULL;
}

void hideCursor();
void showCursor();
void gotoxy (int x, int y);
void sair ();
void sobre();
void ajuda();
void menu ();
void moldura();
void menuBoasVindas();

void hideCursor(){
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void showCursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x,int y){
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y}); //posiciona cursor na tela
}

void sair(){
	system("cls");
	gotoxy(40,2);printf("Obrigada por utilizar nosso sistema!\n");
	exit(0); // força o fechamento do programa;
}

void sobre(){
	int tecla = 32;
	system("cls");
	moldura();
	gotoxy(55,2);printf("SOBRE - BICK AGENDA");
	printf("\n\n\tTrabalho de listas desenvolvido por Bianca Dias e Henrique Marciano (ou simplesmente casal)\n\t");
	printf("\n\tDisciplina: Algoritmos II\n\t");
	printf("\n\tProfessora: Andrea");
	printf("\n\n\t\t\t\tBSI - 2018");
	printf("\n\n\n\t<ESC> Voltar ao menu principal.");

	tecla = getch();

	while(tecla!=27){
		tecla = getch();
	}

	if(tecla == 27)
		menu();
}

void ajuda(){
	gotoxy(55,20);printf("AJUDA - BICK AGENDA");
	gotoxy(10,21);printf("Utilize as setas do seu teclado para mover o quadradinho para cima ou para baixo.");
	gotoxy(10,22);printf("Para escolher uma opcao, aperte ENTER.");
	gotoxy(10,23);printf("Para finalizar o programa, aperte ESC");
	gotoxy(10,24);printf("O sistema possibilita o cadastro, exclusao e consulta de compromissos");
	gotoxy(10,25);printf("Nao esqueca de salvar os seus dados no disco para que nao sejam perdidos!");
}

void menu(){
	system("cls");
	moldura();
	int primeiraVez = 1;
	FILE *arquivo;
	int tecla;
	int cont = 0;
	int cheque;

	hideCursor();
	
	// Verifica se o usuário já tem compromissos cadastrados
	if ((arquivo = fopen("agenda.txt", "rb")) != NULL) {
		primeiraVez = 0;
	}
	fclose(arquivo);
				
	gotoxy(55,2);printf("BICK AGENDA");
	gotoxy(8,4);printf("%c",254);
	gotoxy(10,4);printf("Insere compromisso");
	gotoxy(10,6);printf("Remove compromissos");
	gotoxy(10,8);printf("Consulta compromissos");
	gotoxy(10,10);printf("Consulta compromisso por palavra");
	gotoxy(10,12);printf("Salva compromissos no disco");
	gotoxy(10,14);printf("Le compromissos do disco");
	gotoxy(10,16);printf("Sobre");
	gotoxy(10,18);printf("<ESC> Sair");
	gotoxy(30,18);printf("<SPACE> Ajuda");

   	while(tecla!=27){
   		gotoxy(10,14);tecla = getch();

   		if(tecla == 80 && cont<=10){ // para baixo
   			gotoxy(8,4+cont);printf("  ");
   			cont+=2;
			gotoxy(8,4+cont);printf("%c",254);
		}

		if(tecla == 72 && cont>0){ // para cima
   			gotoxy(8,4+cont);printf("  ");
   			cont-=2;
			gotoxy(8,4+cont);printf("%c",254);
		}

		if(tecla == 13){
			switch(cont){
				case 0:
					cheque = 0;
					// calculaNotasEMoedas(cheque);
					break;
				case 2:
					cheque = 1;
					// calculaNotasEMoedas(cheque);
					break;
				case 12:
					sobre();
					break;
			}
		}

		if(tecla==32){
			ajuda();
		}
	}

	sair();
}

void moldura(){ //desenha a moldura
	int a;
	unsigned char caracter=178;
	int i = 30, j = 130;
	system("cls");
	//parede de cima horizontal
	for(a=0;a<j+1;a++){
		gotoxy(a,0);
		printf("%c",caracter);
	}

	//parede da direita vertical
	for(a=1;a<i;a++)
    {
        gotoxy(j,a);
        printf("%c",caracter);
    }

    //parede de baixo horizontal
    for(a=j;a>=0;a--)
    {
        gotoxy(a,i);
        printf("%c",caracter);
    }

    //parede da esquerda vertical
    for(a=i;a>0;a--)
    {
       	gotoxy(0,a);
        printf("%c",caracter);
    }
}

void menuBoasVindas(){
	char tecla;
	int aux = 1;
	int tent = 1;
	int i;
	
	moldura();
	gotoxy(50,10);printf("Bem-vindo a Bick Agenda");
	gotoxy(25,13);printf("Na Bick Agenda, voce pode cadastrar e visualizar todos os seus compromissos.");
	gotoxy(38,14);printf("Para administrar seu tempo, eh so com Bick Agenda!");
	gotoxy(40,20);printf("Pressione qualquer tecla para continuar...");
	hideCursor();
	if(tecla = getch()){
		system("cls");
		moldura();
		for(i=3;i>0;i--){
			if(i==3){
				gotoxy(50,15);printf("Carregando compromissos...    ");
			} else if(i==2){
				gotoxy(50,15);printf("Montando o layout...          ");
			} else if(i=1){
				gotoxy(50,15);printf("Finalizando carregamento...    ");
			}
			Sleep(1000);
		}
		menu();
	}
}

int main(){
	system("mode con:cols=131 lines=31");
	menuBoasVindas();
}
