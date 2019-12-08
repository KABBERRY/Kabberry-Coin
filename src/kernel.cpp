<<<<<<< Updated upstream
// Copyright (c) 2011-2013 The PPCoin developers
// Copyright (c) 2013-2014 The NovaCoin Developers
// Copyright (c) 2014-2018 The BlackCoin Developers
// Copyright (c) 2015-2019 The PIVX developers
=======
// Copyright (c) 2012-2013 The PPCoin developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp>
<<<<<<< Updated upstream
=======
#include <boost/lexical_cast.hpp>
>>>>>>> Stashed changes

#include "db.h"
#include "kernel.h"
#include "script/interpreter.h"
<<<<<<< Updated upstream
#include "util.h"
#include "stakeinput.h"
#include "utilmoneystr.h"
#include "zpivchain.h"

// v1 modifier interval.
static const int64_t OLD_MODIFIER_INTERVAL = 2087;
=======
#include "timedata.h"
#include "util.h"
#include "stakeinput.h"
#include "zPSCchain.h"

using namespace std;

bool fTestNet = false; //Params().NetworkID() == CBaseChainParams::TESTNET;

// Modifier interval: time to elapse before new modifier is computed
// Set to 3-hour for production network and 20-minute for test network
unsigned int nModifierInterval;
int nStakeTargetSpacing = 60;
unsigned int getIntervalVersion(bool fTestNet)
{
    if (fTestNet)
        return MODIFIER_INTERVAL_TESTNET;
    else
        return MODIFIER_INTERVAL;
}
>>>>>>> Stashed changes

// Hard checkpoints of stake modifiers to ensure they are deterministic
static std::map<int, unsigned int> mapStakeModifierCheckpoints =
    boost::assign::map_list_of(0, 0xfd11f4e7u);

<<<<<<< Updated upstream
=======
// Get time weight
int64_t GetWeight(int64_t nIntervalBeginning, int64_t nIntervalEnd)
{
    return nIntervalEnd - nIntervalBeginning - nStakeMinAge;
}

>>>>>>> Stashed changes
// Get the last stake modifier and its generation time from a given block
static bool GetLastStakeModifier(const CBlockIndex* pindex, uint64_t& nStakeModifier, int64_t& nModifierTime)
{
    if (!pindex)
<<<<<<< Updated upstream
        return error("%s : null pindex", __func__);
    while (pindex && pindex->pprev && !pindex->GeneratedStakeModifier())
        pindex = pindex->pprev;
    if (!pindex->GeneratedStakeModifier())
        return error("%s : no generation at genesis block", __func__);
=======
        return error("GetLastStakeModifier: null pindex");
    while (pindex && pindex->pprev && !pindex->GeneratedStakeModifier())
        pindex = pindex->pprev;
    if (!pindex->GeneratedStakeModifier())
        return error("GetLastStakeModifier: no generation at genesis block");
>>>>>>> Stashed changes
    nStakeModifier = pindex->nStakeModifier;
    nModifierTime = pindex->GetBlockTime();
    return true;
}

// Get selection interval section (in seconds)
static int64_t GetStakeModifierSelectionIntervalSection(int nSection)
{
    assert(nSection >= 0 && nSection < 64);
<<<<<<< Updated upstream
    int64_t a = MODIFIER_INTERVAL  * 63 / (63 + ((63 - nSection) * (MODIFIER_INTERVAL_RATIO - 1)));
    return a;
}

=======
    int64_t a = getIntervalVersion(fTestNet) * 63 / (63 + ((63 - nSection) * (MODIFIER_INTERVAL_RATIO - 1)));
    return a;
}

// Get stake modifier selection interval (in seconds)
static int64_t GetStakeModifierSelectionInterval()
{
    int64_t nSelectionInterval = 0;
    for (int nSection = 0; nSection < 64; nSection++) {
        nSelectionInterval += GetStakeModifierSelectionIntervalSection(nSection);
    }
    return nSelectionInterval;
}

