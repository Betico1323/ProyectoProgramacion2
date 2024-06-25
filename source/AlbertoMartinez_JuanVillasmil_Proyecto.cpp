#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Usuario {
    int id;
    string nombre;
    string contrasena;
    string rol;
    bool suspendido;
};

struct Libro {
    int id;
    string titulo;
    string autor;
    bool disponible;
};