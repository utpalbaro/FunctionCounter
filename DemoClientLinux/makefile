main.out: linux64/main.o linux64/FunctionCounter.o linux64/HooksCallbacks.o linux64/HooksImpl.o linux64/SymbolsLoader.o
	g++ linux64/main.o linux64/FunctionCounter.o linux64/HooksCallbacks.o linux64/HooksImpl.o linux64/SymbolsLoader.o -rdynamic -o main.out

linux64/main.o: main.cpp
	g++ -g -c main.cpp -finstrument-functions -o linux64/main.o

linux64/FunctionCounter.o: ../FunctionCounter/_private/FunctionCounter.cpp
	g++ -g -c ../FunctionCounter/_private/FunctionCounter.cpp -o linux64/FunctionCounter.o

linux64/HooksCallbacks.o: ../HooksCallbacks/_private/HooksCallbacks.cpp 
	g++ -g -c ../HooksCallbacks/_private/HooksCallbacks.cpp -o linux64/HooksCallbacks.o

linux64/HooksImpl.o: ../HooksCallbacks/_private/Linux/HooksImpl.cpp
	g++ -g -c ../HooksCallbacks/_private/Linux/HooksImpl.cpp -o linux64/HooksImpl.o

linux64/SymbolsLoader.o: ../SymbolsLoader/_private/Linux/SymbolsManager.cpp
	g++ -g -c ../SymbolsLoader/_private/Linux/SymbolsManager.cpp -o linux64/SymbolsLoader.o

clean:
	rm -rf linux64/*.o