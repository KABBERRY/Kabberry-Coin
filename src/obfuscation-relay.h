// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
<<<<<<< Updated upstream
=======
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef OBFUSCATION_RELAY_H
#define OBFUSCATION_RELAY_H

#include "activemasternode.h"
#include "main.h"
#include "masternodeman.h"


<<<<<<< Updated upstream
class CObfuScationRelay : public CSignedMessage
{
private:
    std::vector<unsigned char> vchSig2;

public:
    CTxIn vinMasternode;
=======
class CObfuScationRelay
{
public:
    CTxIn vinMasternode;
    vector<unsigned char> vchSig;
    vector<unsigned char> vchSig2;
>>>>>>> Stashed changes
    int nBlockHeight;
    int nRelayType;
    CTxIn in;
    CTxOut out;

    CObfuScationRelay();
<<<<<<< Updated upstream
    CObfuScationRelay(CTxIn& vinMasternodeIn, std::vector<unsigned char>& vchSigIn, int nBlockHeightIn, int nRelayTypeIn, CTxIn& in2, CTxOut& out2);
=======
    CObfuScationRelay(CTxIn& vinMasternodeIn, vector<unsigned char>& vchSigIn, int nBlockHeightIn, int nRelayTypeIn, CTxIn& in2, CTxOut& out2);
>>>>>>> Stashed changes

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion)
    {
        READWRITE(vinMasternode);
        READWRITE(vchSig);
        READWRITE(vchSig2);
        READWRITE(nBlockHeight);
        READWRITE(nRelayType);
        READWRITE(in);
        READWRITE(out);
<<<<<<< Updated upstream
        try
        {
            READWRITE(nMessVersion);
        } catch (...) {
            nMessVersion = MessageVersion::MESS_VER_STRMESS;
        }
=======
>>>>>>> Stashed changes
    }

    std::string ToString();

<<<<<<< Updated upstream
    // override CSignedMessage functions
    uint256 GetSignatureHash() const override;
    std::string GetStrMessage() const override;
    const CTxIn GetVin() const override { return vinMasternode; };
    bool Sign(std::string strSharedKey);   // use vchSig2

=======
    bool Sign(std::string strSharedKey);
    bool VerifyMessage(std::string strSharedKey);
>>>>>>> Stashed changes
    void Relay();
    void RelayThroughNode(int nRank);
};


#endif
