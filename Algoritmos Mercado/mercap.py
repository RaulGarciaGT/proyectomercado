python

import os

class Producto:
    def __init__(self, codigo, nombre, precio, proveedor, existencia, estado):
        self.codigo = codigo
        self.nombre = nombre
        self.precio = precio
        self.proveedor = proveedor
        self.existencia = existencia
        self.estado = estado

def guardar_productos(productos):
    with open("productos.txt", "w") as archivo:
        for producto in productos:
            archivo.write(f"{producto.codigo} {producto.nombre} {producto.precio} {producto.proveedor} {producto.existencia} {producto.estado}\n")

def cargar_productos():
    productos = []
    if os.path.exists("productos.txt"):
        with open("productos.txt", "r") as archivo:
            for linea in archivo:
                datos = linea.split()
                codigo, nombre, precio, proveedor, existencia, estado = datos
                producto = Producto(codigo, nombre, float(precio), proveedor, int(existencia), estado)
                productos.append(producto)
    return productos

def main():
    productos = []
    while True:
        print("Elija qué acción desea realizar:")
        print("1. Agregar producto")
        print("2. Modificar un producto")
        print("3. Consultar un producto")
        print("4. Salir")
        opcion = input("Escriba el número de la acción que desea realizar: ")

        if opcion == "1":
            codigo = input("Asigne un código del producto: ")
            nombre = input("Ingrese el nombre del producto: ")
            precio = float(input("Ingrese el precio que tendrá el producto: "))
            proveedor = input("Proveedor: ")
            existencia = int(input("Ingrese la existencia del producto: "))
            estado = input("¿El producto fue aprobado? (A para sí, R para no): ").upper()

            nuevo_producto = Producto(codigo, nombre, precio, proveedor, existencia, estado)
            productos.append(nuevo_producto)
            guardar_productos(productos)
        elif opcion == "2":
            codigo_modificar = input("Ingrese el código del producto que desea modificar: ")
            encontrado = False
            for producto in productos:
                if producto.codigo == codigo_modificar:
                    encontrado = True
                    producto.precio = float(input("Ingrese el nuevo precio del producto: $"))
                    producto.proveedor = input("Ingrese el nuevo proveedor del producto: ")
                    producto.existencia = int(input("Ingrese la nueva existencia del producto: "))
                    producto.estado = input("El producto está disponible? (1 para sí, 0 para no): ").upper()
                    print("Producto modificado exitosamente.")
                    break
            if not encontrado:
                print("Producto no encontrado. Intente nuevamente.")
        elif opcion == "3":
            codigo_consultar = input("Ingrese el código del producto que desea consultar: ")
            encontrado = False
            for producto in productos:
                if producto.codigo == codigo_consultar:
                    encontrado = True
                    print("Código:", producto.codigo)
                    print("Nombre:", producto.nombre)
                    print(f"Precio: ${producto.precio}")
                    print("Proveedor:", producto.proveedor)
                    print("Existencia:", producto.existencia)
                    print("Estado: Aprobado" if producto.estado == "A" else "Reprobado")
                    print("-------------------------")
                    break
            if not encontrado:
                print("Producto no encontrado.")
        elif opcion == "4":
            print("Saliendo del programa. ¡Hasta luego!")
            break
        else:
            print("Opción no válida. Por favor, elija una opción válida.")

if __name__ == "__main__":
    main()