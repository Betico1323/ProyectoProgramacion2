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

void cargarUsuarios(Usuario usuarios[], int& totalUsuarios) {
    ifstream archivo("usuarios.csv");
    string linea, palabra;
    totalUsuarios = 0;

    //id,usuario,contraseña,rol,suspendido
    while (getline(archivo, linea) && totalUsuarios < 200) {
        stringstream s(linea);
        getline(s, palabra, ',');
        usuarios[totalUsuarios].id = stoi(palabra);
        getline(s, usuarios[totalUsuarios].nombre, ',');
        getline(s, usuarios[totalUsuarios].contrasena, ',');
        getline(s, usuarios[totalUsuarios].rol, ',');
        getline(s, palabra, ',');
        usuarios[totalUsuarios].suspendido = (palabra == "1");
        totalUsuarios++;
    }
    archivo.close();
}
  
void cargarLibros(Libro libros[], int& totalLibros) {
    ifstream archivo("libros.csv");
    string linea, palabra;
    totalLibros = 0;

    //id,titulo,autor,disponible
    while (getline(archivo, linea) && totalLibros < 150) {
        stringstream s(linea);
        getline(s, palabra, ',');
        libros[totalLibros].id = stoi(palabra);
        getline(s, libros[totalLibros].titulo, ',');
        getline(s, libros[totalLibros].autor, ',');
        getline(s, palabra, ',');
        libros[totalLibros].disponible = (palabra == "1");
        totalLibros++;
    }
    archivo.close();
}
void guardarUsuarios(const Usuario usuarios[], int totalUsuarios) {
    ofstream archivo("usuarios.csv");
    for (int i = 0; i < totalUsuarios; ++i) {
        archivo << usuarios[i].id << "," 
                << usuarios[i].nombre << "," 
                << usuarios[i].contrasena << "," 
                << usuarios[i].rol << "," 
                << (usuarios[i].suspendido ? "1" : "0") << "\n";
    }
    archivo.close();
}

void guardarLibros(const Libro libros[], int totalLibros) {
    ofstream archivo("libros.csv");
    for (int i = 0; i < totalLibros; ++i) {
        archivo << libros[i].id << "," 
                << libros[i].titulo << "," 
                << libros[i].autor << "," 
                << (libros[i].disponible ? "1" : "0") << "\n";
    }
    archivo.close();
}