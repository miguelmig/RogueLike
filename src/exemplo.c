#include <stdlib.h>
#include <string.h> // memcpy
#include <math.h> // for abs
#include <time.h> // for time

#include "cgi.h"
#include "estado.h"
#include "map.h"
#include "utils.h"
#include "query.h"
#include "pathfinding.h"

#define MAX_BUFFER		10240

int posicao_valida(int x, int y) 
{
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}

void imprime_casa(ESTADO* e, int x, int y) 
{
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
		if (e->inimigo[i].pos.x == x && e->inimigo[i].pos.y == y)
			return 0;
	}

	// Check against obstacles coords
	for (i = 0; i < e->num_obstaculos; ++i)
	{
		if (e->obstaculo[i].x == x && e->obstaculo[i].y == y)
			return 0;
	}

	// Check against potions coords
	for (i = 0; i < e->num_pocoes; ++i)
	{
		if (e->pocoes[i].x == x && e->pocoes[i].y == y)
			return 0;
	}

	// Check against player's coords
	if (x == e->jog.pos.x && y == e->jog.pos.y)
		return 0;

	// Check against exit's coords
	if (x == e->exit.x && y == e->exit.y)
		return 0;

	return 1;
}

ESTADO inicializar(int level) {
	ESTADO e = { 0 };
	e.gameSeed = (unsigned int)time(0);
	srand(e.gameSeed);

	e.jog.pos.x = PLAYER_START_X;
	e.jog.pos.y = PLAYER_START_Y;

	e.jog.current_health = PLAYER_MAX_HEALTH;
	e.jog.max_health = PLAYER_MAX_HEALTH;

	e.exit.x = EXIT_X;
	e.exit.y = EXIT_Y;
	e.level = level;

	int id = 0;
	TileSets tileset = get_tileset_by_level(level);

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

		e.inimigo[i].id = id;

		e.enemy_texture_offset[id++] = generate_random_enemy_offset(tileset);
		e.inimigo[i].pos.x = x;
		e.inimigo[i].pos.y = y;
	}

	int num_obstacles = random_number(MIN_OBSTACLES, MAX_OBSTACLES - 1);
	// Generate obstacles coords

	int walkableGrid[TAM][TAM];
	int j;
	for (i = 0; i < TAM; i++)
	{
		for (j = 0; j < TAM; j++)
		{
			walkableGrid[i][j] = 1;
		}
	}


	for (i = 0; num_obstacles != 0; num_obstacles--, e.num_obstaculos++, i++)
	{
		int x = random_number(0, TAM - 1);
		int y = random_number(0, TAM - 1);

		// re-randomize coordinates until they are free

		walkableGrid[x][y] = 0;
		while (posicao_livre(x, y, &e) == 0 || exists_path(e.jog.pos.x, e.jog.pos.y, e.exit.x, e.exit.y, walkableGrid) == 0)
		{
			walkableGrid[x][y] = 1;
			x = random_number(0, TAM - 1);
			y = random_number(0, TAM - 1);
			walkableGrid[x][y] = 0;
		}

		e.obstaculo[i].x = x;
		e.obstaculo[i].y = y;
	}

	int max_health_potions = level - 1; 
	int num_potions = random_number(MIN_POCOES, max_health_potions);

	// Generate potions coords
	for (i = 0; num_potions != 0; num_potions--, e.num_pocoes++, i++)
	{
		int x = random_number(0, TAM - 1);
		int y = random_number(0, TAM - 1);
		// re-randomize coordinates until they are free
		while (posicao_livre(x, y, &e) == 0)
		{
			x = random_number(0, TAM - 1);
			y = random_number(0, TAM - 1);
		}

		e.pocoes[i].x = x;
		e.pocoes[i].y = y;
	}


	int x, y;
	for (y = 0; y < TAM; y++)
	{
		for (x = 0; x < TAM; x++)
		{
			CellTypes cell_type = get_cell_type_at_pos(&e, x, y);
			switch (cell_type)
			{
			case OBSTACLE:
				e.obstacle_texture_offset[x][y] = generate_random_obstacle_offset(tileset);
				break;
			default:
				break;
			}
			e.tile_texture_offset[x][y] = generate_random_tile_offset(tileset);
		}
	}

	return e;
}

void imprimir_health_bar(int current_health, int max_health)
{
	printf("<div class=\"health-bar\" data-total=\"%d\" data-value=\"%d\">\n",
		max_health, current_health);
	printf("<div class=\"bar\">\n");
	printf("<div class =\"hit\"></div>");
	printf("</div></div>\n");
}

