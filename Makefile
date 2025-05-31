#------------------------------------------------
# infection lab Makefile
#------------------------------------------------

#------------------------------------------------
# Sets the C++ compiler flags
# -Wall means Warn about all
# -o are the created files connected to the .cpp
# -g for extra debuggin help
#------------------------------------------------

FLAGS = -Wall -g

# Compiling and creating executable file
infection: Human.o Pokemon.o Board.o conio.o
	g++ $(FLAGS) -o infection Human.o Pokemon.o Board.o conio.o main.cpp

# Cleans up all the .o and other executable files
clean:
	rm -f *.o a.out infection
	@echo "Removed all junk"


Human.o: Human.cpp Human.h
Pokemon.o: Pokemon.cpp Pokemon.h Human.h Board.h
Board.o: Board.cpp Board.h Human.h Pokemon.h
conio.o: conio.cpp conio.h
