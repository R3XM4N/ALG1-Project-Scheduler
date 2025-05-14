#include <vector>
#include <iostream>
#include <fstream>
#include "core.hpp"

int main(int argc, char** argv){
    Cpu* r_cpu = new Cpu();
    Cpu* m_cpu = new Cpu();
    std::ifstream file(argv[1], std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }
    int loops;
    file >> loops;
    loops = loops/8;
    char data[8] = {0};
    for (size_t i = 0; i < loops; i++)
    {
        for (size_t i = 0; i < 8; i++)
        {
            file >> data[i];
        }
        batch batch = toBatch(data);
        r_cpu->roundRobin(batch);
        m_cpu->AsignBatch(batch);
    }
    std::cout << "Round robin: " << r_cpu->runTime() << "\n";
    std::cout << "Custom algorithm: " << m_cpu->runTime() << "\n";
    std::cout << "Difference: " << std::abs((int)r_cpu->runTime() - (int)m_cpu->runTime()) << "\n";
    
    return 0;
}