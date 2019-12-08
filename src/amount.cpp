// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
<<<<<<< Updated upstream
// Copyright (c) 2017-2018 The PIVX developers
=======
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amount.h"

#include "tinyformat.h"

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nSize)
{
    if (nSize > 0)
        nSatoshisPerK = nFeePaid * 1000 / nSize;
    else
        nSatoshisPerK = 0;
}

CAmount CFeeRate::GetFee(size_t nSize) const
{
    CAmount nFee = nSatoshisPerK * nSize / 1000;

    if (nFee == 0 && nSatoshisPerK > 0)
        nFee = nSatoshisPerK;

    return nFee;
}

std::string CFeeRate::ToString() const
{
<<<<<<< Updated upstream
    return strprintf("%d.%08d PIV/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN);
=======
    return strprintf("%d.%08d PrimeStone/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN);
>>>>>>> Stashed changes
}
