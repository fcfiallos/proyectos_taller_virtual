#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> // Necesario para cv::imwrite
#include <algorithm>
int main() {
    // Define la ruta de la imagen de entrada y de salida
    std::string image_path = "iglesia.jpg";
    std::string output_path = "prewitt_result.jpg"; // Nuevo nombre del archivo de salida
    std::cout << "--- Procesador de Bordes Prewitt ---" << std::endl;
    // 1. Cargar la imagen
    cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);
    if (image.empty() || image.rows == 0 || image.cols == 0) {
        std::cerr << "Error: No se pudo cargar la imagen o tiene dimensiones cero." << std::endl;
        std::cerr << "Ruta intentada: " << image_path << std::endl;
        return 1;
    }
    std::cout << "Imagen original cargada: " << image.cols << "x" << image.rows << std::endl;
    // 2. PROCESAMIENTO DE PREWITT
    cv::Mat gray_image, grad_x, grad_y, prewitt_result;
    // a) Convertir a escala de grises
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
    // b) Definir los kernels de Prewitt
    cv::Mat kernel_x = (cv::Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
    cv::Mat kernel_y = (cv::Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
    // c) Aplicar los filtros
    // Se usa CV_32F para mantener la precisión de los gradientes (valores float)
    cv::filter2D(gray_image, grad_x, CV_32F, kernel_x);
    cv::filter2D(gray_image, grad_y, CV_32F, kernel_y);
    // d) Convertir a valores absolutos y escalar (Mapeo de gradientes)
    // Se convierten los valores a 8 bits (CV_8U) para poder mostrarlos o guardarlos como imagen estándar.
    cv::Mat abs_grad_x, abs_grad_y;
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    // e) Combinar los gradientes (magnitud aproximada)
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, prewitt_result);
    std::cout << "Filtro Prewitt aplicado exitosamente." << std::endl;
    // 3. GUARDAR LA IMAGEN RESULTANTE
    // El resultado del filtro de Prewitt (prewitt_result) se guarda directamente.
    bool success = cv::imwrite(output_path, prewitt_result);
    if (success) {
        std::cout << "Resultado guardado exitosamente en: " << output_path << std::endl;
    } else {
        std::cerr << "Error: No se pudo guardar la imagen en: " << output_path << std::endl;
        return 1;
    }
    return 0;
}