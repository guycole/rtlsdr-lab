#include <iostream>
#include <string>

#include "decoder.h"

Decoder::Decoder(void) {
    std::cout << "decoder constructor" << std::endl;
}

Decoder::~Decoder(void) {
    std::cout << "decoder destructor" << std::endl;
}

void Decoder::converter(std::string raw_buffer) {
    std::cout << "converter" << std::endl;

}

#if 0
void mode_s_decoder::adsb_parser(std::string raw_buffer) {
    std::cout << "adsb_parser" << std::endl;
}

void mode_s_decoder::converter(std::string raw_buffer) {
    std::cout << "converter" << std::endl;

    // buffer looks like "*f6d8c9833540611d6ebdee841425;"
    // *8da0c53899080612c8040979d912;
    // test for "*"" and ";" 
    std::size_t asterisk_ndx = raw_buffer.find("*");
    if (asterisk_ndx == std::string::npos) {
        std::cout << "not found x" << std::endl;
        // error
    }

    std::size_t semicolon_ndx = raw_buffer.find(";");
    if (semicolon_ndx == std::string::npos) {
        std::cout << "not found ;" << std::endl;
        // error
    }

    // remove the * and ;
    std::string temp_string = raw_buffer.substr(asterisk_ndx + 1, semicolon_ndx - asterisk_ndx - 1);

    //std::cout << "raw_buffer:" << raw_buffer << std::endl;
    //std::cout << "temp_string:" << temp_string << std::endl;

    for (long unsigned ii = 0, jj=0; ii < temp_string.length(); ii+=2, jj++) { 
        std::string short_buffer = temp_string.substr(ii, 2);
        //std::cout << short_buffer << std::endl;

        converted_array[jj] = std::stoi(short_buffer, nullptr, 16);

        //std::cout << short_buffer << ":" << converted_array[jj] << ":" << jj << std::endl;
    }

    downlink_format = converted_array[0] >> 3;
    xponder_capability = converted_array[0] & 0x07;
    icao_address = (converted_array[1] << 16) | (converted_array[2] << 8) | converted_array[3];
    type_code = converted_array[4] >> 3;

    switch (downlink_format) {
        case 11:
            std::cout << "downlink format 11" << std::endl;
            break;
        case 17:
            std::cout << "downlink format 17" << std::endl;
            adsb_parser(temp_string);
            break;
        case 18:
            std::cout << "downlink format 18" << std::endl;
            adsb_parser(temp_string);
            break;
        default:
            std::cout << "downlink format default:" << downlink_format << std::endl;
            break;
    }
}
#endif