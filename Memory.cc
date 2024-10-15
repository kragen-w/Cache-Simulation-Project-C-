#include <stdio.h>

#include "Memory.h"

Memory::Memory(int mem_size){
    this->mem_size = mem_size;
    this->mem_pointer = new unsigned char[this->mem_size];
    for (int i = 0; i < this->mem_size; i++){
        this->mem_pointer[i] = i%255;
    }
}

unsigned char Memory::getByte(unsigned long* p){
    return (unsigned char)(*p);
}

void Memory::setByte(unsigned long* p, unsigned char c){
    *p = c;
}

int Memory::getMemorySize(){
    return mem_size;
}

void Memory::display(){
    printf("MAIN MEMORY:\n");
    for (int i = 0; i < this->mem_size; i++){
        if (i == mem_size/2){
            printf("\n");
        }
        printf("%02x ", this->mem_pointer[i]);
    }
    printf("\n");
}

unsigned char* Memory::getMemPointer(){
    return this->mem_pointer;
}