void imprimir_dano(int damage)
{
	printf("<script>on_damage(%d);</script>\n", damage);
}


void imprime_movimento(Orientations orientation, ESTADO e, int dx, int dy) {
	int x = e.jog.pos.x + dx;
	int y = e.jog.pos.y + dy;

	static char link[MAX_BUFFER];
	if (!posicao_valida(x, y) || !posicao_livre(x, y, &e))
	{
		return;
	}

	create_move_query(dx, dy, link);
	create_arrow_link(orientation, x, y, link);
}

void imprime_movimentos(ESTADO e) {
	imprime_movimento(UP, e,  0, -1);

	imprime_movimento(DOWN, e,  0, +1);

	imprime_movimento(LEFT, e, -1,  0);

	imprime_movimento(RIGHT, e, +1,  0);

}


void imprime_ataque(Orientations orientation, ESTADO e, int dx, int dy) 
{
	int x = e.jog.pos.x + dx;
	int y = e.jog.pos.y + dy;
	static char link[MAX_BUFFER];

	if (!posicao_valida(x, y) || posicao_livre(x, y, &e) || get_cell_type_at_pos(&e, x, y) != ENEMY)
	{
		return;
	}

	create_attack_query(dx, dy, link);
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
	IMAGEM(e.jog.pos.x, e.jog.pos.y, ESCALA, PLAYER_IMAGE_FILE_NAME);
	imprime_movimentos(e);
	imprime_ataques(e);
}

void imprime_saida(ESTADO e)
{
	if (abs(e.jog.pos.x - e.exit.x) + abs(e.jog.pos.y - e.exit.y) <= 1)
	{
		char link[MAX_BUFFER];
		create_exit_query(link);
		ABRIR_LINK_ADV(link, "exit", "exit");
		IMAGEM(e.exit.x, e.exit.y, ESCALA, EXIT_IMAGE_FILE_NAME);
		FECHAR_LINK;
	}
	else
	{
		IMAGEM(e.exit.x, e.exit.y, ESCALA, EXIT_IMAGE_FILE_NAME);
	}

}

void imprime_inimigos(ESTADO e) {
	int i;
	for (i = 0; i < e.num_inimigos; i++)
	{
		draw_enemy(&e, e.inimigo[i].pos.x, e.inimigo[i].pos.y, e.inimigo[i].id);
	}
}

void imprime_obstaculos(ESTADO e) {

	int i;
	for (i = 0; i < e.num_obstaculos; i++)
	{
		draw_obstacle(&e, e.obstaculo[i].x, e.obstaculo[i].y);
	}
}

void imprime_pocoes(ESTADO* e)
{
	int i;
	for (i = 0; i < e->num_pocoes; i++)
	{
		int potion_x = e->pocoes[i].x;
		int potion_y = e->pocoes[i].y;
		int player_x = e->jog.pos.x;
		int player_y = e->jog.pos.y;
		if (abs(player_x - potion_x) + abs(player_y - potion_y) <= 1)
		{
			char link[MAX_BUFFER];
			int dx = potion_x - player_x;
			int dy = potion_y - player_y;
			create_potion_query(dx, dy, link);
			create_potion_link(potion_x, potion_y, link);
		}
		else
		{
			draw_potion_image(potion_x, potion_y);
		}
	}
}

#ifdef USE_COOKIES
ESTADO obter_estado(const char* cookies_string)
{
	ESTADO e = { 0 };
	if (cookies_string == NULL || strlen(cookies_string) == 0)
	{
		e = inicializar(1);
		output_state_to_cookie(&e);
		return e;
	}
	else
	{
		int cookie_exists = read_state_from_request_header(cookies_string, &e);
		if (!cookie_exists)
		{
			e = inicializar(1);
			output_state_to_cookie(&e);
			return e;
		}
	}

	srand(e.gameSeed);
	return e;
}
#else
ESTADO obter_estado()
{
	ESTADO e = {0};
	int file_exists = read_state_from_file(STATE_FILE_NAME, &e);
	if (!file_exists)
	{
		e = inicializar(1);
		output_state_to_file(&e, STATE_FILE_NAME);
	}
	else
	{
		srand(e.gameSeed);
	}

	return e;
}
#endif

