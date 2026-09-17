CXX:=g++
CFLAGS:=-g
OUT=output
MAINSRC:=main.cpp

hellomake:
	@$(CXX) $(CFLAGS) $(MAINSRC) -o $(OUT);
