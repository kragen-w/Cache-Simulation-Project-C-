#include <stdio.h>
#include <string>
#include <cmath>
#include "Cache.h"
#include "Set.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"
#include "Memory.h"

Cache::Cache(Memory* memory, int cache_size, int block_size, int set_associativity){
    this->memory = (memory);
    this->cache_size = cache_size;
    this->block_size = block_size;
    this->set_associativity = set_associativity;
    this->set_count = (cache_size/block_size)/set_associativity;

    
    this->set_index_len = log2((double)this->set_count);
    this->block_index_len = log2((double)this->block_size);
    this->tag_len = log2((double)this->memory->getMemorySize()) - this->set_index_len - this->block_index_len;

    this->decoder = new AddressDecoder(tag_len, set_index_len, block_index_len);
    this->counter = new PerformanceCounter();

    this->sets = new Set*[set_count];
    for (int i = 0; i < set_count; i++){
        this->sets[i] = new Set(memory, decoder, set_associativity, block_size, counter);
    }

    

    


}

unsigned char Cache::read(unsigned long p){
    int index = this->decoder->getSetIndex(p);
    return sets[index]->read(p);
}
void Cache::write(unsigned long p, unsigned char c){
    int index = this->decoder->getSetIndex(p);
    sets[index]->write(p, c);
}

void Cache::display(){
    printf("CACHE MEMORY:\n");
    
    printf("\n");
    for (int i = 0; i < this->set_count; i++){
        printf("\tSet %d\n", i);
        this->sets[i]->display();
        printf("\n");
    }
    this->counter->display();
}