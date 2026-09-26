CXX:=g++
CFLAGS:=-g
OUT=output
MAINSRC:=main.cpp
BRANCH = offstream

.PHONY: git test

hellomake:
	@$(CXX) $(CFLAGS) $(MAINSRC) -o $(OUT);

git:
	@git add .; \
	read -p "Commit message: " msg; \
	git commit -m "$$msg"; \
	git push origin $(BRANCH);

test:
	@$(CXX) test.cpp -o test; \
	./test > test_output.txt 2> test_error.txt; \
	less test_output.txt;
