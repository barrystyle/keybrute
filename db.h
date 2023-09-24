#ifndef DB_H
#define DB_H

#include <base58.h>

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <cstdint>

#include <algorithm>
#include <vector>

struct address_t {
    unsigned char pubkeyhash[20];
};

void initdb(const std::string& in_file);
bool is_in_db(unsigned char* pkh);

#endif // DB_H