void imprimir_butao_restart()
{
	printf("<button type=\"button\" id=restart >Restart</button>\n");
}

void imprimir_score_board(int* highscores, ESTADO* e)
{
	printf("<div id=\"scoreboard\">\n");
	printf("<div id=\"highscores\">\n");
	 
	printf("<span id=highscore_title>Pontuações Máximas</span>\n");  
	for (int i = 0; i < HIGHSCORE_SAVE_COUNT; i++)
	{
		printf("<span id=highscore%d class=text>%d</span>\n", i, highscores[i]);
	}
	printf("</div>\n");

	printf("<p id=score>Pontuação Atual: %d</p>\n",
		e->score); 

	printf("<p id=enemies>Inimigos Mortos: %d </p>\n",
		e->inimigos_mortos);

	printf("<p id=potions>Poções Usadas: %d </p>\n",
		e->pocoes_usadas);

	printf("</div>\n");

}

int ler_highscores(int* highscore_array)
{
	if (highscore_array == NULL)
	{
		return 0;
	}

	FILE* f = fopen(HIGHSCORES_FILE_NAME, "rb");
	if (f == NULL)
	{
		return 0;
	}

	static char buffer[MAX_BUFFER];
	int num_bytes_read = fread(buffer, sizeof(char), MAX_BUFFER, f);
	fclose(f);

	sscanf(buffer, "%d %d %d", &highscore_array[0], &highscore_array[1], &highscore_array[2]);
	return num_bytes_read;
}

void guardar_highscores(int* highscore_array)
{
	if (highscore_array == NULL)
	{
		return;
	}

	FILE* f = fopen(HIGHSCORES_FILE_NAME, "wb");
	if (f == NULL)
	{
		return;
	}

	static char buffer[MAX_BUFFER];
	int len = sprintf(buffer, "%d %d %d", highscore_array[0], highscore_array[1], highscore_array[2]);

	fwrite((const void*)buffer, sizeof(char), len, f);
	fclose(f);
}

void atacar_jogador(INIMIGO* enemy, ESTADO* e, int* damage_done)
{
	if (enemy == NULL || e == NULL)  
	{
		*damage_done = 0;
		return;
	}

	//int jogador_health = e->jog.current_health;
	*damage_done = MIN(PLAYER_MAX_HEALTH, e->level * 10);
	e->jog.current_health -= *damage_done;
}

void mover_inimigos(ESTADO* e, int* damage_done)
{
	int i;

	int player_x = e->jog.pos.x;
	int player_y = e->jog.pos.y;
	int walkableGrid[TAM][TAM];
	fill_matrix_from_estado(e, 1, walkableGrid);

	for (i = 0; i < e->num_inimigos; i++)
	{
		int x = e->inimigo[i].pos.x;
		int y = e->inimigo[i].pos.y;

		if (abs(player_x - x) + abs(player_y - y) <= 1)
		{
			// Can attack
			atacar_jogador(&e->inimigo[i], e, damage_done);
			continue;
		}

		/*

		int directions[5][2] = {
			{ -1, 0 }, // Esquerda
			{ 1, 0 }, // Direita
			{ 0, 1 }, // Cima
			{ 0, -1 }, // Baixo
			{ 0, 0 } // Sem mexer
		};

		int available_directions = 5;
		float minDistance = TAM * TAM;
		int bestDirection = 0;
		int found_available_move = 0;

		for (j = 0; j < available_directions; j++)
		{
			int dx = directions[j][0];
			int dy = directions[j][1];

			int new_x = x + dx;
			int new_y = y + dy;

			if ((posicao_valida(new_x, new_y) != 0 && posicao_livre(new_x, new_y, e) != 0) || (new_y == y && new_x == x))
			{
				found_available_move = 1;

				int new_dx = player_x - new_x;
				int new_dy = player_y - new_y;

				float distance = sqrtf((float)new_dx * new_dx + new_dy * new_dy);
				if (minDistance > distance)
				{
					minDistance = distance;
					bestDirection = j;
				}
			}
		}

		if (!found_available_move)
		{
			continue;
		}

		

		int optimal_dx = directions[bestDirection][0];
		int optimal_dy = directions[bestDirection][1];

		int new_x = x + optimal_dx;
		int new_y = y + optimal_dy;

		*/
		//fill_matrix_from_estado(e, 1, walkableGrid);
		Path* path = find_path(x, y, player_x, player_y, walkableGrid);
		if (path == NULL || path->prox == NULL)
		{
			continue;
		}

		POSICAO bestPosition = path->prox->pos;
		if (get_cell_type_at_pos(e, bestPosition.x, bestPosition.y) != EMPTY)
		{
			continue;
		}

		freePath(path);
		e->inimigo[i].pos = bestPosition;

		int new_x = bestPosition.x;
		int new_y = bestPosition.y;
		walkableGrid[new_x][new_y] = 0;
		walkableGrid[x][y] = 1;
	}
}

