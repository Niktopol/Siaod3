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
patientInfo::patientInfo(){}
patientInfo::patientInfo(const patientInfo& info){
    this->cardNum = info.cardNum;
    for (int i = 0; i < 8; i++){
        this->illness[i] = info.illness[i];
    }
    for (int i = 0; i < 16; i++){
        this->doctor[i] = info.doctor[i];
    }
}