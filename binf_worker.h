#ifndef BINF_WORKER
#define BINF_WORKER
#include <fstream>
#include <string>
#include "hash_table.h"
#include "structures.h"
class binf_worker{
    std::fstream file;
    int size;
public:
    binf_worker();
    void write_to_file(patientInfo&);
    void remove_from_file(unsigned int);
    std::string find_in_file(unsigned int);
    hash_table* make_table();
    ~binf_worker();
};
#endif