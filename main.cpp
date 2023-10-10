#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <algorithm>
#include <chrono>

struct patient{
    int cardNum;
    int ind;
    bool operator == (const patient& compared){
        return (this->cardNum == compared.cardNum && this->ind == compared.ind);
    }
    patient(int cardNum, int ind){
        this->cardNum = cardNum;
        this->ind = ind;
    }
    patient(){
        this->cardNum = 0;
        this->ind = -1;
    }
};
struct patientInfo{
    int cardNum;
    char illness[8];
    char doctor[16];
};
struct hashTable{
    int size;
    int records;
    std::forward_list<patient> *table;
    void re_hash(){
        std::forward_list<patient> *newTable = new std::forward_list<patient>[size*2];
        for(int i = 0; i < size; i++){
            for(patient j: table[i]){
                newTable[j.cardNum%(size*2)].push_front(patient(j.cardNum, j.ind));
            }
        }
        delete [] table;
        size *= 2;
        table = newTable;
    }
    void push_key(patientInfo &info, int ind){
         table[info.cardNum%size].push_front(patient(info.cardNum, ind));
        ++records;
        if((records/size) >= 0.75){
            this->re_hash();
        }
    }
    int find(int key){
        for (patient i : table[key%size]){
            if (i.cardNum == key){
                return i.ind;
            }
        }
        return -1;
    }
    int remove(int key){
        for (patient i : table[key%size]){
            if (i.cardNum == key){
                int ind = i.ind;
                table[key%size].remove(i);
                --records;
                return ind;
            }
        }
        return -1;
    }
    void print_table(){
        for (int i = 0; i < size; i++){
            std::cout << "Row " << i << ": ";
            for(patient j : table[i]){
                std::cout << "Index: " << j.ind << " Key: " << j.cardNum;
            }
            std::cout << std::endl;
        }
    }
    hashTable(){
        this->size = 8;
        this->records = 0;
        this->table = new std::forward_list<patient>[8];
    }
    ~hashTable(){
        delete [] table;
    }
};

void genTxtFile(int size){
    std::ofstream fout("input.txt", std::ios::trunc | std::ios::out);
    std::string surnames [15] = {"Petrov", "Ivanov", "Sidorov", "Efimov", "Pahomov",
                                 "Dmitrov", "Palmov", "Pechkin", "Ptichkin", "Butilkin", 
                                 "Lyamkin", "Shishkin", "Medvedko", "Lemenko", "Muhinko"};
    if (fout.is_open()){
        for (int i = 0; i < size; i++){
            std::string data = std::to_string(1000000+rand()%9000000)+' ' + char(65+rand()%26) + std::to_string(10+rand()%90) + ' ' + surnames[rand()%15];
            fout << data << std::endl;
        }
    }
    fout.close();
}
void genBinFile(int size){
    std::ifstream fin("input.txt");
    std::ofstream binfout("bininput.bin", std::ios::trunc | std::ios::out | std::ios::binary);
    if (fin.is_open() && binfout.is_open()){
        patientInfo info;
        for (int i = 0; i < size; i++){
            fin >> info.cardNum;
            fin >> info.illness;
            fin >> info.doctor;
            binfout.write((char*)&info, sizeof(info));
        }
    }
    binfout.close();
    fin.close();
}
void remove_from_file(int key, hashTable &table, std::ifstream &file){
    int toremove = table.remove(key);
    if(toremove >= 0){
        file.seekg(0, std::ios::beg);
        std::ofstream ofs("temp.bin", std::ios::out | std::ios::binary); 
        patientInfo info;
        for (int i = 0; i < (table.records+1); i++){
            if (i != toremove){
                file.read(reinterpret_cast<char*>(&info), sizeof(patientInfo));
                ofs.write(reinterpret_cast<char*>(&info), sizeof(patientInfo));
            }else{
                file.seekg(sizeof(patientInfo), std::ios::cur);
            }
        }
        ofs.close(); 
        file.close();
        remove("bininput.bin");
        rename("temp.bin", "bininput.bin"); 
        file.open("bininput.bin", std::ios::in | std::ios::binary);
    }
}
void make_table_from_file(hashTable &table, std::ifstream &file, int size){
    patientInfo info;
    for(int i = 0; i < size; i++){
        file.read(reinterpret_cast<char*>(&info), sizeof(patientInfo));
        table.push_key(info, i);
    }
}
int main(){
    srand(time(nullptr));
    int size;

    std::cout << "Enter file size" << std::endl;
    std::cin >> size;
    genTxtFile(size);
    genBinFile(size);

    std::ifstream binf("bininput.bin", std::ios::in | std::ios::binary);
    hashTable table;
    auto begin = std::chrono::high_resolution_clock::now();
    make_table_from_file(table, binf, size);
    std::cout << "Finished in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns\n";
    remove_from_file(size, table, binf);
    binf.close();
    return 0;
}