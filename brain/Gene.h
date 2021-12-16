#pragma once

#include "Random.h"

static_assert(INT16_MAX == 0x7fff, "Invalid max for UINT16");

// Lots of genetic algos mutate _very_ quickly
// But if we want to get close to something living, I guess
// We should create something that is only able to mutate new features a small percentage of the time
// and do some kind of error correction, like DNA I guess? Many genes don't do crap.
// Sometimes, sometimes, sometimes an error will occur unchecked, and a ton of these errors may eventually lead
// to something unique, development of blue eyes took a lot less time than monkey to human
// We need something to start off incredibly simple. Stupidly simple. That will over long periods of time
// Develop new features of itself.


// 1 byte hash for DNA-like error correction
// 3 bytes for data

#pragma pack(1)

// Note: Sex actually isn't decided in genes. Genes may differ (?) due to sex
// but X/Y of sperm in reproduction (random) determines sex

// Note 2: We will have to somewhat "construct" our first beings out of basic genes

class Gene
{
public:
    static Gene* CreateRandom()
    {
        return nullptr;
    }

    // Genes that define the creature
    // This can be as fundamental or not... as you like
    // Since our creatures exist in a 2d world, genes defining:
    //      - shape
    //      - color
    //      - 
    enum class Type
    {
        Shape,
        Color, 
        Size,
    };

    // An extremely basic hash function
    // 1 byte hash, this means when mutations occur not only
    // do they need to corrupt the data, they also need to corrupt the paired hash
    // This is made much simpler by making the hash itself much simpler and prone to collisions
    // If a hash check fails, the gene is ignored. If a "crucial" gene is missing, the birth will fail
    uint8_t GetHash()
    {
        uint8_t hash = 0u;

        for (size_t i = 0; i < sizeof(data); ++i)
        {
            hash = ((37 * hash) + data[i]) & 0xff;
        }
    }

    union
    {
        struct {
            unsigned char geneType;
            unsigned char p0;
            unsigned char p1;
            unsigned char p2;
        } geneParameters;

        unsigned char data[4];
    };
};

#pragma pack()

static_assert(sizeof(Gene) == sizeof(uint32_t), "Invalid size for Gene.");