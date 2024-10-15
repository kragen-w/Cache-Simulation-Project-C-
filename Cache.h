#ifndef CACHE_H
#define CACHE_H
#include "Set.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"
#include "Memory.h"

class Cache{
    private:
        Memory* memory;
        int cache_size;
        int block_size;
        int set_associativity;
        int set_count;
        Set** sets;
        AddressDecoder* decoder;
        int tag_len;
        int set_index_len;
        int block_index_len;
        PerformanceCounter* counter;



        
    public:
        Cache(Memory* memory, int cache_size, int block_size, int set_associativity);
        unsigned char read(unsigned long p);
        void write(unsigned long p, unsigned char c);
        void display();

};

#endif