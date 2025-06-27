#include <stdio.h>
#include "funciones.h"

int main() {
    inicializarProductosBase();
    int opcion;
    do {
        printf("\nMenu:\n");
        printf("1. Agregar producto\n");
        printf("2. Listar productos\n");
        printf("3. Agregar cliente\n");
        printf("4. Listar clientes\n");
        printf("5. Registrar venta\n");
        printf("6. Ver ventas\n");
        printf("7. Estadisticas\n");
        printf("8. Eliminar producto\n");
        printf("9. Eliminar cliente\n");
        printf("10. Editar producto\n");
        printf("11. Resumen de ventas\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: agregarProducto(); break;
            case 2: listarProductos(); break;
            case 3: agregarCliente(); break;
            case 4: listarClientes(); break;
            case 5: registrarVenta(); break;
            case 6: verVentas(); break;
            case 7: estadisticas(); break;
            case 8: eliminarProducto(); break;
            case 9: eliminarCliente(); break;
            case 10: editarProducto(); break;
            case 11: resumenVentas(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida\n");
        }
    } while(opcion != 0);

    return 0;
}
