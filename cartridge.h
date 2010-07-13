#ifndef CARTRIDGE_H_
#define CARTRIDGE_H_

#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif


    typedef enum{
        EGB,
        EGBC,
        ESGB
    }GBMODE;

    typedef struct {
        uint8 index;
        char * Name;
    }Cart_mode;

    typedef struct {
        uint8 index;
        char * Name;
        int nbanks;
    }Cart_size_mode;

    typedef struct
    {
        uint8 * gbcart;
        char name[17];
        int SGB,GBC;
        Cart_mode type;
        Cart_size_mode size;
        int ramsize;
        int rombank,rambank;
    } Cartridge;

    int read_cart_file(const char * name,Cartridge * cart);
    void destroy_cart_file(Cartridge * cart);

    void parse_cart_Header(GBMODE mode,Cartridge * cart);
    void parse_cart_Name(GBMODE mode,Cartridge * cart);
    void parse_cart_SGBCapable(Cartridge * cart);
    void parse_cart_GBCCapable(Cartridge * cart);
    void parse_cart_type(Cartridge * cart);
    void parse_cart_size(Cartridge * cart);
    void parse_cart_ramsize(Cartridge * cart);
    void parse_cart_notimportant(Cartridge * cart);

    void initMemory(uint8** gbmemory,Cartridge ** gbcart,Cartridge * cart);



#ifdef __cplusplus
}
#endif


#endif /*CARTRIDGE_H_*/