>>>>>>> Stashed changes
// select a block from the candidate blocks in vSortedByTimestamp, excluding
// already selected blocks in vSelectedBlocks, and with timestamp up to
// nSelectionIntervalStop.
static bool SelectBlockFromCandidates(
<<<<<<< Updated upstream
    std::vector<std::pair<int64_t, uint256> >& vSortedByTimestamp,
    std::map<uint256, const CBlockIndex*>& mapSelectedBlocks,
=======
    vector<pair<int64_t, uint256> >& vSortedByTimestamp,
    map<uint256, const CBlockIndex*>& mapSelectedBlocks,
>>>>>>> Stashed changes
    int64_t nSelectionIntervalStop,
    uint64_t nStakeModifierPrev,
    const CBlockIndex** pindexSelected)
{
    bool fModifierV2 = false;
    bool fFirstRun = true;
    bool fSelected = false;
    uint256 hashBest = 0;
    *pindexSelected = (const CBlockIndex*)0;
<<<<<<< Updated upstream
    for (const PAIRTYPE(int64_t, uint256) & item : vSortedByTimestamp) {
        if (!mapBlockIndex.count(item.second))
            return error("%s : failed to find block index for candidate block %s", __func__, item.second.ToString().c_str());
=======
    BOOST_FOREACH (const PAIRTYPE(int64_t, uint256) & item, vSortedByTimestamp) {
        if (!mapBlockIndex.count(item.second))
            return error("SelectBlockFromCandidates: failed to find block index for candidate block %s", item.second.ToString().c_str());
>>>>>>> Stashed changes

        const CBlockIndex* pindex = mapBlockIndex[item.second];
        if (fSelected && pindex->GetBlockTime() > nSelectionIntervalStop)
            break;

        //if the lowest block height (vSortedByTimestamp[0]) is >= switch height, use new modifier calc
        if (fFirstRun){
            fModifierV2 = pindex->nHeight >= Params().ModifierUpgradeBlock();
            fFirstRun = false;
        }

        if (mapSelectedBlocks.count(pindex->GetBlockHash()) > 0)
            continue;

        // compute the selection hash by hashing an input that is unique to that block
        uint256 hashProof;
        if(fModifierV2)
            hashProof = pindex->GetBlockHash();
        else
            hashProof = pindex->IsProofOfStake() ? 0 : pindex->GetBlockHash();

        CDataStream ss(SER_GETHASH, 0);
        ss << hashProof << nStakeModifierPrev;
        uint256 hashSelection = Hash(ss.begin(), ss.end());

        // the selection hash is divided by 2**32 so that proof-of-stake block
        // is always favored over proof-of-work block. this is to preserve
        // the energy efficiency property
        if (pindex->IsProofOfStake())
            hashSelection >>= 32;

        if (fSelected && hashSelection < hashBest) {
            hashBest = hashSelection;
            *pindexSelected = (const CBlockIndex*)pindex;
        } else if (!fSelected) {
            fSelected = true;
            hashBest = hashSelection;
            *pindexSelected = (const CBlockIndex*)pindex;
        }
    }
    if (GetBoolArg("-printstakemodifier", false))
<<<<<<< Updated upstream
        LogPrintf("%s : selection hash=%s\n", __func__, hashBest.ToString().c_str());
    return fSelected;
}

/* NEW MODIFIER */

// Stake Modifier (hash modifier of proof-of-stake):
// The purpose of stake modifier is to prevent a txout (coin) owner from
// computing future proof-of-stake generated by this txout at the time
// of transaction confirmation. To meet kernel protocol, the txout
// must hash with a future stake modifier to generate the proof.
uint256 ComputeStakeModifier(const CBlockIndex* pindexPrev, const uint256& kernel)
{
    // genesis block's modifier is 0
    // all block's modifiers are 0 on regtest
    if (!pindexPrev || Params().NetworkID() == CBaseChainParams::REGTEST)
        return uint256();

    CHashWriter ss(SER_GETHASH, 0);
    ss << kernel;

    // switch with old modifier on upgrade block
    if (!Params().IsStakeModifierV2(pindexPrev->nHeight + 1))
        ss << pindexPrev->nStakeModifier;
    else
        ss << pindexPrev->nStakeModifierV2;

    return ss.GetHash();
}

=======
        LogPrintf("SelectBlockFromCandidates: selection hash=%s\n", hashBest.ToString().c_str());
    return fSelected;
}

