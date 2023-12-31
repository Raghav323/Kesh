# kesh: Square.cpp kesh.cpp init.cpp BoardState.cpp Piece.cpp
# 	g++ -Wall -I../include -o Square.cpp kesh.cpp init.cpp BoardState.cpp Piece.cpp 
	 
CC = g++ -O2
CFLAGS = -Wall -I../include 

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = Square.cpp kesh.cpp init.cpp Board.cpp Piece.cpp defs.cpp magics.cpp movegen.cpp MoveMaker.cpp Search.cpp hash.cpp evaluate.cpp moveorder.cpp uci.cpp misc.cpp
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
EXECUTABLE = $(BINDIR)/kesh

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)