void highscore_update(int* highscores, int pos, int value)
{
	for (int i = pos; i < HIGHSCORE_SAVE_COUNT - 1; i++)
	{
		highscores[i + 1] = highscores[i];
	}
	highscores[pos] = value;
} 

void imprimir_game_over(ESTADO* e)
{
	printf("<script>on_game_over(%d)</script>", e->score);
}

void imprime_caminho_saida(ESTADO e)
{
	if (e.num_inimigos != 0)
	{
		return;
	}

	int walkableGrid[TAM][TAM];
	fill_matrix_from_estado(&e, 0, walkableGrid);
	Path* path = find_path(e.jog.pos.x, e.jog.pos.y, e.exit.x, e.exit.y, walkableGrid);

	for (; path != NULL; path = path->prox)
	{
		POSICAO pos = path->pos;
		QUADRADO_SEMI_TRANSPARENTE(pos.x, pos.y, ESCALA, "#32CD32", "0.5");
	}
	freePath(path);
}

int is_game_over(ESTADO* e)
{
	if (e == NULL)
	{
		return 1;
	}
	 
	return e->jog.current_health <= 0;
}

void on_game_over(ESTADO* e)
{
	if (e == NULL)
	{
		return;
	}


	int highscores[HIGHSCORE_SAVE_COUNT] = { 0 };
	ler_highscores(highscores);
	for (int i = 0; i < HIGHSCORE_SAVE_COUNT; i++)
	{
		if (e->score > highscores[i])
		{
			highscore_update(highscores, i, e->score);
			break;
		}
	}

	guardar_highscores(highscores);


	imprimir_game_over(e);

	// Clear the board
	*e = inicializar(1);
	output_state_to_file(e, STATE_FILE_NAME);
}

int main() {
	int x, y;

#ifdef USE_COOKIES
	const char *method_str = getenv("HTTP_COOKIE");
	ESTADO e = obter_estado(method_str);
#else
	ESTADO e = obter_estado();
#endif

	//exists_path(PLAYER_START_X, PLAYER_START_Y, EXIT_X, EXIT_Y, &e, walkableGrid);

	COMECAR_HTML;
	printf("<meta charset = \"UTF-8\">");
#ifdef USE_COOKIES
	print_debug("Request Header: \n %s ", method_str);
#endif
	int change_turn = 0;
	int state_changed = parse_query(getenv("QUERY_STRING"), &e, &change_turn);
	int damage_done = 0;
	if (change_turn)
	{
		mover_inimigos(&e, &damage_done);
	}

	if (state_changed)
	{
		output_state_to_file(&e, STATE_FILE_NAME);
	}

	//print_debug("game seed: %u", e.gameSeed);
	INCLUIR_JQUERY;
	INCLUIR_SCRIPT("roguelike.js");
	INCLUIR_CSS("roguelike.css");

	if (is_game_over(&e))
	{
		on_game_over(&e);
	}

	/* Pontuações */
	int highscores[HIGHSCORE_SAVE_COUNT] = { 0 };
	ler_highscores(highscores);


	printf("<body onLoad=\"load();\">\n");
	imprimir_score_board(highscores, &e);
	printf("<div class=center>");
	printf("<span id=level> Nível %d</span>", e.level); 
	ABRIR_SVG(TAM * ESCALA, TAM * ESCALA);
	for(y = 0; y < TAM; y++)
		for(x = 0; x < TAM; x++)
			imprime_casa(&e, x, y);

	imprime_caminho_saida(e);
	imprime_inimigos(e);
	imprime_jogador(e); 
	imprime_obstaculos(e);   
	imprime_pocoes(&e);
	imprime_saida(e);

	FECHAR_SVG;
	imprimir_health_bar(e.jog.current_health, e.jog.max_health);
	imprimir_butao_restart();
	printf("</div>"); 
	if (damage_done)
	{
		imprimir_dano(damage_done);
	}
	printf("</body>");

	return 0;
}
