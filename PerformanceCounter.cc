#include <stdio.h>

#include "PerformanceCounter.h"

PerformanceCounter::PerformanceCounter(){
    this->hit_count = 0;
    this->miss_count = 0;
    this->writeback_count = 0;
}
void PerformanceCounter::incrementHits(){
    this->hit_count++;
}
void PerformanceCounter::incrementMisses(){
    this->miss_count += 1;
}
void PerformanceCounter::incrementWritebacks(){
    this->writeback_count++;
}
int PerformanceCounter::getHits(){
    return this->hit_count;
}
int PerformanceCounter::getMisses(){
    return this->miss_count;
}
int PerformanceCounter::getWritebacks(){
    return this->writeback_count;
}
int PerformanceCounter::getAccesses(){
    return this->miss_count + this->hit_count;
}
void PerformanceCounter::display(){
    printf("PERFORMANCE COUNTER:\n");
    printf("\tAccesses: %d\n", this->getAccesses());
    printf("\tHits: %d\n", this->hit_count);
    printf("\tMisses: %d\n", this->miss_count);
    printf("\tWritebacks: %d\n", this->writeback_count);
    if (this->getAccesses() == 0){
        printf("\tMiss Rate: 0.00\n");
        printf("\tWriteback Rate: 0.00\n");
        return;
    }
    printf("\tMiss Rate: %.2f\n", (float)this->miss_count/(float)this->getAccesses());
    printf("\tWriteback Rate: %.2f\n", (float)this->writeback_count/(float)this->getAccesses());
    return;
}