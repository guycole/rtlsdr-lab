#include <iostream>
#include <string>

#include "decoder.h"

Decoder::Decoder(void) {
    std::cout << "decoder constructor" << std::endl;
}

Decoder::~Decoder(void) {
    std::cout << "decoder destructor" << std::endl;
}

void Decoder::wake_vortex() {
    switch (adsb_struct.type_code) {
        case 1:
            std::cout << "type code 1:reserved" << std::endl;
            break;
        case 2:
            switch (adsb_struct.aircraft_category) {
                case 0:
                    std::cout << "no category" << std::endl;
                    break;
                case 1:
                    std::cout << "surface emergency vehicle" << std::endl;
                    break;
                case 2:
                    std::cout << "unknown" << std::endl;
                    break;
                case 3: 
                    std::cout << "surface service vehicle" << std::endl;
                    break;
                case 4:
                case 5:
                case 6:
                case 7:
                    std::cout << "ground obstruction" << std::endl;
                    break;
            }
            break;
        case 3:
            switch (adsb_struct.aircraft_category) {
                case 1:
                    std::cout << "glider or sailplane" << std::endl;
                    break;
                case 2:
                    std::cout << "lighter than air" << std::endl;
                    break;
                case 3:
                    std::cout << "parachutist or skydiver" << std::endl;
                    break;
                case 4:
                    std::cout << "ultralight" << std::endl;
                    break;
                case 5:
                    std::cout << "reserved" << std::endl;
                    break;
                case 6:
                    std::cout << "uav unmanned" << std::endl;
                    break;
                case 7:
                    std::cout << "space vehicle" << std::endl;
                    break;
            }
           break;
        case 4:
            switch (adsb_struct.aircraft_category) {
                case 0:
                    std::cout << "no category" << std::endl;
                    break;
                case 1:
                    std::cout << "light" << std::endl;
                    break;
                case 2:
                    std::cout << "medium1" << std::endl;
                    break;
                case 3:
                    std::cout << "medium2" << std::endl;
                    break;
                case 4:
                    std::cout << "high vortex" << std::endl;
                    break;
                case 5:
                    std::cout << "heavy" << std::endl;
                    break;
                case 6:
                    std::cout << "high performance" << std::endl;
                    break;
                case 7:
                    std::cout << "rotorcraft" << std::endl;
                    break;
            }
            break;
    }  
}

void Decoder::adsb() {
    // service ADS-B message, i.e. DF17 or DF18

    int limit;
    char buffer[32];

    adsb_struct.capability = converted_array[0] & 0x07;
    adsb_struct.icao = (converted_array[1] << 16) | (converted_array[2] << 8) | converted_array[3];
    adsb_struct.type_code = converted_array[4] >> 3;

    //std::cout << converted_array[4] << std::endl;
    //std::cout << std::hex << converted_array[4] << std::endl;

    switch (adsb_struct.type_code) {
        case 4:
            std::cout << "type code 4" << std::endl;
            adsb_struct.aircraft_category = converted_array[4] & 0x07;

            std::cout << "------------" << std::endl;
            std::cout << std::hex << converted_array[5] << std::endl;
            std::cout << std::dec << converted_array[5] << std::endl;
            std::cout << "------------" << std::endl;

            buffer[0] = (converted_array[5] & 0xfc) >> 2;
            buffer[1] = (converted_array[5] & 0x03) << 4 | (converted_array[6] & 0xf0) >> 4;
            buffer[2] = (converted_array[6] & 0x0f) << 2 | (converted_array[7] & 0xc0) >> 6;
            buffer[3] = (converted_array[7] & 0x3f);
            buffer[4] = (converted_array[8] & 0xfc) >> 2;
            buffer[5] = (converted_array[8] & 0x03) << 4 | (converted_array[9] & 0xf0) >> 4;
            buffer[6] = (converted_array[9] & 0x0f) << 2 | (converted_array[10] & 0xc0) >> 6;
            buffer[7] = (converted_array[10] & 0x3f);
            buffer[8] = '\0';

            limit = strlen(buffer);
            for (int ii = 0; ii < limit; ii++) {
                if (buffer[ii] < 0x20) {
                    buffer[ii] |= 0x40;
                } else if (buffer[ii] > 0x20) {
                    buffer[ii] |= 0x30;
                }
            }

            printf("%s\n", buffer);
            printf("%d\n", adsb_struct.aircraft_category);
             
            break;
        case 19: //airborne velocity
            std::cout << "type code 19" << std::endl;
            std::cout << std::hex << converted_array[5] << std::endl;
            std::cout << std::dec << converted_array[5] << std::endl;

            adsb_struct.sub_type_code = converted_array[4] & 0x07;
            adsb_struct.intent_change_flag = converted_array[5] & 0x80 >> 3;
            adsb_struct.ifr_capability_flag = converted_array[5] & 0x40 >> 2;
            adsb_struct.uncertainty_flag = converted_array[5] & 0x03 << 1;
            adsb_struct.uncertainty_flag |= converted_array[6] & 0x80 >> 3;

            std::cout << "sub_type_code:" << adsb_struct.sub_type_code << ":";
            std::cout << "intent_change_flag:" << adsb_struct.intent_change_flag << ":";
            std::cout << "ifr_capability_flag:" << adsb_struct.ifr_capability_flag << ":";
            std::cout << "uncertainty_flag:" << adsb_struct.uncertainty_flag << std::endl;
            break;
        default:
            std::cout << "adsb type code default:" << adsb_struct.type_code << std::endl;
            break;
    }

    std::cout << "converted:" << std::dec << adsb_struct.df << ":" << adsb_struct.capability << ":" << adsb_struct.type_code << ":";
    std::cout << std::hex << adsb_struct.icao << std::endl;

    wake_vortex();
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
    // test for "*" and ";" 
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
    //temp_string = "8D4840D6202CC371C32CE0576098"; // aircraft identity
    temp_string = "8D485020994409940838175B284F"; // airborne velocity sub type 1
    //temp_string = "8DA05F219B06B6AF189400CBC33F"; // airborne velocity sub type 3

    //std::cout << "raw_buffer:" << raw_buffer << std::endl;
    std::cout << "temp_string:" << temp_string << std::endl;

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
