#ifndef STRUCTURES
#define STRUCTURES
#include <string>
struct patient{
    int cardNum;
    int ind;
    bool operator == (const patient&);
    patient(int, int);
    patient();
};
struct patientInfo{
    int cardNum;
    char illness[8];
    char doctor[16];
    void set_fields(int, std::string, std::string);
};
#endif