>>>>>>> Stashed changes
// Stake Modifier (hash modifier of proof-of-stake):
// The purpose of stake modifier is to prevent a txout (coin) owner from
// computing future proof-of-stake generated by this txout at the time
// of transaction confirmation. To meet kernel protocol, the txout
// must hash with a future stake modifier to generate the proof.
// Stake modifier consists of bits each of which is contributed from a
// selected block of a given block group in the past.
// The selection of a block is based on a hash of the block's proof-hash and
// the previous stake modifier.
// Stake modifier is recomputed at a fixed time interval instead of every
// block. This is to make it difficult for an attacker to gain control of
// additional bits in the stake modifier, even after generating a chain of
// blocks.
bool ComputeNextStakeModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier, bool& fGeneratedStakeModifier)
{
    nStakeModifier = 0;
    fGeneratedStakeModifier = false;
<<<<<<< Updated upstream

    // modifier 0 on RegTest
    if (Params().NetworkID() == CBaseChainParams::REGTEST) {
        return true;
    }
=======
>>>>>>> Stashed changes
    if (!pindexPrev) {
        fGeneratedStakeModifier = true;
        return true; // genesis block's modifier is 0
    }
    if (pindexPrev->nHeight == 0) {
        //Give a stake modifier to the first block
        fGeneratedStakeModifier = true;
        nStakeModifier = uint64_t("stakemodifier");
        return true;
    }

    // First find current stake modifier and its generation block time
    // if it's not old enough, return the same stake modifier
    int64_t nModifierTime = 0;
    if (!GetLastStakeModifier(pindexPrev, nStakeModifier, nModifierTime))
<<<<<<< Updated upstream
        return error("%s : unable to get last modifier", __func__);

    if (GetBoolArg("-printstakemodifier", false))
        LogPrintf("%s : prev modifier= %s time=%s\n", __func__, std::to_string(nStakeModifier).c_str(), DateTimeStrFormat("%Y-%m-%d %H:%M:%S", nModifierTime).c_str());

    if (nModifierTime / MODIFIER_INTERVAL >= pindexPrev->GetBlockTime() / MODIFIER_INTERVAL)
        return true;

    // Sort candidate blocks by timestamp
    std::vector<std::pair<int64_t, uint256> > vSortedByTimestamp;
    vSortedByTimestamp.reserve(64 * MODIFIER_INTERVAL  / Params().TargetSpacing());
    int64_t nSelectionIntervalStart = (pindexPrev->GetBlockTime() / MODIFIER_INTERVAL ) * MODIFIER_INTERVAL  - OLD_MODIFIER_INTERVAL;
    const CBlockIndex* pindex = pindexPrev;

    while (pindex && pindex->GetBlockTime() >= nSelectionIntervalStart) {
        vSortedByTimestamp.push_back(std::make_pair(pindex->GetBlockTime(), pindex->GetBlockHash()));
=======
        return error("ComputeNextStakeModifier: unable to get last modifier");

    if (GetBoolArg("-printstakemodifier", false))
        LogPrintf("ComputeNextStakeModifier: prev modifier= %s time=%s\n", boost::lexical_cast<std::string>(nStakeModifier).c_str(), DateTimeStrFormat("%Y-%m-%d %H:%M:%S", nModifierTime).c_str());

    if (nModifierTime / getIntervalVersion(fTestNet) >= pindexPrev->GetBlockTime() / getIntervalVersion(fTestNet))
        return true;

    // Sort candidate blocks by timestamp
    vector<pair<int64_t, uint256> > vSortedByTimestamp;
    vSortedByTimestamp.reserve(64 * getIntervalVersion(fTestNet) / nStakeTargetSpacing);
    int64_t nSelectionInterval = GetStakeModifierSelectionInterval();
    int64_t nSelectionIntervalStart = (pindexPrev->GetBlockTime() / getIntervalVersion(fTestNet)) * getIntervalVersion(fTestNet) - nSelectionInterval;
    const CBlockIndex* pindex = pindexPrev;

    while (pindex && pindex->GetBlockTime() >= nSelectionIntervalStart) {
        vSortedByTimestamp.push_back(make_pair(pindex->GetBlockTime(), pindex->GetBlockHash()));
>>>>>>> Stashed changes
        pindex = pindex->pprev;
    }

    int nHeightFirstCandidate = pindex ? (pindex->nHeight + 1) : 0;
<<<<<<< Updated upstream
    std::reverse(vSortedByTimestamp.begin(), vSortedByTimestamp.end());
    std::sort(vSortedByTimestamp.begin(), vSortedByTimestamp.end());
=======
    reverse(vSortedByTimestamp.begin(), vSortedByTimestamp.end());
    sort(vSortedByTimestamp.begin(), vSortedByTimestamp.end());
>>>>>>> Stashed changes

    // Select 64 blocks from candidate blocks to generate stake modifier
    uint64_t nStakeModifierNew = 0;
    int64_t nSelectionIntervalStop = nSelectionIntervalStart;
<<<<<<< Updated upstream
    std::map<uint256, const CBlockIndex*> mapSelectedBlocks;
    for (int nRound = 0; nRound < std::min(64, (int)vSortedByTimestamp.size()); nRound++) {
=======
    map<uint256, const CBlockIndex*> mapSelectedBlocks;
    for (int nRound = 0; nRound < min(64, (int)vSortedByTimestamp.size()); nRound++) {
>>>>>>> Stashed changes
        // add an interval section to the current selection round
        nSelectionIntervalStop += GetStakeModifierSelectionIntervalSection(nRound);

        // select a block from the candidates of current round
        if (!SelectBlockFromCandidates(vSortedByTimestamp, mapSelectedBlocks, nSelectionIntervalStop, nStakeModifier, &pindex))
<<<<<<< Updated upstream
            return error("%s : unable to select block at round %d", __func__, nRound);
=======
            return error("ComputeNextStakeModifier: unable to select block at round %d", nRound);
>>>>>>> Stashed changes

        // write the entropy bit of the selected block
        nStakeModifierNew |= (((uint64_t)pindex->GetStakeEntropyBit()) << nRound);

        // add the selected block from candidates to selected list
<<<<<<< Updated upstream
        mapSelectedBlocks.insert(std::make_pair(pindex->GetBlockHash(), pindex));
        if (GetBoolArg("-printstakemodifier", false))
            LogPrintf("%s : selected round %d stop=%s height=%d bit=%d\n", __func__,
=======
        mapSelectedBlocks.insert(make_pair(pindex->GetBlockHash(), pindex));
        if (GetBoolArg("-printstakemodifier", false))
            LogPrintf("ComputeNextStakeModifier: selected round %d stop=%s height=%d bit=%d\n",
>>>>>>> Stashed changes
                nRound, DateTimeStrFormat("%Y-%m-%d %H:%M:%S", nSelectionIntervalStop).c_str(), pindex->nHeight, pindex->GetStakeEntropyBit());
    }

    // Print selection map for visualization of the selected blocks
    if (GetBoolArg("-printstakemodifier", false)) {
<<<<<<< Updated upstream
        std::string strSelectionMap = "";
=======
        string strSelectionMap = "";
>>>>>>> Stashed changes
        // '-' indicates proof-of-work blocks not selected
        strSelectionMap.insert(0, pindexPrev->nHeight - nHeightFirstCandidate + 1, '-');
        pindex = pindexPrev;
        while (pindex && pindex->nHeight >= nHeightFirstCandidate) {
            // '=' indicates proof-of-stake blocks not selected
            if (pindex->IsProofOfStake())
                strSelectionMap.replace(pindex->nHeight - nHeightFirstCandidate, 1, "=");
            pindex = pindex->pprev;
        }
<<<<<<< Updated upstream
        for (const std::pair<const uint256, const CBlockIndex*> &item : mapSelectedBlocks) {
=======
        BOOST_FOREACH (const PAIRTYPE(uint256, const CBlockIndex*) & item, mapSelectedBlocks) {
>>>>>>> Stashed changes
            // 'S' indicates selected proof-of-stake blocks
            // 'W' indicates selected proof-of-work blocks
            strSelectionMap.replace(item.second->nHeight - nHeightFirstCandidate, 1, item.second->IsProofOfStake() ? "S" : "W");
        }
<<<<<<< Updated upstream
        LogPrintf("%s : selection height [%d, %d] map %s\n", __func__, nHeightFirstCandidate, pindexPrev->nHeight, strSelectionMap.c_str());
    }
    if (GetBoolArg("-printstakemodifier", false)) {
        LogPrintf("%s : new modifier=%s time=%s\n", __func__, std::to_string(nStakeModifierNew).c_str(), DateTimeStrFormat("%Y-%m-%d %H:%M:%S", pindexPrev->GetBlockTime()).c_str());
=======
        LogPrintf("ComputeNextStakeModifier: selection height [%d, %d] map %s\n", nHeightFirstCandidate, pindexPrev->nHeight, strSelectionMap.c_str());
    }
    if (GetBoolArg("-printstakemodifier", false)) {
        LogPrintf("ComputeNextStakeModifier: new modifier=%s time=%s\n", boost::lexical_cast<std::string>(nStakeModifierNew).c_str(), DateTimeStrFormat("%Y-%m-%d %H:%M:%S", pindexPrev->GetBlockTime()).c_str());
>>>>>>> Stashed changes
    }

    nStakeModifier = nStakeModifierNew;
    fGeneratedStakeModifier = true;
    return true;
}

// The stake modifier used to hash for a stake kernel is chosen as the stake
// modifier about a selection interval later than the coin generating the kernel
<<<<<<< Updated upstream
bool GetKernelStakeModifier(const uint256& hashBlockFrom, uint64_t& nStakeModifier, int& nStakeModifierHeight, int64_t& nStakeModifierTime, bool fPrintProofOfStake)
{
    nStakeModifier = 0;
    // modifier 0 on RegTest
    if (Params().NetworkID() == CBaseChainParams::REGTEST) {
        return true;
    }
    if (!mapBlockIndex.count(hashBlockFrom))
        return error("%s : block not indexed", __func__);
    const CBlockIndex* pindexFrom = mapBlockIndex[hashBlockFrom];
    nStakeModifierHeight = pindexFrom->nHeight;
    nStakeModifierTime = pindexFrom->GetBlockTime();
    // Fixed stake modifier only for regtest
    if (Params().NetworkID() == CBaseChainParams::REGTEST) {
        nStakeModifier = pindexFrom->nStakeModifier;
        return true;
    }
    const CBlockIndex* pindex = pindexFrom;
    CBlockIndex* pindexNext = chainActive[pindex->nHeight + 1];

    // loop to find the stake modifier later by a selection interval
    do {
        if (!pindexNext) {
            // Should never happen
            return error("%s : Null pindexNext, current block %s ", __func__, pindex->phashBlock->GetHex());
        }
        pindex = pindexNext;
=======
bool GetKernelStakeModifier(uint256 hashBlockFrom, uint64_t& nStakeModifier, int& nStakeModifierHeight, int64_t& nStakeModifierTime, bool fPrintProofOfStake)
{
    nStakeModifier = 0;
    if (!mapBlockIndex.count(hashBlockFrom))
        return error("GetKernelStakeModifier() : block not indexed");
    const CBlockIndex* pindexFrom = mapBlockIndex[hashBlockFrom];
    nStakeModifierHeight = pindexFrom->nHeight;
    nStakeModifierTime = pindexFrom->GetBlockTime();
    int64_t nStakeModifierSelectionInterval = GetStakeModifierSelectionInterval();
    const CBlockIndex* pindex = pindexFrom;
    CBlockIndex* pindexNext = chainActive[pindexFrom->nHeight + 1];

    // loop to find the stake modifier later by a selection interval
    while (nStakeModifierTime < pindexFrom->GetBlockTime() + nStakeModifierSelectionInterval) {
        if (!pindexNext) {
            // Should never happen
            return error("Null pindexNext\n");
        }

        pindex = pindexNext;
        pindexNext = chainActive[pindexNext->nHeight + 1];
>>>>>>> Stashed changes
        if (pindex->GeneratedStakeModifier()) {
            nStakeModifierHeight = pindex->nHeight;
            nStakeModifierTime = pindex->GetBlockTime();
        }
<<<<<<< Updated upstream
        pindexNext = chainActive[pindex->nHeight + 1];
    } while (nStakeModifierTime < pindexFrom->GetBlockTime() + OLD_MODIFIER_INTERVAL);

=======
    }
>>>>>>> Stashed changes
    nStakeModifier = pindex->nStakeModifier;
    return true;
}

<<<<<<< Updated upstream
bool CheckStakeKernelHash(const CBlockIndex* pindexPrev, const unsigned int nBits, CStakeInput* stake, const unsigned int nTimeTx, uint256& hashProofOfStake, const bool fVerify)
{
    // Calculate the proof of stake hash
    if (!GetHashProofOfStake(pindexPrev, stake, nTimeTx, fVerify, hashProofOfStake)) {
        return error("%s : Failed to calculate the proof of stake hash", __func__);
    }

    const CAmount& nValueIn = stake->GetValue();
    const CDataStream& ssUniqueID = stake->GetUniqueness();

    // Base target
    uint256 bnTarget;
    bnTarget.SetCompact(nBits);

    // Weighted target
    uint256 bnWeight = uint256(nValueIn) / 100;
    bnTarget *= bnWeight;

    // Check if proof-of-stake hash meets target protocol
    const bool res = (hashProofOfStake < bnTarget);

    if (fVerify || res) {
        LogPrint("staking", "%s : Proof Of Stake:"
                            "\nssUniqueID=%s"
                            "\nnTimeTx=%d"
                            "\nhashProofOfStake=%s"
                            "\nnBits=%d"
                            "\nweight=%d"
                            "\nbnTarget=%s (res: %d)\n\n",
            __func__, HexStr(ssUniqueID), nTimeTx, hashProofOfStake.GetHex(),
            nBits, nValueIn, bnTarget.GetHex(), res);
    }
    return res;
}

bool GetHashProofOfStake(const CBlockIndex* pindexPrev, CStakeInput* stake, const unsigned int nTimeTx, const bool fVerify, uint256& hashProofOfStakeRet) {
    // Grab the stake data
    CBlockIndex* pindexfrom = stake->GetIndexFrom();
    if (!pindexfrom) return error("%s : Failed to find the block index for stake origin", __func__);
    const CDataStream& ssUniqueID = stake->GetUniqueness();
    const unsigned int nTimeBlockFrom = pindexfrom->nTime;
    CDataStream modifier_ss(SER_GETHASH, 0);

    // Hash the modifier
    if (!Params().IsStakeModifierV2(pindexPrev->nHeight + 1)) {
        // Modifier v1
        uint64_t nStakeModifier = 0;
        if (!stake->GetModifier(nStakeModifier))
            return error("%s : Failed to get kernel stake modifier", __func__);
        modifier_ss << nStakeModifier;
    } else {
        // Modifier v2
        modifier_ss << pindexPrev->nStakeModifierV2;
    }

    CDataStream ss(modifier_ss);
    // Calculate hash
    ss << nTimeBlockFrom << ssUniqueID << nTimeTx;
    hashProofOfStakeRet = Hash(ss.begin(), ss.end());

    if (fVerify) {
        LogPrint("staking", "%s :{ nStakeModifier=%s\n"
                            "nStakeModifierHeight=%s\n"
                            "}\n",
            __func__, HexStr(modifier_ss), ((stake->IsZPIV()) ? "Not available" : std::to_string(stake->getStakeModifierHeight())));
    }
    return true;
}

bool Stake(const CBlockIndex* pindexPrev, CStakeInput* stakeInput, unsigned int nBits, int64_t& nTimeTx, uint256& hashProofOfStake)
{
    const int nHeight = pindexPrev->nHeight + 1;

    // get stake input pindex
    CBlockIndex* pindexFrom = stakeInput->GetIndexFrom();
    if (!pindexFrom || pindexFrom->nHeight < 1) return error("%s : no pindexfrom", __func__);

    // Time protocol V2: one-try
    if (Params().IsTimeProtocolV2(nHeight)) {
        // store a time stamp of when we last hashed on this block
        mapHashedBlocks.clear();
        mapHashedBlocks[pindexPrev->nHeight] = GetTime();

        // check required min depth for stake
        const int nHeightBlockFrom = pindexFrom->nHeight;
        if (nHeight < nHeightBlockFrom + Params().COINSTAKE_MIN_DEPTH())
            return error("%s : min depth violation, nHeight=%d, nHeightBlockFrom=%d", __func__, nHeight, nHeightBlockFrom);

        nTimeTx = GetCurrentTimeSlot();
        // double check that we are not on the same slot as prev block
        if (nTimeTx <= pindexPrev->nTime && Params().NetworkID() != CBaseChainParams::REGTEST)
            return false;

        // check stake kernel
        return CheckStakeKernelHash(pindexPrev, nBits, stakeInput, nTimeTx, hashProofOfStake);
    }

    // Time protocol V1: iterate the hashing (can be removed after hard-fork)
    const uint32_t nTimeBlockFrom = pindexFrom->nTime;
    return StakeV1(pindexPrev, stakeInput, nTimeBlockFrom, nBits, nTimeTx, hashProofOfStake);
}

bool StakeV1(const CBlockIndex* pindexPrev, CStakeInput* stakeInput, const uint32_t nTimeBlockFrom, unsigned int nBits, int64_t& nTimeTx, uint256& hashProofOfStake)
{
    bool fSuccess = false;
    // iterate from maxTime down to pindexPrev->nTime (or min time due to maturity, 60 min after blockFrom)
    const unsigned int prevBlockTime = pindexPrev->nTime;
    const unsigned int maxTime = pindexPrev->MaxFutureBlockTime();
    unsigned int minTime = std::max(prevBlockTime, nTimeBlockFrom + 3600);
    if (Params().NetworkID() == CBaseChainParams::REGTEST)
        minTime = prevBlockTime;
    unsigned int nTryTime = maxTime;

    // check required maturity for stake
    if (maxTime <= minTime)
        return error("%s : stake age violation, nTimeBlockFrom = %d, prevBlockTime = %d -- maxTime = %d ", __func__, nTimeBlockFrom, prevBlockTime, maxTime);

    while (nTryTime > minTime) {
        // store a time stamp of when we last hashed on this block
        mapHashedBlocks.clear();
        mapHashedBlocks[pindexPrev->nHeight] = GetTime();

        //new block came in, move on
        if (chainActive.Height() != pindexPrev->nHeight) break;

        --nTryTime;
        // if stake hash does not meet the target then continue to next iteration
        if (!CheckStakeKernelHash(pindexPrev, nBits, stakeInput, nTryTime, hashProofOfStake))
             continue;

        // if we made it this far, then we have successfully found a valid kernel hash
        fSuccess = true;
        break;
    }

    nTimeTx = nTryTime;

    mapHashedBlocks.clear();
    mapHashedBlocks[pindexPrev->nHeight] = GetTime(); //store a time stamp of when we last hashed on this block

    return fSuccess;
}

bool ContextualCheckZerocoinStake(int nPreviousBlockHeight, CStakeInput* stake)
{
    if (nPreviousBlockHeight < Params().Zerocoin_Block_V2_Start())
        return error("%s : zPIV stake block is less than allowed start height", __func__);

    if (CZPivStake* zPIV = dynamic_cast<CZPivStake*>(stake)) {
        CBlockIndex* pindexFrom = zPIV->GetIndexFrom();
        if (!pindexFrom)
            return error("%s : failed to get index associated with zPIV stake checksum", __func__);

        int depth = (nPreviousBlockHeight + 1) - pindexFrom->nHeight;
        if (depth < Params().Zerocoin_RequiredStakeDepth())
            return error("%s : zPIV stake does not have required confirmation depth. Current height %d,  stakeInput height %d.", __func__, nPreviousBlockHeight, pindexFrom->nHeight);

        //The checksum needs to be the exact checksum from 200 blocks ago or latest checksum
        const int checkpointHeight = std::min(Params().Zerocoin_Block_Last_Checkpoint(), (nPreviousBlockHeight - Params().Zerocoin_RequiredStakeDepth()));
        uint256 nCheckpoint200 = chainActive[checkpointHeight]->nAccumulatorCheckpoint;
        uint32_t nChecksum200 = ParseChecksum(nCheckpoint200, libzerocoin::AmountToZerocoinDenomination(zPIV->GetValue()));
        if (nChecksum200 != zPIV->GetChecksum())
            return error("%s : accumulator checksum is different than the block 200 blocks previous. stake=%d block200=%d", __func__, zPIV->GetChecksum(), nChecksum200);
    } else {
        return error("%s : dynamic_cast of stake ptr failed", __func__);
    }

    return true;
}

bool initStakeInput(const CBlock& block, std::unique_ptr<CStakeInput>& stake, int nPreviousBlockHeight) {
    const CTransaction tx = block.vtx[1];
    if (!tx.IsCoinStake())
        return error("%s : called on non-coinstake %s", __func__, tx.GetHash().ToString().c_str());
=======
//test hash vs target
bool stakeTargetHit(uint256 hashProofOfStake, int64_t nValueIn, uint256 bnTargetPerCoinDay)
{
    //get the stake weight - weight is equal to coin amount
    uint256 bnCoinDayWeight = uint256(nValueIn) / 100;

    // Now check if proof-of-stake hash meets target protocol
    return hashProofOfStake < (bnCoinDayWeight * bnTargetPerCoinDay);
}

bool CheckStake(const CDataStream& ssUniqueID, CAmount nValueIn, const uint64_t nStakeModifier, const uint256& bnTarget,
                unsigned int nTimeBlockFrom, unsigned int& nTimeTx, uint256& hashProofOfStake)
{
    CDataStream ss(SER_GETHASH, 0);
    ss << nStakeModifier << nTimeBlockFrom << ssUniqueID << nTimeTx;
    hashProofOfStake = Hash(ss.begin(), ss.end());
    //LogPrintf("%s: modifier:%d nTimeBlockFrom:%d nTimeTx:%d hash:%s\n", __func__, nStakeModifier, nTimeBlockFrom, nTimeTx, hashProofOfStake.GetHex());

    return stakeTargetHit(hashProofOfStake, nValueIn, bnTarget);
}

bool Stake(CStakeInput* stakeInput, unsigned int nBits, unsigned int nTimeBlockFrom, unsigned int& nTimeTx, uint256& hashProofOfStake)
{
    if (nTimeTx < nTimeBlockFrom)
        return error("CheckStakeKernelHash() : nTime violation");

    if (nTimeBlockFrom + nStakeMinAge > nTimeTx) // Min age requirement
        return error("CheckStakeKernelHash() : min age violation - nTimeBlockFrom=%d nStakeMinAge=%d nTimeTx=%d",
                     nTimeBlockFrom, nStakeMinAge, nTimeTx);

    //grab difficulty
    uint256 bnTargetPerCoinDay;
    bnTargetPerCoinDay.SetCompact(nBits);

    //grab stake modifier
    uint64_t nStakeModifier = 0;
    if (!stakeInput->GetModifier(nStakeModifier))
        return error("failed to get kernel stake modifier");

    bool fSuccess = false;
    unsigned int nTryTime = 0;
    int nHeightStart = chainActive.Height();
    int nHashDrift = 60;
    CDataStream ssUniqueID = stakeInput->GetUniqueness();
    CAmount nValueIn = stakeInput->GetValue();
    for (int i = 0; i < nHashDrift; i++) //iterate the hashing
    {
        //new block came in, move on
        if (chainActive.Height() != nHeightStart)
            break;

        //hash this iteration
        nTryTime = nTimeTx + nHashDrift - i;

        // if stake hash does not meet the target then continue to next iteration
        if (!CheckStake(ssUniqueID, nValueIn, nStakeModifier, bnTargetPerCoinDay, nTimeBlockFrom, nTryTime, hashProofOfStake))
            continue;

        fSuccess = true; // if we make it this far then we have successfully created a stake hash
        //LogPrintf("%s: hashproof=%s\n", __func__, hashProofOfStake.GetHex());
        nTimeTx = nTryTime;
        break;
    }

    mapHashedBlocks.clear();
    mapHashedBlocks[chainActive.Tip()->nHeight] = GetTime(); //store a time stamp of when we last hashed on this block
    return fSuccess;
}

// Check kernel hash target and coinstake signature
bool CheckProofOfStake(const CBlock block, uint256& hashProofOfStake, std::unique_ptr<CStakeInput>& stake)
{
    const CTransaction tx = block.vtx[1];
    if (!tx.IsCoinStake())
        return error("CheckProofOfStake() : called on non-coinstake %s", tx.GetHash().ToString().c_str());
>>>>>>> Stashed changes

    // Kernel (input 0) must match the stake hash target per coin age (nBits)
    const CTxIn& txin = tx.vin[0];

    //Construct the stakeinput object
<<<<<<< Updated upstream
    if (txin.IsZerocoinSpend()) {
        libzerocoin::CoinSpend spend = TxInToZerocoinSpend(txin);
        if (spend.getSpendType() != libzerocoin::SpendType::STAKE)
            return error("%s : spend is using the wrong SpendType (%d)", __func__, (int)spend.getSpendType());

        stake = std::unique_ptr<CStakeInput>(new CZPivStake(spend));

        if (!ContextualCheckZerocoinStake(nPreviousBlockHeight, stake.get()))
            return error("%s : staked zPIV fails context checks", __func__);
=======
    if (tx.IsZerocoinSpend()) {
        libzerocoin::CoinSpend spend = TxInToZerocoinSpend(txin);
        if (spend.getSpendType() != libzerocoin::SpendType::STAKE)
            return error("%s: spend is using the wrong SpendType (%d)", __func__, (int)spend.getSpendType());

        stake = std::unique_ptr<CStakeInput>(new CzPSCStake(spend));
>>>>>>> Stashed changes
    } else {
        // First try finding the previous transaction in database
        uint256 hashBlock;
        CTransaction txPrev;
        if (!GetTransaction(txin.prevout.hash, txPrev, hashBlock, true))
<<<<<<< Updated upstream
            return error("%s : INFO: read txPrev failed, tx id prev: %s, block id %s",
                         __func__, txin.prevout.hash.GetHex(), block.GetHash().GetHex());

        //verify signature and script
        ScriptError serror;
        if (!VerifyScript(txin.scriptSig, txPrev.vout[txin.prevout.n].scriptPubKey, STANDARD_SCRIPT_VERIFY_FLAGS, TransactionSignatureChecker(&tx, 0), &serror)) {
            std::string strErr = "";
            if (serror && ScriptErrorString(serror))
                strErr = strprintf("with the following error: %s", ScriptErrorString(serror));
            return error("%s : VerifyScript failed on coinstake %s %s", __func__, tx.GetHash().ToString(), strErr);
        }

        CPivStake* pivInput = new CPivStake();
        pivInput->SetInput(txPrev, txin.prevout.n);
        stake = std::unique_ptr<CStakeInput>(pivInput);
    }
    return true;
}

// Check kernel hash target and coinstake signature
bool CheckProofOfStake(const CBlock& block, uint256& hashProofOfStake, std::unique_ptr<CStakeInput>& stake, int nPreviousBlockHeight)
{
    // Initialize the stake object
    if(!initStakeInput(block, stake, nPreviousBlockHeight))
        return error("%s : stake input object initialization failed", __func__);

    const CTransaction tx = block.vtx[1];
    // Kernel (input 0) must match the stake hash target per coin age (nBits)
    const CTxIn& txin = tx.vin[0];
    CBlockIndex* pindexPrev = mapBlockIndex[block.hashPrevBlock];
    CBlockIndex* pindexfrom = stake->GetIndexFrom();
    if (!pindexfrom)
        return error("%s : Failed to find the block index for stake origin", __func__);

    unsigned int nBlockFromTime = pindexfrom->nTime;
    unsigned int nTxTime = block.nTime;
    const int nBlockFromHeight = pindexfrom->nHeight;

    if (!txin.IsZerocoinSpend() && nPreviousBlockHeight >= Params().Zerocoin_Block_Public_Spend_Enabled() - 1) {
        //check for maturity (min age/depth) requirements
        if (!Params().HasStakeMinAgeOrDepth(nPreviousBlockHeight+1, nTxTime, nBlockFromHeight, nBlockFromTime))
            return error("%s : min age violation - height=%d - nTimeTx=%d, nTimeBlockFrom=%d, nHeightBlockFrom=%d",
                             __func__, nPreviousBlockHeight, nTxTime, nBlockFromTime, nBlockFromHeight);
    }

    if (!CheckStakeKernelHash(pindexPrev, block.nBits, stake.get(), nTxTime, hashProofOfStake, true))
        return error("%s : INFO: check kernel failed on coinstake %s, hashProof=%s", __func__,
                     tx.GetHash().GetHex(), hashProofOfStake.GetHex());
=======
            return error("CheckProofOfStake() : INFO: read txPrev failed");

        //verify signature and script
        if (!VerifyScript(txin.scriptSig, txPrev.vout[txin.prevout.n].scriptPubKey, STANDARD_SCRIPT_VERIFY_FLAGS, TransactionSignatureChecker(&tx, 0)))
            return error("CheckProofOfStake() : VerifySignature failed on coinstake %s", tx.GetHash().ToString().c_str());

        CPrimeStoneStake* pivInput = new CPrimeStoneStake();
        pivInput->SetInput(txPrev, txin.prevout.n);
        stake = std::unique_ptr<CStakeInput>(pivInput);
    }

    CBlockIndex* pindex = stake->GetIndexFrom();
    if (!pindex)
        return error("%s: Failed to find the block index", __func__);

    // Read block header
    CBlock blockprev;
    if (!ReadBlockFromDisk(blockprev, pindex->GetBlockPos()))
        return error("CheckProofOfStake(): INFO: failed to find block");

    uint256 bnTargetPerCoinDay;
    bnTargetPerCoinDay.SetCompact(block.nBits);

    uint64_t nStakeModifier = 0;
    if (!stake->GetModifier(nStakeModifier))
        return error("%s failed to get modifier for stake input\n", __func__);

    unsigned int nBlockFromTime = blockprev.nTime;
    unsigned int nTxTime = block.nTime;
    if (!CheckStake(stake->GetUniqueness(), stake->GetValue(), nStakeModifier, bnTargetPerCoinDay, nBlockFromTime,
                    nTxTime, hashProofOfStake)) {
        return error("CheckProofOfStake() : INFO: check kernel failed on coinstake %s, hashProof=%s \n",
                     tx.GetHash().GetHex(), hashProofOfStake.GetHex());
    }
>>>>>>> Stashed changes

    return true;
}

<<<<<<< Updated upstream
=======
// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(int64_t nTimeBlock, int64_t nTimeTx)
{
    // v0.3 protocol
    return (nTimeBlock == nTimeTx);
}

>>>>>>> Stashed changes
// Get stake modifier checksum
unsigned int GetStakeModifierChecksum(const CBlockIndex* pindex)
{
    assert(pindex->pprev || pindex->GetBlockHash() == Params().HashGenesisBlock());
    // Hash previous checksum with flags, hashProofOfStake and nStakeModifier
    CDataStream ss(SER_GETHASH, 0);
    if (pindex->pprev)
        ss << pindex->pprev->nStakeModifierChecksum;
    ss << pindex->nFlags << pindex->hashProofOfStake << pindex->nStakeModifier;
    uint256 hashChecksum = Hash(ss.begin(), ss.end());
    hashChecksum >>= (256 - 32);
    return hashChecksum.Get64();
}

// Check stake modifier hard checkpoints
bool CheckStakeModifierCheckpoints(int nHeight, unsigned int nStakeModifierChecksum)
{
<<<<<<< Updated upstream
    if (Params().NetworkID() != CBaseChainParams::MAIN) return true; // Testnet has no checkpoints
=======
    if (fTestNet) return true; // Testnet has no checkpoints
>>>>>>> Stashed changes
    if (mapStakeModifierCheckpoints.count(nHeight)) {
        return nStakeModifierChecksum == mapStakeModifierCheckpoints[nHeight];
    }
    return true;
}
<<<<<<< Updated upstream

// Timestamp for time protocol V2: slot duration 15 seconds
int64_t GetTimeSlot(const int64_t nTime)
{
    const int slotLen = Params().TimeSlotLength();
    return (nTime / slotLen) * slotLen;
}

int64_t GetCurrentTimeSlot()
{
    return GetTimeSlot(GetAdjustedTime());
}



=======
>>>>>>> Stashed changes
