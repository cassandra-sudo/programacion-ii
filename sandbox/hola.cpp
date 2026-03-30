# include <iostream>
# include <vector>
# include <string>

int main() {
    // Vector: la versión moderna de los arrays
    std::vector<std::string> temas = {
        "Especificación y verificación",
        "Tipos abstractos de datos",
        "Estructuras lineales",
        "Estructuras no lineales",
        "Busqueda y ordenación",
    };

    std::cout << "Programaciń II -Temario\n";
    std::cout << "-----------------------\n";

    for (const auto& tema : temas) {
        std::cout << "- " << tema << "\n";
    }

    return 0;
}
