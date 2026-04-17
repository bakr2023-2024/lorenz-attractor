.PHONY: clean
main: main.cpp
	g++ --std=c++20 -o lorenz main.cpp -lraylib -lopengl32 -lgdi32 -lwinmm
clean:
	rm -rf *.exe