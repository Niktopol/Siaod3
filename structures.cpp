#include "structures.h"
bool patient::operator == (const patient& compared){
    return (this->cardNum == compared.cardNum && this->ind == compared.ind);
}
patient::patient(int cardNum, int ind){
    this->cardNum = cardNum;
    this->ind = ind;
}
patient::patient(){
    this->cardNum = 0;
    this->ind = -1;
}
void patientInfo::set_fields(int cardNum, std::string illness, std::string doctor){
    this->cardNum = cardNum;
    for (int i = 0; i < (illness.size() < 7? illness.size() : 7); i++){
        this->illness[i] = illness.at(i);
        if (i+1 == (illness.size() < 7? illness.size() : 7)){
            this->illness[i+1] = '\0';
        }
    }
    for (int i = 0; i < (doctor.size() < 15? doctor.size() : 15); i++){
        this->doctor[i] = doctor.at(i);
        if (i+1 == (doctor.size() < 15? doctor.size() : 15)){
            this->doctor[i+1] = '\0';
        }
    }
}