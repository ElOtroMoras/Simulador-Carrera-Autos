# Compilacion de todos los archivos o por defecto
all: normal debug

# Compilacion archivo normal
normal: simuladorCarreraAutos.cpp
	g++ -std=c++11 -o output simuladorCarreraAutos.cpp -lpthread

# Compilacion archivo debug
debug: simuladorCarreraAutos.cpp
	g++ -std=c++11 -Ddebug -o outputDebug simuladorCarreraAutos.cpp -lpthread

# Limpiar ejecutables
clean:
	rm -f output outputDebug
