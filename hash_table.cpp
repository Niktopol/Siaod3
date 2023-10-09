#include "hash_table.h"
int hash_table::get_records(){
    return records;
}
void hash_table::re_hash(){
    std::forward_list<patient> *newTable = new std::forward_list<patient>[size * 2];
    for (int i = 0; i < size; i++){
        for (patient j : table[i]){
            newTable[j.cardNum % (size * 2)].push_front(patient(j.cardNum, j.ind));
        }
    }
    delete[] table;
    size *= 2;
    table = newTable;
}
void hash_table::push_key(patientInfo &info, int ind){
    table[info.cardNum % size].push_front(patient(info.cardNum, ind));
    ++records;
    if ((records / size) >= 0.75){
        this->re_hash();
    }
}
int hash_table::find(int key){
    for (patient i : table[key % size]){
        if (i.cardNum == key){
            return i.ind;
        }
    }
    return -1;
}
int hash_table::remove(int key){
    for (patient i : table[key % size]){
        if (i.cardNum == key){
            int ind = i.ind;
            table[key % size].remove(i);
            return ind;
        }
    }
    return -1;
}
void hash_table::print_table(){
    for (int i = 0; i < size; i++){
        std::cout << "Row " << i << ": ";
        for (patient j : table[i]){
            std::cout << j.ind << " ";
        }
        std::cout << std::endl;
    }
}
hash_table::hash_table(){
    this->size = 8;
    this->records = 0;
    this->table = new std::forward_list<patient>[8];
}
hash_table::~hash_table(){
    delete[] table;
}