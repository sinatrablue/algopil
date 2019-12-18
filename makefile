exec: data_struct.o
	g++ -o exec data_struct.o

data_struct.o: data_struct.cpp
	g++ -c data_struct.cpp

clean:
	rm -rf *.o

mrproper: clean
	rm -rf exec