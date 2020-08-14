CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -Werror=vla
EXEC = cc3k
OBJECTS = main.o floor.o cell.o subject.o hero.o  gold.o potion.o orc.o elf.o dwarf.o human.o dragon.o merchant.o halfling.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean


