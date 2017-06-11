/**
  * @file constants.h
  * @brief Contém as demais constantes usadas ao longo do código
*/
#pragma once

/** \brief Número minimo de inimigos por nível */
#define MIN_ENEMIES 5

/** \brief Número máximo de inimigos por nível */
#define MAX_ENEMIES 10

/** \brief Número minimo de obstáculos por nível */
#define MIN_OBSTACLES 10

/** \brief Número máximo de obstáculos por nível */
#define MAX_OBSTACLES 20

/** \brief Tamanho da grelha quadrada ( TAM x TAM ) */
#define TAM 10

/** \brief Número minimo de poções por nível */
#define MIN_POCOES 0

/** \brief Largura e comprimento, em pixeis, de cada telha do mapa */
#define ESCALA 40

#ifdef _WIN32
/** \brief Nome do ficheiro onde será guardado o estado de jogo */
#define STATE_FILE_NAME "gamestate.txt"
#else
/** \brief Nome do ficheiro onde será guardado o estado de jogo */
#define STATE_FILE_NAME "/tmp/gamestate.txt"	
#endif

/** \brief Coordenada X inicial do jogador */
#define PLAYER_START_X 5

/** \brief Coordenada Y inicial do jogador */
#define PLAYER_START_Y 9

/** \brief Valor máximo de vida do jogador */
#define PLAYER_MAX_HEALTH 100

/** \brief Coordenada X da saída */
#define EXIT_X 5

/** \brief Coordenada Y da saída */
#define EXIT_Y 0

/** \brief Pontos ganhos pelo jogador quando um inimigo é morto, escala com o nível atual do jogo */
#define KILL_SCORE_BONUS 300

/** \brief Pontos ganhos pelo jogador quando sai do nível, escala com o nível atual do jogo */
#define NEW_LEVEL_SCORE_BONUS 500

/** \brief O nº de pontuações máximas a guardar */
#define HIGHSCORE_SAVE_COUNT 3

/** \brief Nome do ficheiro onde vão ser guardados os highscores */
#ifdef _WIN32
/** \brief Nome do ficheiro onde serão guardadas as pontuações máximas */
#define HIGHSCORES_FILE_NAME "highscores.txt"
#else
/** \brief Nome do ficheiro onde serão guardadas as pontuações máximas */
#define HIGHSCORES_FILE_NAME "/tmp/highscores.txt"
#endif

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