#include <stdio.h>

#include "AddressDecoder.h"

AddressDecoder::AddressDecoder(int tag_len, int set_index_len, int block_offset_len){
    this->tag_len = tag_len;
    this->set_index_len = set_index_len;
    this->block_offset_len = block_offset_len;
}

int AddressDecoder::getTag(unsigned long address){
    int temp = ((int)address>>(this->set_index_len + this->block_offset_len));
    return temp;


}
int AddressDecoder::getSetIndex(unsigned long address){
    int temp = (address >> this->block_offset_len) & ((1 << this->set_index_len) - 1);
    return temp;

}
int AddressDecoder::getBlockOffset(unsigned long address){
    int temp = address & ((1 << this->block_offset_len) - 1);
    return temp;
    

}