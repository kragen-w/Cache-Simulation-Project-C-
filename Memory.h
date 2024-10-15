#ifndef MEMORY_H
#define MEMORY_H

class Memory{
    private:
        int mem_size;
        unsigned char* mem_pointer;

    public:
        Memory(int mem_size);
        unsigned char getByte(unsigned long* p);
        void setByte(unsigned long* p, unsigned char c);
        int getMemorySize();
        void display();
        unsigned char* getMemPointer();
};

#endif