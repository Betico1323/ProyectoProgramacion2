#include "../include/libro.h"
#include "../include/controlador.h"
#include <iostream>
#include <fstream>
#include <sstream>

void cargarLibros(Libro*& libros, int& totalLibros) {
    ifstream archivo("libros.csv");
    string linea, palabra;
    totalLibros = 0;

    if (!archivo.is_open()) {
        manejarErrores("Error al abrir el archivo de libros.");
        return;
    }

    Libro* tempLibros = new Libro[150];

    while (getline(archivo, linea) && totalLibros < 150) {
        stringstream s(linea);
        getline(s, palabra, ',');
        tempLibros[totalLibros].id = stoi(palabra);
        getline(s, tempLibros[totalLibros].titulo, ',');
        getline(s, tempLibros[totalLibros].autor, ',');
        getline(s, palabra, ',');
        tempLibros[totalLibros].disponible = (palabra == "1");
        totalLibros++;
    }

    delete[] libros;
    libros = tempLibros;
    archivo.close();
}

void guardarLibros(const Libro* libros, int totalLibros) {
    ofstream archivo("libros.csv");
    if (!archivo.is_open()) {
        manejarErrores("Error al abrir el archivo de libros para guardar.");
        return;
    }
    for (int i = 0; i < totalLibros; ++i) {
        archivo << libros[i].id << "," 
                << libros[i].titulo << "," 
                << libros[i].autor << "," 
                << (libros[i].disponible ? "1" : "0") << "\n";
    }
    archivo.close();
}

int buscarLibroPorID(Libro* libros, int totalLibros, int id) {
    int inicio
= 0, fin = totalLibros - 1;
while (inicio <= fin) {
int medio = (inicio + fin) / 2;
if (libros[medio].id == id) return medio;
else if (libros[medio].id < id) inicio = medio + 1;
else fin = medio - 1;
}
return -1;
}

void agregarLibro(Libro*& libros, int& totalLibros) {
Libro nuevoLibro;
nuevoLibro.id = totalLibros == 0 ? 1 : libros[totalLibros-1].id + 1;
cout << "Ingrese titulo del libro: ";
cin.ignore();
getline(cin, nuevoLibro.titulo);
cout << "Ingrese autor del libro: ";
getline(cin, nuevoLibro.autor);
nuevoLibro.disponible = true;


if (totalLibros >= 150) {
    manejarErrores("No se pueden agregar más libros. Límite alcanzado.");
    return;
}

libros[totalLibros++] = nuevoLibro;
guardarLibros(libros, totalLibros);
}

void modificarLibro(Libro* libros, int totalLibros) {
int id;
cout << "Ingrese ID del libro a modificar: ";
cin >> id;


int indice = buscarLibroPorID(libros, totalLibros, id);
if (indice != -1) {
    cout << "Ingrese nuevo titulo del libro: ";
    cin.ignore();
    getline(cin, libros[indice].titulo);
    cout << "Ingrese nuevo autor del libro: ";
    getline(cin, libros[indice].autor);
    guardarLibros(libros, totalLibros);
} else {
    manejarErrores("Libro no encontrado.");
}
}

void eliminarLibro(Libro*& libros, int& totalLibros) {
int id;
cout << "Ingrese ID del libro a eliminar: ";
cin >> id;


int indice = buscarLibroPorID(libros, totalLibros, id);
if (indice != -1) {
    for (int i = indice; i < totalLibros - 1; ++i) {
        libros[i] = libros[i + 1];
    }
    totalLibros--;
    guardarLibros(libros, totalLibros);
} else {
    manejarErrores("Libro no encontrado.");
}
}

void retirarLibro(Libro* libros, int totalLibros) {
int id;
cout << "Ingrese ID del libro a retirar: ";
cin >> id;


int indice = buscarLibroPorID(libros, totalLibros, id);
if (indice != -1 && libros[indice].disponible) {
    libros[indice].disponible = false;
    guardarLibros(libros, totalLibros);
} else {
    manejarErrores("Libro no encontrado o no disponible.");
}
}

void devolverLibro(Libro* libros, int totalLibros) {
int id;
cout << "Ingrese ID del libro a devolver: ";
cin >> id;

int indice = buscarLibroPorID(libros, totalLibros, id);
if (indice != -1 && !libros[indice].disponible) {
    libros[indice].disponible = true;
    guardarLibros(libros, totalLibros);
} else {
    manejarErrores("Libro no encontrado o no fue retirado.");
}
}

