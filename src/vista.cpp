#include "../include/vista.h"
#include <iostream>

void mostrarMenu(const Usuario* usuarioActual) {
    cout << "\nMenu:\n";
    if (usuarioActual->rol == "admin") {
        cout << "1. Registrar usuario\n";
        cout << "2. Eliminar usuario\n";
        cout << "3. Suspender usuario\n";
    }
    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
        cout << "4. Agregar libro\n";
        cout << "5. Modificar libro\n";
        cout << "6. Eliminar libro\n";
    }
    if (usuarioActual->rol == "cliente") {
        cout << "7. Retirar libro\n";
        cout << "8. Devolver libro\n";
    }
    cout << "9. Cerrar sesion\n";
    cout << "0. Salir\n";
}

void mostrarMensaje(const string& mensaje) {
    cout << mensaje << endl;
}