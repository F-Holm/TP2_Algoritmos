import os

def numerar_lineas(archivo, carpeta_salida="./entrega"):
    # Verifica que el archivo exista
    if not os.path.isfile(archivo):
        print(f"El archivo '{archivo}' no existe.")
        return

    # Crea la carpeta de salida si no existe
    os.makedirs(carpeta_salida, exist_ok=True)

    # Obtiene el nombre base del archivo sin extensión
    nombre_base = os.path.splitext(os.path.basename(archivo))[0]
    nuevo_nombre = f"{nombre_base}.txt"
    nuevo_path = os.path.join(carpeta_salida, nuevo_nombre)

    # Abre los archivos
    with open(archivo, "r", encoding="utf-8") as entrada, \
         open(nuevo_path, "w", encoding="utf-8") as salida:
        
        for i, linea in enumerate(entrada, start=1):
            salida.write(f"{i:03}: {linea}")

    print(f"Archivo generado: {nuevo_path}")

if __name__ == "__main__":
    # Lista de archivos hardcodeada
    archivos = [
        "TP2V1_K1021G10_HOLM FEDERICO.cpp",
        "datos/Aeropuertos.Txt",
        "datos/Vuelos.Txt",
        "datos/Consultas.Txt",
        "Listado Consulta Vuelos.Txt"
    ]

    for archivo in archivos:
        numerar_lineas(archivo)
