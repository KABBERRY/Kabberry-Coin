// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_PARAMS_H

#include "amount.h"
#include "uint256.h"
#include <map>
#include <string>

namespace Consensus {

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    bool fPowAllowMinDifficultyBlocks;
    uint256 powLimit;
    uint256 posLimitV1;
    uint256 posLimitV2;
    int nCoinbaseMaturity;
    CAmount nMaxMoneyOut;
    int nStakeMinAge;
    int nStakeMinDepth;
    // Height based activations
    int height_start_BIP65;
    int height_start_StakeModifierV2;
    int64_t nTargetSpacing;
    int64_t nTargetTimespan;

    // TODO: Implement the following methods
    int64_t DifficultyAdjustmentInterval() const { return nTargetTimespan / nTargetSpacing; }
    uint256 ProofOfStakeLimit(const bool fV2) const { return fV2 ? posLimitV2 : posLimitV1; }
    bool MoneyRange(const CAmount& nValue) const { return (nValue >= 0 && nValue <= nMaxMoneyOut); }
    bool IsStakeModifierV2(const int nHeight) const { return nHeight >= height_start_StakeModifierV2; }

	    bool HasStakeMinAgeOrDepth(const int contextHeight, const uint32_t contextTime,
            const int utxoFromBlockHeight, const uint32_t utxoFromBlockTime) const
    {
        // before stake modifier V2, we require the utxo to be nStakeMinAge old
        if (!IsStakeModifierV2(contextHeight))
            return (utxoFromBlockTime + nStakeMinAge <= contextTime);
        // with stake modifier V2+, we require the utxo to be nStakeMinDepth deep in the chain
        return (contextHeight - utxoFromBlockHeight >= nStakeMinDepth);
    }
};
} // namespace Consensus

#endif // BITCOIN_CONSENSUS_PARAMS_H