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
	h horario;
	char compromisso[81];
	no prox;
};

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

void cria_lista(no *agenda) {
	*agenda = NULL;
}

void zera_lista(no *agenda){
	no p = *agenda;
	no q;
	while(p != NULL){
		q = p;
		free(q);
		q = NULL;
		p = p->prox;
	}
}

int retorna_data(d data, d agenda) {
	int data1 = data.ano*10000 + data.mes*100 + data.dia;
	int data2 = agenda.ano*10000 + agenda.mes*100 + agenda.dia;
	
	if(data1 < data2) {
	    return 0;
	}
	else if(data1 > data2) {
	        return 1;
	}
	else if(data1 == data2) {
		return 2;
	}
}

int retorna_horario(h horario, h agenda) {
	int h1 = horario.hora*60 + horario.minuto;
	int h2 = agenda.hora*60 + agenda.minuto;
	
	if(h1 < h2) {
		return 0;
	}
	else if(h1 >= h2) {
		return 1;
	}
}

void insere_data(no *agenda, char compromisso[], d data, h horario) {
	no p = (no) malloc (sizeof(struct reg));
	p->data = data;
	p->horario = horario;
	fflush(stdin);
	strcpy(p->compromisso, compromisso);
	
	if(*agenda == NULL) { //lista vazia
		p->prox = *agenda;
		*agenda = p;
		return;
	}
	else { 
		if(retorna_data(data, (*agenda)->data) == 0) { //data inserida < data da agenda
			p->prox = *agenda;
			*agenda = p;
			return;
		}
		no q = *agenda, r;
		while(q != NULL) {
			if(retorna_data(data, q->data) == 1) {
				r = q;
				q = q->prox;
			}
			else {
				if(retorna_data(data, q->data) == 2) {
					if(retorna_horario(horario, q->horario) == 1) {
						r = q;
						q = q->prox;
						
					}	
				}
				if(q == NULL || retorna_horario(horario, q->horario) == 0) {
					r->prox = p;
					p->prox = q;
					return;
				}
			}
			if(q == NULL || retorna_data(data, q->data) == 0) {
				r->prox = p;
				p->prox = q;
				return;
			}

		}
	}
}

void mostra_lista(no agenda) {
	system("cls");
	moldura();
	hideCursor();
	int tecla;
	
	gotoxy(45,2);printf("BICK AGENDA - CONSULTA\n\t");
	
	if(agenda == NULL) {
		printf("\n\tVoce nao tem nenhum compromisso na sua agenda! Que tal adicionar algum?");
	}
	else {
		no p = agenda;
		while(p != NULL) {
			printf("\n");
			printf("\t%d/", p->data.dia);
			printf("%d/", p->data.mes);
			printf("%d ", p->data.ano);
			printf("-- %dh%dmin", p->horario.hora, p->horario.minuto);
			printf(" -- %s", p->compromisso);
			p = p->prox;
		}
	}
	printf("\n\n\n\t<ESC> Voltar ao menu principal.");
	tecla = getch();
	while(tecla!=27){
		tecla = getch();
	}
	if(tecla == 27)
		menu(&agenda);
}

void mostra_lista_palavra(no agenda) {
	system("cls");
	moldura();
	int tecla;
	char palavra[80];
	int passou = 0;
	
	gotoxy(45,2);printf("BICK AGENDA - CONSULTA POR PALAVRA\n\t");
	
	if(agenda == NULL) {
		printf("\n\tVoce nao tem nenhum compromisso na sua agenda! Que tal adicionar algum?");
	}
	else {
		showCursor();
		printf("\n\t Por favor, digite a palavra que deseja procurar nos seus compromissos: ");
		fflush(stdin);
		gets(palavra);
		no p = agenda;
		hideCursor();
		while(p != NULL) {
			if(strstr((p->compromisso), palavra) != NULL){ // tem a palavra aqui dentro
				passou = 1;
				printf("\n");
				printf("\t%d/", p->data.dia);
				printf("%d/", p->data.mes);
				printf("%d ", p->data.ano);
				printf("-- %dh%dmin", p->horario.hora, p->horario.minuto);
				printf(" -- %s", p->compromisso);
			}
			p = p->prox;
		}
	}
	if(!passou){
		printf("\n\t Nao existe nenhum registro com a palavra digitada.");
	}
	printf("\n\n\n\t<ESC> Voltar ao menu principal.");
	tecla = getch();
	while(tecla!=27){
		tecla = getch();
	}
	if(tecla == 27)
		menu(&agenda);
}

void insere_compromisso(no *agenda){
	showCursor();
	char resp, compromisso[81];
	d data;
	h horario;
	no q = *agenda;
	do {
		system("cls");
		moldura();
		gotoxy(45,2);printf("BICK AGENDA - INSERE COMPROMISSO\n\t");
		printf("--- Data ---\n");
		do {
			printf("\tDia: ");
			scanf("%d", &data.dia);	
		} while(data.dia <0 || data.dia > 31);	
		do {
			printf("\tMes: ");
			scanf("%d", &data.mes);	
		} while(data.mes < 1 || data.mes > 12 || (data.mes == 2 && data.dia > 29));	
		do {
			printf("\tAno: ");
			scanf("%d", &data.ano);	
		} while(data.ano < 0 || data.ano > 2050);
		printf("\n\t--- Horario ---\n");
		do {
			printf("\tHora: ");
			scanf("%d", &horario.hora);	
		} while(horario.hora < 0 || horario.hora > 23);
		do {
			printf("\tMinuto: ");
			scanf("%d", &horario.minuto);	
		} while(horario.minuto < 0 || horario.minuto > 59);
		printf("\n\t--- Compromisso ---\n");
		do {
			printf("\tDigite o compromisso: ");
			fflush(stdin);
			gets(compromisso);	
		} while(strlen(compromisso) > 80 || strlen(compromisso) == 0);
		
		insere_data(&q, compromisso, data, horario);
		printf("\n\tInserir nova data? (S/N): ");
		do {
			fflush(stdin);
			scanf("%c", &resp);
			resp = toupper(resp);	
		} while(resp != 'S' && resp != 'N');		
	} while(resp == 'S');
	menu(&q);
}

