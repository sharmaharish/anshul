CFLAGS = -c -std=c++0x -pipe -Wall -W -g2 -O0 -pedantic-errors
LDFLAGS = -pipe 

OBJECTS = obj/main.o \
		  obj/Bishop.o \
		  obj/Config.o \
		  obj/Engine.o \
		  obj/Fen.o    \
		  obj/King.o   \
		  obj/Knight.o \
		  obj/Move.o   \
		  obj/Pawn.o   \
		  obj/Piece.o  \
		  obj/Queen.o  \
		  obj/Rook.o   \
          obj/Board.o  \
          obj/Log.o    \
          obj/util.o   \

anshul: $(OBJECTS)
	g++ $(LDFLAGS) -o anshul $(OBJECTS)

clean:
	rm anshul 
	rm obj/*.o

obj/%.o: %.cpp
	g++ $(CFLAGS) -o $@ $<

# DO NOT DELETE

Bishop.o: values.hpp Bishop.hpp Piece.hpp Board.hpp types.hpp common.hpp
Bishop.o: Move.hpp constants.hpp Config.hpp
Board.o: Queen.hpp Bishop.hpp Piece.hpp Board.hpp types.hpp common.hpp
Board.o: Move.hpp constants.hpp Rook.hpp Knight.hpp Fen.hpp
Config.o: Config.hpp common.hpp util.hpp
Engine.o: Engine.hpp Board.hpp types.hpp common.hpp Move.hpp constants.hpp
Engine.o: Piece.hpp Config.hpp util.hpp
Fen.o: Fen.hpp constants.hpp common.hpp Board.hpp types.hpp Move.hpp
Fen.o: Piece.hpp Pawn.hpp Rook.hpp Knight.hpp Bishop.hpp King.hpp Queen.hpp
King.o: King.hpp Bishop.hpp Piece.hpp Board.hpp types.hpp common.hpp Move.hpp
King.o: constants.hpp Rook.hpp
Knight.o: values.hpp Knight.hpp Piece.hpp Board.hpp types.hpp common.hpp
Knight.o: Move.hpp constants.hpp Config.hpp
main.o: Engine.hpp Board.hpp types.hpp common.hpp Move.hpp constants.hpp
Move.o: Move.hpp common.hpp constants.hpp Piece.hpp Board.hpp types.hpp
Pawn.o: values.hpp Pawn.hpp Piece.hpp Board.hpp types.hpp common.hpp Move.hpp
Pawn.o: constants.hpp Config.hpp
Piece.o: Piece.hpp Board.hpp types.hpp common.hpp Move.hpp constants.hpp
Queen.o: Queen.hpp Bishop.hpp Piece.hpp Board.hpp types.hpp common.hpp
Queen.o: Move.hpp constants.hpp Rook.hpp Config.hpp
Rook.o: values.hpp Rook.hpp Piece.hpp Board.hpp types.hpp common.hpp Move.hpp
Rook.o: constants.hpp Config.hpp
Log.o: Log.hpp
