#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

class ManipuladorPixeles {
private:
    sf::Image imagen;
    sf::Texture textura;
    sf::Sprite sprite;
    int ancho, alto;
    std::vector<sf::Uint8> pixelData;

public:
    ManipuladorPixeles(int w, int h) : ancho(w), alto(h) {
        imagen.create(ancho, alto, sf::Color::White);
        pixelData.resize(ancho * alto * 4); // RGBA
        actualizarTextura();
    }

    // Cargar imagen desde archivo
    bool cargarImagen(const std::string& archivo) {
        if (imagen.loadFromFile(archivo)) {
            ancho = imagen.getSize().x;
            alto = imagen.getSize().y;
            pixelData.resize(ancho * alto * 4);
            copiarPixelesDeImagen();
            actualizarTextura();
            return true;
        }
        return false;
    }

    // Crear imagen de prueba con patrón
    void crearImagenPrueba() {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color;
                
                // Crear patrón de colores
                if (x < ancho / 3) {
                    color = sf::Color(255, (255 * y) / alto, 0); // Gradiente rojo-amarillo
                } else if (x < 2 * ancho / 3) {
                    color = sf::Color(0, 255, (255 * x) / ancho); // Gradiente verde-cian
                } else {
                    color = sf::Color((255 * x) / ancho, 0, 255); // Gradiente azul-magenta
                }
                
                establecerPixel(x, y, color);
            }
        }
        actualizarTextura();
    }

    // Establecer un píxel específico
    void establecerPixel(int x, int y, const sf::Color& color) {
        if (x >= 0 && x < ancho && y >= 0 && y < alto) {
            int index = (y * ancho + x) * 4;
            pixelData[index] = color.r;
            pixelData[index + 1] = color.g;
            pixelData[index + 2] = color.b;
            pixelData[index + 3] = color.a;
        }
    }

    // Obtener un píxel específico
    sf::Color obtenerPixel(int x, int y) const {
        if (x >= 0 && x < ancho && y >= 0 && y < alto) {
            int index = (y * ancho + x) * 4;
            return sf::Color(
                pixelData[index],
                pixelData[index + 1],
                pixelData[index + 2],
                pixelData[index + 3]
            );
        }
        return sf::Color::Black;
    }

    // Filtro: Convertir a escala de grises
    void aplicarEscalaGrises() {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color = obtenerPixel(x, y);
                // Fórmula luminancia: 0.299*R + 0.587*G + 0.114*B
                sf::Uint8 gris = static_cast<sf::Uint8>(
                    0.299f * color.r + 0.587f * color.g + 0.114f * color.b
                );
                establecerPixel(x, y, sf::Color(gris, gris, gris, color.a));
            }
        }
        actualizarTextura();
    }

    // Filtro: Invertir colores
    void invertirColores() {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color = obtenerPixel(x, y);
                establecerPixel(x, y, sf::Color(
                    255 - color.r,
                    255 - color.g,
                    255 - color.b,
                    color.a
                ));
            }
        }
        actualizarTextura();
    }

    // Filtro: Ajustar brillo
    void ajustarBrillo(float factor) {
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color = obtenerPixel(x, y);
                establecerPixel(x, y, sf::Color(
                    std::min(255, static_cast<int>(color.r * factor)),
                    std::min(255, static_cast<int>(color.g * factor)),
                    std::min(255, static_cast<int>(color.b * factor)),
                    color.a
                ));
            }
        }
        actualizarTextura();
    }

    // Filtro: Desenfoque simple
    void aplicarDesenfoque() {
        std::vector<sf::Uint8> nuevosPixeles = pixelData;
        
        for (int y = 1; y < alto - 1; y++) {
            for (int x = 1; x < ancho - 1; x++) {
                int sumaR = 0, sumaG = 0, sumaB = 0;
                
                // Matriz 3x3 de desenfoque
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        sf::Color color = obtenerPixel(x + dx, y + dy);
                        sumaR += color.r;
                        sumaG += color.g;
                        sumaB += color.b;
                    }
                }
                
                int index = (y * ancho + x) * 4;
                nuevosPixeles[index] = sumaR / 9;
                nuevosPixeles[index + 1] = sumaG / 9;
                nuevosPixeles[index + 2] = sumaB / 9;
            }
        }
        
        pixelData = nuevosPixeles;
        actualizarTextura();
    }

    // Filtro: Detección de bordes (Sobel)
    void detectarBordes() {
        std::vector<sf::Uint8> nuevosPixeles(pixelData.size());
        
        // Convertir a escala de grises primero
        std::vector<float> grises(ancho * alto);
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color = obtenerPixel(x, y);
                grises[y * ancho + x] = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
            }
        }
        
        for (int y = 1; y < alto - 1; y++) {
            for (int x = 1; x < ancho - 1; x++) {
                // Operadores Sobel
                float gx = (-1 * grises[(y-1) * ancho + (x-1)] + 1 * grises[(y-1) * ancho + (x+1)] +
                           -2 * grises[y * ancho + (x-1)] + 2 * grises[y * ancho + (x+1)] +
                           -1 * grises[(y+1) * ancho + (x-1)] + 1 * grises[(y+1) * ancho + (x+1)]);
                
                float gy = (-1 * grises[(y-1) * ancho + (x-1)] - 2 * grises[(y-1) * ancho + x] - 1 * grises[(y-1) * ancho + (x+1)] +
                            1 * grises[(y+1) * ancho + (x-1)] + 2 * grises[(y+1) * ancho + x] + 1 * grises[(y+1) * ancho + (x+1)]);
                
                float magnitud = std::sqrt(gx * gx + gy * gy);
                sf::Uint8 valor = std::min(255, static_cast<int>(magnitud));
                
                int index = (y * ancho + x) * 4;
                nuevosPixeles[index] = valor;
                nuevosPixeles[index + 1] = valor;
                nuevosPixeles[index + 2] = valor;
                nuevosPixeles[index + 3] = 255;
            }
        }
        
        pixelData = nuevosPixeles;
        actualizarTextura();
    }

    // Efecto: Ruido aleatorio
    void agregarRuido(float intensidad) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-intensidad, intensidad);
        
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color = obtenerPixel(x, y);
                establecerPixel(x, y, sf::Color(
                    std::max(0, std::min(255, static_cast<int>(color.r + dis(gen)))),
                    std::max(0, std::min(255, static_cast<int>(color.g + dis(gen)))),
                    std::max(0, std::min(255, static_cast<int>(color.b + dis(gen)))),
                    color.a
                ));
            }
        }
        actualizarTextura();
    }

    // Efecto: Posterización
    void posterizar(int niveles) {
        float factor = 255.0f / (niveles - 1);
        
        for (int y = 0; y < alto; y++) {
            for (int x = 0; x < ancho; x++) {
                sf::Color color = obtenerPixel(x, y);
                establecerPixel(x, y, sf::Color(
                    static_cast<sf::Uint8>(std::round(color.r / factor) * factor),
                    static_cast<sf::Uint8>(std::round(color.g / factor) * factor),
                    static_cast<sf::Uint8>(std::round(color.b / factor) * factor),
                    color.a
                ));
            }
        }
        actualizarTextura();
    }

    // Guardar imagen
    void guardarImagen(const std::string& archivo) {
        copiarPixelesAImagen();
        imagen.saveToFile(archivo);
    }

    // Obtener sprite para renderizado
    const sf::Sprite& obtenerSprite() const {
        return sprite;
    }

    // Resetear a imagen original
    void resetear() {
        crearImagenPrueba();
    }

