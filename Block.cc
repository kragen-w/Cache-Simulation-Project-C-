#include <stdio.h>

#include "Block.h"
#include "Memory.h"



#include <chrono> // to bring in the chrono library
// to make an instance of a high resolution clock called m_clock
std::chrono::high_resolution_clock m_clock;
// to get the number of nanoseconds that have elapsed since the epoch (Jan 1, 1970) as a long

Block::Block(Memory* memory, int block_size){
    this->memory = memory;
    this->block_size = block_size;
    this->tag = 0;
    this->data = new unsigned char[this->block_size];
    for (int i = 0; i < this->block_size; i++){
        this->data[i] = 0;
    }
    this->is_valid = false;
    this->is_dirty = false;
    this->time_made = 0;
    this->p = 0;
    
}

unsigned char Block::read(int p){   
    return this->data[p];
}
void Block::write(int p, unsigned char c){
    this->data[p] = c;
}
void Block::setValid(bool valid){
    this->is_valid = valid;
}

void Block::setDirty(bool dirty){
    this->is_dirty = dirty;
}

void Block::setTag(unsigned int tag){
    this->tag = tag;
}

void Block::setTime(){
    long nanoSec = std::chrono::duration_cast<std::chrono::nanoseconds>(m_clock.now().time_since_epoch()).count();
    this->time_made = nanoSec;
}

bool Block::isValid(){
    return this->is_valid;
}

bool Block::isDirty(){
    return this->is_dirty;
}

unsigned int Block::getTag(){
    return this->tag;
}

long Block::getTime(){
    return this->time_made;
}

void Block::display(){
    printf("\t\t\tValid: %d\t Tag: %d\t Dirty: %d\t Time: %ld\n", this->is_valid, this->tag, this->is_dirty, this->time_made);
    printf("\t\t\tData: ");
    for (int i = 0; i < this->block_size; i++){
        printf("%02x ", this->data[i]);
    }
    printf("\n");

}

void Block::loadFromMemory(unsigned long p){
    unsigned long block_start = p - (p % this->block_size);
    for (int i = 0; i < this->block_size; i++){
        this->data[i] = memory->getMemPointer()[block_start+i];
    }
}

void Block::saveToMemory(){
    unsigned long block_start = this->p - (this->p % this->block_size);
    for (int i = 0; i < this->block_size; i++){
        memory->getMemPointer()[block_start+i] = this->data[i];
    }
}

void Block::setP(unsigned long p){
    this->p = p;
}