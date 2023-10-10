#ifndef HASH_TABLE
#define HASH_TABLE
#include <forward_list>
#include "structures.h"
#include <iostream>
class hash_table{
    int size;
    int records;
    std::forward_list<patient> *table;
public:
    void re_hash();
    void push_key(patientInfo&, int);
    int find(int);
    int remove(int);
    void print_table();
    hash_table();
    ~hash_table();
};
#endif