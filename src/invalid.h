// Copyright (c) 2018 The PIVX developers
<<<<<<< Updated upstream
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_INVALID_H
#define PIVX_INVALID_H

#endif //PIVX_INVALID_H
=======
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PrimeStone_INVALID_H
#define PrimeStone_INVALID_H

#endif //PrimeStone_INVALID_H
>>>>>>> Stashed changes

#include <libzerocoin/bignum.h>
#include <univalue/include/univalue.h>
#include <primitives/transaction.h>

namespace invalid_out
{
    extern std::set<CBigNum> setInvalidSerials;
    extern std::set<COutPoint> setInvalidOutPoints;

    UniValue read_json(const std::string& jsondata);

    bool ContainsOutPoint(const COutPoint& out);
    bool ContainsSerial(const CBigNum& bnSerial);
    bool LoadOutpoints();
    bool LoadSerials();
}