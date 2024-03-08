#include <iostream>
#include <string>

#include "mode_s_decoder.h"

void mode_s_decoder::converter(std::string raw_buffer) {
    std::cout << "converter" << std::endl;

    // buffer looks like "*f6d8c9833540611d6ebdee841425;"
    // test for "*"" and ";" 
    std::size_t asterisk = raw_buffer.find("*");
    if (asterisk == std::string::npos) {
        std::cout << "not found x" << std::endl;
        // error
    }

    std::size_t semicolon = raw_buffer.find(";");
    if (semicolon == std::string::npos) {
        std::cout << "not found ;" << std::endl;
        // error
    }

    // remove the * and ;
    std::string temp_string = raw_buffer.substr(asterisk + 1, semicolon - asterisk - 1);

    for (int ii = 0, jj=0; ii < temp_string.length(); ii+=2, jj++) { 
        std::string short_buffer = temp_string.substr(ii, 2);

        converted_array[jj] = std::stoi(short_buffer, nullptr, 16);

        //std::cout << short_buffer << ":" << converted_array[jj] << ":" << jj << std::endl;
    }

    downlink_format = converted_array[0] >> 3;
    xponder_capability = converted_array[0] & 0x07;
    icao_address = (converted_array[1] << 16) | (converted_array[2] << 8) | converted_array[3];
    type_code = converted_array[4] >> 3;
}
