#ifndef SET_H
#define SET_H
#include "Block.h"
#include "AddressDecoder.h"
#include "PerformanceCounter.h"
#include "Memory.h"

class Set{
    private:
        Memory* memory;
        AddressDecoder* decoder;
        Block** blocks;
        int block_number;
        int block_size;
        PerformanceCounter* counter;
        
        
    public:
        Set(Memory* memory, AddressDecoder* decoder, int block_number, int block_size, PerformanceCounter* counter);
        unsigned char read(unsigned long p);
        void write(unsigned long p, unsigned char c);
        void display();
        unsigned char hit(unsigned long p, bool read, int i, unsigned char c);
        unsigned char empty_miss(unsigned long p, bool read, int i, unsigned char c);
        unsigned char full_miss(unsigned long p, bool read, unsigned char c);
};

#endif