private:
    void actualizarTextura() {
        imagen.create(ancho, alto, pixelData.data());
        textura.loadFromImage(imagen);
        sprite.setTexture(textura);
    }

    void copiarPixelesDeImagen() {
        const sf::Uint8* pixels = imagen.getPixelsPtr();
        for (size_t i = 0; i < pixelData.size(); i++) {
            pixelData[i] = pixels[i];
        }
    }

    void copiarPixelesAImagen() {
        imagen.create(ancho, alto, pixelData.data());
    }
};

class InterfazUsuario {
private:
    sf::Font fuente;
    std::vector<sf::Text> textos;
    bool fuenteCargada;

public:
    InterfazUsuario() : fuenteCargada(false) {
        // SFML viene con una fuente por defecto, pero es mejor cargar una
        // Como no tenemos fuentes específicas, usaremos texto simple
    }

    void mostrarInstrucciones(sf::RenderWindow& ventana) {
        if (!fuenteCargada) {
            // Crear textos sin fuente específica (usará fuente por defecto del sistema)
            return;
        }
    }

    void mostrarInformacion(sf::RenderWindow& ventana, const std::string& info) {
        // Mostrar información en consola por simplicidad
        std::cout << info << std::endl;
    }
};

int main() {
    // Configuración de la ventana
    const int ANCHO_VENTANA = 1000;
    const int ALTO_VENTANA = 700;
    const int ANCHO_IMAGEN = 400;
    const int ALTO_IMAGEN = 300;
    
    sf::RenderWindow ventana(sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA), "Manipulacion de Pixeles - SFML");
    ventana.setFramerateLimit(60);
    
    // Crear manipulador de píxeles
    ManipuladorPixeles manipulador(ANCHO_IMAGEN, ALTO_IMAGEN);
    manipulador.crearImagenPrueba();
    
    // Variables de control
    bool imagenModificada = false;
    
    std::cout << "\n=== MANIPULADOR DE PIXELES ===\n";
    std::cout << "Controles:\n";
    std::cout << "1 - Escala de grises\n";
    std::cout << "2 - Invertir colores\n";
    std::cout << "3 - Aumentar brillo\n";
    std::cout << "4 - Disminuir brillo\n";
    std::cout << "5 - Aplicar desenfoque\n";
    std::cout << "6 - Detectar bordes\n";
    std::cout << "7 - Agregar ruido\n";
    std::cout << "8 - Posterizar\n";
    std::cout << "R - Resetear imagen\n";
    std::cout << "S - Guardar imagen\n";
    std::cout << "ESC - Salir\n\n";
    
    // Bucle principal
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
                        std::cout << "Aplicando escala de grises...\n";
                        manipulador.aplicarEscalaGrises();
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num2:
                        std::cout << "Invirtiendo colores...\n";
                        manipulador.invertirColores();
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num3:
                        std::cout << "Aumentando brillo...\n";
                        manipulador.ajustarBrillo(1.3f);
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num4:
                        std::cout << "Disminuyendo brillo...\n";
                        manipulador.ajustarBrillo(0.7f);
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num5:
                        std::cout << "Aplicando desenfoque...\n";
                        manipulador.aplicarDesenfoque();
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num6:
                        std::cout << "Detectando bordes...\n";
                        manipulador.detectarBordes();
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num7:
                        std::cout << "Agregando ruido...\n";
                        manipulador.agregarRuido(30);
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::Num8:
                        std::cout << "Aplicando posterizacion...\n";
                        manipulador.posterizar(4);
                        imagenModificada = true;
                        break;
                        
                    case sf::Keyboard::R:
                        std::cout << "Reseteando imagen...\n";
                        manipulador.resetear();
                        imagenModificada = false;
                        break;
                        
                    case sf::Keyboard::S:
                        std::cout << "Guardando imagen como 'salida.png'...\n";
                        manipulador.guardarImagen("salida.png");
                        std::cout << "Imagen guardada!\n";
                        break;
                        
                    default:
                        break;
                }
            }
        }
        
        // Renderizado
        ventana.clear(sf::Color::Black);
        
        // Centrar la imagen en la ventana
        sf::Sprite sprite = manipulador.obtenerSprite();
        sprite.setPosition(
            (ANCHO_VENTANA - ANCHO_IMAGEN) / 2,
            (ALTO_VENTANA - ALTO_IMAGEN) / 2
        );
        
        ventana.draw(sprite);
        ventana.display();
    }
    
    std::cout << "Programa terminado.\n";
    return 0;
}