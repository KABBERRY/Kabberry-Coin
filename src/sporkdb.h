// Copyright (c) 2017 The PIVX developers
<<<<<<< Updated upstream
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_CSPORKDB_H
#define PIVX_CSPORKDB_H
=======
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PrimeStone_CSPORKDB_H
#define PrimeStone_CSPORKDB_H
>>>>>>> Stashed changes

#include <boost/filesystem/path.hpp>
#include "leveldbwrapper.h"
#include "spork.h"

class CSporkDB : public CLevelDBWrapper
{
public:
    CSporkDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);

private:
    CSporkDB(const CSporkDB&);
    void operator=(const CSporkDB&);

public:
<<<<<<< Updated upstream
    bool WriteSpork(const SporkId nSporkId, const CSporkMessage& spork);
    bool ReadSpork(const SporkId nSporkId, CSporkMessage& spork);
    bool SporkExists(const SporkId nSporkId);
};


#endif //PIVX_CSPORKDB_H
=======
    bool WriteSpork(const int nSporkId, const CSporkMessage& spork);
    bool ReadSpork(const int nSporkId, CSporkMessage& spork);
    bool SporkExists(const int nSporkId);
};


#endif //PrimeStone_CSPORKDB_H
>>>>>>> Stashed changes
