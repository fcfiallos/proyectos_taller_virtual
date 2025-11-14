# Makefile para proyectos SFML
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LIBS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

# Directorio de archivos fuente
SRC_DIR = .
# Directorio de archivos objeto
OBJ_DIR = build
# Directorio de ejecutables
BIN_DIR = bin

# Crear directorios si no existen
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Ejemplo básico
ejemplo_sfml: $(SRC_DIR)/ejemplo_sfml.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN_DIR)/$@ $(LIBS)

# Filtro Prewitt
filtro_prewitt: $(SRC_DIR)/filtros/perwitt.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN_DIR)/$@ $(LIBS)

# Manipulación de píxeles
manipulacion_pixeles: $(SRC_DIR)/manipulacion_pixeles.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN_DIR)/$@ $(LIBS)

# Generador de imágenes de prueba
generador_imagenes: $(SRC_DIR)/generador_imagenes.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN_DIR)/$@ $(LIBS)

# Manipulación avanzada de píxeles
manipulacion_avanzada: $(SRC_DIR)/manipulacion_avanzada.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN_DIR)/$@ $(LIBS)

# Limpiar archivos generados
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) *.png

# Compilar todos los ejemplos
all: ejemplo_sfml filtro_prewitt manipulacion_pixeles generador_imagenes manipulacion_avanzada

# Reglas que no crean archivos
.PHONY: clean all

# Ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make ejemplo_sfml        - Compilar ejemplo básico de SFML"
	@echo "  make filtro_prewitt      - Compilar filtro Prewitt"
	@echo "  make manipulacion_pixeles- Compilar manipulador de píxeles básico"
	@echo "  make manipulacion_avanzada- Compilar manipulador avanzado"
	@echo "  make generador_imagenes  - Compilar generador de imágenes de prueba"
	@echo "  make all                 - Compilar todos los programas"
	@echo "  make clean               - Limpiar archivos generados"
	@echo "  make help                - Mostrar esta ayuda"
	@echo ""
	@echo "Flujo de trabajo sugerido:"
	@echo "  1. make generador_imagenes && ./bin/generador_imagenes"
	@echo "  2. make manipulacion_avanzada"
	@echo "  3. ./setup_display.sh (solo primera vez)"
	@echo "  4. DISPLAY=:99 ./bin/manipulacion_avanzada [imagen.png]"
	@echo ""
	@echo "Ejemplos:"
	@echo "  DISPLAY=:99 ./bin/manipulacion_avanzada gradiente.png"
	@echo "  DISPLAY=:99 ./bin/manipulacion_pixeles"