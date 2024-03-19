#include <cstdlib>
#include <iostream>
#include <string>

#include "decoder.h"

//g++ -o sd -g -Wall *.cxx

int main(int argc, char* argv[]) {
    const std::string banner = "decoder 0.0"; //TODO get version from cmake

    std::cout << "begin" << std::endl;
    std::cout << banner << std::endl;
    std::cout << __DATE__ << " " << __TIME__ << std::endl;

    //TODO service command line arguments

    //int ret_value = pipe_to_decoder();

    Decoder* decoder = new Decoder();
    decoder->pipe_to_decoder();

    std::cout << "end" << std::endl;

    int ret_value = EXIT_SUCCESS;

    return ret_value;
}