// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
<<<<<<< Updated upstream
// Copyright (c) 2015-2019 The PIVX developers
=======
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "transactionrecord.h"

#include "base58.h"
#include "obfuscation.h"
#include "swifttx.h"
#include "timedata.h"
<<<<<<< Updated upstream
#include "wallet/wallet.h"
#include "zpivchain.h"
#include "main.h"

#include <iostream>
#include <stdint.h>

=======
#include "wallet.h"
#include "zPSCchain.h"

#include <stdint.h>

/* Return positive answer if transaction should be shown in list.
 */
bool TransactionRecord::showTransaction(const CWalletTx& wtx)
{
    if (wtx.IsCoinBase()) {
        // Ensures we show generated coins / mined transactions at depth 1
        if (!wtx.IsInMainChain()) {
            return false;
        }
    }
    return true;
}

>>>>>>> Stashed changes
/*
 * Decompose CWallet transaction to model transaction records.
 */
QList<TransactionRecord> TransactionRecord::decomposeTransaction(const CWallet* wallet, const CWalletTx& wtx)
{
    QList<TransactionRecord> parts;
    int64_t nTime = wtx.GetComputedTxTime();
    CAmount nCredit = wtx.GetCredit(ISMINE_ALL);
    CAmount nDebit = wtx.GetDebit(ISMINE_ALL);
    CAmount nNet = nCredit - nDebit;
    uint256 hash = wtx.GetHash();
    std::map<std::string, std::string> mapValue = wtx.mapValue;
    bool fZSpendFromMe = false;

<<<<<<< Updated upstream
    if (wtx.HasZerocoinSpendInputs()) {
        libzerocoin::CoinSpend zcspend = wtx.HasZerocoinPublicSpendInputs() ? ZPIVModule::parseCoinSpend(wtx.vin[0]) : TxInToZerocoinSpend(wtx.vin[0]);
=======
    if (wtx.IsZerocoinSpend()) {
        // a zerocoin spend that was created by this wallet
        libzerocoin::CoinSpend zcspend = TxInToZerocoinSpend(wtx.vin[0]);
>>>>>>> Stashed changes
        fZSpendFromMe = wallet->IsMyZerocoinSpend(zcspend.getCoinSerialNumber());
    }

    if (wtx.IsCoinStake()) {
<<<<<<< Updated upstream
        TransactionRecord sub(hash, nTime, wtx.GetTotalSize());

        CTxDestination address;
        if (!wtx.HasZerocoinSpendInputs() && !ExtractDestination(wtx.vout[1].scriptPubKey, address))
            return parts;

        if (wtx.HasZerocoinSpendInputs() && (fZSpendFromMe || wallet->zpivTracker->HasMintTx(hash))) {
            //zPIV stake reward
            sub.involvesWatchAddress = false;
            sub.type = TransactionRecord::StakeZPIV;
=======
        TransactionRecord sub(hash, nTime);
        CTxDestination address;
        if (!wtx.IsZerocoinSpend() && !ExtractDestination(wtx.vout[1].scriptPubKey, address))
            return parts;

        if (wtx.IsZerocoinSpend() && (fZSpendFromMe || wallet->zPSCTracker->HasMintTx(hash))) {
            //zPSC stake reward
            sub.involvesWatchAddress = false;
            sub.type = TransactionRecord::StakezPSC;
>>>>>>> Stashed changes
            sub.address = mapValue["zerocoinmint"];
            sub.credit = 0;
            for (const CTxOut& out : wtx.vout) {
                if (out.IsZerocoinMint())
                    sub.credit += out.nValue;
            }
            sub.debit -= wtx.vin[0].nSequence * COIN;
        } else if (isminetype mine = wallet->IsMine(wtx.vout[1])) {
<<<<<<< Updated upstream

            // Check for cold stakes.
            if (wtx.HasP2CSOutputs()) {
                sub.credit = nCredit;
                sub.debit = -nDebit;
                loadHotOrColdStakeOrContract(wallet, wtx, sub);
                parts.append(sub);
                return parts;
            } else {
                // PIV stake reward
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                sub.type = TransactionRecord::StakeMint;
                sub.address = CBitcoinAddress(address).ToString();
                sub.credit = nNet;
            }
=======
            // PrimeStone stake reward
            sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
            sub.type = TransactionRecord::StakeMint;
            sub.address = CBitcoinAddress(address).ToString();
            sub.credit = nNet;
>>>>>>> Stashed changes
        } else {
            //Masternode reward
            CTxDestination destMN;
            int nIndexMN = wtx.vout.size() - 1;
            if (ExtractDestination(wtx.vout[nIndexMN].scriptPubKey, destMN) && IsMine(*wallet, destMN)) {
                isminetype mine = wallet->IsMine(wtx.vout[nIndexMN]);
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                sub.type = TransactionRecord::MNReward;
                sub.address = CBitcoinAddress(destMN).ToString();
                sub.credit = wtx.vout[nIndexMN].nValue;
            }
        }

        parts.append(sub);
<<<<<<< Updated upstream
    } else if (wtx.HasZerocoinSpendInputs()) {
=======
    } else if (wtx.IsZerocoinSpend()) {
>>>>>>> Stashed changes
        //zerocoin spend outputs
        bool fFeeAssigned = false;
        for (const CTxOut& txout : wtx.vout) {
            // change that was reminted as zerocoins
            if (txout.IsZerocoinMint()) {
                // do not display record if this isn't from our wallet
                if (!fZSpendFromMe)
                    continue;

                isminetype mine = wallet->IsMine(txout);
<<<<<<< Updated upstream
                TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                sub.type = TransactionRecord::ZerocoinSpend_Change_zPiv;
=======
                TransactionRecord sub(hash, nTime);
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                sub.type = TransactionRecord::ZerocoinSpend_Change_zPSC;
>>>>>>> Stashed changes
                sub.address = mapValue["zerocoinmint"];
                if (!fFeeAssigned) {
                    sub.debit -= (wtx.GetZerocoinSpent() - wtx.GetValueOut());
                    fFeeAssigned = true;
                }
                sub.idx = parts.size();
                parts.append(sub);
                continue;
            }

<<<<<<< Updated upstream
            std::string strAddress = "";
=======
            string strAddress = "";
>>>>>>> Stashed changes
            CTxDestination address;
            if (ExtractDestination(txout.scriptPubKey, address))
                strAddress = CBitcoinAddress(address).ToString();

            // a zerocoinspend that was sent to an address held by this wallet
            isminetype mine = wallet->IsMine(txout);
            if (mine) {
<<<<<<< Updated upstream
                TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
=======
                TransactionRecord sub(hash, nTime);
>>>>>>> Stashed changes
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                if (fZSpendFromMe) {
                    sub.type = TransactionRecord::ZerocoinSpend_FromMe;
                } else {
                    sub.type = TransactionRecord::RecvFromZerocoinSpend;
                    sub.credit = txout.nValue;
                }
                sub.address = mapValue["recvzerocoinspend"];
                if (strAddress != "")
                    sub.address = strAddress;
                sub.idx = parts.size();
                parts.append(sub);
                continue;
            }

            // spend is not from us, so do not display the spend side of the record
            if (!fZSpendFromMe)
                continue;

            // zerocoin spend that was sent to someone else
<<<<<<< Updated upstream
            TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
=======
            TransactionRecord sub(hash, nTime);
>>>>>>> Stashed changes
            sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
            sub.debit = -txout.nValue;
            sub.type = TransactionRecord::ZerocoinSpend;
            sub.address = mapValue["zerocoinspend"];
            if (strAddress != "")
                sub.address = strAddress;
            sub.idx = parts.size();
            parts.append(sub);
        }
<<<<<<< Updated upstream
    } else if (wtx.HasP2CSOutputs()) {
        // Delegate tx.
        TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
        sub.credit = nCredit;
        sub.debit = -nDebit;
        loadHotOrColdStakeOrContract(wallet, wtx, sub, true);
        parts.append(sub);
        return parts;
    } else if (wtx.HasP2CSInputs()) {
        // Delegation unlocked
        TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
        loadUnlockColdStake(wallet, wtx, sub);
        parts.append(sub);
        return parts;
=======
>>>>>>> Stashed changes
    } else if (nNet > 0 || wtx.IsCoinBase()) {
        //
        // Credit
        //
<<<<<<< Updated upstream
        for (const CTxOut& txout : wtx.vout) {
            isminetype mine = wallet->IsMine(txout);
            if (mine) {
                TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
=======
        BOOST_FOREACH (const CTxOut& txout, wtx.vout) {
            isminetype mine = wallet->IsMine(txout);
            if (mine) {
                TransactionRecord sub(hash, nTime);
>>>>>>> Stashed changes
                CTxDestination address;
                sub.idx = parts.size(); // sequence number
                sub.credit = txout.nValue;
                sub.involvesWatchAddress = mine & ISMINE_WATCH_ONLY;
                if (ExtractDestination(txout.scriptPubKey, address) && IsMine(*wallet, address)) {
<<<<<<< Updated upstream
                    // Received by PIVX Address
=======
                    // Received by PrimeStone Address
>>>>>>> Stashed changes
                    sub.type = TransactionRecord::RecvWithAddress;
                    sub.address = CBitcoinAddress(address).ToString();
                } else {
                    // Received by IP connection (deprecated features), or a multisignature or other non-simple transaction
                    sub.type = TransactionRecord::RecvFromOther;
                    sub.address = mapValue["from"];
                }
                if (wtx.IsCoinBase()) {
                    // Generated
                    sub.type = TransactionRecord::Generated;
                }

                parts.append(sub);
            }
        }
    } else {
        bool fAllFromMeDenom = true;
        int nFromMe = 0;
        bool involvesWatchAddress = false;
        isminetype fAllFromMe = ISMINE_SPENDABLE;
<<<<<<< Updated upstream
        for (const CTxIn& txin : wtx.vin) {
=======
        BOOST_FOREACH (const CTxIn& txin, wtx.vin) {
>>>>>>> Stashed changes
            if (wallet->IsMine(txin)) {
                fAllFromMeDenom = fAllFromMeDenom && wallet->IsDenominated(txin);
                nFromMe++;
            }
            isminetype mine = wallet->IsMine(txin);
            if (mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if (fAllFromMe > mine) fAllFromMe = mine;
        }

        isminetype fAllToMe = ISMINE_SPENDABLE;
        bool fAllToMeDenom = true;
        int nToMe = 0;
<<<<<<< Updated upstream
        for (const CTxOut& txout : wtx.vout) {
=======
        BOOST_FOREACH (const CTxOut& txout, wtx.vout) {
>>>>>>> Stashed changes
            if (wallet->IsMine(txout)) {
                fAllToMeDenom = fAllToMeDenom && wallet->IsDenominatedAmount(txout.nValue);
                nToMe++;
            }
            isminetype mine = wallet->IsMine(txout);
            if (mine & ISMINE_WATCH_ONLY) involvesWatchAddress = true;
            if (fAllToMe > mine) fAllToMe = mine;
        }

        if (fAllFromMeDenom && fAllToMeDenom && nFromMe * nToMe) {
<<<<<<< Updated upstream
            parts.append(TransactionRecord(hash, nTime, wtx.GetTotalSize(), TransactionRecord::ObfuscationDenominate, "", -nDebit, nCredit));
=======
            parts.append(TransactionRecord(hash, nTime, TransactionRecord::ObfuscationDenominate, "", -nDebit, nCredit));
>>>>>>> Stashed changes
            parts.last().involvesWatchAddress = false; // maybe pass to TransactionRecord as constructor argument
        } else if (fAllFromMe && fAllToMe) {
            // Payment to self
            // TODO: this section still not accurate but covers most cases,
            // might need some additional work however

<<<<<<< Updated upstream
            TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
=======
            TransactionRecord sub(hash, nTime);
>>>>>>> Stashed changes
            // Payment to self by default
            sub.type = TransactionRecord::SendToSelf;
            sub.address = "";

            if (mapValue["DS"] == "1") {
                sub.type = TransactionRecord::Obfuscated;
                CTxDestination address;
                if (ExtractDestination(wtx.vout[0].scriptPubKey, address)) {
<<<<<<< Updated upstream
                    // Sent to PIVX Address
=======
                    // Sent to PrimeStone Address
>>>>>>> Stashed changes
                    sub.address = CBitcoinAddress(address).ToString();
                } else {
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.address = mapValue["to"];
                }
            } else {
                for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++) {
                    const CTxOut& txout = wtx.vout[nOut];
                    sub.idx = parts.size();

                    if (wallet->IsCollateralAmount(txout.nValue)) sub.type = TransactionRecord::ObfuscationMakeCollaterals;
                    if (wallet->IsDenominatedAmount(txout.nValue)) sub.type = TransactionRecord::ObfuscationCreateDenominations;
                    if (nDebit - wtx.GetValueOut() == OBFUSCATION_COLLATERAL) sub.type = TransactionRecord::ObfuscationCollateralPayment;
                }
<<<<<<< Updated upstream

                // Label for payment to self
                CTxDestination address;
                if (ExtractDestination(wtx.vout[0].scriptPubKey, address)) {
                    sub.address = CBitcoinAddress(address).ToString();
                }
=======
>>>>>>> Stashed changes
            }

            CAmount nChange = wtx.GetChange();

            sub.debit = -(nDebit - nChange);
            sub.credit = nCredit - nChange;
            parts.append(sub);
            parts.last().involvesWatchAddress = involvesWatchAddress; // maybe pass to TransactionRecord as constructor argument
<<<<<<< Updated upstream
        } else if (fAllFromMe || wtx.HasZerocoinMintOutputs()) {
=======
        } else if (fAllFromMe || wtx.IsZerocoinMint()) {
>>>>>>> Stashed changes
            //
            // Debit
            //
            CAmount nTxFee = nDebit - wtx.GetValueOut();

            for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++) {
                const CTxOut& txout = wtx.vout[nOut];
<<<<<<< Updated upstream
                TransactionRecord sub(hash, nTime, wtx.GetTotalSize());
=======
                TransactionRecord sub(hash, nTime);
>>>>>>> Stashed changes
                sub.idx = parts.size();
                sub.involvesWatchAddress = involvesWatchAddress;

                if (wallet->IsMine(txout)) {
                    // Ignore parts sent to self, as this is usually the change
                    // from a transaction sent back to our own address.
                    continue;
                }

                CTxDestination address;
                if (ExtractDestination(txout.scriptPubKey, address)) {
                    //This is most likely only going to happen when resyncing deterministic wallet without the knowledge of the
                    //private keys that the change was sent to. Do not display a "sent to" here.
<<<<<<< Updated upstream
                    if (wtx.HasZerocoinMintOutputs())
                        continue;
                    // Sent to PIVX Address
=======
                    if (wtx.IsZerocoinMint())
                        continue;
                    // Sent to PrimeStone Address
>>>>>>> Stashed changes
                    sub.type = TransactionRecord::SendToAddress;
                    sub.address = CBitcoinAddress(address).ToString();
                } else if (txout.IsZerocoinMint()){
                    sub.type = TransactionRecord::ZerocoinMint;
                    sub.address = mapValue["zerocoinmint"];
                    sub.credit += txout.nValue;
                } else {
                    // Sent to IP, or other non-address transaction like OP_EVAL
                    sub.type = TransactionRecord::SendToOther;
                    sub.address = mapValue["to"];
                }

                if (mapValue["DS"] == "1") {
                    sub.type = TransactionRecord::Obfuscated;
                }

                CAmount nValue = txout.nValue;
                /* Add fee to first output */
                if (nTxFee > 0) {
                    nValue += nTxFee;
                    nTxFee = 0;
                }
                sub.debit = -nValue;

                parts.append(sub);
            }
        } else {
            //
            // Mixed debit transaction, can't break down payees
            //
<<<<<<< Updated upstream
            parts.append(TransactionRecord(hash, nTime, wtx.GetTotalSize(), TransactionRecord::Other, "", nNet, 0));
=======
            parts.append(TransactionRecord(hash, nTime, TransactionRecord::Other, "", nNet, 0));
>>>>>>> Stashed changes
            parts.last().involvesWatchAddress = involvesWatchAddress;
        }
    }

    return parts;
}

<<<<<<< Updated upstream
void TransactionRecord::loadUnlockColdStake(const CWallet* wallet, const CWalletTx& wtx, TransactionRecord& record)
{
    record.involvesWatchAddress = false;

    // Get the p2cs
    const CScript* p2csScript = nullptr;
    bool isSpendable = false;

    for (const auto &input : wtx.vin) {
        const CWalletTx* tx = wallet->GetWalletTx(input.prevout.hash);
        if (tx && tx->vout[input.prevout.n].scriptPubKey.IsPayToColdStaking()) {
            p2csScript = &tx->vout[input.prevout.n].scriptPubKey;
            isSpendable = wallet->IsMine(input) & ISMINE_SPENDABLE_ALL;
            break;
        }
    }

    if (isSpendable) {
        // owner unlocked the cold stake
        record.type = TransactionRecord::P2CSUnlockOwner;
        record.debit = -(wtx.GetStakeDelegationDebit());
        record.credit = wtx.GetCredit(ISMINE_ALL);
    } else {
        // hot node watching the unlock
        record.type = TransactionRecord::P2CSUnlockStaker;
        record.debit = -(wtx.GetColdStakingDebit());
        record.credit = -(wtx.GetColdStakingCredit());
    }

    // Extract and set the owner address
    ExtractAddress(*p2csScript, false, record.address);
}

void TransactionRecord::loadHotOrColdStakeOrContract(
        const CWallet* wallet,
        const CWalletTx& wtx,
        TransactionRecord& record,
        bool isContract)
{
    record.involvesWatchAddress = false;

    // Get the p2cs
    CTxOut p2csUtxo;
    for (unsigned int nOut = 0; nOut < wtx.vout.size(); nOut++) {
        const CTxOut &txout = wtx.vout[nOut];
        if (txout.scriptPubKey.IsPayToColdStaking()) {
            p2csUtxo = txout;
            break;
        }
    }
    bool isSpendable = wallet->IsMine(p2csUtxo) & ISMINE_SPENDABLE_DELEGATED;

    if (isContract) {
        if (isSpendable) {
            // Wallet delegating balance
            record.type = TransactionRecord::P2CSDelegationSent;
        } else {
            // Wallet receiving a delegation
            record.type = TransactionRecord::P2CSDelegation;
        }
    } else {
        // Stake
        if (isSpendable) {
            // Offline wallet receiving an stake due a delegation
            record.type = TransactionRecord::StakeDelegated;

        } else {
            // Online wallet receiving an stake due a received utxo delegation that won a block.
            record.type = TransactionRecord::StakeHot;
        }
    }

    // Extract and set the owner address
    ExtractAddress(p2csUtxo.scriptPubKey, false, record.address);
}

bool TransactionRecord::ExtractAddress(const CScript& scriptPubKey, bool fColdStake, std::string& addressStr) {
    CTxDestination address;
    if (!ExtractDestination(scriptPubKey, address, fColdStake)) {
        // this shouldn't happen..
        addressStr = "No available address";
        return false;
    } else {
        addressStr = CBitcoinAddress(
                address,
                (fColdStake ? CChainParams::STAKING_ADDRESS : CChainParams::PUBKEY_ADDRESS)
        ).ToString();
        return true;
    }
}

bool IsZPIVType(TransactionRecord::Type type)
{
    switch (type) {
        case TransactionRecord::StakeZPIV:
        case TransactionRecord::ZerocoinMint:
        case TransactionRecord::ZerocoinSpend:
        case TransactionRecord::RecvFromZerocoinSpend:
        case TransactionRecord::ZerocoinSpend_Change_zPiv:
=======
bool IszPSCType(TransactionRecord::Type type)
{
    switch (type) {
        case TransactionRecord::StakezPSC:
        case TransactionRecord::ZerocoinMint:
        case TransactionRecord::ZerocoinSpend:
        case TransactionRecord::RecvFromZerocoinSpend:
        case TransactionRecord::ZerocoinSpend_Change_zPSC:
>>>>>>> Stashed changes
        case TransactionRecord::ZerocoinSpend_FromMe:
            return true;
        default:
            return false;
    }
}

void TransactionRecord::updateStatus(const CWalletTx& wtx)
{
    AssertLockHeld(cs_main);
    // Determine transaction status

    // Find the block the tx is in
    CBlockIndex* pindex = NULL;
    BlockMap::iterator mi = mapBlockIndex.find(wtx.hashBlock);
    if (mi != mapBlockIndex.end())
        pindex = (*mi).second;

    // Sort order, unrecorded transactions sort to the top
    status.sortKey = strprintf("%010d-%01d-%010u-%03d",
        (pindex ? pindex->nHeight : std::numeric_limits<int>::max()),
        (wtx.IsCoinBase() ? 1 : 0),
        wtx.nTimeReceived,
        idx);
    //status.countsForBalance = wtx.IsTrusted() && !(wtx.GetBlocksToMaturity() > 0);
<<<<<<< Updated upstream
    bool fConflicted;
    status.depth = wtx.GetDepthAndMempool(fConflicted);
    const bool isOffline = (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0);
=======
    status.depth = wtx.GetDepthInMainChain();
>>>>>>> Stashed changes

    //Determine the depth of the block
    int nBlocksToMaturity = wtx.GetBlocksToMaturity();

    status.countsForBalance = wtx.IsTrusted() && !(nBlocksToMaturity > 0);
    status.cur_num_blocks = chainActive.Height();
    status.cur_num_ix_locks = nCompleteTXLocks;

    if (!IsFinalTx(wtx, chainActive.Height() + 1)) {
        if (wtx.nLockTime < LOCKTIME_THRESHOLD) {
            status.status = TransactionStatus::OpenUntilBlock;
            status.open_for = wtx.nLockTime - chainActive.Height();
        } else {
            status.status = TransactionStatus::OpenUntilDate;
            status.open_for = wtx.nLockTime;
        }
    }
    // For generated transactions, determine maturity
<<<<<<< Updated upstream
    else if (type == TransactionRecord::Generated || type == TransactionRecord::StakeMint || type == TransactionRecord::StakeZPIV || type == TransactionRecord::MNReward) {
=======
    else if (type == TransactionRecord::Generated || type == TransactionRecord::StakeMint || type == TransactionRecord::StakezPSC || type == TransactionRecord::MNReward) {
>>>>>>> Stashed changes
        if (nBlocksToMaturity > 0) {
            status.status = TransactionStatus::Immature;
            status.matures_in = nBlocksToMaturity;

            if (pindex && chainActive.Contains(pindex)) {
                // Check if the block was requested by anyone
<<<<<<< Updated upstream
                if (isOffline)
=======
                if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0)
>>>>>>> Stashed changes
                    status.status = TransactionStatus::MaturesWarning;
            } else {
                status.status = TransactionStatus::NotAccepted;
            }
        } else {
            status.status = TransactionStatus::Confirmed;
            status.matures_in = 0;
        }
    } else {
<<<<<<< Updated upstream
        if (status.depth < 0 || fConflicted) {
            status.status = TransactionStatus::Conflicted;
        } else if (isOffline) {
=======
        if (status.depth < 0) {
            status.status = TransactionStatus::Conflicted;
        } else if (GetAdjustedTime() - wtx.nTimeReceived > 2 * 60 && wtx.GetRequestCount() == 0) {
>>>>>>> Stashed changes
            status.status = TransactionStatus::Offline;
        } else if (status.depth == 0) {
            status.status = TransactionStatus::Unconfirmed;
        } else if (status.depth < RecommendedNumConfirmations) {
            status.status = TransactionStatus::Confirming;
        } else {
            status.status = TransactionStatus::Confirmed;
        }
    }
}

bool TransactionRecord::statusUpdateNeeded()
{
    AssertLockHeld(cs_main);
    return status.cur_num_blocks != chainActive.Height() || status.cur_num_ix_locks != nCompleteTXLocks;
}

QString TransactionRecord::getTxID() const
{
    return QString::fromStdString(hash.ToString());
}

int TransactionRecord::getOutputIndex() const
{
    return idx;
}
<<<<<<< Updated upstream

bool TransactionRecord::isCoinStake() const
{
    return (type == TransactionRecord::StakeMint || type == TransactionRecord::Generated || type == TransactionRecord::StakeZPIV);
}

bool TransactionRecord::isAnyColdStakingType() const
{
    return (type == TransactionRecord::P2CSDelegation || type == TransactionRecord::P2CSDelegationSent
           || type == TransactionRecord::StakeDelegated || type == TransactionRecord::StakeHot
           || type == TransactionRecord::P2CSUnlockOwner || type == TransactionRecord::P2CSUnlockStaker);
}

bool TransactionRecord::isNull() const
{
    return hash.IsNull() || size == 0;
}

std::string TransactionRecord::statusToString(){
    switch (status.status){
        case TransactionStatus::MaturesWarning:
            return "Abandoned (not mature because no nodes have confirmed)";
        case TransactionStatus::Confirmed:
            return "Confirmed";
        case TransactionStatus::OpenUntilDate:
            return "OpenUntilDate";
        case TransactionStatus::OpenUntilBlock:
            return "OpenUntilBlock";
        case TransactionStatus::Unconfirmed:
            return "Unconfirmed";
        case TransactionStatus::Confirming:
            return "Confirming";
        case TransactionStatus::Conflicted:
            return "Conflicted";
        case TransactionStatus::Immature:
            return "Immature";
        case TransactionStatus::NotAccepted:
            return "Not Accepted";
        default:
            return "No status";
    }
}
=======
>>>>>>> Stashed changes
