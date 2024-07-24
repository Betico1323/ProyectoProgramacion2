#include "../include/controlador.h"
#include <fstream>
#include <iostream>

void manejarErrores(const string& mensaje) { 
    //Poner ruta completa de error.log
    ofstream archivo("C:\\Users\\jdvil\\OneDrive\\Escritorio\\ProyectoProg2\\ProyectoProgramacion2\\log\\error.log", ios::app);
    if (archivo.is_open()) {
        archivo << mensaje << "\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo de log.\n";
    }
}