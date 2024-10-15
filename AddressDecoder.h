#ifndef ADDRESSDECODER_H
#define ADDRESSDECODER_H

class AddressDecoder{
    private:
        int tag_len;
        int set_index_len;
        int block_offset_len;
        
        

        
    public:
        AddressDecoder(int tag_len, int set_index_len, int block_offset_len);
        int getTag(unsigned long address);
        int getSetIndex(unsigned long address);
        int getBlockOffset(unsigned long address);


};

#endif