#pragma once

#define MIN_ENEMIES 5
#define MAX_ENEMIES 10

#define MIN_OBSTACLES 10
#define MAX_OBSTACLES 20

/** \brief Tamanho da grelha quadrada ( TAM x TAM ) */
#define TAM 10

#define MIN_POCOES 0

#define ESCALA 40

#ifdef _WIN32
#define STATE_FILE_NAME "gamestate.txt"
#else
#define STATE_FILE_NAME "~/gamestate.txt"	
#endif

#define PLAYER_START_X 5
#define PLAYER_START_Y 9

#define PLAYER_MAX_HEALTH 100

#define EXIT_X 5
#define EXIT_Y 0


#define KILL_SCORE_BONUS 300
#define NEW_LEVEL_SCORE_BONUS 500

/** \brief O nº de pontuações máximas a guardar */
#define HIGHSCORE_SAVE_COUNT 3

/** \brief Nome do ficheiro onde vão ser guardados os highscores */
#define HIGHSCORES_FILE_NAME "~/highscores.txt"

/** \brief Nome do ficheiro de imagem correspondente ao jogador */
#define PLAYER_IMAGE_FILE_NAME "DwellerN_03.png"

/** \brief Nome do ficheiro de imagem correspondente à saida */
#define EXIT_IMAGE_FILE_NAME "trapdoor1.png"

/** \brief Nome do ficheiro de imagem correspondente à saida */
#define POTION_IMAGE_FILE_NAME "health_potion.png"

/** \brief Quantidade de vida que uma poção regenera */
#define POTION_HEALTH_AMOUNT 50

/** \brief Nome do cookie para guardar o estado */
#define COOKIE_NAME "gamestate"

/** \brief Tamanho máximo do header de cookie */
#define COOKIE_MAX_LENGTH 4096