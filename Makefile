build:
	g++ -Wall -std=c++17 ./src/*.cpp -o renderer

run:
	./renderer

clean:
	rm renderer
