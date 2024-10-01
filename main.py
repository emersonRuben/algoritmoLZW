def comprimir_LZW(mensaje):
    # Inicialización del diccionario con todos los caracteres ASCII
    diccionario = {chr(i): i for i in range(256)}
    codigo_actual = 256
    cadena = ""
    codificado = []
    
    # Procesar el mensaje
    for caracter in mensaje:
        cadena_caracter = cadena + caracter
        if cadena_caracter in diccionario:
            cadena = cadena_caracter
        else:
            codificado.append(diccionario[cadena])
            diccionario[cadena_caracter] = codigo_actual
            codigo_actual += 1
            cadena = caracter
    
    if cadena:
        codificado.append(diccionario[cadena])
    
    return codificado


def descomprimir_LZW(codificado):
    # Inicialización del diccionario inverso con todos los caracteres ASCII
    diccionario = {i: chr(i) for i in range(256)}
    codigo_actual = 256
    cadena = chr(codificado[0])
    resultado = cadena
    
    # Procesar los códigos
    for codigo in codificado[1:]:
        if codigo in diccionario:
            entrada = diccionario[codigo]
        elif codigo == codigo_actual:
            entrada = cadena + cadena[0]
        else:
            raise ValueError("Código incorrecto en la secuencia codificada")
        
        resultado += entrada
        diccionario[codigo_actual] = cadena + entrada[0]
        codigo_actual += 1
        cadena = entrada
    
    return resultado


# Mensaje de entrada
mensaje = "ABABABAABABBBBBABAAABAB"
# Comprimir el mensaje utilizando LZW
mensaje_codificado = comprimir_LZW(mensaje)
print(f"Mensaje comprimido: {mensaje_codificado}")

# Descomprimir el mensaje
mensaje_descomprimido = descomprimir_LZW(mensaje_codificado)
print(f"Mensaje descomprimido: {mensaje_descomprimido}")
