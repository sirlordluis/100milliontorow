import csv
import sys

# Verificar si se proporciona el nombre del archivo CSV
if len(sys.argv) != 2:
    print("Por favor, proporciona el nombre del archivo CSV como argumento.")
    sys.exit(1)

csv_filename = sys.argv[1]

# Abrir el archivo CSV y generar los inserts SQL
with open(csv_filename, 'r') as csv_file:
    reader = csv.reader(csv_file, delimiter=',')
    
    # Saltar la primera fila si contiene encabezados
    next(reader, None)

    for row in reader:
        # Asegurarse de que los índices estén dentro del rango del array
        if len(row) >= 8:
            # Generar el insert SQL
            insert_sql = f"INSERT INTO chessgame (game_type, url , white, black, white_elo, black_elo, result) VALUES ('{row[0]}','{row[1]}', '{row[3]}', '{row[4]}', '{row[6]}', '{row[7]}', '{row[5]}');"
            
            # Imprimir el insert SQL en la salida estándar
            print(insert_sql)
        else:
            print(f"La fila no tiene suficientes columnas: {row}")
