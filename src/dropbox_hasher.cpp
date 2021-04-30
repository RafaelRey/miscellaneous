
/* Dropbox Hash 
    This little C++ implements the dropbox hash algorithm

    1.Split the file into blocks of 4 MB (4,194,304 or 4 * 1024 * 1024 bytes). The last block (if any) may be smaller than 4 MB.
    2.Compute the hash of each block using SHA-256.
    3.Concatenate the hash of all blocks in the binary format to form a single binary string.
    4.Compute the hash of the concatenated string using SHA-256. Output the resulting hash in hexadecimal format.

    Rafael Rey 2021
*/
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <openssl/sha.h>

/*
SHA 256 Calculation function adapted from one found on StackOverflow
*/
std::string sha256(const char *start, size_t len)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, start, len);
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    
    return ss.str();
}
int main(int argc, char* argv[]) {

    std::streampos block_size = 4 * 1024 * 1024; //4 MB

    if(argc != 2){
        std::cout << "Error bag args" << std::endl;
        return 1;
    }else{
        std::ifstream input_file(argv[1], std::ifstream::binary);

        if( input_file.is_open() ){
            
            std::vector<std::string> hash_strings;
            std::string concatenned_hashes;

            input_file.seekg (0, input_file.end);
            std::streampos size = input_file.tellg();
            input_file.seekg (0, std::ios::beg);

            std::cout<< "File Size: " << size << std::endl;
            std::cout<< "Ratio: " << (float)size/block_size << ", Blocks: " << std::ceil((float)size/block_size) << std::endl;

            for(int steps = 1; steps < std::ceil((float)size/block_size); steps++){
                char* memblock = new char [block_size];

                input_file.read (memblock, block_size);
                input_file.seekg( block_size * steps );

                hash_strings.push_back(sha256(memblock,block_size));
                delete[] memblock;
            }

            for(auto &it: hash_strings){
                std::cout<< it << std::endl;
                concatenned_hashes += it;
            }

            std::cout<<"Final Hash: " << sha256(concatenned_hashes.data(), concatenned_hashes.size()) << std::endl;

            input_file.close();
        }
    }
    return 0;
}
