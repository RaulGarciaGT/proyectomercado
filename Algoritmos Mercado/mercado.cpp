//Abrilos las liberrias que deseamos utilizar para el correcto funcionamiento del programa
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//Definimos la estructura del programa
class Producto {
public:
    string codigo;
    string nombre;
    double precio;
    string proveedor;
    int existencia;
    char estado;

    Producto(const string& codigo, const string& nombre, double precio, const string& proveedor, int existencia, char estado)
        : codigo(codigo), nombre(nombre), precio(precio), proveedor(proveedor), existencia(existencia), estado(estado) {}
};

// Función para guardar los productos en un archivo de texto
void GuardarProductos(const vector<Producto>& productos) {
    ofstream archivo("productos.txt");
    if (archivo.is_open()) {
        for (const Producto& producto : productos) {
            archivo << producto.codigo << " " << producto.nombre << " " << producto.precio << " " << producto.proveedor << " " << producto.existencia << " " << producto.estado << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar los productos." << endl;
    }
}

// Función para cargar los productos desde un archivo de texto
vector<Producto> CargarProductos() {
    vector<Producto> productos;
    ifstream archivo("productos.txt");
    if (archivo.is_open()) {
        string codigo, nombre, proveedor;
        double precio;
        int existencia;
        char estado;
        while (archivo >> codigo >> nombre >> precio >> proveedor >> existencia >> estado) {
            Producto producto(codigo, nombre, precio, proveedor, existencia, estado);
            productos.push_back(producto);
        }
        archivo.close();
    }
    return productos;
}

int main() {
    vector<Producto> productos;
    int opcion;

    do {
        cout << "Elija que acción desea realizar:\n";
        cout << "1. Agregar producto\n";
        cout << "2. Modificar un producto\n";
        cout << "3. Consultar un producto\n";
        cout << "4. Salir\n";
        cout << "Escriba el numero de la accion que desea realizar: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string codigo;
                string nombre;
                double precio;
                string proveedor;
                int existencia;
                char estado;

                cout << "Asigne un código del producto: ";
                cin >> codigo;
                cout << "Ingrese el nombre del producto: ";
                cin >> nombre;
                cout << "Ingrese el precio que tendrá el producto: ";
                cin >> precio;
                cout << "Proveedor: ";
                cin.ignore();
                getline(cin, proveedor);
                cout << "Ingrese la existencia del producto: ";
                cin >> existencia;
                cout << "¿El producto fue aprobado? (A para sí, R para no): ";
                cin >> estado;

                Producto nuevoProducto(codigo, nombre, precio, proveedor, existencia, estado);
                productos.push_back(nuevoProducto);
                GuardarProductos(productos);
                break;
            }
            case 2: {
                int codigoModificar;
                cout << "Ingrese el código del producto que desea modificar: ";
                cin >> codigoModificar;

                bool encontrado = false;
                for (Producto& producto : productos) {
                    if (producto.codigo == to_string(codigoModificar)) {
                        encontrado = true;

                        cout << "Ingrese el nuevo precio del producto: $";
                        cin >> producto.precio;
                        cout << "Ingrese el nuevo proveedor del producto: ";
                        cin.ignore();
                        getline(cin, producto.proveedor);
                        cout << "Ingrese la nueva existencia del producto: ";
                        cin >> producto.existencia;
                        cout << "El producto está disponible? (1 para sí, 0 para no): ";
                        cin >> producto.estado;

                        cout << "Producto modificado exitosamente.\n";
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Producto no encontrado. Intente nuevamente." << endl;
                }

                break;
            }
            case 3: {
                int codigoConsultar;
                cout << "Ingrese el código del producto que desea consultar: ";
                cin >> codigoConsultar;

                bool encontrado = false;
                for (const Producto& producto : productos) {
                    if (producto.codigo == to_string(codigoConsultar)) {
                        encontrado = true;
                        cout << "Código: " << producto.codigo << endl;
                        cout << "Nombre: " << producto.nombre << endl;
                        cout << "Precio: Q." << producto.precio << endl;
                        cout << "Proveedor: " << producto.proveedor << endl;
                        cout << "Existencia: " << producto.existencia << endl;
                        cout << "Estado: " << (producto.estado ? "Aprobado" : "Reprobado") << endl;
                        cout << "-------------------------\n";
                        break;
                    }
                }

                if (!encontrado) {
                    cout << "Producto no encontrado." << endl;
                }

                break;
            }
            case 4: {
                cout << "Saliendo del programa. Hasta luego!" << endl;
                break;
            }
            default: {
                cout << "Opción no válida. Por favor, elija una opción válida." << endl;
            }
        }
    } while (opcion != 4);

    return 0;
}