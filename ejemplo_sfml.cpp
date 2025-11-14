#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Crear ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mi primera ventana SFML");
    
    // Crear un círculo
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(375, 275);
    
    // Crear un rectángulo
    sf::RectangleShape rectangle(sf::Vector2f(100, 50));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(100, 100);
    
    // Cargar fuente (opcional - comentado porque necesita archivo de fuente)
    // sf::Font font;
    // if (!font.loadFromFile("arial.ttf")) {
    //     std::cerr << "Error cargando fuente" << std::endl;
    // }
    
    // Crear texto
    sf::Text text;
    // text.setFont(font);  // Descomentar si tienes fuente
    // text.setString("Hola SFML!");
    // text.setCharacterSize(24);
    // text.setFillColor(sf::Color::White);
    
    std::cout << "Ventana SFML creada exitosamente!" << std::endl;
    std::cout << "Presiona ESC o cierra la ventana para salir." << std::endl;
    
    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        
        // Procesar eventos
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Cerrar con ESC
            if (event.type == sf::Event::KeyPressed && 
                event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Limpiar pantalla
        window.clear(sf::Color::Black);
        
        // Dibujar objetos
        window.draw(circle);
        window.draw(rectangle);
        // window.draw(text);  // Descomentar si tienes fuente
        
        // Mostrar contenido
        window.display();
    }
    
    std::cout << "Programa terminado." << std::endl;
    return 0;
}