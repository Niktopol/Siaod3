#ifndef STRUCTURES
#define STRUCTURES
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
    patientInfo();
    patientInfo(const patientInfo&);
};
#endif