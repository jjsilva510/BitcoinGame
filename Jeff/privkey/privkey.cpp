/*Jeffrey Silva 
privkey.cpp : This file contains the 'main' function.Program execution begins and ends there.

*/
#include <iostream>
#include <iomanip>
//custom include files
#include <osrng.h>
#include <hex.h>

int main() {
    // Define byte as unsigned char if not defined
    typedef unsigned char byte;

    // Initialize the random number generator
    CryptoPP::AutoSeededRandomPool rng;

    // Generate a 256-bit (32 bytes) random number
    byte privateKey[32];
    rng.GenerateBlock(privateKey, sizeof(privateKey));

    // Convert the private key to a hexadecimal string
    std::string hexPrivateKey;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexPrivateKey));
    encoder.Put(privateKey, sizeof(privateKey));
    encoder.MessageEnd();

    // Output the private key
    std::cout << "Bitcoin Private Key (hex): " << hexPrivateKey << std::endl;

    return 0;
}