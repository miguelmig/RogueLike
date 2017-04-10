#include <stdlib.h>
#include <string.h>

#include "cgi.h"
#include "estado.h"
#include "map.h"
#include "time.h"
#include "utils.h"

#define MAX_BUFFER		10240


int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}

void imprime_casa(ESTADO* e, int x, int y) {
	/*
	char *cor[] = {"#666600", "#555500"};
	int idx = (x + y) % 2;
	QUADRADO(x, y,ESCALA, cor[idx]);
	*/

	draw_tile(e, x, y);
}

int posicao_livre(int x, int y, ESTADO* e)
{
	if (e == NULL)
	{
		return 0;
	}

	int i;
	// Check against enemies coords
	for (i = 0; i < e->num_inimigos; ++i)
	{
		if (e->inimigo[i].x == x && e->inimigo[i].y == y)
			return 0;
	}

	// Check against obstacles coords
	for (i = 0; i < e->num_obstaculos; ++i)
	{
		if (e->obstaculo[i].x == x && e->obstaculo[i].y == y)
			return 0;
	}

	// Check against player's coords
	if (x == e->jog.x && y == e->jog.y)
		return 0;

	// Check against exit's coords
	if (x == e->exit.x && y == e->exit.y)
		return 0;

	return 1;
}
ESTADO inicializar() {
	ESTADO e = {{0}};
	e.gameSeed = (unsigned int)time(0);
	srand(e.gameSeed);

	e.jog.x = 5;
	e.jog.y = 9;

	e.exit.x = 5;
	e.exit.y = 0;

	int num_inimigos = random_number(MIN_ENEMIES, MAX_ENEMIES - 1);
	// Generate monster coords
	int i;
	for (i=0; num_inimigos != 0; num_inimigos--, e.num_inimigos++, i++)
	{
		int x = random_number(0, TAM - 1);
		int y = random_number(0, TAM - 1);
		// re-randomize coordinates until they are free
		while (posicao_livre(x, y, &e) == 0)
		{
			x = random_number(0, TAM - 1);
			y = random_number(0, TAM - 1);
		}

		e.inimigo[i].x = x;
		e.inimigo[i].y = y;
	}

	/*
	e.num_inimigos = 3;
	e.inimigo[0].x = 3;
	e.inimigo[0].y = 2;
	e.inimigo[1].x = 7;
	e.inimigo[1].y = 3;
	e.inimigo[2].x = 4;
	e.inimigo[2].y = 5;
	*/


	int num_obstacles = random_number(MIN_OBSTACLES, MAX_OBSTACLES - 1);
	// Generate monster coords
	for (i = 0; num_obstacles != 0; num_obstacles--, e.num_obstaculos++, i++)
	{
		int x = random_number(0, TAM - 1);
		int y = random_number(0, TAM - 1);
		// re-randomize coordinates until they are free
		while (posicao_livre(x, y, &e) == 0)
		{
			x = random_number(0, TAM - 1);
			y = random_number(0, TAM - 1);
		}

		e.obstaculo[i].x = x;
		e.obstaculo[i].y = y;
	}

	/*
	e.num_obstaculos = 2;
	e.obstaculo[0].x = 8;
	e.obstaculo[0].y = 1;
	e.obstaculo[1].x = 4;
	e.obstaculo[1].y = 6;
	*/

	int x, y;
	for (y = 0; y < TAM; y++)
	{
		for (x = 0; x < TAM; x++)
		{
			CellTypes cell_type = getCellTypeAtPosition(&e, x, y);
			switch (cell_type)
			{
			case OBSTACLE:
				e.obstacleTextureOffset[x][y] = generateRandomObstacleOffset();
			default:
				e.tileTextureOffset[x][y] = generateRandomTileOffset();
				break;
			}
		}
	}

	return e;
}

void imprime_movimento(Orientations orientation, ESTADO e, int dx, int dy) {
	ESTADO novo = e;
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;
	char link[MAX_BUFFER];
	if(!posicao_valida(x, y))
		return;

	if (!posicao_livre(x, y, &e))
	{
		return;
	}
	
	novo.jog.x = x;
	novo.jog.y = y;
	sprintf(link, "http://localhost/cgi-bin/jogo.cgi?%s", estado2str(novo));
	createArrowLink(orientation, x, y, link);
	/*
	ABRIR_LINK(link);
	drawArrow(orientation, x, y);
	//imprime_casa(x, y);
	FECHAR_LINK;
	*/
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

void imprime_saida(ESTADO e)
{
	if (abs(e.jog.x - e.exit.x) + abs(e.jog.y - e.exit.y) <= 1)
	{
		char link[MAX_BUFFER];
		ESTADO novo = inicializar();
		sprintf(link, "http://localhost/cgi-bin/jogo.cgi?%s", estado2str(novo));
		ABRIR_LINK(link);
		IMAGEM(e.exit.x, e.exit.y, ESCALA, "trapdoor1.png");
		FECHAR_LINK;
	}
	else
	{
		IMAGEM(e.exit.x, e.exit.y, ESCALA, "trapdoor1.png");
	}

}

ESTADO ler_estado(char *args) {
	if (args == NULL || strlen(args) == 0)
	{
		return inicializar();
	}

	ESTADO resultado = str2estado(args);
	srand(resultado.gameSeed);
	return resultado;
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
		draw_obstacle(&e, e.obstaculo[i].x, e.obstaculo[i].y);
}

int main() {
	int x, y;
	ESTADO e = ler_estado(getenv("QUERY_STRING"));

	COMECAR_HTML;
	//print_debug("game seed: %u", e.gameSeed);
	ABRIR_SVG(600, 600);
	for(y = 0; y < TAM; y++)
		for(x = 0; x < TAM; x++)
			imprime_casa(&e, x, y);

	imprime_jogador(e);
	imprime_inimigos(e);
	imprime_obstaculos(e);
	imprime_saida(e);

	FECHAR_SVG;
	
	return 0;
}
