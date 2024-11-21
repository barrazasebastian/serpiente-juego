#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

#define ARRIBA    72
#define IZQUIERDA 75
#define DERECHA   77
#define ABAJO     80
#define ESC       27

int cuerpo [200][2];
int n=1;
int tam=5;
int x=10,y=12;
int dir=3;
int xc=30,yc=15;
int velocidad=150,h=1;
int score=0;
int w=300;

char tecla;

void gotoxy(int x, int y)  {
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}
void OcultarCursor(){
    HANDLE hCon;
    COORD dwPos;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon,&cci);

}


void pintar(){
     // Líneas horizontales
     for(int i=2; i < 78; i++){
        gotoxy (i, 3); printf ("%c", 205);  // los números hacen referencia al código acsii
        gotoxy(i, 23); printf ("%c", 205);
     }
     //Líneas verticales
     for(int v=4; v < 23; v++){
        gotoxy (2,v);  printf ("%c", 186);
        gotoxy(77,v);  printf ("%c", 186);
     }
     // Esquinas
     gotoxy  (2,3);    printf ("%c", 201);
     gotoxy (2,23);    printf ("%c", 200);
     gotoxy (77,3);    printf ("%c", 187);
     gotoxy(77,23);    printf ("%c", 188);
}

void guardar_posicion(){
	cuerpo[n][0]=x;
	cuerpo[n][1]=y;
	n++;
	if(n==tam)n=1;
}

void dibujar_cuerpo(){
	for(int i=1;i<tam;i++){
		gotoxy(cuerpo[i][0],cuerpo[i][1]);printf("%c",15);
	}
}

void borrar_cuerpo(){
		gotoxy(cuerpo[n][0],cuerpo[n][1]);printf(" ");

}
void teclear(){
	if(kbhit()){
		tecla=getch();
		switch(tecla){
			case ARRIBA:
				if(dir!=2)
				   dir=1;
				   break;
		    case ABAJO:
		    	if(dir!=1)
			       dir=2;
				   break;
			case DERECHA:
				if(dir!=4)
				   dir=3;
				   break;
			case IZQUIERDA:
				if(dir!=3)
				   dir=4;
				   break;
		}
	}

}

void cambiar_velocidad(){
	if(score==h*20){
		velocidad-=10;
		h++;
	}
}

void comida(){
	if(x==xc&&y==yc){
		xc=(rand()%73)+4;
		yc=(rand()%19)+4;
		tam++;
		score+=10;
		gotoxy(xc,yc);printf("%c",4);

	}

}

bool game_over(){
	if(y==3||y==23||x==2||x==77)return false;
	for(int j=tam-1;j>0;j--){
		if(cuerpo[j][0]==x&&cuerpo[j][1]==y)
		return false;
	}
	return true;
}

void puntos(){
	gotoxy(3,1);printf("score 00%d",score);
}

bool win(){
	if(w==score)return false;
	return true;

	}
	void titulo(){
        printf("\n\n");
        printf("       \t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
        printf("       \t\t\t%c   ||           || %c\n",186,186);
        printf("       \t\t\t%c   || S.N.A.K.E || %c\n",186,186);
        printf("       \t\t\t%c   ||    V.2    || %c\n",186,186);
        printf("       \t\t\t%c   ||           || %c\n",186,186);
        printf("       \t\t\t%c    \\===========/  %c\n",186,186);
        printf("       \t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n", 200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
        printf("\t\t\t     JUEGO NO APTO\n");
        printf("\t\t            PARA EPILEPTICOS\n\n");
        printf("\t\t\t   **INSTRUCCIONES**\n\n");
        printf("        El juego termina al alcanzar 50 puntos \n");
        printf("        Debera recolectar la comida para acupumar puntos: %c\n",4);
        printf("        Pierdes al chocar con el limite del marco o con tu propio cuerpo!\n\t\t\t\tSUERTE!!\n\n");
        printf("        \n");
        printf("        Para moverte debes utilizar las flechas del teclado:\n\n");

        printf("\t\t\tPrecione enter para iniciar!!\n\n");

        system("pause>NULL");
        system("cls");


}

void game(){
	while(tecla!=ESC&&game_over()&& win()){
	puntos();
	borrar_cuerpo();
	guardar_posicion();
	dibujar_cuerpo();
	comida();

	teclear();
	teclear();

	if(dir==1)y--;
	if(dir==2)y++;
	if(dir==3)x++;
	if(dir==4)x--;
	Sleep(velocidad);

if ( !game_over()){
	MessageBox(NULL,"HAS PERDIDO","  GAME OVER", MB_OK);
	system("cls");
}
if ( !win()){
	MessageBox(NULL,"HAS GANADO","  WIN", MB_OK);
	system("cls");

}
}
}

int main(){
	titulo();
	pintar();
	gotoxy(xc,yc);printf("%c",4);
	game();

	system("pause>NULL");
	return 0;
}
