#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"
#include "map.h"
#include "time.h"
#include "utils.h"

#define MAX_BUFFER		10240
#define TAM				10
#define ESCALA			40


int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}

void imprime_casa(int x, int y) {
	/*
	char *cor[] = {"#666600", "#555500"};
	int idx = (x + y) % 2;
	QUADRADO(x, y,ESCALA, cor[idx]);
	*/

	drawCell(EMPTY, x, y);
}

ESTADO inicializar() {
	ESTADO e = {{0}};
	e.jog.x = 5;
	e.jog.y = 9;
	e.num_inimigos = 3;
	e.inimigo[0].x = 3;
	e.inimigo[0].y = 2;
	e.inimigo[1].x = 7;
	e.inimigo[1].y = 3;
	e.inimigo[2].x = 4;
	e.inimigo[2].y = 5;
	e.num_obstaculos = 2;
	e.obstaculo[0].x = 8;
	e.obstaculo[0].y = 1;
	e.obstaculo[1].x = 4;
	e.obstaculo[1].y = 6;
	e.gameSeed = (unsigned int)time(0);
	return e;
}

void imprime_movimento(Orientations orientation, ESTADO e, int dx, int dy) {
	ESTADO novo = e;
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;
	char link[MAX_BUFFER];
	if(!posicao_valida(x, y))
		return;
	
	novo.jog.x = x;
	novo.jog.y = y;
	sprintf(link, "http://localhost/cgi-bin/jogo.cgi?%s", estado2str(novo));
	ABRIR_LINK(link);
	drawArrow(orientation, x, y);
	//imprime_casa(x, y);
	FECHAR_LINK;
}

void imprime_movimentos(ESTADO e) {
	imprime_movimento(UP, e,  0, -1);

	imprime_movimento(DOWN, e,  0, +1);

	imprime_movimento(LEFT, e, -1,  0);

	imprime_movimento(RIGHT, e, +1,  0);

}

void imprime_jogador(ESTADO e) {
	IMAGEM(e.jog.x, e.jog.y, ESCALA, "DwellerN_03.png");
	imprime_movimentos(e);
}

ESTADO ler_estado(char *args) {
	if (args == NULL || strlen(args) == 0)
	{
		return inicializar();
	}

	return str2estado(args);
}

void imprime_inimigos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_inimigos; i++)
		IMAGEM(e.inimigo[i].x, e.inimigo[i].y, ESCALA, "Driders_04.png");
}

void imprime_obstaculos(ESTADO e) {

	int i;
	for (i = 0; i < e.num_obstaculos; i++)
		//IMAGEM(e.obstaculo[i].x, e.obstaculo[i].y, ESCALA, "lava_pool1.png");
		drawCell(OBSTACLE, e.obstaculo[i].x, e.obstaculo[i].y);
}

int main() {
	int x, y;
	ESTADO e = ler_estado(getenv("QUERY_STRING"));
	srand(e.gameSeed);

	COMECAR_HTML;
	//print_debug("game seed: %u", e.gameSeed);
	ABRIR_SVG(600, 600);
	for(y = 0; y < TAM; y++)
		for(x = 0; x < TAM; x++)
			imprime_casa(x, y);

	imprime_jogador(e);
	imprime_inimigos(e);
	imprime_obstaculos(e);

	FECHAR_SVG;
	
	return 0;
}
