CC= g++
PROG= dterm
SRC= main.cpp 
HEADERFILES = 
OBJ= $(SRC:.cpp=.o)
DEFINE += -DDEBUG
FLAGS += -g -Wall
CFLAGS  = $(FLAGS) $(DEFINE)

$(PROG):	$(OBJ) main

main.o: main.cpp
	$(CC) main.cpp -c $(CFLAGS) 
main:	main.o 
	${CC}  main.o $(LIB)  -o $(PROG)
clean:
	rm -rf $(OBJ) $(PROG) main.o  core *.core
