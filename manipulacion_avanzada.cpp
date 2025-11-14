#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class ManipuladorPixelesAvanzado {
private:
    sf::Image imagenOriginal;
    sf::Image imagenActual;
    sf::Texture textura;
    sf::Sprite sprite;
    int ancho, alto;
    bool imagenCargada;

public:
    ManipuladorPixelesAvanzado() : imagenCargada(false) {}

    bool cargarImagen(const std::string& archivo) {
        if (imagenOriginal.loadFromFile(archivo)) {
            ancho = imagenOriginal.getSize().x;
            alto = imagenOriginal.getSize().y;
            imagenActual = imagenOriginal;
            actualizarTextura();
            imagenCargada = true;
            std::cout << "Imagen cargada: " << archivo << " (" << ancho << "x" << alto << ")" << std::endl;
            return true;
        }
        std::cout << "Error: No se pudo cargar " << archivo << std::endl;
        return false;
    }

    void crearImagenDemo(int w, int h) {
        ancho = w;
        alto = h;
        imagenOriginal.create(ancho, alto);
        
        // Crear patrón de prueba más complejo
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                float fx = static_cast<float>(x) / ancho;
                float fy = static_cast<float>(y) / alto;
                
                // Crear ondas sinusoidales
                float onda1 = sin(fx * 10) * sin(fy * 10);
                float onda2 = sin(fx * 15 + fy * 15);
                
                sf::Uint8 r = static_cast<sf::Uint8>(128 + 127 * onda1);
                sf::Uint8 g = static_cast<sf::Uint8>(128 + 127 * onda2);
                sf::Uint8 b = static_cast<sf::Uint8>(128 + 127 * sin(fx * 8 - fy * 8));
                
                imagenOriginal.setPixel(x, y, sf::Color(r, g, b));
            }
        }
        
        imagenActual = imagenOriginal;
        actualizarTextura();
        imagenCargada = true;
    }

    // Manipulaciones avanzadas de píxeles
    void aplicarFiltroPersonalizado() {
        if (!imagenCargada) return;
        
        for (unsigned int y = 1; y < static_cast<unsigned int>(alto - 1); y++) {
            for (unsigned int x = 1; x < static_cast<unsigned int>(ancho - 1); x++) {
                // Obtener píxeles vecinos
                std::vector<sf::Color> vecinos;
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        vecinos.push_back(imagenOriginal.getPixel(x + dx, y + dy));
                    }
                }
                
                // Aplicar operación personalizada
                int sumaR = 0, sumaG = 0, sumaB = 0;
                for (const auto& color : vecinos) {
                    sumaR += color.r;
                    sumaG += color.g;
                    sumaB += color.b;
                }
                
                // Promedio con énfasis en el centro
                sf::Color centro = imagenOriginal.getPixel(x, y);
                sf::Uint8 r = (sumaR / 9 + centro.r) / 2;
                sf::Uint8 g = (sumaG / 9 + centro.g) / 2;
                sf::Uint8 b = (sumaB / 9 + centro.b) / 2;
                
                imagenActual.setPixel(x, y, sf::Color(r, g, b));
            }
        }
        actualizarTextura();
    }

    void aplicarMatrizConvolucion(const std::vector<std::vector<float>>& kernel) {
        if (!imagenCargada || kernel.empty()) return;
        
        int kernelSize = kernel.size();
        int offset = kernelSize / 2;
        sf::Image resultado = imagenOriginal;
        
        for (int y = offset; y < alto - offset; y++) {
            for (int x = offset; x < ancho - offset; x++) {
                float sumaR = 0, sumaG = 0, sumaB = 0;
                
                for (int ky = 0; ky < kernelSize; ky++) {
                    for (int kx = 0; kx < kernelSize; kx++) {
                        sf::Color pixel = imagenOriginal.getPixel(
                            x + kx - offset, 
                            y + ky - offset
                        );
                        float peso = kernel[ky][kx];
                        sumaR += pixel.r * peso;
                        sumaG += pixel.g * peso;
                        sumaB += pixel.b * peso;
                    }
                }
                
                resultado.setPixel(x, y, sf::Color(
                    std::max(0, std::min(255, static_cast<int>(sumaR))),
                    std::max(0, std::min(255, static_cast<int>(sumaG))),
                    std::max(0, std::min(255, static_cast<int>(sumaB)))
                ));
            }
        }
        
        imagenActual = resultado;
        actualizarTextura();
    }

    void aplicarFiltroRealce() {
        // Kernel de realce (sharpening)
        std::vector<std::vector<float>> kernel = {
            {0, -1, 0},
            {-1, 5, -1},
            {0, -1, 0}
        };
        aplicarMatrizConvolucion(kernel);
    }

    void aplicarFiltroGaussiano() {
        // Kernel Gaussiano 3x3
        std::vector<std::vector<float>> kernel = {
            {1/16.0f, 2/16.0f, 1/16.0f},
            {2/16.0f, 4/16.0f, 2/16.0f},
            {1/16.0f, 2/16.0f, 1/16.0f}
        };
        aplicarMatrizConvolucion(kernel);
    }

    void aplicarDeteccionBordesAvanzada() {
        // Operador Laplaciano
        std::vector<std::vector<float>> kernel = {
            {0, -1, 0},
            {-1, 4, -1},
            {0, -1, 0}
        };
        aplicarMatrizConvolucion(kernel);
    }

    void aplicarEfectoSepia() {
        if (!imagenCargada) return;
        
        for (unsigned int y = 0; y < static_cast<unsigned int>(alto); y++) {
            for (unsigned int x = 0; x < static_cast<unsigned int>(ancho); x++) {
                sf::Color color = imagenOriginal.getPixel(x, y);
                
                // Fórmula sepia
                int tr = static_cast<int>((color.r * 0.393) + (color.g * 0.769) + (color.b * 0.189));
                int tg = static_cast<int>((color.r * 0.349) + (color.g * 0.686) + (color.b * 0.168));
                int tb = static_cast<int>((color.r * 0.272) + (color.g * 0.534) + (color.b * 0.131));
                
                imagenActual.setPixel(x, y, sf::Color(
                    std::min(255, tr),
                    std::min(255, tg),
                    std::min(255, tb)
                ));
            }
        }
        actualizarTextura();
    }

    void aplicarUmbralización(sf::Uint8 umbral) {
        if (!imagenCargada) return;
        
        for (unsigned int y = 0; y < static_cast<unsigned int>(alto); y++) {
            for (unsigned int x = 0; x < static_cast<unsigned int>(ancho); x++) {
                sf::Color color = imagenOriginal.getPixel(x, y);
                
                // Convertir a escala de grises
                sf::Uint8 gris = static_cast<sf::Uint8>(
                    0.299 * color.r + 0.587 * color.g + 0.114 * color.b
                );
                
                // Aplicar umbral
                sf::Uint8 valor = (gris > umbral) ? 255 : 0;
                imagenActual.setPixel(x, y, sf::Color(valor, valor, valor));
            }
        }
        actualizarTextura();
    }

    void aplicarMosaico(int tamañoBloque) {
        if (!imagenCargada || tamañoBloque <= 0) return;
        
        for (int y = 0; y < alto; y += tamañoBloque) {
            for (int x = 0; x < ancho; x += tamañoBloque) {
                // Calcular color promedio del bloque
                int sumaR = 0, sumaG = 0, sumaB = 0, contador = 0;
                
                for (int by = 0; by < tamañoBloque && (y + by) < alto; by++) {
                    for (int bx = 0; bx < tamañoBloque && (x + bx) < ancho; bx++) {
                        sf::Color color = imagenOriginal.getPixel(x + bx, y + by);
                        sumaR += color.r;
                        sumaG += color.g;
                        sumaB += color.b;
                        contador++;
                    }
                }
                
                sf::Color colorPromedio(
                    sumaR / contador,
                    sumaG / contador,
                    sumaB / contador
                );
                
                // Aplicar color promedio a todo el bloque
                for (int by = 0; by < tamañoBloque && (y + by) < alto; by++) {
                    for (int bx = 0; bx < tamañoBloque && (x + bx) < ancho; bx++) {
                        imagenActual.setPixel(x + bx, y + by, colorPromedio);
                    }
                }
            }
        }
        actualizarTextura();
    }

    void resetear() {
        if (imagenCargada) {
            imagenActual = imagenOriginal;
            actualizarTextura();
        }
    }

    void guardar(const std::string& archivo) {
        if (imagenCargada) {
            imagenActual.saveToFile(archivo);
            std::cout << "Imagen guardada: " << archivo << std::endl;
        }
    }

    const sf::Sprite& getSprite() const { return sprite; }
    bool estaImagenCargada() const { return imagenCargada; }
    sf::Vector2i getTamaño() const { return sf::Vector2i(ancho, alto); }

