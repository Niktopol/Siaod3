#include "binf_worker.h"
binf_worker::binf_worker(){
    file.open("bininput.bin", std::ios::trunc | std::ios::in | std::ios::out | std::ios::binary);
    size = 0;
}
void binf_worker::write_to_file(patientInfo& info){
    if (file.is_open()){
        file.seekp(0, std::ios::end);
        file.write(reinterpret_cast<char*>(&info), sizeof(info));
        ++size;
    }
}
void binf_worker::remove_from_file(unsigned int key){
    if(file.is_open()){
        file.seekg(0, std::ios::beg);
        std::ofstream ofs("temp.bin", std::ios::out | std::ios::binary); 
        patientInfo info;
        for (int i = 0; i < size; i++){
            if (i != key){
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
        file.open("bininput.bin", std::ios::in | std::ios::out | std::ios::binary);
        --size;
    }
}
std::string binf_worker::find_in_file(unsigned int key){
    std::string record;
    if(file.is_open() && key  <= (size-1)){
        patientInfo info;
        file.seekg(key*sizeof(info), std::ios::beg);
        file.read(reinterpret_cast<char*>(&info), sizeof(patientInfo));
        record.append(std::to_string(info.cardNum)+" ");
        record.append(info.illness);
        record.append(" ");
        record.append(info.doctor);
    }
    return record;
}
hash_table* binf_worker::make_table(){
    patientInfo info;
    hash_table* table = new hash_table();
    if (file.is_open()){
        file.seekg(0, std::ios::beg);
        for(int i = 0; i < size; i++){
            file.read(reinterpret_cast<char*>(&info), sizeof(info));
            table->push_key(info, i);
        }
    }
    return table;
}
binf_worker::~binf_worker(){
    file.close();
}