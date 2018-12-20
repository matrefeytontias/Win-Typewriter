run: soft dll
	@echo ">>> Running typewriter ..."
	@./typewriter

soft: main.cpp
	gcc main.cpp -lstdc++ -o typewriter

dll: dll.c
	gcc -shared dll.c -lwinmm -o typewriter.dll

clean:
	rm -f typewriter.*
