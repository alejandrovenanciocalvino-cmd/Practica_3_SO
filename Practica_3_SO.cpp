#include <iostream>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>

int main() {
    // 1. Crear el socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "Error al crear el socket" << std::endl;
        return 1;
    }

    // 2. Configurar la dirección (IP del Host de Windows)
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(12345);

    
    if (inet_pton(AF_INET, "172.31.144.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Direccion invalida o no soportada" << std::endl;
        return 1;
    }

    // 3. Conectar
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Error al conectar");
        return 1;
    }

    std::cout << "Conectado al servidor. Recibiendo datos..." << std::endl;

    // 4. Recibir los datos 
    std::vector<int> datos_recibidos; 
    unsigned char buffer; 

    
    while (recv(sockfd, &buffer, 1, 0) > 0) {
        datos_recibidos.push_back((int)buffer);
    }

    // 5. Guardar los datos en un archivo de texto
    std::ofstream archivo("datos_recibidos.txt");
    if (archivo.is_open()) {
        for (int n : datos_recibidos) {
            archivo << n << std::endl;
        }
        archivo.close();
        std::cout << "Datos guardados en datos_recibidos.txt" << std::endl;
    }

    // 6. Imprimir los números en pantalla
    std::cout << "Numeros recibidos del servidor Python:" << std::endl;
    for (int n : datos_recibidos) {
        std::cout << n << " "; 
    }
    std::cout << std::endl;

    // 7. Cerrar el socket
    close(sockfd);
    return 0;
}