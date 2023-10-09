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