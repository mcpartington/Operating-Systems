#######################################
# Maxwell Partington and Mary Wakefield
# Class:   Operating Systems
# Program: 5
# Date:    5/7/14
#######################################
CC = g++		# use g++ for compiling c++ code or gcc for c code
CFLAGS = -g -Wall	# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm		# linked libraries	
LDFLAGS = -L.		# link flags
PROG = PageSim		# target executable (output)
OBJ = main.o structures.o		# object files for the target. Add more to this and next lines if there are more than one source files.
SRC = main.cpp structures.cpp		# .c or .cpp source files.  

all : $(PROG)

$(PROG): $(OBJ) 
	$(CC) -c $(CFLAGS) $(SRC)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)


# cleanup
clean:
	/bin/rm -f *.o $(PROG)

# DO NOT DELETE
