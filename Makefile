CPPFLAGS = -std=c++20 -Wall -Werror -pedantic -ggdb -pthread
OBJS = Wriggler.o Terminal.o PixelMatrix.o RGB.o Snake.o Stone.o Poop.o

%.o : %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

ice2_wiggler : $(OBJS) Wiggler.o ice2_wiggler.o
	g++ -lcurses -lpthread $^ -o $@

ice2_solution : $(OBJS) Wiggler.o ice2_solution.o
	g++ -lcurses -lpthread $^ -o $@

ice1_wriggler : $(OBJS) ice1_wriggler.o
	g++ -lcurses -lpthread $^ -o $@

ice1_solution : $(OBJS) ice1_solution.o
	g++ -lcurses -lpthread $^ -o $@

p1 : $(OBJS) Wiggler.o p1.o
	g++ -lcurses -lpthread $^ -o $@

ice1 : ice1_wriggler ice1_solution

ice2 : ice2_wiggler ice2_solution

all : p1

clean :
	rm -f *.o ice1_wriggler ice1_solution ice2_wiggler ice2_solution p1
