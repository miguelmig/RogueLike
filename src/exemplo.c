#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cgi.h"
#include "estado.h"
#include "map.h"
#include "time.h"
#include "utils.h"
#include "query.h"

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

ESTADO inicializar(int level) {
	ESTADO e = {{0}};
	e.gameSeed = (unsigned int)time(0);
	srand(e.gameSeed);

	e.jog.x = PLAYER_START_X;
	e.jog.y = PLAYER_START_Y;

	e.exit.x = 5;
	e.exit.y = 0;
	e.level = level;

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

	int num_obstacles = random_number(MIN_OBSTACLES, MAX_OBSTACLES - 1);
	// Generate obstacles coords
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

	int x, y;
	for (y = 0; y < TAM; y++)
	{
		for (x = 0; x < TAM; x++)
		{
			CellTypes cell_type = getCellTypeAtPosition(&e, x, y);
			TileSets tileset = get_tileset_by_level(level);
			switch (cell_type)
			{
			case OBSTACLE:
				e.obstacleTextureOffset[x][y] = generateRandomObstacleOffset(tileset);
			default:
				e.tileTextureOffset[x][y] = generateRandomTileOffset(tileset);
				break;
			}
		}
	}

	return e;
}

void imprime_movimento(Orientations orientation, ESTADO e, int dx, int dy) {
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;
	char link[MAX_BUFFER];
	if(!posicao_valida(x, y))
		return;

	if (!posicao_livre(x, y, &e))
	{
		return;
	}
	create_move_query(dx, dy, link);
	//sprintf(link, "?%s", estado2str(novo));
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


void imprime_ataque(Orientations orientation, ESTADO e, int dx, int dy) 
{
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;
	char link[MAX_BUFFER];

	if (!posicao_valida(x, y) || posicao_livre(x, y, &e) || getCellTypeAtPosition(&e, x, y) != ENEMY)
	{
		return;
	}

	create_attack_query(dx, dy, link);
	//sprintf(link, "?%s", estado2str(novo));
	create_attack_link(orientation, x, y, link);
}
void imprime_ataques(ESTADO e)
{
	imprime_ataque(UP, e, 0, -1);

	imprime_ataque(DOWN, e, 0, +1);

	imprime_ataque(LEFT, e, -1, 0);

	imprime_ataque(RIGHT, e, +1, 0);
}

void imprime_jogador(ESTADO e) {
	IMAGEM(e.jog.x, e.jog.y, ESCALA, "DwellerN_03.png");
	imprime_movimentos(e);
	imprime_ataques(e);
}

void imprime_saida(ESTADO e)
{
	if (abs(e.jog.x - e.exit.x) + abs(e.jog.y - e.exit.y) <= 1)
	{
		char link[MAX_BUFFER];
		/*
		ESTADO novo = inicializar();
		sprintf(link, "?%s", estado2str(novo));
		*/
		create_exit_query(link);
		ABRIR_LINK_ADV(link, "exit", "exit");
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
		return inicializar(1);
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

ESTADO obter_estado()
{
	ESTADO e = {{0}}; 
	int file_exists = read_state_from_file(STATE_FILE_NAME, &e);
	if (!file_exists)
	{
		e = inicializar(1);
		output_state_to_file(&e, STATE_FILE_NAME);
	}

	return e;
}

void imprimir_butao_restart()
{
	printf("<button type=\"button\" id=restart >Restart</button>\n");
}

void imprimir_score_board(int score)
{
	printf("<div id=\"scoreboard\"><span id=score>Pontuação: %d</span></div>\n",
		score); 
}

void mover_inimigos(ESTADO* e)
{
	int i, j;
	for (i = 0; i < e->num_inimigos; i++)
	{
		int directions[5][2] = {
			{ -1, 0 }, // Esquerda
			{ 1, 0 }, // Direita
			{ 0, 1 }, // Cima
			{ 0, -1 }, // Baixo
			{ 0, 0 } // Sem mexer
		};

		int x = e->inimigo[i].x;
		int y = e->inimigo[i].y;
		int available_directions = 5;
		for (j = 0; j < available_directions; j++)
		{
			int dx = directions[j][0];
			int dy = directions[j][1];

			int new_x = x + dx;
			int new_y = y + dy;

			if (posicao_valida(new_x, new_y) == 0 || (posicao_livre(new_x, new_y, e) == 0 && !(new_y == y && new_x == x)))
			{
				for (int k = j; k < available_directions - 1; k++)
				{
					memcpy(directions[k], directions[k + 1], sizeof(int) * 2);
				}

				--available_directions;
				j--;
			}
		}

		// available_directions deve conter o numero de direcões validas para o inimigo se movimentar
		if (available_directions == 0)
			continue;

		// Debug
		/*
		print_debug("Available directions: \n");
		for (j = 0; j < available_directions; j++)
		{
			print_debug("(%d,%d) \t", directions[j][0], directions[j][1]);
		}
		*/

		float minDistance = TAM * TAM;
		int bestDirection = 0;
		for (j = 0; j < available_directions; j++)
		{
			int dx = directions[j][0];
			int dy = directions[j][1];
			int new_x = x + dx;
			int new_y = y + dy;
			int player_x = e->jog.x;
			int player_y = e->jog.y;

			dx = player_x - new_x;
			dy = player_y - new_y;
			float distance = sqrtf((float)dx * dx + dy * dy);

			if (minDistance > distance)
			{
				minDistance = distance;
				bestDirection = j;
			}
		}

		/*
		srand(time(0));
		int randomly_selected_direction = random_number(0, available_directions - 1);
		*/
		int dx = directions[bestDirection][0];
		int dy = directions[bestDirection][1];
		//print_debug("Best direction (%d, %d) \t Player Coordinates (%d,%d), ", dx, dy, e->jog.x, e->jog.y);

		//print_debug("selected random direction(%d) from available(%d), dx %d, dy %d\n", randomly_selected_direction, available_directions, dx, dy);

		int new_x = x + dx;
		int new_y = y + dy;

		e->inimigo[i].x = new_x;
		e->inimigo[i].y = new_y;
	}
}


int main() {
	int x, y;
	//ESTADO e = ler_estado(getenv("QUERY_STRING"));
	ESTADO e = obter_estado();
	
	COMECAR_HTML;
	int change_turn = 0;
	int state_changed = parse_query(getenv("QUERY_STRING"), &e, &change_turn);
	if (change_turn)
	{
		mover_inimigos(&e);
	}

	if (state_changed)
	{
		output_state_to_file(&e, STATE_FILE_NAME);
	}

	//print_debug("game seed: %u", e.gameSeed);
	INCLUIR_JQUERY;
	INCLUIR_SCRIPT("roguelike.js");
	INCLUIR_CSS("roguelike.css");

	printf("<body onLoad=\"load();\">\n");
	imprimir_score_board(e.score);
	ABRIR_SVG(TAM * ESCALA , TAM * ESCALA);
	for(y = 0; y < TAM; y++)
		for(x = 0; x < TAM; x++)
			imprime_casa(&e, x, y);

	imprime_inimigos(e);
	imprime_jogador(e);
	imprime_obstaculos(e);
	imprime_saida(e);
	FECHAR_SVG;

	imprimir_butao_restart();
	printf("</body>");

	
	return 0;
}
