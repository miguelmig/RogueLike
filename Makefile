CFLAGS=-Wall -Wextra -pedantic -O2
FICHEIROS=cgi.h estado.c estado.h map.c map.h exemplo.c Makefile pathfinding.h pathfinding.c

SOURCEDIR = src/

install: exemplo
	sudo cp exemplo /usr/lib/cgi-bin/jogo.cgi
	sudo cp exemplo /usr/lib/cgi-bin/exemplo
	sudo chmod 777 /usr/lib/cgi-bin/
	sudo cp -R scripts/ /var/www/html/
	sudo cp -R css/ /var/www/html/
	sudo cp -R images/ /var/www/html/
	touch install

exemplo: $(SOURCEDIR)exemplo.o $(SOURCEDIR)estado.o $(SOURCEDIR)map.o $(SOURCEDIR)utils.o $(SOURCEDIR)query.o pathfinding.o
	cc -Wall -Wextra -pedantic -O2 -o exemplo $(SOURCEDIR)exemplo.o $(SOURCEDIR)estado.o $(SOURCEDIR)map.o $(SOURCEDIR)utils.o $(SOURCEDIR)query.o pathfinding.o -lm 

exemplo.zip: $(FICHEIROS)
	zip -9 exemplo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf src/*.o exemplo Doxyfile latex html install

estado.o: estado.c
exemplo.o: exemplo.c
map.o: map.c
utils.o: utils.c
query.o: query.c
pathfinding.o: pathfinding.c