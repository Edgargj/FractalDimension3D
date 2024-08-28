#include <iostream>
#include <random>
#include <vector>
#include <set>
#include <chrono>
#include <unistd.h>  // Para getopt
#include <cstdio> //Para std::remove
#include "FractalDimension3D.h"

// Función para generar radios aleatorios
std::vector<int> generateRandomRadii(int minRadius, int maxRadius, int count) {
    std::set<int> radiiSet;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minRadius / 2, maxRadius / 2);

    while (radiiSet.size() < static_cast<size_t>(count)) {
        int randomRadius = 2 * dis(gen) + 1;  // Multiplicar por 2 y sumar 1 para asegurarse de que es impar
        radiiSet.insert(randomRadius);
    }

    return std::vector<int>(radiiSet.begin(), radiiSet.end());
}

// Función para mostrar el mensaje de ayuda
void printHelp(const char* program_name) {
    std::cout << "Uso: " << program_name << " [opciones] archivo.pdb\n"
              << "Opciones:\n"
              << "  -m minRadius   Especifica el radio mínimo (por defecto es 3)\n"
              << "  -M maxRadius   Especifica el radio máximo (por defecto es 21)\n"
              << "  -c count       Especifica el número de radios a generar (por defecto es 50)\n"
              << "  -h             Muestra este mensaje de ayuda y termina\n"
              << std::endl;
}

int main(int argc, char* argv[]) {
    using namespace std::chrono;

    int minRadius = 3;   // Valor por defecto
    int maxRadius = 21;  // Valor por defecto
    int count = 20;      // Valor por defecto

    int opt;
    while ((opt = getopt(argc, argv, "m:M:c:h")) != -1) {
        switch (opt) {
            case 'm':
                minRadius = std::stoi(optarg);
                break;
            case 'M':
                maxRadius = std::stoi(optarg);
                break;
            case 'c':
                count = std::stoi(optarg);
                break;
            case 'h':
                printHelp(argv[0]);
                return 0;
            default:
                printHelp(argv[0]);
                return 1;
        }
    }

    // Verificar si se ha pasado el archivo PDB
    if (optind != argc - 1) {
        printHelp(argv[0]);
        return 1;
    }


    //Borar archivos anteriores si existen 
    std::remove("extractXYZData.txt");
    std::remove("maxRadiusData.txt");
    std::remove("smallSphereData.txt");


    std::string input_file = argv[optind];
    FractalDimension3D fractalDimension(input_file);

    // Medir el tiempo de inicio
    auto start = high_resolution_clock::now();

    // Guardar las coordenadas del archivo PDB
    fractalDimension.savePDBCoordinates("extractXYZData.txt");

    // Calcular el centro geométrico y la distancia máxima
    fractalDimension.calculateGeometricCenter();
    fractalDimension.calculateMaxDistanceAndFarthestAtom();

    // Guardar los datos geométricos
    fractalDimension.saveGeometricData("maxRadiusData.txt");

    // Generar radios aleatorios con los valores proporcionados
    std::vector<int> radii = generateRandomRadii(minRadius, maxRadius, count);

    // Generar esferas y contar átomos, y guardar en el archivo correspondiente
    fractalDimension.generateSpheresAndCountAtoms(radii, "smallSphereData.txt");

    // Medir el tiempo de finalización
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    auto duration_seconds = duration_cast<seconds>(end - start);
    auto duration_minutes = duration_cast<minutes>(end - start);


    // Mostrar el tiempo de ejecución en segundos
    std::cout << "Tiempo de ejecución: " << duration.count() << " ms" << std::endl;
    std::cout << "Tiempo de ejecución: " << duration_seconds.count() << " s" << std::endl;
    std::cout << "Tiempo de ejecución: " << duration_minutes.count() << " min" << std::endl;

    return 0;
}

