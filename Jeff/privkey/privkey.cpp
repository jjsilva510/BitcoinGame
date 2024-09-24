#include <iostream>
#include <iomanip>
#include <osrng.h>
#include <hex.h>
#include <eccrypto.h>
#include <secblock.h>
#include <ecp.h>
#include <oids.h>

int main() {
    // Define byte as unsigned char if not defined
    typedef unsigned char byte;

    // Initialize the random number generator
    CryptoPP::AutoSeededRandomPool rng;

    // Create private and public key objects
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey privateKey;
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PublicKey publicKey;

    // Generate a private key on the secp256k1 curve (Bitcoin's elliptic curve)
    privateKey.Initialize(rng, CryptoPP::ASN1::secp256k1());

    // Derive the corresponding public key
    privateKey.MakePublicKey(publicKey);

    // Convert the private key to a hexadecimal string
    CryptoPP::Integer privKeyInt = privateKey.GetPrivateExponent();
    std::string hexPrivateKey;

    // Use a StringSink to capture the output into a string
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(hexPrivateKey));
    privKeyInt.Encode(encoder, privKeyInt.MinEncodedSize());
    encoder.MessageEnd();

    // Output the private key
    std::cout << "Bitcoin Private Key (hex): " << hexPrivateKey << std::endl;

    // Convert the public key to a hexadecimal string
    const CryptoPP::ECP::Point& point = publicKey.GetPublicElement();
    std::string hexPublicKey;

    // Encode the public key X and Y coordinates
    CryptoPP::HexEncoder pubKeyEncoder(new CryptoPP::StringSink(hexPublicKey));
    point.x.Encode(pubKeyEncoder, point.x.MinEncodedSize());
    point.y.Encode(pubKeyEncoder, point.y.MinEncodedSize());
    pubKeyEncoder.MessageEnd();

    // Output the public key
    std::cout << "Bitcoin Public Key (hex): " << hexPublicKey << std::endl;

    return 0;
}
