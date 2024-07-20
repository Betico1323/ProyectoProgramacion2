#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

struct Usuario {
    int id;
    string nombre;
    string contrasena;
    string rol;
    bool suspendido;
};

void cargarUsuarios(Usuario*& usuarios, int& totalUsuarios);
void guardarUsuarios(const Usuario* usuarios, int totalUsuarios);
int buscarUsuarioPorID(Usuario* usuarios, int totalUsuarios, int id);
Usuario* login(Usuario* usuarios, int totalUsuarios);
void registrarUsuario(Usuario*& usuarios, int& totalUsuarios);
void eliminarUsuario(Usuario*& usuarios, int& totalUsuarios);
void suspenderUsuario(Usuario* usuarios, int totalUsuarios);

#endif
