CXX:=g++
CFLAGS:=-g
OUT=output
MAINSRC:=main.cpp
BRANCH = offstream

.PHONY: git

hellomake:
	@$(CXX) $(CFLAGS) $(MAINSRC) -o $(OUT);\

git:
	@git add .;
	read -p "Commit message: " msg;
	git commit -m $msg;
	git push origin $(BRANCH);