void sair(){
	system("cls");
	gotoxy(40,2);printf("Obrigada por utilizar Bick Agenda!\n");
	exit(0); // força o fechamento do programa;
}

void sobre(no agenda){
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
		menu(&agenda);
}

void ajuda(){
	gotoxy(55,20);printf("AJUDA - BICK AGENDA");
	gotoxy(10,21);printf("Utilize as setas do seu teclado para mover o quadradinho para cima ou para baixo.");
	gotoxy(10,22);printf("Para escolher uma opcao, aperte ENTER.");
	gotoxy(10,23);printf("Para finalizar o programa, aperte ESC");
	gotoxy(10,24);printf("O sistema possibilita o cadastro, exclusao e consulta de compromissos");
	gotoxy(10,25);printf("Nao esqueca de salvar os seus dados no disco para que nao sejam perdidos!");
}

void salva_disco(no agenda){
  system("cls");
  moldura();
  hideCursor();
  FILE *arquivo;
  int tecla;
  // Abertura do arquivo
  gotoxy(55,2);printf("SALVAR NO DISCO - BICK AGENDA");
  // Leitura dos registros e gravacao
  if(agenda == NULL) {
  	printf("\n\n\tVoce nao tem nenhum compromisso na sua agenda! Que tal adicionar algum?");
  } else {
  	if ((arquivo = fopen("agenda.txt", "r+w")) == NULL) {
		 if ((arquivo = fopen("agenda.txt", "w")) == NULL) {
		      printf ("\nErro da abertura do arquivo.\n\n");
		      return;
		 }    
	} else {
		fseek (arquivo, 0, SEEK_END); // Arquivo existe e posiciono o ponteiro no final do arquivo
	}
  	no p = agenda;
  	fflush (stdin); // "Limpa" o buffer de entrada - teclado
	while(p != NULL) {
		printf("\n");
		printf("\t%d/", p->data.dia);
		printf("%d/", p->data.mes);
		printf("%d ", p->data.ano);
		printf("-- %dh%dmin", p->horario.hora, p->horario.minuto);
		printf(" -- %s", p->compromisso);
		fprintf(arquivo,"%d %d %d %d %d \n %s \n",p->data.dia, p->data.mes,p->data.ano,p->horario.hora,p->horario.minuto, p->compromisso); 
		p = p->prox;
	}
	printf("\n\n\t Dados salvos com sucesso!");
	zera_lista(&agenda);
  	fclose (arquivo);
  }   
  printf("\n\n\n\t<ESC> Voltar ao menu principal.");

  tecla = getch();

  while(tecla!=27){
	tecla = getch(); 
  }

  if(tecla == 27)
	menu(&agenda);  
}     

void le_disco(no agenda){
  FILE *arquivo;
  int tecla = 32;
  system("cls");
  moldura();
  hideCursor();
  gotoxy(50,2);printf("ARQUIVOS DO DISCO - BICK AGENDA");
  // Abertura do arquivo
  if ((arquivo = fopen("agenda.txt", "r")) == NULL) {
    printf ("\n\n\tNao existe nenhum dado armazenado no disco. Que tal adicionar?\n\n");
  } else {
  	  int dia, mes, ano, hora, minuto;
  	  char compromisso[81];
	  // Leitura dos registros 
	  printf("\n");
	  while (fscanf (arquivo,"%d %d %d %d %d ",&dia, &mes, &ano, &hora, &minuto) != EOF) {
	  		fgets(compromisso,80,arquivo);
			printf("\t%d/", dia);
			printf("%d/", mes);
			printf("%d ", ano);
			printf("-- %dh%dmin", hora, minuto);
			printf(" -- %s", compromisso);
	  }
	  fclose (arquivo);
  }
  printf("\n\n\n\t<ESC> Voltar ao menu principal.");

  tecla = getch();

  while(tecla!=27){
	tecla = getch(); 
  }

  if(tecla == 27)
	menu(&agenda);
}

void menu(no *agenda){
	system("cls");
	moldura();
	int primeiraVez = 1;
	int tecla;
	int cont = 0;
	no q = *agenda;
	
	hideCursor();
				
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
					insere_compromisso(&q);
					break;
				case 2:
					//remover compromisso
					break;
				case 4:
					mostra_lista(q);
					break;
				case 6:
					mostra_lista_palavra(q);
					break;
				case 8:
					salva_disco(q);
					break;
				case 10:
					le_disco(q);
					break;
				case 12:
					sobre(q);
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
	no agenda;
	cria_lista(&agenda);
	
	moldura();
	gotoxy(50,10);printf("Bem-vindo a Bick Agenda");
	gotoxy(25,13);printf("Na Bick Agenda, voce pode cadastrar, visualizar e remover seus compromissos.");
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
		menu(&agenda);
	}
}

int main(){
	system("mode con:cols=131 lines=31");
	menuBoasVindas();
}
