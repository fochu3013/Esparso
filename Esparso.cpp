#include <iostream>
#include <fstream>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Uso: detecta_esparso <caminho_do_arquivo>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo\n";
        return 1;
    }

    struct stat file_stats;
    if (stat(filename.c_str(), &file_stats) == -1) {
        std::cerr << "Erro ao obter as informações do arquivo\n";
        file.close();
        return 1;
    }

    off_t file_size = file_stats.st_size;
    off_t blocks_used = file_stats.st_blocks;

    if (file_size > blocks_used * 512) {
        std::cout << "ESPARSO\n";
    } else {
        std::cout << "REGULAR\n";
    }

    file.close();

    return 0;
}

// Execute-o usando os nomes dos arquivos como argumentos:
// detecta_esparso x.txt
// Saída: ESPARSO

// detecta_esparso y.txt
// Saída: REGULAR

// imprimirá "ESPARSO" se o arquivo for esparso
