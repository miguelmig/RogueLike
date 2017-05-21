#include <string.h>
#include "query.h"
#include "estado.h"
#include "utils.h"
#include "map.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // abs

#define MAX_BUFFER		10240
#define CMP(str)		else if(strcmp(buffer, str) == 0)

ESTADO inicializar(int level);
void on_game_over(ESTADO* e);

int parse_move_action(const char* move_query_string, ESTADO* e)
{
	if (e == NULL)
	{
		return 0;
	}
	int dx, dy;
	int num_elements_filled = sscanf(move_query_string, "x=%d&y=%d", &dx, &dy);
	if (num_elements_filled != 2)
	{
		return 0;
	}

	if (abs(dx) + abs(dy) > 1)
	{
		return 0;
	}

	if (get_cell_type_at_pos(e, e->jog.pos.x + dx, e->jog.pos.y + dy) != EMPTY)
	{
		return 0;
	}

	e->jog.pos.x += dx;
	e->jog.pos.y += dy;
	return 1;
}

int parse_exit_action(const char* exit_query_string, ESTADO* e)
{
	if (e == NULL)
	{
		return 0;
	}
	int dx, dy;
	int num_elements_filled = sscanf(exit_query_string, "x=%d&y=%d", &dx, &dy);
	if (num_elements_filled != 2)
	{
		return 0;
	}

	ESTADO novo = inicializar(++e->level);
	novo.level = e->level;
	novo.score = e->score;
	*e = novo;
	e->jog.pos.x = dx;
	e->jog.pos.y = dy;
	return 1;
}

int parse_attack_action(const char* attack_query_string, ESTADO* e)
{
	if (e == NULL)
	{
		return 0;
	}
	int dx, dy;
	int num_elements_filled = sscanf(attack_query_string, "x=%d&y=%d", &dx, &dy);
	if (num_elements_filled != 2)
	{
		return 0;
	}

	int i;

	int command_x = e->jog.pos.x + dx;
	int command_y = e->jog.pos.y + dy;
	for (i = 0; i < e->num_inimigos; i++)
	{
		int monster_x = e->inimigo[i].pos.x;
		int monster_y = e->inimigo[i].pos.y;

		if (monster_x == command_x && command_y == monster_y)
		{
			update_enemy_array(e, i);
			return 1;
		}
	}

	return 0;
}

int parse_query(const char* query_string, ESTADO* e, int* change_turn)
{
	if (e == NULL || change_turn == NULL)
	{
		return 0;
	}

	if (query_string == NULL || strlen(query_string) == 0)
	{
		*change_turn = 0;
		return 0;
	}

	const char* end_param_name = strchr(query_string, '&');
	if (end_param_name == NULL)
	{
		end_param_name = query_string + strlen(query_string);
	}

	size_t param_size = end_param_name - query_string;

	static char buffer[MAX_BUFFER];
	memcpy(buffer, query_string, param_size);
	buffer[param_size] = '\0';

	if (strlen(query_string) < param_size)
	{
		*change_turn = 0;
		return 0;
	}

	const char* params_start = end_param_name + 1;

	/* Buffer contains the action name */
	if (strcmp(buffer, "move") == 0)
	{
		int ret = parse_move_action(params_start, e);
		*change_turn = ret;
		return ret;
	}
	CMP("attack")
	{
		int ret = parse_attack_action(params_start, e);
		*change_turn = ret;
		return ret;
	}
	CMP("exit")
	{
		*change_turn = 0; // When the player goes through the exit, don't change turn.
		return parse_exit_action(params_start, e);
	}
	CMP("restart")
	{
		on_game_over(e);
		ESTADO novo = inicializar(1);
		*e = novo;
		*change_turn = 0;
		return 1;
	}
	return 0;
}


void create_move_query(int dx, int dy, char* destination)
{
	sprintf(destination, "?move&x=%d&y=%d", dx, dy);
}


void create_exit_query(char* destination)
{
	sprintf(destination, "?exit&x=%d&y=%d", PLAYER_START_X, PLAYER_START_Y);
}


void create_attack_query(int dx, int dy, char* destination)
{
	sprintf(destination, "?attack&x=%d&y=%d", dx, dy);
}
