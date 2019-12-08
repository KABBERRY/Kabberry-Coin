// Copyright (c) 2017-2018 The PIVX developers
<<<<<<< Updated upstream
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_STAKEINPUT_H
#define PIVX_STAKEINPUT_H

#include "chain.h"
#include "streams.h"
#include "uint256.h"
=======
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PrimeStone_STAKEINPUT_H
#define PrimeStone_STAKEINPUT_H
>>>>>>> Stashed changes

class CKeyStore;
class CWallet;
class CWalletTx;

class CStakeInput
{
protected:
<<<<<<< Updated upstream
    CBlockIndex* pindexFrom = nullptr;
=======
    CBlockIndex* pindexFrom;
>>>>>>> Stashed changes

public:
    virtual ~CStakeInput(){};
    virtual CBlockIndex* GetIndexFrom() = 0;
    virtual bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = 0) = 0;
    virtual bool GetTxFrom(CTransaction& tx) = 0;
    virtual CAmount GetValue() = 0;
<<<<<<< Updated upstream
    virtual bool CreateTxOuts(CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) = 0;
    virtual bool GetModifier(uint64_t& nStakeModifier) = 0;
    virtual bool IsZPIV() = 0;
    virtual CDataStream GetUniqueness() = 0;
    virtual uint256 GetSerialHash() const = 0;

    virtual uint64_t getStakeModifierHeight() const {
        return 0;
    }
};


// zPIVStake can take two forms
// 1) the stake candidate, which is a zcmint that is attempted to be staked
// 2) a staked zpiv, which is a zcspend that has successfully staked
class CZPivStake : public CStakeInput
=======
    virtual bool CreateTxOuts(CWallet* pwallet, vector<CTxOut>& vout, CAmount nTotal) = 0;
    virtual bool GetModifier(uint64_t& nStakeModifier) = 0;
    virtual bool IszPSC() = 0;
    virtual CDataStream GetUniqueness() = 0;
};


// zPSCStake can take two forms
// 1) the stake candidate, which is a zcmint that is attempted to be staked
// 2) a staked zPSC, which is a zcspend that has successfully staked
class CzPSCStake : public CStakeInput
>>>>>>> Stashed changes
{
private:
    uint32_t nChecksum;
    bool fMint;
    libzerocoin::CoinDenomination denom;
    uint256 hashSerial;

public:
<<<<<<< Updated upstream
    explicit CZPivStake(libzerocoin::CoinDenomination denom, const uint256& hashSerial)
    {
        this->denom = denom;
        this->hashSerial = hashSerial;
        fMint = true;
    }

    explicit CZPivStake(const libzerocoin::CoinSpend& spend);
=======
    explicit CzPSCStake(libzerocoin::CoinDenomination denom, const uint256& hashSerial)
    {
        this->denom = denom;
        this->hashSerial = hashSerial;
        this->pindexFrom = nullptr;
        fMint = true;
    }

    explicit CzPSCStake(const libzerocoin::CoinSpend& spend);
>>>>>>> Stashed changes

    CBlockIndex* GetIndexFrom() override;
    bool GetTxFrom(CTransaction& tx) override;
    CAmount GetValue() override;
    bool GetModifier(uint64_t& nStakeModifier) override;
    CDataStream GetUniqueness() override;
    bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = 0) override;
<<<<<<< Updated upstream
    bool CreateTxOuts(CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) override;
    bool MarkSpent(CWallet* pwallet, const uint256& txid);
    bool IsZPIV() override { return true; }
    uint256 GetSerialHash() const override { return hashSerial; }
=======
    bool CreateTxOuts(CWallet* pwallet, vector<CTxOut>& vout, CAmount nTotal) override;
    bool MarkSpent(CWallet* pwallet, const uint256& txid);
    bool IszPSC() override { return true; }
>>>>>>> Stashed changes
    int GetChecksumHeightFromMint();
    int GetChecksumHeightFromSpend();
    uint32_t GetChecksum();
};

<<<<<<< Updated upstream
class CPivStake : public CStakeInput
=======
class CPrimeStoneStake : public CStakeInput
>>>>>>> Stashed changes
{
private:
    CTransaction txFrom;
    unsigned int nPosition;
<<<<<<< Updated upstream

    // cached data
    uint64_t nStakeModifier = 0;
    int nStakeModifierHeight = 0;
    int64_t nStakeModifierTime = 0;
public:
    CPivStake(){}
=======
public:
    CPrimeStoneStake()
    {
        this->pindexFrom = nullptr;
    }
>>>>>>> Stashed changes

    bool SetInput(CTransaction txPrev, unsigned int n);

    CBlockIndex* GetIndexFrom() override;
    bool GetTxFrom(CTransaction& tx) override;
    CAmount GetValue() override;
    bool GetModifier(uint64_t& nStakeModifier) override;
    CDataStream GetUniqueness() override;
    bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = 0) override;
<<<<<<< Updated upstream
    bool CreateTxOuts(CWallet* pwallet, std::vector<CTxOut>& vout, CAmount nTotal) override;
    bool IsZPIV() override { return false; }
    uint256 GetSerialHash() const override { return uint256(0); }

    uint64_t getStakeModifierHeight() const override { return nStakeModifierHeight; }
};


#endif //PIVX_STAKEINPUT_H
=======
    bool CreateTxOuts(CWallet* pwallet, vector<CTxOut>& vout, CAmount nTotal) override;
    bool IszPSC() override { return false; }
};


#endif //PrimeStone_STAKEINPUT_H
>>>>>>> Stashed changes
