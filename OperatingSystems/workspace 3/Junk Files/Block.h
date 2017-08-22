#ifndef BLOCK_H
#define BLOCK_H
#include <string>
#include <vector>

class Block{
    private:
        int block_num;
        int block_size;
        std::vector<char> bytes;
        
    public:
        std::vector<char> getBytes();
        int getBlockNum();
        void addByte(char byte);
        void overwriteByte(int index, char byte);
        Block();
        Block(int block_num, int block_size);
        bool full();
}



#endif