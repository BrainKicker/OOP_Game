#ifndef GAME_DATA_H
#define GAME_DATA_H

union data {

    bool b;

    char c;

    unsigned char uc;

    short s;
    int i;
    long l;
    long long ll;

    unsigned short us;
    unsigned int ui;
    unsigned long ul;
    unsigned long long ull;

    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;

    uint8_t ui8;
    uint16_t ui16;
    uint32_t ui32;
    uint64_t ui64;

    float f;
    double d;
    long double ld;

    bool* b_p;

    char* c_p;

    unsigned char* uc_p;

    short* s_p;
    int* i_p;
    long* l_p;
    long long* ll_p;

    unsigned short* us_p;
    unsigned int* ui_p;
    unsigned long* ul_p;
    unsigned long long* ull_p;

    int8_t* i8_p;
    int16_t* i16_p;
    int32_t* i32_p;
    int64_t* i64_p;

    uint8_t* ui8_p;
    uint16_t* ui16_p;
    uint32_t* ui32_p;
    uint64_t* ui64_p;

    float* f_p;
    double* d_p;
    long double* ld_p;

    void* v;

    void (*func)();

    data* data_p;
};

#endif //GAME_DATA_H