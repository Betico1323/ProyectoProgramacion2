#include "controlador.h"
#include <fstream>
#include <iostream>

void manejarErrores(const string& mensaje) {
    ofstream archivo("..\\log\\error.log", ios::app);
    if (archivo.is_open()) {
        archivo << mensaje << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de log.\n";
    }
}