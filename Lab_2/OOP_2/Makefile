KEYS = -std=c++17

app.exe: main.o basemyset.o
	g++ -o app.exe main.o basemyset.o

main.o: main.cpp
	g++ -c $(KEYS) main.cpp myset.h myset.hpp my_exceptions.h

basemyset.o: basemyset.cpp
	g++ -c $(KEYS) basemyset.cpp basemyset.h

clean:
	rm -rf *.o *.exe *.gch
	
