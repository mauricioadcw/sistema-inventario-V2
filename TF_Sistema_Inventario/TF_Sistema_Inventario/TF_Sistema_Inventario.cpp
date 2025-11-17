#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;

// Estructura para productos
struct Producto {
    int codigo;
    string nombre;
    int stock;
    float precio;
};

// Prototipos de funciones
void mostrarPresentacion();
void menuPrincipal();
bool procesoDatos(Producto**, int*);

void registrarProducto(Producto**, int*);
void listarProductos(Producto**, int*);
void calcularValorInventario(Producto**, int*);
void buscarProductoPorCodigo(Producto**, int*);
void actualizarProducto(Producto**, int*);

int asignarPosicion(Producto**, int*);
bool codigoValido(int, Producto**, int*, bool);
bool esNumero(string);
bool esEntero(string);
void expandirInventario(Producto***, int*);
void verificarExpansion(Producto***, int*);

int main()
{
    mostrarPresentacion();
    menuPrincipal();

    int* n = new int;
    *n = 3;

    Producto** inventario = new Producto * [*n];

    for (int i = 0; i < *n; i++)
    {
        inventario[i] = new Producto;
        inventario[i]->codigo = 0;
        inventario[i]->nombre = "";
        inventario[i]->stock = 0;
        inventario[i]->precio = 0.0;
    }

    bool salir;
    do
    {
        menuPrincipal();
        salir = procesoDatos(inventario, n);
        verificarExpansion(&inventario, n);
    } while (!salir);

    for (int i = 0; i < *n; i++)
    {
        delete inventario[i];
    }
    delete[] inventario;
    delete n;

    return 0;
}

void mostrarPresentacion() {
    system("cls");
    cout << "\n\n";
    cout << "\t===========================================================\n";
    cout << "\t                                                           \n";
    cout << "\t            SISTEMA DE INVENTARIO \"DATA STOCK\"           \n";
    cout << "\t                                                           \n";
    cout << "\t===========================================================\n";
    cout << "\t                                                           \n";
    cout << "\t                      TRABAJO FINAL                        \n";
    cout << "\t                 LENGUAJE DE PROGRAMACION                  \n";
    cout << "\t                                                           \n";
    cout << "\t===========================================================\n";
    cout << "\t                                                           \n";
    cout << "\t                    <- INTEGRANTES ->                      \n";
    cout << "\t                                                           \n";
    cout << "\t     - Mauricio Adriel del Castillo Wan...(U202517849)     \n";
    cout << "\t     - Joaking Alonso Cruz Garvich........(U20251b984)     \n";
    cout << "\t     - Sharon Jazmin Valeriano Blas.......(U20251F655)     \n";
    cout << "\t     - Thiago Andrei Zelayes Escobedo.....(U202512708)     \n";
    cout << "\t                                                           \n";
    cout << "\t===========================================================\n";
    cout << "\tPresione una tecla para continuar...";
    _getch();
}

void menuPrincipal() {
    system("cls");
    cout << "\n\t=========================================================";
    cout << "\n\t          SISTEMA DE INVENTARIO \"DATA STOCK\"           ";
    cout << "\n\t=========================================================";
    cout << "\n\t 1. Registrar productos";
    cout << "\n\t 2. Listar productos con stock y precio";
    cout << "\n\t 3. Calcular valor total de inventario";
    cout << "\n\t 4. Buscar producto por codigo";
    cout << "\n\t 5. Actualizar stock o precio";
    cout << "\n\t 6. Guardar inventario en archivo (Proximamente)";
    cout << "\n\t 7. Cargar inventario desde archivo (Proximamente)";
    cout << "\n\t 8. Generar reportes de productos (Proximamente)";
    cout << "\n\t 9. Salir del sistema";
    cout << "\n\t=========================================================\n";
}

