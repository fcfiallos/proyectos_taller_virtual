#!/bin/bash

# Script para configurar display virtual para aplicaciones gráficas en codespaces

echo "Configurando display virtual..."

# Instalar Xvfb si no está instalado
if ! command -v Xvfb &> /dev/null; then
    echo "Instalando Xvfb..."
    sudo apt-get update
    sudo apt-get install -y xvfb
fi

# Iniciar display virtual
export DISPLAY=:99
Xvfb :99 -screen 0 1024x768x24 > /dev/null 2>&1 &

echo "Display virtual configurado en :99"
echo "Para ejecutar aplicaciones gráficas, usa: DISPLAY=:99 ./tu_programa"

# Opcional: instalar herramientas para capturar pantalla
if ! command -v scrot &> /dev/null; then
    echo "¿Quieres instalar herramientas para capturar pantalla? (y/n)"
    read -r response
    if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        sudo apt-get install -y scrot
        echo "Instalado scrot para capturas de pantalla"
        echo "Uso: DISPLAY=:99 scrot screenshot.png"
    fi
fi

echo "Configuración completada!"