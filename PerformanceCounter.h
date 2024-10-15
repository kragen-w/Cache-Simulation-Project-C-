#ifndef PERFORMANCECOUNTER_H
#define PERFORMANCECOUNTER_H

class PerformanceCounter{
    private:
        int hit_count;
        int miss_count;
        int writeback_count;
        
        

        
    public:
        PerformanceCounter();
        void incrementHits();
        void incrementMisses();
        void incrementWritebacks();
        int getHits();
        int getMisses();
        int getWritebacks();
        int getAccesses();
        void display();


};

#endif