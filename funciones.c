#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Función auxiliar para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Verifica si un producto con el mismo ID ya existe
int existeProducto(int id) {
    Producto p;
    FILE *f = fopen("productos.dat", "rb");
    if (!f) return 0;
    while (fread(&p, sizeof(Producto), 1, f)) {
        if (p.id == id) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

// Verifica si un cliente con el mismo ID ya existe
int existeCliente(int id) {
    Cliente c;
    FILE *f = fopen("clientes.dat", "rb");
    if (!f) return 0;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.id == id) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void agregarProducto() {
    Producto p;
    FILE *f = fopen("productos.dat", "ab");
    if (!f) {
        printf("Error al abrir productos.dat\n");
        return;
    }
    printf("ID: ");
    scanf("%d", &p.id);
    limpiarBuffer();
    if (existeProducto(p.id)) {
        printf("Ya existe un producto con ese ID.\n");
        fclose(f);
        return;
    }
    printf("Nombre: ");
    fgets(p.nombre, sizeof(p.nombre), stdin);
    p.nombre[strcspn(p.nombre, "\n")] = 0;
    printf("Precio: ");
    scanf("%f", &p.precio);
    printf("Stock: ");
    scanf("%d", &p.stock);
    fwrite(&p, sizeof(Producto), 1, f);
    fclose(f);
    printf("Producto agregado correctamente.\n");
}

void listarProductos() {
    Producto p;
    FILE *f = fopen("productos.dat", "rb");
    if (!f) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("\n%-5s %-25s %-10s %-6s\n", "ID", "Nombre", "Precio", "Stock");
    printf("------------------------------------------------------\n");
    while (fread(&p, sizeof(Producto), 1, f)) {
        printf("%-5d %-25s %-10.2f %-6d\n", p.id, p.nombre, p.precio, p.stock);
    }
    fclose(f);
}

void agregarCliente() {
    Cliente c;
    FILE *f = fopen("clientes.dat", "ab");
    if (!f) {
        printf("Error al abrir clientes.dat\n");
        return;
    }
    printf("ID: ");
    scanf("%d", &c.id);
    limpiarBuffer();
    if (existeCliente(c.id)) {
        printf("Ya existe un cliente con ese ID.\n");
        fclose(f);
        return;
    }
    printf("Nombre: ");
    fgets(c.nombre, sizeof(c.nombre), stdin);
    c.nombre[strcspn(c.nombre, "\n")] = 0;
    printf("Telefono: ");
    fgets(c.telefono, sizeof(c.telefono), stdin);
    c.telefono[strcspn(c.telefono, "\n")] = 0;
    fwrite(&c, sizeof(Cliente), 1, f);
    fclose(f);
    printf("Cliente agregado correctamente.\n");
}

void listarClientes() {
    Cliente c;
    FILE *f = fopen("clientes.dat", "rb");
    if (!f) {
        printf("No hay clientes registrados.\n");
        return;
    }
    printf("\nLista de clientes:\n");
    while (fread(&c, sizeof(Cliente), 1, f)) {
        printf("ID: %d, Nombre: %s, Telefono: %s\n", c.id, c.nombre, c.telefono);
    }
    fclose(f);
}

void listarProductosVenta() {
    Producto p;
    FILE *f = fopen("productos.dat", "rb");
    if (!f) {
        printf("No hay productos registrados.\n");
        return;
    }
    printf("\n%-5s %-25s %-10s %-6s\n", "ID", "Nombre", "Precio", "Stock");
    printf("------------------------------------------------------\n");
    while (fread(&p, sizeof(Producto), 1, f)) {
        printf("%-5d %-25s %-10.2f %-6d\n", p.id, p.nombre, p.precio, p.stock);
    }
    fclose(f);
}

// Busca el nombre de un producto por su ID
int obtenerNombreProducto(int id, char *nombre) {
    Producto p;
    FILE *f = fopen("productos.dat", "rb");
    if (!f) return 0;
    while (fread(&p, sizeof(Producto), 1, f)) {
        if (p.id == id) {
            strcpy(nombre, p.nombre);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

// Busca y muestra los datos de un cliente por su ID
int mostrarDatosCliente(int id) {
    Cliente c;
    FILE *f = fopen("clientes.dat", "rb");
    if (!f) return 0;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.id == id) {
            printf("Datos del cliente:\n");
            printf("ID: %d, Nombre: %s, Telefono: %s\n", c.id, c.nombre, c.telefono);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    printf("No se encontro un cliente con ese ID.\n");
    return 0;
}

// Busca el nombre de un cliente por su ID
int obtenerNombreCliente(int id, char *nombre) {
    Cliente c;
    FILE *f = fopen("clientes.dat", "rb");
    if (!f) return 0;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.id == id) {
            strcpy(nombre, c.nombre);
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void registrarVenta() {
    Venta v;
    int numProductos;
    char fechaVenta[11];
    FILE *f = fopen("ventas.dat", "ab");
    if (!f) {
        printf("Error al abrir ventas.dat\n");
        return;
    }
    printf("ID Venta: "); scanf("%d", &v.idVenta);
    printf("ID Cliente: "); scanf("%d", &v.idCliente);
    if (!mostrarDatosCliente(v.idCliente)) {
        fclose(f);
        printf("No se puede registrar la venta sin un cliente valido.\n");
        return;
    }
    printf("Cuantos productos desea vender en esta venta? ");
    scanf("%d", &numProductos);
    limpiarBuffer();
    printf("Fecha (YYYY-MM-DD): ");
    fgets(fechaVenta, sizeof(fechaVenta), stdin);
    fechaVenta[strcspn(fechaVenta, "\n")] = 0;
    for (int i = 0; i < numProductos; i++) {
        printf("\nProducto #%d\n", i+1);
        listarProductosVenta();
        printf("ID Producto: "); scanf("%d", &v.idProducto);
        printf("Cantidad: "); scanf("%d", &v.cantidad);
        limpiarBuffer();
        if (!descontarStock(v.idProducto, v.cantidad)) {
            printf("No hay suficiente stock para el producto ID %d. Venta cancelada para este producto.\n", v.idProducto);
            i--; // Permitir reintentar este producto
            continue;
        }
        strncpy(v.fecha, fechaVenta, sizeof(v.fecha));
        v.fecha[sizeof(v.fecha)-1] = '\0';
        fwrite(&v, sizeof(Venta), 1, f);
    }
    fclose(f);
    printf("Venta registrada correctamente.\n");
}

void verVentas() {
    Venta v;
    char nombreProd[50];
    FILE *f = fopen("ventas.dat", "rb");
    if (!f) {
        printf("No hay ventas registradas.\n");
        return;
    }
    printf("\nHistorial de ventas:\n");
    int ventaActual = -1;
    while (fread(&v, sizeof(Venta), 1, f)) {
        if (ventaActual != v.idVenta) {
            printf("\nVenta #%d | Cliente: %d\n", v.idVenta, v.idCliente);
            ventaActual = v.idVenta;
        }
        if (obtenerNombreProducto(v.idProducto, nombreProd)) {
            printf("  Producto: %s | Cantidad: %d | Fecha: %s\n", nombreProd, v.cantidad, v.fecha);
        } else {
            printf("  Producto: ID %d (no encontrado) | Cantidad: %d | Fecha: %s\n", v.idProducto, v.cantidad, v.fecha);
        }
    }
    fclose(f);
}

void estadisticas() {
    Venta v;
    int ventasProd[1000] = {0};
    int comprasCliente[1000] = {0};
    int ventasPorCliente[1000] = {0};
    int maxIdProd = 0, maxIdCli = 0;
    FILE *f = fopen("ventas.dat", "rb");
    if (!f) {
        printf("No hay ventas registradas.\n");
        return;
    }
    int lastVenta = -1;
    int lastCliente = -1;
    while (fread(&v, sizeof(Venta), 1, f)) {
        if (v.idProducto >= 0 && v.idProducto < 1000) {
            ventasProd[v.idProducto] += v.cantidad;
            if (v.idProducto > maxIdProd) maxIdProd = v.idProducto;
        }
        if (v.idCliente >= 0 && v.idCliente < 1000) {
            comprasCliente[v.idCliente] += v.cantidad;
            if (v.idCliente > maxIdCli) maxIdCli = v.idCliente;
        }
        // Contar ventas únicas por cliente
        if (v.idVenta != lastVenta || v.idCliente != lastCliente) {
            ventasPorCliente[v.idCliente]++;
            lastVenta = v.idVenta;
            lastCliente = v.idCliente;
        }
    }
    fclose(f);
    printf("\nEstadisticas de ventas (por producto):\n");
    printf("%-5s %-25s %-10s\n", "ID", "Nombre", "Vendidos");
    printf("-----------------------------------------------\n");
    char nombreProd[50];
    int maxProd = 0, idMaxProd = -1;
    for (int i = 0; i <= maxIdProd; i++) {
        if (ventasProd[i] > 0) {
            if (obtenerNombreProducto(i, nombreProd))
                printf("%-5d %-25s %-10d\n", i, nombreProd, ventasProd[i]);
            else
                printf("%-5d %-25s %-10d\n", i, "Desconocido", ventasProd[i]);
            if (ventasProd[i] > maxProd) {
                maxProd = ventasProd[i];
                idMaxProd = i;
            }
        }
    }
    if (idMaxProd != -1) {
        obtenerNombreProducto(idMaxProd, nombreProd);
        printf("\nProducto mas vendido: %s (ID %d) con %d unidades\n", nombreProd, idMaxProd, maxProd);
    } else {
        printf("\nNo hay productos vendidos.\n");
    }
    int maxCli = 0, idMaxCli = -1;
    for (int i = 0; i <= maxIdCli; i++) {
        if (ventasPorCliente[i] > maxCli) {
            maxCli = ventasPorCliente[i];
            idMaxCli = i;
        }
    }
    if (idMaxCli != -1 && maxCli > 0) {
        char nombreCli[50];
        if (obtenerNombreCliente(idMaxCli, nombreCli))
            printf("Cliente con mas compras: %s (ID %d) con %d ventas realizadas\n", nombreCli, idMaxCli, maxCli);
        else
            printf("Cliente con mas compras: ID %d con %d ventas realizadas\n", idMaxCli, maxCli);
    } else {
        printf("No hay clientes con compras registradas.\n");
    }
}

// Función para inicializar productos base
void inicializarProductosBase() {
    FILE *f = fopen("productos.dat", "rb");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        if (size > 0) return; // Ya existen productos
    }
    f = fopen("productos.dat", "wb");
    if (!f) return;
    Producto base[] = {
        {1, "Filtro de aceite", 8.50, 30},
        {2, "Bujia NGK", 3.20, 50},
        {3, "Pastillas de freno", 25.00, 20},
        {4, "Aceite 10W40", 18.00, 40},
        {5, "Correa de distribucion", 45.00, 10},
        {6, "Amortiguador delantero", 60.00, 8},
        {7, "Bateria 12V", 75.00, 12},
        {8, "Filtro de aire", 10.00, 25},
        {9, "Lampara H4", 5.00, 35},
        {10, "Termostato", 15.00, 15}
    };
    fwrite(base, sizeof(Producto), 10, f);
    fclose(f);
}

void eliminarProducto() {
    listarProductos();
    int id, encontrado = 0;
    printf("Ingrese el ID del producto a eliminar: ");
    scanf("%d", &id);
    FILE *f = fopen("productos.dat", "rb");
    if (!f) {
        printf("No hay productos registrados.\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    Producto p;
    while (fread(&p, sizeof(Producto), 1, f)) {
        if (p.id != id) {
            fwrite(&p, sizeof(Producto), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(f);
    fclose(temp);
    remove("productos.dat");
    rename("temp.dat", "productos.dat");
    if (encontrado)
        printf("Producto eliminado correctamente.\n");
    else
        printf("No se encontro un producto con ese ID.\n");
}

void eliminarCliente() {
    listarClientes();
    int id, encontrado = 0;
    printf("Ingrese el ID del cliente a eliminar: ");
    scanf("%d", &id);
    FILE *f = fopen("clientes.dat", "rb");
    if (!f) {
        printf("No hay clientes registrados.\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, f)) {
        if (c.id != id) {
            fwrite(&c, sizeof(Cliente), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    fclose(f);
    fclose(temp);
    remove("clientes.dat");
    rename("temp.dat", "clientes.dat");
    if (encontrado)
        printf("Cliente eliminado correctamente.\n");
    else
        printf("No se encontro un cliente con ese ID.\n");
}

void editarProducto() {
    int id, encontrado = 0;
    printf("Ingrese el ID del producto a editar: ");
    scanf("%d", &id);
    FILE *f = fopen("productos.dat", "rb");
    if (!f) {
        printf("No hay productos registrados.\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    Producto p;
    while (fread(&p, sizeof(Producto), 1, f)) {
        if (p.id == id) {
            encontrado = 1;
            printf("Producto actual: %s | Precio: %.2f | Stock: %d\n", p.nombre, p.precio, p.stock);
            printf("Nuevo nombre (enter para mantener): ");
            limpiarBuffer();
            char nuevoNombre[50];
            fgets(nuevoNombre, sizeof(nuevoNombre), stdin);
            if (nuevoNombre[0] != '\n') {
                nuevoNombre[strcspn(nuevoNombre, "\n")] = 0;
                strncpy(p.nombre, nuevoNombre, sizeof(p.nombre));
                p.nombre[sizeof(p.nombre)-1] = '\0';
            }
            printf("Nuevo precio (-1 para mantener): ");
            float nuevoPrecio;
            scanf("%f", &nuevoPrecio);
            if (nuevoPrecio >= 0) p.precio = nuevoPrecio;
            printf("Nuevo stock (-1 para mantener): ");
            int nuevoStock;
            scanf("%d", &nuevoStock);
            if (nuevoStock >= 0) p.stock = nuevoStock;
            printf("Producto editado.\n");
        }
        fwrite(&p, sizeof(Producto), 1, temp);
    }
    fclose(f);
    fclose(temp);
    remove("productos.dat");
    rename("temp.dat", "productos.dat");
    if (!encontrado)
        printf("No se encontro un producto con ese ID.\n");
}

// Modifica el stock de un producto por ID, retorna 1 si exito, 0 si no hay stock suficiente
int descontarStock(int id, int cantidad) {
    int exito = 0;
    FILE *f = fopen("productos.dat", "rb");
    if (!f) return 0;
    FILE *temp = fopen("temp.dat", "wb");
    Producto p;
    while (fread(&p, sizeof(Producto), 1, f)) {
        if (p.id == id) {
            if (p.stock >= cantidad) {
                p.stock -= cantidad;
                exito = 1;
            } else {
                exito = 0;
            }
        }
        fwrite(&p, sizeof(Producto), 1, temp);
    }
    fclose(f);
    fclose(temp);
    remove("productos.dat");
    rename("temp.dat", "productos.dat");
    return exito;
}

void resumenVentas() {
    Venta v;
    int totalVentas = 0;
    float totalDinero = 0.0;
    FILE *f = fopen("ventas.dat", "rb");
    if (!f) {
        printf("No hay ventas registradas.\n");
        return;
    }
    char nombreProd[50];
    float precio = 0.0;
    while (fread(&v, sizeof(Venta), 1, f)) {
        totalVentas++;
        // Buscar precio del producto
        Producto p;
        FILE *fp = fopen("productos.dat", "rb");
        if (fp) {
            while (fread(&p, sizeof(Producto), 1, fp)) {
                if (p.id == v.idProducto) {
                    precio = p.precio;
                    break;
                }
            }
            fclose(fp);
        }
        totalDinero += precio * v.cantidad;
    }
    fclose(f);
    printf("\nResumen de ventas:\n");
    printf("Total de productos vendidos (lineas de venta): %d\n", totalVentas);
    printf("Dinero total recaudado: $%.2f\n", totalDinero);
}
