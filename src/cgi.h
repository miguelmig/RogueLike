/**
@file cgi.h
Macros úteis para gerar CGIs
*/

#include <stdio.h>

/**
* Caminho para as imagens
*/
#define IMAGE_PATH							"/images/"

/**
* Caminho para os scripts
*/
#define SCRIPT_PATH							"/scripts/"

/**
\brief Macro para começar o html
*/
#define COMECAR_HTML						printf("Content-Type: text/html\n\n")

/**
\brief Macro para abrir um svg
@param tamx O comprimento do svg
@param tamy A altura do svg
*/
#define ABRIR_SVG(tamx, tamy)				printf("<svg width=%d height=%d>\n", tamx, tamy)
/**
\brief Macro para fechar um svg
*/
#define FECHAR_SVG							printf("</svg>\n")

/**
\brief Macro para criar uma imagem
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, IMAGE_PATH FICHEIRO)

/**
\brief Macro para criar um quadrado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala do quadrado
@param COR A cor de preenchimento do quadrado
*/
#define QUADRADO(X, Y, ESCALA, COR)			printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, COR)

/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link)					printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para abrir um link com mais opções
@param link O caminho para o link
@param id Identificador do link
@param class_ Classe de identificação do link
*/

#define ABRIR_LINK_ADV(link, id, class_)	printf("<a id=%s class=%s xlink:href=%s>\n", id, class_, link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")

/**
\brief Macro para incluir JQuery
*/
#define INCLUIR_JQUERY						printf("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js\"></script>")


#define INCLUIR_SCRIPT(script)				printf("<script type=\"text/javascript\" src=\"%s\"></script>", SCRIPT_PATH script)