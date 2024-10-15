#ifndef BLOCK_H
#define BLOCK_H
#include "Memory.h"

class Block{
    private:
        Memory* memory;
        int block_size;
        int tag;
        bool is_valid;
        bool is_dirty;
        long time_made;
        unsigned char* data;
        unsigned long p;

        
    public:
        Block(Memory* memory, int block_size);
        unsigned char read(int p);
        void write(int p, unsigned char c);
        void loadFromMemory(unsigned long p);
        void saveToMemory();
        void setValid(bool valid);
        void setDirty(bool dirty);
        void setTag(unsigned int tag);
        void setTime();
        bool isValid();
        bool isDirty();
        unsigned int getTag();
        long getTime();
        void display();
        void setP(unsigned long p);



};

#endif