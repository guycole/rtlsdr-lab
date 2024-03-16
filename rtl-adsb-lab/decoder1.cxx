#include <iostream>
#include <string>

#include "mode_s_decoder.h"

//g++ -o sd -g -Wall *.cxx
 
int main(int argc, char* argv[]) {
    std::cout << "begin" << endl;

    std::string buffer;
    mode_s_decoder mode_s;

    while (std::getline(std::cin, buffer)) {
        if (buffer.empty()) {
            break;
        }

        mode_s.converter(buffer);

//        mode_s.converter("*8da0c53899080612c8040979d912;");

//        std::cout << "converted:" << mode_s.get_df() << ":" << mode_s.get_ca()<< ":" << mode_s.get_tc();
//        std::cout << ":" << std::hex << mode_s.get_icao() << std::endl;
    }

    std::cout << "end" << endl;

    return 0;
}