# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Asignatura : Algoritmos y Estructuras de Datos Avanzadas
# Curso : 2º
# Práctica 5: Ordenación
#
# Autor : Javier Almenara Herrera 
# Correo : alu01014666552@ull.edu.es
# Fecha : 06/04/2023
# Archivo Makefile : crea el ejecutable.

CXX = g++						             # The C++ compiler command
CXXFLAGS = -std=c++2a -g 	 # The C++ compiler options (C++14, preserve debug symbols and warn all)
LDFLAGS =						             # The linker options (if any)

# The all target builds all of the programs handled by the makefile.
all: client

client: client.cc functions.cc
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean

# The following rule is effectively built into make and
# therefore need not be explicitly specified:
# hello_world.o: hello_world.cc
#
	$(CXX) $(CXXFLAGS) -c $<

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	rm -f *.o client doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;