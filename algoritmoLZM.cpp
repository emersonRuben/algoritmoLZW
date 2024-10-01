#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Función para comprimir utilizando el algoritmo LZW
vector<int> comprimirLZW(string mensaje) {
    // Inicializar el diccionario con los caracteres ASCII
    unordered_map<string, int> diccionario;
    for (int i = 0; i < 256; i++) {
        diccionario[string(1, char(i))] = i;
    }

    int codigoActual = 256; // Primer código disponible
    string cadena = "";
    vector<int> codificado;

    for (char caracter : mensaje) {
        string cadenaCaracter = cadena + caracter;

        // Si la cadena ya está en el diccionario, expandirla
        if (diccionario.find(cadenaCaracter) != diccionario.end()) {
            cadena = cadenaCaracter;
        } else {
            // Si no está, agregar el código de la cadena anterior al vector
            codificado.push_back(diccionario[cadena]);
            // Agregar la nueva secuencia al diccionario
            diccionario[cadenaCaracter] = codigoActual++;
            cadena = string(1, caracter); // Reiniciar cadena con el nuevo caracter
        }
    }

    // Agregar el último código al vector
    if (!cadena.empty()) {
        codificado.push_back(diccionario[cadena]);
    }

    return codificado;
}

// Función para descomprimir utilizando el algoritmo LZW
string descomprimirLZW(vector<int>& codigos) {
    // Inicializar el diccionario inverso con los caracteres ASCII
    unordered_map<int, string> diccionario;
    for (int i = 0; i < 256; i++) {
        diccionario[i] = string(1, char(i));
    }

    int codigoActual = 256; // Primer código disponible
    string cadena = diccionario[codigos[0]]; // Primer carácter decodificado
    string resultado = cadena;

    for (size_t i = 1; i < codigos.size(); i++) {
        int codigo = codigos[i];
        string entrada;

        // Si el código está en el diccionario, tomar la entrada correspondiente
        if (diccionario.find(codigo) != diccionario.end()) {
            entrada = diccionario[codigo];
        } 
        // Si el código no está, generar la entrada como cadena + primer carácter de cadena
        else if (codigo == codigoActual) {
            entrada = cadena + cadena[0];
        } else {
            throw "Código incorrecto en la secuencia codificada";
        }

        resultado += entrada;

        // Agregar la nueva secuencia al diccionario
        diccionario[codigoActual++] = cadena + entrada[0];

        // Actualizar la cadena
        cadena = entrada;
    }

    return resultado;
}

int main() {
    // Mensaje de prueba
    string mensaje = "ABABABAABABBBBBABAAABAB";
    
    // Comprimir el mensaje
    vector<int> mensajeCodificado = comprimirLZW(mensaje);
    cout << "Mensaje comprimido: ";
    for (int codigo : mensajeCodificado) {
        cout << codigo << " ";
    }
    cout << endl;

    // Descomprimir el mensaje
    string mensajeDescomprimido = descomprimirLZW(mensajeCodificado);
    cout << "Mensaje descomprimido: " << mensajeDescomprimido << endl;

    return 0;
}
