/**
  * @file constants.h
  * @brief Cont�m as demais constantes usadas ao longo do c�digo
*/
#pragma once

/** \brief N�mero minimo de inimigos por n�vel */
#define MIN_ENEMIES 5

/** \brief N�mero m�ximo de inimigos por n�vel */
#define MAX_ENEMIES 10

/** \brief N�mero minimo de obst�culos por n�vel */
#define MIN_OBSTACLES 10

/** \brief N�mero m�ximo de obst�culos por n�vel */
#define MAX_OBSTACLES 20

/** \brief Tamanho da grelha quadrada ( TAM x TAM ) */
#define TAM 10

/** \brief N�mero minimo de po��es por n�vel */
#define MIN_POCOES 0

/** \brief Largura e comprimento, em pixeis, de cada telha do mapa */
#define ESCALA 40

#ifdef _WIN32
/** \brief Nome do ficheiro onde ser� guardado o estado de jogo */
#define STATE_FILE_NAME "gamestate.txt"
#else
/** \brief Nome do ficheiro onde ser� guardado o estado de jogo */
#define STATE_FILE_NAME "/tmp/gamestate.txt"	
#endif

/** \brief Coordenada X inicial do jogador */
#define PLAYER_START_X 5

/** \brief Coordenada Y inicial do jogador */
#define PLAYER_START_Y 9

/** \brief Valor m�ximo de vida do jogador */
#define PLAYER_MAX_HEALTH 100

/** \brief Coordenada X da sa�da */
#define EXIT_X 5

/** \brief Coordenada Y da sa�da */
#define EXIT_Y 0

/** \brief Pontos ganhos pelo jogador quando um inimigo � morto, escala com o n�vel atual do jogo */
#define KILL_SCORE_BONUS 300

/** \brief Pontos ganhos pelo jogador quando sai do n�vel, escala com o n�vel atual do jogo */
#define NEW_LEVEL_SCORE_BONUS 500

/** \brief O n� de pontua��es m�ximas a guardar */
#define HIGHSCORE_SAVE_COUNT 3

/** \brief Nome do ficheiro onde v�o ser guardados os highscores */
#ifdef _WIN32
/** \brief Nome do ficheiro onde ser�o guardadas as pontua��es m�ximas */
#define HIGHSCORES_FILE_NAME "highscores.txt"
#else
/** \brief Nome do ficheiro onde ser�o guardadas as pontua��es m�ximas */
#define HIGHSCORES_FILE_NAME "/tmp/highscores.txt"
#endif

/** \brief Nome do ficheiro de imagem correspondente ao jogador */
#define PLAYER_IMAGE_FILE_NAME "DwellerN_03.png"

/** \brief Nome do ficheiro de imagem correspondente � saida */
#define EXIT_IMAGE_FILE_NAME "trapdoor1.png"

/** \brief Nome do ficheiro de imagem correspondente � saida */
#define POTION_IMAGE_FILE_NAME "health_potion.png"

/** \brief Quantidade de vida que uma po��o regenera */
#define POTION_HEALTH_AMOUNT 50

/** \brief Nome do cookie para guardar o estado */
#define COOKIE_NAME "gamestate"

/** \brief Tamanho m�ximo do header de cookie */
#define COOKIE_MAX_LENGTH 4096