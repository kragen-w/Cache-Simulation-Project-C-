#include <stdio.h>

#include "Set.h"
#include "Block.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"
#include "Memory.h"

Set::Set(Memory* memory, AddressDecoder* decoder, int block_number, int block_size, PerformanceCounter* counter){
    this->memory = (memory);
    this->blocks = new Block*[block_number];
    this->decoder = decoder;
    this->counter = counter;
    this->block_number = block_number;
    this->block_size = block_size;
    for (int i = 0; i < block_number; i++){
        this->blocks[i] = new Block(memory, block_size);
        this->blocks[i]->setValid(false);
    }
}

unsigned char Set::hit(unsigned long p, bool read, int i, unsigned char c = 0){
    printf("HIT\n");
    counter->incrementHits();
    blocks[i]->setTime();
    blocks[i]->setP(p);
    if (read){
        return blocks[i]->read(decoder->getBlockOffset(p));
    }
    blocks[i]->write(decoder->getBlockOffset(p), c);
    blocks[i]->setDirty(true);
    return 0;
}

unsigned char Set::empty_miss(unsigned long p, bool read, int i, unsigned char c = 0){
    printf("MISS\n");
    counter->incrementMisses();
    blocks[i]->setValid(true);
    blocks[i]->setTag(decoder->getTag(p));
    blocks[i]->setTime();
    blocks[i]->loadFromMemory(p);
    blocks[i]->setP(p);
    if (read){
        return blocks[i]->read(decoder->getBlockOffset(p));
    }
    blocks[i]->write(decoder->getBlockOffset(p), c);
    blocks[i]->setDirty(true);
    return 0;
}

unsigned char Set::full_miss(unsigned long p, bool read, unsigned char c = 0){
    printf("MISS\n");
    counter->incrementMisses();
    long lowest_time = blocks[0]->getTime();
    int lowest_time_index = 0;
    for (int i = 0; i < block_number; i++){
        if (blocks[i]->getTime() < lowest_time){
            lowest_time = blocks[i]->getTime();
            lowest_time_index = i;
        }
    }



    printf("LRU\n");

    if (blocks[lowest_time_index]->isDirty()){
        blocks[lowest_time_index]->saveToMemory();
        blocks[lowest_time_index]->setDirty(false);
        counter->incrementWritebacks();

    } 

    blocks[lowest_time_index]->setTag(decoder->getTag(p));
    blocks[lowest_time_index]->setTime();
    blocks[lowest_time_index]->loadFromMemory(p);
    blocks[lowest_time_index]->setP(p);
    if (read){
        return blocks[lowest_time_index]->read(decoder->getBlockOffset(p));
    }
    blocks[lowest_time_index]->write(decoder->getBlockOffset(p), c);
    blocks[lowest_time_index]->setDirty(true);

    return 0;
}

unsigned char Set::read(unsigned long p){
    int tag = decoder->getTag(p);
    // checking if a block with the same tag is in the set
    for (int i = 0; i < block_number; i++){
        if (blocks[i]->isValid() && blocks[i]->getTag() == tag){
            return hit(p, true, i, 0);
        }
    }
    // the block is not in the set
    // miss
    // checking if there is an empty block
    for (int i = 0; i < block_number; i++){
        if (!blocks[i]->isValid()){
            return empty_miss(p, true, i, 0);
        }
    }
    // there is no empty block
    // getting the oldest block
    return full_miss(p, true, 0);
    

    
}



void Set::write(unsigned long p, unsigned char c){
    int tag = decoder->getTag(p);
    // checking if a block with the same tag is in the set
    for (int i = 0; i < block_number; i++){
        if (blocks[i]->isValid() && blocks[i]->getTag() == tag){
            hit(p, false, i, c);
            return;
        }
    }
    // the block is not in the set
    // miss
    // checking if there is an empty block
    for (int i = 0; i < block_number; i++){
        if (!blocks[i]->isValid()){
            empty_miss(p, false, i, c);
            return;
        }
    }
    // there is no empty block
    // getting the oldest block

    full_miss(p, false, c);
    return;
}



void Set::display(){
    printf("\t\tBLOCKS:\n");
    for (int i = 0; i < this->block_number; i++){
        printf("\t\tBlock %d\n", i);
        this->blocks[i]->display();
    }
}


