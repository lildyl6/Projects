CC = gcc
CFLAGS = -g -ansi -pedantic-errors -Wall -fstack-protector-all -Werror -Wshadow

all: public01.x public02.x public03.x public04.x public05.x\
	public06.x public07.x public08.x public09.x public10.x

wstring-graph.o: wstring-graph.c wstring-graph.h wstring-graph-datastructure.h
	$(CC) $(CFLAGS) -c wstring-graph.c

public01.o: public01.c wstring-graph.h wstring-graph-datastructure.h
	$(CC) $(CFLAGS) -c public01.c

public02.o: public02.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public02.c

public03.o: public03.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public03.c

public04.o: public04.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public04.c

public05.o: public05.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public05.c

public06.o: public06.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public06.c

public07.o: public07.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public07.c

public08.o: public08.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public08.c

public09.o: public09.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public09.c

public10.o: public10.c wstring-graph.h wstring-graph-datastructure.h graph-utils.h
	$(CC) $(CFLAGS) -c public10.c

public01.x: public01.o wstring-graph.o
	$(CC) $(CFLAGS) public01.o wstring-graph.o -o public01.x

public02.x: public02.o wstring-graph.o
	$(CC) $(CFLAGS)	public02.o wstring-graph.o graph-utils.o -o public02.x

public03.x: public03.o wstring-graph.o
	$(CC) $(CFLAGS)	public03.o wstring-graph.o graph-utils.o -o public03.x

public04.x: public04.o wstring-graph.o graph-utils.o
	$(CC) $(CFLAGS)	public04.o wstring-graph.o graph-utils.o -o public04.x

public05.x: public05.o wstring-graph.o
	$(CC) $(CFLAGS)	public05.o wstring-graph.o graph-utils.o -o public05.x

public06.x: public06.o wstring-graph.o
	$(CC) $(CFLAGS)	public06.o wstring-graph.o graph-utils.o -o public06.x

public07.x: public07.o wstring-graph.o
	$(CC) $(CFLAGS)	public07.o wstring-graph.o graph-utils.o -o public07.x

public08.x: public08.o wstring-graph.o
	$(CC) $(CFLAGS)	public08.o wstring-graph.o graph-utils.o -o public08.x

public09.x: public09.o wstring-graph.o
	$(CC) $(CFLAGS)	public09.o wstring-graph.o graph-utils.o -o public09.x

public10.x: public10.o wstring-graph.o
	$(CC) $(CFLAGS)	public10.o wstring-graph.o graph-utils.o -o public10.x

clean:
	rm -f *.x public01.o public02.o public03.o public04.o public05.o\
	public06.o public07.o public08.o public09.o public10.o\
	wstring-graph.o
