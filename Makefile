all: exe

SYSTEMC_HOME=/home/doctor/d101061819/Chicago/checkout_0701_repo/tools/Arteris/FlexNoC-2.11.4/externals

exe: main.o
	g++ -m32 -L${SYSTEMC_HOME}/lib-linux main.o -lsystemc -o exe

main.o: main.cpp 
	g++ -m32 -g -c -I${SYSTEMC_HOME}/include main.cpp

run:
	./exe

clean:
	rm *.o exe
