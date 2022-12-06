CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
EXEC = chess
OBJECTS = bishop.o boardcontroller.o boardmodel.o boardview.o chesspiece.o computer.o decorator.o human.o invalidmoveexception.o king.o knight.o main.o pawn.o piece.o queen.o rook.o subject.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
