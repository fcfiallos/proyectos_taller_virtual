# Proyectos Taller Virtual - C++ con SFML

Este repositorio contiene proyectos de C++ utilizando la librería SFML (Simple and Fast Multimedia Library) para desarrollo de aplicaciones gráficas.

## 📋 Requisitos Instalados

Ya tienes instalado en tu codespace:

- ✅ **SFML 2.6.1** - Librería multimedia
- ✅ **G++ 13.3.0** - Compilador de C++
- ✅ **Build tools** - Make, CMake, pkg-config
- ✅ **Dependencias gráficas** - OpenGL, ALSA, PulseAudio

## 🚀 Cómo Compilar y Ejecutar

### Método 1: Usando Makefile (Recomendado)

```bash
# Compilar ejemplo básico
make ejemplo_sfml

# Compilar filtro Prewitt
make filtro_prewitt

# Compilar todo
make all

# Ver ayuda
make help

# Limpiar archivos generados
make clean
```

### Método 2: Compilación manual

```bash
# Compilar manualmente
g++ -std=c++17 -Wall -Wextra ejemplo_sfml.cpp -o ejemplo_sfml -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
```

## 🖥️ Ejecutar Aplicaciones Gráficas en Codespace

Como estás en un codespace, necesitas configurar un display virtual para aplicaciones gráficas:

```bash
# Configurar display virtual
./setup_display.sh

# Ejecutar tu aplicación
DISPLAY=:99 ./bin/ejemplo_sfml
```

## 📁 Estructura del Proyecto

```
proyectos_taller_virtual/
├── README.md              # Este archivo
├── Makefile              # Archivo para compilación
├── setup_display.sh      # Script para configurar display virtual
├── ejemplo_sfml.cpp      # Ejemplo básico de SFML
├── filtros/
│   └── perwitt.cpp       # Filtro Prewitt
├── bin/                  # Ejecutables (se crea automáticamente)
└── build/                # Archivos objeto (se crea automáticamente)
```

## 🎮 Ejemplos Incluidos

### 1. Ejemplo Básico SFML
- Crea una ventana gráfica
- Dibuja un círculo verde y un rectángulo rojo
- Manejo básico de eventos (cerrar ventana, ESC)

### 2. Filtro Prewitt
- Tu implementación del filtro Prewitt existente
- Puedes integrarlo con SFML para visualización

## 💡 Módulos SFML Disponibles

- **sfml-system**: Funciones básicas del sistema
- **sfml-window**: Manejo de ventanas y eventos
- **sfml-graphics**: Renderizado 2D
- **sfml-audio**: Reproducción de sonido
- **sfml-network**: Comunicación de red

## 🔧 Comandos Útiles

```bash
# Verificar instalación de SFML
pkg-config --cflags --libs sfml-all

# Verificar versión del compilador
g++ --version

# Ver estructura del proyecto
tree -I 'build|bin'
```

## 📚 Recursos Adicionales

- [Documentación oficial de SFML](https://www.sfml-dev.org/documentation/2.6.1/)
- [Tutoriales de SFML](https://www.sfml-dev.org/tutorials/2.6/)
- [Ejemplos de código](https://github.com/SFML/SFML/tree/master/examples)

## 🐛 Solución de Problemas

### Error de Display
Si obtienes errores como "cannot connect to X server":
```bash
./setup_display.sh
export DISPLAY=:99
```

### Errores de Compilación
Verifica que tienes las librerías:
```bash
ldconfig -p | grep sfml
```

### Performance
Para mejor rendimiento en aplicaciones gráficas:
```bash
# Compilar con optimizaciones
g++ -O2 -std=c++17 tu_programa.cpp -lsfml-graphics -lsfml-window -lsfml-system
```