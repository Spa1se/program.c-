#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Color {
    int red;
    int green;
    int blue;

    bool operator==(const Color& other) const {
        return red == other.red && green == other.green && blue == other.blue;
    }
};

int main() {
    std::string filename;
    std::cout << "Wprowadź nazwę pliku: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "nie można otworzyć pliku!" << std::endl;
        return 1;
    }

    std::string format;
    int width, height, maxColor;
    file >> format >> width >> height >> maxColor;

    std::vector<Color> pixels;
    int red, green, blue;
    while (file >> red >> green >> blue) {
        pixels.push_back({red, green, blue});
    }

    // Znajdujemy najpopularniejszy kolor
    std::vector<int> colorCount(256 * 256 * 256, 0);
    for (const auto& pixel : pixels) {
        int index = pixel.red * 256 * 256 + pixel.green * 256 + pixel.blue;
        colorCount[index]++;
    }

    auto maxCount = std::max_element(colorCount.begin(), colorCount.end());
    int maxIndex = std::distance(colorCount.begin(), maxCount);
    int maxRed = maxIndex / (256 * 256);
    int maxGreen = (maxIndex % (256 * 256)) / 256;
    int maxBlue = maxIndex % 256;

    int uniqueColors = std::count_if(colorCount.begin(), colorCount.end(), [](int count) { return count > 0; });

    std::cout << std::endl;
    std::cout << "Szerokość obrazu: " << width << std::endl;
    std::cout << "Wysokość obrazu: " << height << std::endl;
    std::cout << "Wysokość brązowa: " << maxColor << std::endl;
    std::cout << "Najczęstszy kolor: " << maxRed << "-" << maxGreen << "-" << maxBlue << " spotykamy " << *maxCount << " iloszcz" << std::endl;
    std::cout << "liczba unikalnych numerów: " << uniqueColors << std::endl;

    std::string answer;
    std::cout << std::endl;
    std::cout << "  Czy chcesz pobrać kolejny plik? (Tak/Nie): ";
    std::cin >> answer;

    if (answer == "Tak") {
        // wywolamy main() aby pobrać kolejny plik
        return main();
    } else {
        return 0;
    }
}
