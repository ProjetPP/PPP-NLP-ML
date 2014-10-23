CC=g++
C11= -std=c++11
FLAGSBASE= -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wwrite-strings -Wsign-compare -Wmissing-declarations -lpthread
NAZIBASE= $(FLAGSBASE) -pedantic -Wconversion -Wmissing-noreturn -Wold-style-cast -Weffc++ -Wall -Wunused -Wsign-conversion -Wunused -Wstrict-aliasing -Wstrict-overflow -Wconversion -Wdisabled-optimization
ifeq ($(CC), g++)
    NAZI= $(NAZIBASE) -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=pure -Wlogical-op -Wunsafe-loop-optimizations
else
    NAZI=$(NAZIBASE)
endif
CFLAGS=$(NAZI)
LDFLAGS= -lpthread
EXEC= setup reformulation

all: $(EXEC) 

debug: CFLAGS = $(NAZI) -D DEBUG -g
debug: FLAGSBASE = -O2 -W -Wextra -Wcast-qual -Wcast-align -Wfloat-equal -Wshadow -Wpointer-arith -Wunreachable-code -Wchar-subscripts -Wcomment -Wformat -Werror-implicit-function-declaration -Wmain -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch -Wuninitialized -Wreorder -Wundef -Wshadow -Wwrite-strings -Wsign-compare -Wmissing-declarations -D DEBUG -g -pthread
debug: $(EXEC)

purge: clean all

clang: CC=clang++
clang: C11=-std=c++11
clang: $(EXEC)

setup:
	mkdir -p obj
	
reformulation: obj/reformulation.o obj/Request.o obj/Dictionary.o obj/Transformator.o obj/Request.o obj/Functions.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
obj/reformulation.o: reformulation.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/Request.o: Request.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/Dictionary.o: Dictionary.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/Transformator.o: Transformator.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
obj/Functions.o: Functions.cpp
	$(CC) -o $@ -c $< $(C11) $(CFLAGS)
	
clean:
	rm -f obj/*.o
