CFLAGS=-Wall
FICHEIROS=cgi.h estado.c estado.h map.c map.h exemplo.c Makefile

SOURCEDIR = src/

install: exemplo
	sudo cp exemplo /usr/lib/cgi-bin
	touch install

exemplo: $(SOURCEDIR)exemplo.o $(SOURCEDIR)estado.o $(SOURCEDIR)map.o $(SOURCEDIR)utils.o
	cc -o exemplo $(SOURCEDIR)exemplo.o $(SOURCEDIR)estado.o $(SOURCEDIR)map.o $(SOURCEDIR)utils.o

exemplo.zip: $(FICHEIROS)
	zip -9 exemplo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o exemplo Doxyfile latex html install

estado.o: estado.c
exemplo.o: exemplo.c
map.o: map.c
utils.o: utils.c