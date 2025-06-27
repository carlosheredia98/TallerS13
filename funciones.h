#ifndef FUNCIONES_H
#define FUNCIONES_H

typedef struct {
    int id;
    char nombre[50];
    float precio;
    int stock;
} Producto;

typedef struct {
    int id;
    char nombre[50];
    char telefono[15];
} Cliente;

typedef struct {
    int idVenta;
    int idCliente;
    int idProducto;
    int cantidad;
    char fecha[11]; // formato: YYYY-MM-DD
} Venta;

void agregarProducto();
void listarProductos();
void agregarCliente();
void listarClientes();
void registrarVenta();
void verVentas();
void estadisticas();
void inicializarProductosBase();
void listarProductosVenta();
int obtenerNombreProducto(int id, char *nombre);
int obtenerNombreCliente(int id, char *nombre);
void eliminarProducto();
void eliminarCliente();
int mostrarDatosCliente(int id);
void editarProducto();
int descontarStock(int id, int cantidad);
void resumenVentas();

#endif
