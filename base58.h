// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_BASE58_H
#define BITCOIN_BASE58_H

#include <algorithm>
#include <assert.h>
#include <string.h>

#include <string>
#include <vector>

bool DecodeBase58(const char* psz, unsigned char* vout, int max_ret_len = 34);

#endif // BITCOIN_BASE58_H
