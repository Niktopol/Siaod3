#include <iostream>
#include <fstream>
#include <string>
#include <forward_list>
#include <vector>
#include <algorithm>
#include <chrono>
#include "binf_worker.h"
#include "hash_table.h"
#include "structures.h"
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
void genBinFile(int size, binf_worker& file){
    std::ifstream fin("input.txt");
    if (fin.is_open()){
        patientInfo info;
        for (int i = 0; i < size; i++){
            fin >> info.cardNum;
            fin >> info.illness;
            fin >> info.doctor;
            file.write_to_file(info);
        }
        fin.close();
    }
}
int main(){
    /*
    while (true){
        std::cout << "Enter a command" << std::endl;
        std::cin >> cmd;
        if (cmd == "Add"){
            std::cout << "Enter card number, illness code and doctor's surname" << std::endl;
            std::cin >> info.cardNum;
            std::cin >> info.illness;
            std::cin >> info.doctor;
            inp_table.push_key(info, records.size());
            records.push_back(patientInfo(info));
        }else if(cmd == "Print"){
            inp_table.print_table();
        }else if(cmd == "Array"){
            for(int i = 0; i < records.size(); i++){
                std::cout << i <<": " << records.at(i).cardNum << ' ' << records.at(i).illness << ' ' << records.at(i).doctor << std::endl;
            }
        }else if(cmd == "Find"){
            std::cin >> num;
            num = inp_table.find(num);
            if (num >= 0){
                std::cout << "Record found: " << records.at(num).cardNum << ' ' << records.at(num).illness << ' ' << records.at(num).doctor << std::endl;
            }else{
                std::cout << "Record not found" << std::endl;
            }
        }else if(cmd == "Remove"){
            std::cin >> num;
            num = inp_table.remove(num);
            if (num >= 0){
                std::cout << "Record removed"<< std::endl;
                records.erase(records.begin()+num);
            }else{
                std::cout << "No such record" << std::endl;
            }
        }else{
            break;
        }
    }*/

    srand(time(nullptr));
    hash_table inp_table;
    std::string cmd;
    patientInfo info;
    int num;
    std::vector<patientInfo> records;
    
    //Задание 2
    //Тест 1
    info.set_fields(123, "X99", "Petrovich");
    inp_table.push_key(info, records.size());
    records.push_back(info);
    

    info.set_fields(256, "C34", "Pavlovich");
    inp_table.push_key(info, records.size());
    records.push_back(info);
    

    info.set_fields(98, "F33", "Phomich");
    inp_table.push_key(info, records.size());
    records.push_back(info);
    
    inp_table.print_table();

    for(int i = 0; i < records.size(); i++){
        std::cout << i <<": " << records.at(i).cardNum << ' ' << records.at(i).illness << ' ' << records.at(i).doctor << std::endl;
    }
    std::cout << "----------------" << std::endl;
    //Тест 2
    info.set_fields(16, "B21", "Storonovich");
    inp_table.push_key(info, records.size());
    records.push_back(info);

    inp_table.print_table();

    for(int i = 0; i < records.size(); i++){
        std::cout << i <<": " << records.at(i).cardNum << ' ' << records.at(i).illness << ' ' << records.at(i).doctor << std::endl;
    }
    std::cout << "----------------" << std::endl;
    //Тест 3
    info.set_fields(8, "B21", "Brat1");
    inp_table.push_key(info, records.size());
    records.push_back(info);

    info.set_fields(24, "B22", "Brat2");
    inp_table.push_key(info, records.size());
    records.push_back(info);

    info.set_fields(32, "B23", "Brat3");
    inp_table.push_key(info, records.size());
    records.push_back(info);

    info.set_fields(40, "B24", "Brat4");
    inp_table.push_key(info, records.size());
    records.push_back(info);

    info.set_fields(48, "B25", "Brat5");
    inp_table.push_key(info, records.size());
    records.push_back(info);

    inp_table.print_table();

    for(int i = 0; i < records.size(); i++){
        std::cout << i <<": " << records.at(i).cardNum << ' ' << records.at(i).illness << ' ' << records.at(i).doctor << std::endl;
    }
    std::cout << "----------------" << std::endl;
    //Тест 4
    records.erase(records.begin()+inp_table.remove(16));
    records.erase(records.begin()+inp_table.remove(40));

    inp_table.print_table();

    for(int i = 0; i < records.size(); i++){
        std::cout << i <<": " << records.at(i).cardNum << ' ' << records.at(i).illness << ' ' << records.at(i).doctor << std::endl;
    }
    std::cout << "----------------" << std::endl;
    //Тест 5
    int ind = inp_table.find(32);
    std::cout << ind <<": " << records.at(ind).cardNum << ' ' << records.at(ind).illness << ' ' << records.at(ind).doctor << std::endl;
    std::cout << "----------------" << std::endl;

    //Задание 3
    int size;
    std::cout << "Enter file size" << std::endl;
    std::cin >> size;
    genTxtFile(size);
    binf_worker file;
    genBinFile(size, file);

    auto begin = std::chrono::high_resolution_clock::now();
    hash_table* table = file.make_table();
    std::cout << "Table created in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns\n";
    while (true){
        std::cout << "Enter a command" << std::endl;
        std::cin >> cmd;
        if (cmd == "Add"){
            std::cout << "Enter card number, illness code and doctor's surname" << std::endl;
            std::cin >> info.cardNum;
            std::cin >> info.illness;
            std::cin >> info.doctor;
            table->push_key(info, file.get_size());
            file.write_to_file(info);
        }else if(cmd == "Find"){
            std::cin >> num;
            begin = std::chrono::high_resolution_clock::now();
            num = table->find(num);
            if (num >= 0){
                std::cout << "Record found: " << file.find_in_file(num) << std::endl;
            }else{
                std::cout << "Record not found" << std::endl;
            }
            std::cout << "Search finished in: " << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - begin).count() << " ns\n";
        }else if(cmd == "Remove"){
            std::cin >> num;
            num = table->remove(num);
            if (num >= 0){
                std::cout << "Record removed"<< std::endl;
                file.remove_from_file(num);
            }else{
                std::cout << "No such record" << std::endl;
            }
        }else{
            break;
        }
    }
    delete table;
    return 0;
}