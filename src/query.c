#include <string.h>
#include "query.h"
#include "estado.h"
#include "utils.h"
#include <stdio.h>

#define MAX_BUFFER		10240
#define CMP(str)		else if(strcmp(buffer, str) == 0)

ESTADO inicializar();

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

	e->jog.x += dx;
	e->jog.y += dy;
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

	ESTADO novo = inicializar();
	*e = novo;
	e->jog.x = dx;
	e->jog.y = dy;
	return 1;
}

int parse_query(const char* query_string, ESTADO* e)
{
	if (e == NULL)
	{
		return 0;
	}

	if (query_string == NULL || strlen(query_string) == 0)
	{
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

	if (strlen(query_string) <= param_size)
	{
		return 0;
	}

	const char* params_start = end_param_name + 1;

	/* Buffer contains the action name */
	if (strcmp(buffer, "move") == 0)
	{
		return parse_move_action(params_start, e);
	}
	CMP("attack")
	{
		print_debug("implementation needed");
	}
	CMP("exit")
	{
		return parse_exit_action(params_start, e);
	}
	return 0;
}


void create_move_query(int dx, int dy, char* destination)
{
	sprintf(destination, "http://localhost/cgi-bin/jogo.cgi?move&x=%d&y=%d", dx, dy);
}


void create_exit_query(char* destination)
{
	sprintf(destination, "http://localhost/cgi-bin/jogo.cgi?exit&x=%d&y=%d", PLAYER_START_X, PLAYER_START_Y);
}