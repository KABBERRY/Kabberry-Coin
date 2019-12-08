// Copyright (c) 2017 The PIVX developers
<<<<<<< Updated upstream
=======
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sporkdb.h"
#include "spork.h"

CSporkDB::CSporkDB(size_t nCacheSize, bool fMemory, bool fWipe) : CLevelDBWrapper(GetDataDir() / "sporks", nCacheSize, fMemory, fWipe) {}

<<<<<<< Updated upstream
bool CSporkDB::WriteSpork(const SporkId nSporkId, const CSporkMessage& spork)
=======
bool CSporkDB::WriteSpork(const int nSporkId, const CSporkMessage& spork)
>>>>>>> Stashed changes
{
    LogPrintf("Wrote spork %s to database\n", sporkManager.GetSporkNameByID(nSporkId));
    return Write(nSporkId, spork);

}

<<<<<<< Updated upstream
bool CSporkDB::ReadSpork(const SporkId nSporkId, CSporkMessage& spork)
=======
bool CSporkDB::ReadSpork(const int nSporkId, CSporkMessage& spork)
>>>>>>> Stashed changes
{
    return Read(nSporkId, spork);
}

<<<<<<< Updated upstream
bool CSporkDB::SporkExists(const SporkId nSporkId)
=======
bool CSporkDB::SporkExists(const int nSporkId)
>>>>>>> Stashed changes
{
    return Exists(nSporkId);
}