bool procesoDatos(Producto** inventario, int* n) {
    string entrada;
    int opcion = 0;

    while (true)
    {
        cout << "\tElija una opcion (1 - 9): ";
        cin >> entrada;

        if (!esNumero(entrada))
        {
            continue;
        }

        opcion = stoi(entrada);

        if (opcion < 1 || opcion > 9)
        {
            cout << "\t> ERROR: Opcion no valida\n" << endl;
            continue;
        }
        break;
    }

    switch (opcion)
    {
    case 1: registrarProducto(inventario, n); break;
    case 2: listarProductos(inventario, n); break;
    case 3: calcularValorInventario(inventario, n); break;
    case 4: buscarProductoPorCodigo(inventario, n); break;
    case 5: actualizarProducto(inventario, n); break;
    case 6:
        cout << "\n\t> Funcion en desarrollo..." << endl;
        Sleep(1500);
        break;
    case 7:
        cout << "\n\t> Funcion en desarrollo..." << endl;
        Sleep(1500);
        break;
    case 8:
        cout << "\n\t> Funcion en desarrollo..." << endl;
        Sleep(1500);
        break;
    case 9:
        cout << "\n\tSee u next time ;)" << endl;

        return true;
    }

    return false;
}

void registrarProducto(Producto** inventario, int* n) {
    int codigo = 0, stock = 0;
    float precio = 0.0;
    string nombre;
    string entrada;
    int fila;

    cout << "\n\t-------- REGISTRAR NUEVO PRODUCTO --------\n\n";

    while (true)
    {
        cout << "\tIngrese el codigo del producto (6 digitos): ";
        cin >> entrada;

        if (!esEntero(entrada))
        {
            continue;
        }

        codigo = stoi(entrada);

        if (codigoValido(codigo, inventario, n, true))
        {
            break;
        }
    }

    cin.ignore(10000, '\n');

    while (true)
    {
        cout << "\tIngrese el nombre del producto: ";
        getline(cin, nombre);

        if (nombre == "")
        {
            cout << "\t> ERROR: El nombre no puede estar vacio\n" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "\tIngrese el stock del producto: ";
        cin >> entrada;

        if (!esEntero(entrada))
        {
            continue;
        }

        stock = stoi(entrada);

        if (stock < 0)
        {
            cout << "\t> ERROR: El stock no puede ser negativo\n" << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "\tIngrese el precio del producto: ";
        cin >> entrada;

        if (!esNumero(entrada))
        {
            continue;
        }
        else
        {
            precio = stof(entrada);
        }

        if (precio < 0)
        {
            cout << "\t> ERROR: El precio no puede ser negativo\n" << endl;
            continue;
        }
        break;
    }

    fila = asignarPosicion(inventario, n);
    inventario[fila]->codigo = codigo;
    inventario[fila]->nombre = nombre;
    inventario[fila]->stock = stock;
    inventario[fila]->precio = precio;

    cout << "\n\t> Producto registrado con exito!";
    Sleep(1500);
}

void listarProductos(Producto** inventario, int* n) {
    cout << "\n\t=============== LISTADO DE PRODUCTOS ===============\n";
    cout << "\t "
        << left
        << setw(6) << "Codigo" << " | "
        << setw(20) << "Nombre" << " | "
        << setw(6) << "Stock" << " | "
        << "Precio"
        << endl;
    cout << "\t--------|----------------------|--------|-----------" << endl;

    for (int i = 0; i < *n; i++)
    {
        if (i == 0 && inventario[i]->codigo == 0)
        {
            cout << "\t "
                << left
                << setw(6) << "-" << " | "
                << setw(20) << "-" << " | "
                << setw(6) << "-" << " | "
                << "-"
                << endl;
        }
        if (inventario[i]->codigo != 0)
        {
            cout << "\t "
                << left
                << setw(6) << inventario[i]->codigo << " | "
                << setw(20) << inventario[i]->nombre << " | "
                << right
                << setw(6) << inventario[i]->stock << " | "
                << "S/. " << fixed << setprecision(2) << inventario[i]->precio
                << endl;
        }
    }

    cout << "\n\tPresione una tecla para continuar...";
    _getch();
}

void calcularValorInventario(Producto** inventario, int* n) {
    cout << "\n\t================== VALOR DE INVENTARIO ==================\n";

    float total = 0;
    int cont = 0;

    for (int i = 0; i < *n; i++) {
        if (inventario[i]->codigo != 0) {
            cont++;
            float valor = inventario[i]->stock * inventario[i]->precio;
            total += valor;

            cout << "\tProducto: " << left << setw(20) << inventario[i]->nombre
                << " Valor: S/. " << fixed << setprecision(2) << valor << endl;
        }
    }

    if (cont == 0) {
        cout << "\n\tNo hay productos registrados\n";
    }
    else {
        cout << "\t---------------------------------------------------------" << endl;
        cout << "\tValor total de inventario: S/. " << fixed << setprecision(2) << total << "\n";
    }

    cout << "\n\tPresione una tecla para continuar...";
    _getch();
}

void buscarProductoPorCodigo(Producto** inventario, int* n) {
    int codigoBuscado = 0;
    string entrada;
    bool encontrado = false;
    int fila = -1;

    cout << "\n\t--------------- BUSCAR PRODUCTO POR CODIGO ---------------\n\n";

    while (true)
    {
        cout << "\tIngrese el codigo del producto a buscar: ";
        cin >> entrada;

        if (!esEntero(entrada))
        {
            continue;
        }

        codigoBuscado = stoi(entrada);

        if (!codigoValido(codigoBuscado, inventario, n, false))
        {
            continue;
        }
        break;
    }

    for (int i = 0; i < *n; i++)
    {
        if (inventario[i]->codigo == codigoBuscado)
        {
            encontrado = true;
            fila = i;
            break;
        }
    }

    if (encontrado)
    {
        cout << "\n\t> Producto encontrado:\n" << endl;
        cout << "\tNombre: " << inventario[fila]->nombre << endl;
        cout << "\tStock: " << inventario[fila]->stock << endl;
        cout << "\tPrecio: S/. " << fixed << setprecision(2) << inventario[fila]->precio << endl;

        cout << "\n\t "
            << left
            << setw(6) << "Codigo" << " | "
            << setw(20) << "Nombre" << " | "
            << setw(6) << "Stock" << " | "
            << "Precio"
            << endl;
        cout << "\t--------|----------------------|--------|--------" << endl;

        cout << "\t "
            << left
            << setw(6) << inventario[fila]->codigo << " | "
            << setw(20) << inventario[fila]->nombre << " | "
            << right
            << setw(6) << inventario[fila]->stock << " | "
            << "S/. " << fixed << setprecision(2) << inventario[fila]->precio
            << endl;

        float valorTotal = 0.0;
        valorTotal = inventario[fila]->stock * inventario[fila]->precio;
        cout << "\n\tValor total: S/. " << fixed << setprecision(2) << valorTotal << endl;

        cout << "\n\tPresione una tecla para continuar...";
        _getch();
    }
    else
    {
        cout << "\n\t> Sin existencias" << endl;
        Sleep(1500);
    }
}

void actualizarProducto(Producto** inventario, int* n) {
    int codigoBuscado = 0;
    string entrada;
    bool encontrado = false;
    int fila = -1;

    cout << "\n\t-------- ACTUALIZAR STOCK O PRECIO --------\n\n";

    while (true)
    {
        cout << "\tIngrese codigo del producto: ";
        cin >> entrada;

        if (!esEntero(entrada))
        {
            continue;
        }

        codigoBuscado = stoi(entrada);

        if (!codigoValido(codigoBuscado, inventario, n, false))
        {
            continue;
        }
        break;
    }

    for (int i = 0; i < *n; i++)
    {
        if (inventario[i]->codigo == codigoBuscado)
        {
            encontrado = true;
            fila = i;
            break;
        }
    }

    if (encontrado)
    {
        int nuevoStock;
        float nuevoPrecio;

        cout << "\n\tProducto encontrado: " << inventario[fila]->nombre << endl;
        cout << "\tStock actual: " << inventario[fila]->stock << endl;
        cout << "\tPrecio actual: S/. " << fixed << setprecision(2) << inventario[fila]->precio << endl;

        while (true)
        {
            cout << "\n\tNuevo stock: ";
            cin >> entrada;

            if (!esEntero(entrada))
            {
                continue;
            }

            nuevoStock = stoi(entrada);

            if (nuevoStock < 0)
            {
                cout << "\t> ERROR: El stock no puede ser negativo\n" << endl;
                continue;
            }
            break;
        }

        while (true)
        {
            cout << "\tNuevo precio: ";
            cin >> entrada;

            if (!esNumero(entrada))
            {
                continue;
            }

            nuevoPrecio = stof(entrada);

            if (nuevoPrecio < 0)
            {
                cout << "\t> ERROR: El precio no puede ser negativo\n" << endl;
                continue;
            }
            break;
        }

        inventario[fila]->stock = nuevoStock;
        inventario[fila]->precio = nuevoPrecio;

        cout << "\n\t> Datos actualizados correctamente";
        Sleep(1500);
    }
    else
    {
        cout << "\n\t> Producto no encontrado en inventario" << endl;
        Sleep(2000);
    }
}

int asignarPosicion(Producto** inventario, int* n) {
    for (int i = 0; i < *n; i++)
    {
        if (inventario[i]->codigo == 0)
        {
            return i;
        }
    }
    return -1;
}

bool codigoValido(int codigo, Producto** inventario, int* n, bool evCodigoExist) {
    if (codigo < 100000 || codigo > 999999)
    {
        cout << "\t> ERROR: El codigo debe tener seis digitos\n" << endl;
        return false;
    }

    if (evCodigoExist)
    {
        for (int i = 0; i < *n; i++)
        {
            if (inventario[i]->codigo == codigo)
            {
                cout << "\t> ERROR: Codigo existente\n" << endl;
                return false;
            }
        }
    }

    return true;
}

bool esNumero(string entrada) {
    bool punto = false;

    if (entrada == "" || entrada == ".") {
        cout << "\t> ERROR: Valor ingresado no valido\n" << endl;
        return false;
    }

    for (int i = 0; i < entrada.size(); i++)
    {
        char c = entrada[i];
        if (c == '.')
        {
            if (punto)
            {
                cout << "\t> ERROR: Valor ingresado no valido\n" << endl;
                return false;
            }
            punto = true;
        }
        else if (!isdigit(c))
        {
            cout << "\t> ERROR: Se esperaba un numero\n" << endl;
            return false;
        }
    }
    return true;
}

bool esEntero(string entrada) {
    if (entrada == "") {
        cout << "\t> ERROR: Valor ingresado no valido\n" << endl;
        return false;
    }

    for (int i = 0; i < entrada.size(); i++) {
        if (!isdigit(entrada[i])) {
            cout << "\t> ERROR: Se esperaba un numero entero\n" << endl;
            return false;
        }
    }
    return true;
}

void expandirInventario(Producto*** inventario, int* n) {
    int nuevoTam = *n + 3;

    Producto** nuevo = new Producto * [nuevoTam];

    for (int i = 0; i < *n; i++) {
        nuevo[i] = (*inventario)[i];
    }

    for (int i = *n; i < nuevoTam; i++) {
        nuevo[i] = new Producto;
        nuevo[i]->codigo = 0;
        nuevo[i]->nombre = "";
        nuevo[i]->stock = 0;
        nuevo[i]->precio = 0.0;
    }

    delete[] * inventario;
    *inventario = nuevo;
    *n = nuevoTam;
}

void verificarExpansion(Producto*** inventario, int* n) {
    if ((*inventario)[*n - 1]->codigo != 0)
    {
        expandirInventario(inventario, n);
    }
}