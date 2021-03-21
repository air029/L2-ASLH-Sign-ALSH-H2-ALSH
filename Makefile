# Project: ASLH
# author: air029


CPP = g++
CPPFLAGS = -std=c++11 -pthread -O3
OBJ = main.o util.o sign_alsh.o mip.o l2_alsh.o h2_alsh.o


proc: $(OBJ)
	$(CPP) $(CPPFLAGS) -o proc $(OBJ)
main.o: def.h util.h mip.h l2_alsh.h sign_alsh.h h2_alsh.h
util.o: util.h def.h
mip.o: mip.h def.h util.h
l2_alsh.o: l2_alsh.h def.h util.h
sign_alsh.o: sign_alsh.h def.h util.h
h2_alsh.o: h2_alsh.h def.h util.h


.PHONY: clean
clean:
	rm proc $(OBJ)