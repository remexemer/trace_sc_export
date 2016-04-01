all: exe

exe: main.o
	g++ -L/usr/cadtool/systemc-2.3/lib-linux64 main.o -lsystemc -o exe

main.o: main.cpp 
	g++ -g -c -I/usr/cadtool/systemc-2.3/include main.cpp

run:
	./exe

clean:
	rm *.o exe
