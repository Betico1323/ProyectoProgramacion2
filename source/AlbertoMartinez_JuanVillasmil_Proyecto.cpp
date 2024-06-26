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

int buscarUsuarioPorID(Usuario usuarios[], int totalUsuarios, int id) {
    int inicio = 0, fin = totalUsuarios - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (usuarios[medio].id == id) return medio;
        else if (usuarios[medio].id < id) inicio = medio + 1;
        else fin = medio - 1;
    }
    return -1;
}

int buscarLibroPorID(Libro libros[], int totalLibros, int id) {
    int inicio = 0, fin = totalLibros - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        if (libros[medio].id == id) return medio;
        else if (libros[medio].id < id) inicio = medio + 1;
        else fin = medio - 1;
    }
    return -1;
}
Usuario* login(Usuario usuarios[], int totalUsuarios) {
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

void registrarUsuario(Usuario usuarios[], int& totalUsuarios) {
    Usuario nuevoUsuario;
    nuevoUsuario.id = totalUsuarios == 0 ? 1 : usuarios[totalUsuarios-1].id + 1;
    cout << "Ingrese nombre de usuario: ";
    cin >> nuevoUsuario.nombre;
    cout << "Ingrese contrasena: ";
    cin >> nuevoUsuario.contrasena;
    cout << "Ingrese rol (admin/empleado/cliente): ";
    cin >> nuevoUsuario.rol;
    nuevoUsuario.suspendido = false;

    usuarios[totalUsuarios++] = nuevoUsuario;
    
    ofstream archivo("usuarios.csv", ios::app);
    archivo << nuevoUsuario.id << "," 
            << nuevoUsuario.nombre << "," 
            << nuevoUsuario.contrasena << "," 
            << nuevoUsuario.rol << "," 
            << (nuevoUsuario.suspendido ? "1" : "0") << "\n";
    archivo.close();
}

void eliminarUsuario(Usuario usuarios[], int& totalUsuarios) {
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
        cout << "Usuario no encontrado.\n";
    }
}

void suspenderUsuario(Usuario usuarios[], int totalUsuarios) {
    int id;
    cout << "Ingrese ID de usuario a suspender: ";
    cin >> id;

    int indice = buscarUsuarioPorID(usuarios, totalUsuarios, id);
    if (indice != -1) {
        usuarios[indice].suspendido = true;
        guardarUsuarios(usuarios, totalUsuarios);
    } else {
        cout << "Usuario no encontrado.\n";
    }
}

void agregarLibro(Libro libros[], int& totalLibros) {
    Libro nuevoLibro;
    nuevoLibro.id = totalLibros == 0 ? 1 : libros[totalLibros-1].id + 1;
    cout << "Ingrese titulo del libro: ";
    cin.ignore();
    getline(cin, nuevoLibro.titulo);
    cout << "Ingrese autor del libro: ";
    getline(cin, nuevoLibro.autor);
    nuevoLibro.disponible = true;

    libros[totalLibros++] = nuevoLibro;
    guardarLibros(libros, totalLibros);
}

void modificarLibro(Libro libros[], int totalLibros) {
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
        cout << "Libro no encontrado.\n";
    }
}

void eliminarLibro(Libro libros[], int& totalLibros) {
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
        cout << "Libro no encontrado.\n";
    }
}

void retirarLibro(Libro libros[], int totalLibros) {
    int id;
    cout << "Ingrese ID del libro a retirar: ";
    cin >> id;

    int indice = buscarLibroPorID(libros, totalLibros, id);
    if (indice != -1 && libros[indice].disponible) {
        libros[indice].disponible = false;
        guardarLibros(libros, totalLibros);
    } else {
        cout << "Libro no encontrado o no disponible.\n";
    }
}

void devolverLibro(Libro libros[], int totalLibros) {
    int id;
    cout << "Ingrese ID del libro a devolver: ";
    cin >> id;

    int indice = buscarLibroPorID(libros, totalLibros, id);
    if (indice != -1 && !libros[indice].disponible) {
        libros[indice].disponible = true;
        guardarLibros(libros, totalLibros);
    } else {
        cout << "Libro no encontrado o no fue retirado.\n";
    }
}

int main() {
    Usuario usuarios[200]; 
    Libro libros[150];
    int totalUsuarios = 0, totalLibros = 0;

    cargarUsuarios(usuarios, totalUsuarios);
    cargarLibros(libros, totalLibros);

    while (true) {
        Usuario* usuarioActual = nullptr;

        while (usuarioActual == nullptr) {
            usuarioActual = login(usuarios, totalUsuarios);
            if (usuarioActual == nullptr) {
                cout << "Usuario o contrasena incorrecta. Intente de nuevo.\n";
            }
        }

        if (usuarioActual->suspendido) {
            cout << "Usuario suspendido. Acceso denegado.\n";
            return 0;
        }

        int opcion;

        do {
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
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion) {
                case 1:
                    if (usuarioActual->rol == "admin") {
                        registrarUsuario(usuarios, totalUsuarios);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 2:
                    if (usuarioActual->rol == "admin") {
                        eliminarUsuario(usuarios, totalUsuarios);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 3:
                    if (usuarioActual->rol == "admin") {
                        suspenderUsuario(usuarios, totalUsuarios);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 4:
                    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
                        agregarLibro(libros, totalLibros);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 5:
                    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
                        modificarLibro(libros, totalLibros);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 6:
                    if (usuarioActual->rol == "admin" || usuarioActual->rol == "empleado") {
                        eliminarLibro(libros, totalLibros);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 7:
                    if (usuarioActual->rol == "cliente") {
                        retirarLibro(libros, totalLibros);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 8:
                    if (usuarioActual->rol == "cliente") {
                        devolverLibro(libros, totalLibros);
                    } else {
                        cout << "Opcion no valida.\n";
                    }
                    break;
                case 9:
                    cout << "Cerrando sesion...\n";
                    usuarioActual = nullptr;
                    break;
                case 0:
                    cout << "Saliendo del sistema.\n";
                    return 0;
                default:
                    cout << "Opcion no valida.\n";
                    break;
            }
        } while (opcion != 9 && opcion != 0);
    }

    return 0;
}