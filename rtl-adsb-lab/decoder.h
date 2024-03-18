#ifndef __DECODER_H 
#define __DECODER_H

class Decoder {
public:
    Decoder(void);
    ~Decoder(void);

    void converter(std::string raw_buffer);

};

#endif

#if 0

#define CONVERTED_ARRAY_LIMIT 14

//using namespace std;

class Decoder {
public:
    void converter(std::string raw_buffer);
    void adsb_parser(std::string raw_buffer);

    int get_ca() { return xponder_capability; }
    int get_df() { return downlink_format; }
    int get_icao() { return icao_address; }
    int get_me() { return message; }
    int get_pi() { return parity; }
    int get_tc() { return type_code; }
private:
    int downlink_format; // DF
    int icao_address; // ICAO
    int xponder_capability; // CA
    int message; // ME
    int parity; // PI
    int type_code; // TC

    // raw array contains original extracted message
    //int raw_array_limit;
    //char* raw_array_ptr;

    // converted array is for converted message
    //int converted_array_limit;
    unsigned short int converted_array[CONVERTED_ARRAY_LIMIT];
};
#endif
