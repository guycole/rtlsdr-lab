#include <cstdlib>
#include <iostream>
#include <string>

#include "decoder.h"

//g++ -o sd -g -Wall *.cxx

#if 0
int dispatcher(std::string raw_buffer) {
    // buffer looks like "*f6d8c9833540611d6ebdee841425;"
    // *8da0c53899080612c8040979d912;
    // test for "*"" and ";" 
    std::size_t asterisk_ndx = raw_buffer.find("*");
    if (asterisk_ndx == std::string::npos) {
        std::cout << "not found x" << std::endl;
        return -1;
    }

    std::size_t semicolon_ndx = raw_buffer.find(";");
    if (semicolon_ndx == std::string::npos) {
        std::cout << "not found ;" << std::endl;
        return -1;
    }

    // remove the * and ;
    std::string temp_string = raw_buffer.substr(asterisk_ndx + 1, semicolon_ndx - asterisk_ndx - 1);
}
#endif

#if 0
int pipe_to_decoder() {

    std::string buffer;
    mode_s_decoder mode_s;

    while (std::getline(std::cin, buffer)) {
        if (buffer.empty()) {
            break;
        }

        dispatcher(buffer);

//        mode_s.converter(buffer);

//        mode_s.converter("*8da0c53899080612c8040979d912;");

//        std::cout << "converted:" << mode_s.get_df() << ":" << mode_s.get_ca()<< ":" << mode_s.get_tc();
//        std::cout << ":" << std::hex << mode_s.get_icao() << std::endl;
    }

    return EXIT_SUCCESS;
}
#endif



int main(int argc, char* argv[]) {
    const std::string banner = "decoder 0.0"; //TODO get version from cmake

    std::cout << "begin" << std::endl;
    std::cout << banner << std::endl;
    std::cout << __DATE__ << " " << __TIME__ << std::endl;

    //TODO service command line arguments

    //int ret_value = pipe_to_decoder();


    Decoder* decoder = new Decoder();

    std::cout << "end" << std::endl;

    int ret_value = EXIT_SUCCESS;

    return ret_value;
}