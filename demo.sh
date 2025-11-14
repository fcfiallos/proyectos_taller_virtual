#!/bin/bash

# Script de demostración para manipulación de píxeles con SFML

echo "=== DEMO: Manipulación de Píxeles con SFML ==="
echo ""

# Configurar display
export DISPLAY=:99
echo "Display configurado en :99"

# Verificar que tenemos las imágenes
echo "Imágenes disponibles:"
ls -la *.png 2>/dev/null || echo "Generando imágenes de prueba..."

# Generar imágenes si no existen
if [ ! -f "gradiente.png" ]; then
    echo "Generando imágenes de prueba..."
    ./bin/generador_imagenes
fi

echo ""
echo "Imágenes disponibles:"
ls -1 *.png

echo ""
echo "=== PROGRAMAS COMPILADOS ==="
echo "Ejecutables en bin/:"
ls -la bin/

echo ""
echo "=== DEMO AUTOMÁTICA ==="
echo ""

# Función para ejecutar programa y tomar screenshot
demo_programa() {
    local programa=$1
    local imagen=$2
    local tiempo=$3
    local descripcion=$4
    
    echo "🎮 $descripcion"
    echo "   Ejecutando: $programa $imagen"
    echo "   Duración: ${tiempo}s"
    
    # Ejecutar en background
    if [ -n "$imagen" ]; then
        timeout $tiempo $programa $imagen > /dev/null 2>&1 &
    else
        timeout $tiempo $programa > /dev/null 2>&1 &
    fi
    
    local pid=$!
    sleep 1
    
    # Tomar screenshot
    local screenshot_name="demo_$(basename $programa)_$(date +%H%M%S).png"
    scrot "$screenshot_name" 2>/dev/null
    
    # Esperar a que termine
    wait $pid 2>/dev/null
    
    if [ -f "$screenshot_name" ]; then
        echo "   ✅ Screenshot guardado: $screenshot_name"
    else
        echo "   ⚠️  No se pudo tomar screenshot"
    fi
    
    echo ""
    sleep 1
}

# Demos
demo_programa "./bin/manipulacion_pixeles" "" 5 "Programa básico con imagen procedural"
demo_programa "./bin/manipulacion_avanzada" "gradiente.png" 5 "Programa avanzado con gradiente"
demo_programa "./bin/manipulacion_avanzada" "circulos.png" 5 "Programa avanzado con círculos"
demo_programa "./bin/manipulacion_avanzada" "ajedrez.png" 5 "Programa avanzado con patrón de ajedrez"

echo "=== RESUMEN ==="
echo "Screenshots generados:"
ls -la demo_*.png 2>/dev/null || echo "No se generaron screenshots"

echo ""
echo "=== INSTRUCCIONES DE USO MANUAL ==="
echo ""
echo "Para usar interactivamente:"
echo "1. DISPLAY=:99 ./bin/manipulacion_pixeles"
echo "   - Usa las teclas 1-8 para aplicar filtros"
echo "   - R para resetear, S para guardar, ESC para salir"
echo ""
echo "2. DISPLAY=:99 ./bin/manipulacion_avanzada imagen.png"
echo "   - Usa las teclas 1-7 para filtros avanzados"
echo "   - R para resetear, S para guardar, ESC para salir"
echo ""
echo "Controles disponibles:"
echo "  1 - Escala de grises / Filtro suavizado"
echo "  2 - Invertir colores / Filtro realce" 
echo "  3 - Brillo / Filtro Gaussiano"
echo "  4 - Detectar bordes / Laplaciano"
echo "  5 - Desenfoque / Efecto sepia"
echo "  6 - Detección bordes / Umbralización"
echo "  7 - Ruido / Efecto mosaico"
echo ""
echo "🎉 Demo completada!"