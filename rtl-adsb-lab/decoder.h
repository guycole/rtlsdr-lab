#ifndef __DECODER_H 
#define __DECODER_H

#define CONVERTED_ARRAY_LIMIT 14

typedef struct {
    unsigned short df;
    unsigned short capability;
    unsigned int icao;
} ADSB, *ADSB_PTR;

class Decoder {
public:
    Decoder(void);
    ~Decoder(void);

    int pipe_to_decoder();

/*
    unsigned short get_ca() { return xponder_capability; }
    unsigned short get_df() { return downlink_format; }
    unsigned short get_icao() { return icao_address; }
    unsigned short get_me() { return message; }
    unsigned short get_pi() { return parity; }
    unsigned short get_tc() { return type_code; }
    */
private:
    void adsb();
    void dispatcher();
    int converter(std::string raw_buffer);

    int converted_array_size;
    unsigned short int converted_array[CONVERTED_ARRAY_LIMIT];

    ADSB adsb_struct;

/*
    unsigned short downlink_format; // DF
    unsigned short icao_address; // ICAO
    unsigned short xponder_capability; // CA
    unsigned short message; // ME
    unsigned short parity; // PI
    unsigned short type_code; // TC
    */
};

#endif