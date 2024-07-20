#ifndef LIBRO_H
#define LIBRO_H

#include <string>
using namespace std;

struct Libro {
    int id;
    string titulo;
    string autor;
    bool disponible;
};

void cargarLibros(Libro*& libros, int& totalLibros);
void guardarLibros(const Libro* libros, int totalLibros);
int buscarLibroPorID(Libro* libros, int totalLibros, int id);
void agregarLibro(Libro*& libros, int& totalLibros);
void modificarLibro(Libro* libros, int totalLibros);
void eliminarLibro(Libro*& libros, int& totalLibros);
void retirarLibro(Libro* libros, int totalLibros);
void devolverLibro(Libro* libros, int totalLibros);

#endif