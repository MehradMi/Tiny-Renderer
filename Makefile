build:
	g++ -Wall -std=c++17 ./src/*.cpp -lSDL2 -o tiny_renderer

run:
	./tiny_renderer

clean:
	rm tiny_renderer
