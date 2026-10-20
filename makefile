CXX:=g++
CFLAGS:=-g -Wall -Wextra
# no Windows, linka estático para não pegar uma libstdc++-6.dll de outro programa no PATH // IA no meu makefile, eis a decadência da mente humana 
ifeq ($(OS),Windows_NT)
CFLAGS += -static
endif
OUT=output
DOUT:=debug_output
MAINSRC:=main.cpp
BRANCH = offstream

.PHONY: git test run clean

hellomake:
	@$(CXX) -O2 $(MAINSRC) -o $(OUT)

debug:
	@$(CXX) $(CFLAGS) $(MAINSRC) -o $(DOUT)

run:
	@$(CXX) -O2 $(MAINSRC) -o $(OUT); \
	./$(OUT) vc;

rund:
	@make debug; \
	./$(DOUT) vc;

clean:
	@rm $(OUT) $(DOUT);

#git:
#	@git add .; \
#	read -p "Commit message: " msg; \
#	git commit -m "$$msg"; \
#	git push origin $(BRANCH);

test:
	@$(CXX) -g test.cpp -o test; \
	./test > test_output.txt 2> test_error.txt; \
