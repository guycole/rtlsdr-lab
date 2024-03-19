#include <iostream>
#include <string>

#include "decoder.h"

Decoder::Decoder(void) {
    std::cout << "decoder constructor" << std::endl;
}

Decoder::~Decoder(void) {
    std::cout << "decoder destructor" << std::endl;
}

void Decoder::adsb() {
    // service ADS-B message, i.e. DF17 or DF18

    adsb_struct.capability = converted_array[0] & 0x07;
    adsb_struct.icao = (converted_array[1] << 16) | (converted_array[2] << 8) | converted_array[3];
    //type_code = converted_array[4] >> 3;

    std::cout << "converted:" << std::dec << adsb_struct.df << ":" << adsb_struct.capability << ":";
    std::cout << std::hex << adsb_struct.icao << std::endl;
}

void Decoder::dispatcher() {
    adsb_struct.df = converted_array[0] >> 3;
    std::cout << adsb_struct.df << std::endl;

    switch (adsb_struct.df) {
        case 11:
            std::cout << "downlink format 11" << std::endl;
            break;
        case 17:
            std::cout << "downlink format 17" << std::endl;
            adsb();
            break;
        case 18:
            std::cout << "downlink format 18" << std::endl;
            adsb();
            break;
        default:
            std::cout << "downlink format default:" << adsb_struct.df << std::endl;
            break;
    }
}

int Decoder::converter(std::string raw_buffer) {
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

    //std::cout << "raw_buffer:" << raw_buffer << std::endl;
    //std::cout << "temp_string:" << temp_string << std::endl;

    long unsigned ii, jj;
    for (ii = 0, jj=0; ii < temp_string.length(); ii+=2, jj++) { 
        std::string short_buffer = temp_string.substr(ii, 2);
        converted_array[jj] = std::stoi(short_buffer, nullptr, 16);
    }

    converted_array_size = jj;

    return 0;   
}

int Decoder::pipe_to_decoder() {
    std::string buffer;

    while (std::getline(std::cin, buffer)) {
        if (buffer.empty()) {
            break;
        }

        if (converter(buffer) < 0) {
            std::cout << "converter error noted" << std::endl;
        } else {
            std::cout << "converter success" << std::endl;
            dispatcher();
        }
    }

    return EXIT_SUCCESS;
}