private:
    void actualizarTextura() {
        textura.loadFromImage(imagenActual);
        sprite.setTexture(textura);
    }
};

int main(int argc, char* argv[]) {
    const int ANCHO_VENTANA = 1200;
    const int ALTO_VENTANA = 800;
    
    sf::RenderWindow ventana(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), 
                            "Manipulacion Avanzada de Pixeles - SFML");
    ventana.setFramerateLimit(60);
    
    ManipuladorPixelesAvanzado manipulador;
    
    // Intentar cargar imagen desde argumentos o crear demo
    if (argc > 1) {
        if (!manipulador.cargarImagen(argv[1])) {
            std::cout << "Creando imagen de demostración..." << std::endl;
            manipulador.crearImagenDemo(600, 400);
        }
    } else {
        std::cout << "Creando imagen de demostración..." << std::endl;
        manipulador.crearImagenDemo(600, 400);
    }
    
    std::cout << "\n=== MANIPULADOR AVANZADO DE PIXELES ===\n";
    std::cout << "Uso: " << argv[0] << " [archivo_imagen]\n\n";
    std::cout << "Controles avanzados:\n";
    std::cout << "1 - Filtro personalizado (suavizado)\n";
    std::cout << "2 - Filtro de realce (sharpening)\n";
    std::cout << "3 - Filtro Gaussiano (desenfoque)\n";
    std::cout << "4 - Detección de bordes Laplaciano\n";
    std::cout << "5 - Efecto sepia\n";
    std::cout << "6 - Umbralización (threshold)\n";
    std::cout << "7 - Efecto mosaico\n";
    std::cout << "R - Resetear a imagen original\n";
    std::cout << "S - Guardar imagen procesada\n";
    std::cout << "ESC - Salir\n\n";
    
    while (ventana.isOpen()) {
        sf::Event evento;
        
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            
            if (evento.type == sf::Event::KeyPressed) {
                switch (evento.key.code) {
                    case sf::Keyboard::Escape:
                        ventana.close();
                        break;
                        
                    case sf::Keyboard::Num1:
                        std::cout << "Aplicando filtro personalizado..." << std::endl;
                        manipulador.aplicarFiltroPersonalizado();
                        break;
                        
                    case sf::Keyboard::Num2:
                        std::cout << "Aplicando filtro de realce..." << std::endl;
                        manipulador.aplicarFiltroRealce();
                        break;
                        
                    case sf::Keyboard::Num3:
                        std::cout << "Aplicando filtro Gaussiano..." << std::endl;
                        manipulador.aplicarFiltroGaussiano();
                        break;
                        
                    case sf::Keyboard::Num4:
                        std::cout << "Aplicando detección de bordes..." << std::endl;
                        manipulador.aplicarDeteccionBordesAvanzada();
                        break;
                        
                    case sf::Keyboard::Num5:
                        std::cout << "Aplicando efecto sepia..." << std::endl;
                        manipulador.aplicarEfectoSepia();
                        break;
                        
                    case sf::Keyboard::Num6:
                        std::cout << "Aplicando umbralización..." << std::endl;
                        manipulador.aplicarUmbralización(128);
                        break;
                        
                    case sf::Keyboard::Num7:
                        std::cout << "Aplicando efecto mosaico..." << std::endl;
                        manipulador.aplicarMosaico(10);
                        break;
                        
                    case sf::Keyboard::R:
                        std::cout << "Reseteando imagen..." << std::endl;
                        manipulador.resetear();
                        break;
                        
                    case sf::Keyboard::S:
                        manipulador.guardar("imagen_procesada.png");
                        break;
                        
                    default:
                        break;
                }
            }
        }
        
        ventana.clear(sf::Color::Black);
        
        if (manipulador.estaImagenCargada()) {
            sf::Sprite sprite = manipulador.getSprite();
            sf::Vector2i tamaño = manipulador.getTamaño();
            
            // Centrar imagen
            sprite.setPosition(
                (ANCHO_VENTANA - tamaño.x) / 2,
                (ALTO_VENTANA - tamaño.y) / 2
            );
            
            ventana.draw(sprite);
        }
        
        ventana.display();
    }
    
    return 0;
}