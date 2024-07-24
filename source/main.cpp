#include "usuario.h"
#include "libro.h"
#include "vista.h"
#include "controlador.h"
#include <iostream>

int main() {
    Usuario* usuarios = nullptr; 
    Libro* libros = nullptr;
    int totalUsuarios = 0, totalLibros = 0;

    cargarUsuarios(usuarios, totalUsuarios);
    cargarLibros(libros, totalLibros);

    while (true) {
        Usuario* usuarioActual = nullptr;

        while (usuarioActual == nullptr) {
            usuarioActual = login(usuarios, totalUsuarios);
            if (usuarioActual == nullptr) {
                mostrarMensaje("Usuario o contrasena incorrecta. Intente de nuevo.");
            }
        }

        if (usuarioActual->suspendido) {
            mostrarMensaje("Usuario suspendido. Acceso denegado.");
            delete[] usuarios;
            delete[] libros;
            return 0;
        }

        int opcion;

        do {
            mostrarMenu(usuarioActual);
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    if (usuarioActual->rol == "admin") {
                        registrarUsuario(usuarios, totalUsuarios);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 2:
                    if (usuarioActual->rol == "admin") {
                        eliminarUsuario(usuarios, totalUsuarios);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 3:
                    if (usuarioActual->rol == "admin") {
                        suspenderUsuario(usuarios, totalUsuarios);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 4:
                    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
                        agregarLibro(libros, totalLibros);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 5:
                    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
                        modificarLibro(libros, totalLibros);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 6:
                    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
                        eliminarLibro(libros, totalLibros);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 7:
                    if (usuarioActual->rol == "cliente") {
                        retirarLibro(libros, totalLibros);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 8:
                    if (usuarioActual->rol == "cliente") {
                        devolverLibro(libros, totalLibros);
                    } else {
                        mostrarMensaje("Opcion no valida.");
                    }
                    break;
                case 9:
                    mostrarMensaje("Cerrando sesion...");
                    usuarioActual = nullptr;
                    break;
                case 0:
                    mostrarMensaje("Saliendo del sistema.");
                    delete[] usuarios;
                    delete[] libros;
                    return 0;
                default:
                    mostrarMensaje("Opcion no valida.");
                    break;
            }
        } while (opcion != 9 && opcion != 0);
    }

    return 0;
}
