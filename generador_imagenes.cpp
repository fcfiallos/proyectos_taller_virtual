#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void crearImagenGradiente(const std::string& nombre, int ancho, int alto) {
    sf::Image imagen;
    imagen.create(ancho, alto);
    
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            sf::Uint8 r = (255 * x) / ancho;
            sf::Uint8 g = (255 * y) / alto;
            sf::Uint8 b = (255 * (x + y)) / (ancho + alto);
            imagen.setPixel(x, y, sf::Color(r, g, b));
        }
    }
    
    imagen.saveToFile(nombre);
    std::cout << "Creada: " << nombre << std::endl;
}

void crearImagenCirculos(const std::string& nombre, int ancho, int alto) {
    sf::Image imagen;
    imagen.create(ancho, alto, sf::Color::Black);
    
    int centroX = ancho / 2;
    int centroY = alto / 2;
    int maxRadio = std::min(ancho, alto) / 2;
    
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            float distancia = std::sqrt((x - centroX) * (x - centroX) + (y - centroY) * (y - centroY));
            
            if (distancia < maxRadio) {
                float intensidad = (maxRadio - distancia) / maxRadio;
                sf::Uint8 valor = static_cast<sf::Uint8>(255 * intensidad);
                
                // Crear patrón de círculos concéntricos
                if (static_cast<int>(distancia / 20) % 2 == 0) {
                    imagen.setPixel(x, y, sf::Color(valor, valor/2, 255 - valor));
                } else {
                    imagen.setPixel(x, y, sf::Color(255 - valor, valor, valor/2));
                }
            }
        }
    }
    
    imagen.saveToFile(nombre);
    std::cout << "Creada: " << nombre << std::endl;
}

void crearImagenAjedrez(const std::string& nombre, int ancho, int alto) {
    sf::Image imagen;
    imagen.create(ancho, alto);
    
    int tamañoCasilla = 50;
    
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            bool blanco = ((x / tamañoCasilla) + (y / tamañoCasilla)) % 2 == 0;
            sf::Color color = blanco ? sf::Color::White : sf::Color::Black;
            imagen.setPixel(x, y, color);
        }
    }
    
    imagen.saveToFile(nombre);
    std::cout << "Creada: " << nombre << std::endl;
}

void crearImagenRuido(const std::string& nombre, int ancho, int alto) {
    sf::Image imagen;
    imagen.create(ancho, alto);
    
    srand(time(nullptr));
    
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            sf::Uint8 r = rand() % 256;
            sf::Uint8 g = rand() % 256;
            sf::Uint8 b = rand() % 256;
            imagen.setPixel(x, y, sf::Color(r, g, b));
        }
    }
    
    imagen.saveToFile(nombre);
    std::cout << "Creada: " << nombre << std::endl;
}

int main() {
    std::cout << "Generando imágenes de prueba...\n" << std::endl;
    
    const int ancho = 400;
    const int alto = 300;
    
    crearImagenGradiente("gradiente.png", ancho, alto);
    crearImagenCirculos("circulos.png", ancho, alto);
    crearImagenAjedrez("ajedrez.png", ancho, alto);
    crearImagenRuido("ruido.png", ancho, alto);
    
    std::cout << "\n¡Imágenes de prueba generadas exitosamente!" << std::endl;
    std::cout << "Puedes usar estas imágenes para probar los filtros." << std::endl;
    
    return 0;
}