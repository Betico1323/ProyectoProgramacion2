#include "../include/usuario.h"
#include "../include/controlador.h"
#include <iostream>
#include <fstream>
#include <sstream>

void cargarUsuarios(Usuario*& usuarios, int& totalUsuarios) {
    ifstream archivo("usuarios.csv");
    string linea, palabra;
    totalUsuarios = 0;

    if (!archivo.is_open()) {
        manejarErrores("Error al abrir el archivo de usuarios.");
        return;
    }

    Usuario* tempUsuarios = new Usuario[200];

    while (getline(archivo, linea) && totalUsuarios < 200) {
        stringstream s(linea);
        getline(s, palabra, ',');
        tempUsuarios[totalUsuarios].id = stoi(palabra);
        getline(s, tempUsuarios[totalUsuarios].nombre, ',');
        getline(s, tempUsuarios[totalUsuarios].contrasena, ',');
        getline(s, tempUsuarios[totalUsuarios].rol, ',');
        getline(s, palabra, ',');
        tempUsuarios[totalUsuarios].suspendido = (palabra == "1");
        totalUsuarios++;
    }

    delete[] usuarios;
    usuarios = tempUsuarios;
    archivo.close();
}

void guardarUsuarios(const Usuario* usuarios, int totalUsuarios) {
    ofstream archivo("usuarios.csv");
    if (!archivo.is_open()) {
        manejarErrores("Error al abrir el archivo de usuarios para guardar.");
        return;
    }
    for (int i = 0; i < totalUsuarios; ++i) {
        archivo << usuarios[i].id << "," 
                << usuarios[i].nombre << "," 
                << usuarios[i].contrasena << "," 
                << usuarios[i].rol << "," 
                << (usuarios[i].suspendido ? "1" : "0") << "\n";
    }
    archivo.close();
}

int buscarUsuarioPorID(Usuario* usuarios, int totalUsuarios, int id) {
    int inicio = 0, fin = totalUsuarios - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (usuarios[medio].id == id) return medio;
        else if (usuarios[medio].id < id) inicio = medio + 1;
        else fin = medio - 1;
    }
    return -1;
}

Usuario* login(Usuario* usuarios, int totalUsuarios) {
    string nombre, contrasena;
    cout << "Ingrese su nombre de usuario: ";
    cin >> nombre;
    cout << "Ingrese su contrasena: ";
    cin >> contrasena;

    for (int i = 0; i < totalUsuarios; ++i) {
        if (usuarios[i].nombre == nombre && usuarios[i].contrasena == contrasena) {
            return &usuarios[i];
        }
    }
    return nullptr;
}

void registrarUsuario(Usuario*& usuarios, int& totalUsuarios) {
    Usuario nuevoUsuario;
    nuevoUsuario.id = totalUsuarios == 0 ? 1 : usuarios[totalUsuarios-1].id + 1;
    cout << "Ingrese nombre de usuario: ";
    cin >> nuevoUsuario.nombre;
    cout << "Ingrese contrasena: ";
    cin >> nuevoUsuario.contrasena;
    cout << "Ingrese rol (admin/empleado/cliente): ";
    cin >> nuevoUsuario.rol;
    nuevoUsuario.suspendido = false;

    if (totalUsuarios >= 200) {
        manejarErrores("No se pueden registrar más usuarios. Límite alcanzado.");
        return;
    }

    usuarios[totalUsuarios++] = nuevoUsuario;
    
    ofstream archivo("usuarios.csv", ios::app);
    if (!archivo.is_open()) {
        manejarErrores("Error al abrir el archivo de usuarios para añadir.");
        return;
    }
    archivo << nuevoUsuario.id << "," 
            << nuevoUsuario.nombre << "," 
            << nuevoUsuario.contrasena << "," 
            << nuevoUsuario.rol << "," 
            << (nuevoUsuario.suspendido ? "1" : "0") << "\n";
    archivo.close();
}

void eliminarUsuario(Usuario*& usuarios, int& totalUsuarios) {
    int id;
    cout << "Ingrese ID de usuario a eliminar: ";
    cin >> id;

    int indice = buscarUsuarioPorID(usuarios, totalUsuarios, id);
    if (indice != -1) {
        for (int i = indice; i < totalUsuarios - 1; ++i) {
            usuarios[i] = usuarios[i + 1];
        }
        totalUsuarios--;
        guardarUsuarios(usuarios, totalUsuarios);
    } else {
        manejarErrores("Usuario no encontrado.");
    }
}

void suspenderUsuario(Usuario* usuarios, int totalUsuarios) {
    int id;
    cout << "Ingrese ID de usuario a suspender: ";
    cin >> id;

    int indice = buscarUsuarioPorID(usuarios, totalUsuarios, id);
    if (indice != -1) {
        usuarios[indice].suspendido = true;
        guardarUsuarios(usuarios, totalUsuarios);
    } else {
        manejarErrores("Usuario no encontrado.");
    }
}
