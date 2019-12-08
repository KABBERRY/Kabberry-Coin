// Copyright (c) 2011-2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "key.h"
#include "keystore.h"
#include "main.h"
#include "script/script.h"
#include "script/script_error.h"
#include "script/interpreter.h"
#include "script/sign.h"
#include "uint256.h"
<<<<<<< Updated upstream
#include "test_pivx.h"

#ifdef ENABLE_WALLET
#include "wallet/wallet_ismine.h"
#endif

#include <boost/test/unit_test.hpp>


typedef std::vector<unsigned char> valtype;

BOOST_FIXTURE_TEST_SUITE(multisig_tests, TestingSetup)

CScript
sign_multisig(CScript scriptPubKey, std::vector<CKey> keys, CTransaction transaction, int whichIn)
=======

#ifdef ENABLE_WALLET
#include "wallet_ismine.h"
#endif

#include <boost/assign/std/vector.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost::assign;

typedef vector<unsigned char> valtype;

BOOST_AUTO_TEST_SUITE(multisig_tests)

CScript
sign_multisig(CScript scriptPubKey, vector<CKey> keys, CTransaction transaction, int whichIn)
>>>>>>> Stashed changes
{
    uint256 hash = SignatureHash(scriptPubKey, transaction, whichIn, SIGHASH_ALL);

    CScript result;
    result << OP_0; // CHECKMULTISIG bug workaround
<<<<<<< Updated upstream
    for (const CKey &key : keys)
    {
        std::vector<unsigned char> vchSig;
=======
    BOOST_FOREACH(const CKey &key, keys)
    {
        vector<unsigned char> vchSig;
>>>>>>> Stashed changes
        BOOST_CHECK(key.Sign(hash, vchSig));
        vchSig.push_back((unsigned char)SIGHASH_ALL);
        result << vchSig;
    }
    return result;
}

BOOST_AUTO_TEST_CASE(multisig_verify)
{
    unsigned int flags = SCRIPT_VERIFY_P2SH | SCRIPT_VERIFY_STRICTENC;

    ScriptError err;
    CKey key[4];
    for (int i = 0; i < 4; i++)
        key[i].MakeNewKey(true);

    CScript a_and_b;
    a_and_b << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;

    CScript a_or_b;
    a_or_b << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;

    CScript escrow;
    escrow << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << ToByteVector(key[2].GetPubKey()) << OP_3 << OP_CHECKMULTISIG;

    CMutableTransaction txFrom;  // Funding transaction
    txFrom.vout.resize(3);
    txFrom.vout[0].scriptPubKey = a_and_b;
    txFrom.vout[1].scriptPubKey = a_or_b;
    txFrom.vout[2].scriptPubKey = escrow;

    CMutableTransaction txTo[3]; // Spending transaction
    for (int i = 0; i < 3; i++)
    {
        txTo[i].vin.resize(1);
        txTo[i].vout.resize(1);
        txTo[i].vin[0].prevout.n = i;
        txTo[i].vin[0].prevout.hash = txFrom.GetHash();
        txTo[i].vout[0].nValue = 1;
    }

<<<<<<< Updated upstream
    std::vector<CKey> keys;
=======
    vector<CKey> keys;
>>>>>>> Stashed changes
    CScript s;

    // Test a AND b:
    keys.clear();
<<<<<<< Updated upstream
    keys.push_back(key[0]);
    keys.push_back(key[1]);
=======
    keys += key[0],key[1]; // magic operator+= from boost.assign
>>>>>>> Stashed changes
    s = sign_multisig(a_and_b, keys, txTo[0], 0);
    BOOST_CHECK(VerifyScript(s, a_and_b, flags, MutableTransactionSignatureChecker(&txTo[0], 0), &err));
    BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_OK, ScriptErrorString(err));

    for (int i = 0; i < 4; i++)
    {
        keys.clear();
<<<<<<< Updated upstream
        keys.push_back(key[i]);
=======
        keys += key[i];
>>>>>>> Stashed changes
        s = sign_multisig(a_and_b, keys, txTo[0], 0);
        BOOST_CHECK_MESSAGE(!VerifyScript(s, a_and_b, flags, MutableTransactionSignatureChecker(&txTo[0], 0), &err), strprintf("a&b 1: %d", i));
        BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_INVALID_STACK_OPERATION, ScriptErrorString(err));

        keys.clear();
<<<<<<< Updated upstream
        keys.push_back(key[1]);
        keys.push_back(key[i]);
=======
        keys += key[1],key[i];
>>>>>>> Stashed changes
        s = sign_multisig(a_and_b, keys, txTo[0], 0);
        BOOST_CHECK_MESSAGE(!VerifyScript(s, a_and_b, flags, MutableTransactionSignatureChecker(&txTo[0], 0), &err), strprintf("a&b 2: %d", i));
        BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_EVAL_FALSE, ScriptErrorString(err));
    }

    // Test a OR b:
    for (int i = 0; i < 4; i++)
    {
        keys.clear();
<<<<<<< Updated upstream
        keys.push_back(key[i]);
=======
        keys += key[i];
>>>>>>> Stashed changes
        s = sign_multisig(a_or_b, keys, txTo[1], 0);
        if (i == 0 || i == 1)
        {
            BOOST_CHECK_MESSAGE(VerifyScript(s, a_or_b, flags, MutableTransactionSignatureChecker(&txTo[1], 0), &err), strprintf("a|b: %d", i));
            BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_OK, ScriptErrorString(err));
        }
        else
        {
            BOOST_CHECK_MESSAGE(!VerifyScript(s, a_or_b, flags, MutableTransactionSignatureChecker(&txTo[1], 0), &err), strprintf("a|b: %d", i));
            BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_EVAL_FALSE, ScriptErrorString(err));
        }
    }
    s.clear();
    s << OP_0 << OP_1;
    BOOST_CHECK(!VerifyScript(s, a_or_b, flags, MutableTransactionSignatureChecker(&txTo[1], 0), &err));
    BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_SIG_DER, ScriptErrorString(err));


    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            keys.clear();
<<<<<<< Updated upstream
            keys.push_back(key[i]);
            keys.push_back(key[j]);
=======
            keys += key[i],key[j];
>>>>>>> Stashed changes
            s = sign_multisig(escrow, keys, txTo[2], 0);
            if (i < j && i < 3 && j < 3)
            {
                BOOST_CHECK_MESSAGE(VerifyScript(s, escrow, flags, MutableTransactionSignatureChecker(&txTo[2], 0), &err), strprintf("escrow 1: %d %d", i, j));
                BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_OK, ScriptErrorString(err));
            }
            else
            {
                BOOST_CHECK_MESSAGE(!VerifyScript(s, escrow, flags, MutableTransactionSignatureChecker(&txTo[2], 0), &err), strprintf("escrow 2: %d %d", i, j));
                BOOST_CHECK_MESSAGE(err == SCRIPT_ERR_EVAL_FALSE, ScriptErrorString(err));
            }
        }
}

BOOST_AUTO_TEST_CASE(multisig_IsStandard)
{
    CKey key[4];
    for (int i = 0; i < 4; i++)
        key[i].MakeNewKey(true);

    txnouttype whichType;

    CScript a_and_b;
    a_and_b << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;
    BOOST_CHECK(::IsStandard(a_and_b, whichType));

    CScript a_or_b;
    a_or_b  << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;
    BOOST_CHECK(::IsStandard(a_or_b, whichType));

    CScript escrow;
    escrow << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << ToByteVector(key[2].GetPubKey()) << OP_3 << OP_CHECKMULTISIG;
    BOOST_CHECK(::IsStandard(escrow, whichType));

    CScript one_of_four;
    one_of_four << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << ToByteVector(key[2].GetPubKey()) << ToByteVector(key[3].GetPubKey()) << OP_4 << OP_CHECKMULTISIG;
    BOOST_CHECK(!::IsStandard(one_of_four, whichType));

    CScript malformed[6];
    malformed[0] << OP_3 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;
    malformed[1] << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_3 << OP_CHECKMULTISIG;
    malformed[2] << OP_0 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;
    malformed[3] << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_0 << OP_CHECKMULTISIG;
    malformed[4] << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_CHECKMULTISIG;
    malformed[5] << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey());

    for (int i = 0; i < 6; i++)
        BOOST_CHECK(!::IsStandard(malformed[i], whichType));
}

BOOST_AUTO_TEST_CASE(multisig_Solver1)
{
    // Tests Solver() that returns lists of keys that are
    // required to satisfy a ScriptPubKey
    //
    // Also tests IsMine() and ExtractDestination()
    //
    // Note: ExtractDestination for the multisignature transactions
    // always returns false for this release, even if you have
    // one key that would satisfy an (a|b) or 2-of-3 keys needed
    // to spend an escrow transaction.
    //
    CBasicKeyStore keystore, emptykeystore, partialkeystore;
    CKey key[3];
    CTxDestination keyaddr[3];
    for (int i = 0; i < 3; i++)
    {
        key[i].MakeNewKey(true);
        keystore.AddKey(key[i]);
        keyaddr[i] = key[i].GetPubKey().GetID();
    }
    partialkeystore.AddKey(key[0]);

    {
<<<<<<< Updated upstream
        std::vector<valtype> solutions;
=======
        vector<valtype> solutions;
>>>>>>> Stashed changes
        txnouttype whichType;
        CScript s;
        s << ToByteVector(key[0].GetPubKey()) << OP_CHECKSIG;
        BOOST_CHECK(Solver(s, whichType, solutions));
        BOOST_CHECK(solutions.size() == 1);
        CTxDestination addr;
        BOOST_CHECK(ExtractDestination(s, addr));
        BOOST_CHECK(addr == keyaddr[0]);
#ifdef ENABLE_WALLET
        BOOST_CHECK(IsMine(keystore, s));
        BOOST_CHECK(!IsMine(emptykeystore, s));
#endif
    }
    {
<<<<<<< Updated upstream
        std::vector<valtype> solutions;
=======
        vector<valtype> solutions;
>>>>>>> Stashed changes
        txnouttype whichType;
        CScript s;
        s << OP_DUP << OP_HASH160 << ToByteVector(key[0].GetPubKey().GetID()) << OP_EQUALVERIFY << OP_CHECKSIG;
        BOOST_CHECK(Solver(s, whichType, solutions));
        BOOST_CHECK(solutions.size() == 1);
        CTxDestination addr;
        BOOST_CHECK(ExtractDestination(s, addr));
        BOOST_CHECK(addr == keyaddr[0]);
#ifdef ENABLE_WALLET
        BOOST_CHECK(IsMine(keystore, s));
        BOOST_CHECK(!IsMine(emptykeystore, s));
#endif
    }
    {
<<<<<<< Updated upstream
        std::vector<valtype> solutions;
=======
        vector<valtype> solutions;
>>>>>>> Stashed changes
        txnouttype whichType;
        CScript s;
        s << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;
        BOOST_CHECK(Solver(s, whichType, solutions));
        BOOST_CHECK_EQUAL(solutions.size(), 4U);
        CTxDestination addr;
        BOOST_CHECK(!ExtractDestination(s, addr));
#ifdef ENABLE_WALLET
        BOOST_CHECK(IsMine(keystore, s));
        BOOST_CHECK(!IsMine(emptykeystore, s));
        BOOST_CHECK(!IsMine(partialkeystore, s));
#endif
    }
    {
<<<<<<< Updated upstream
        std::vector<valtype> solutions;
=======
        vector<valtype> solutions;
>>>>>>> Stashed changes
        txnouttype whichType;
        CScript s;
        s << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;
        BOOST_CHECK(Solver(s, whichType, solutions));
        BOOST_CHECK_EQUAL(solutions.size(), 4U);
<<<<<<< Updated upstream
        std::vector<CTxDestination> addrs;
=======
        vector<CTxDestination> addrs;
>>>>>>> Stashed changes
        int nRequired;
        BOOST_CHECK(ExtractDestinations(s, whichType, addrs, nRequired));
        BOOST_CHECK(addrs[0] == keyaddr[0]);
        BOOST_CHECK(addrs[1] == keyaddr[1]);
        BOOST_CHECK(nRequired == 1);
#ifdef ENABLE_WALLET
        BOOST_CHECK(IsMine(keystore, s));
        BOOST_CHECK(!IsMine(emptykeystore, s));
        BOOST_CHECK(!IsMine(partialkeystore, s));
#endif
    }
    {
<<<<<<< Updated upstream
        std::vector<valtype> solutions;
=======
        vector<valtype> solutions;
>>>>>>> Stashed changes
        txnouttype whichType;
        CScript s;
        s << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << ToByteVector(key[2].GetPubKey()) << OP_3 << OP_CHECKMULTISIG;
        BOOST_CHECK(Solver(s, whichType, solutions));
        BOOST_CHECK(solutions.size() == 5);
    }
}

BOOST_AUTO_TEST_CASE(multisig_Sign)
{
    // Test SignSignature() (and therefore the version of Solver() that signs transactions)
    CBasicKeyStore keystore;
    CKey key[4];
    for (int i = 0; i < 4; i++)
    {
        key[i].MakeNewKey(true);
        keystore.AddKey(key[i]);
    }

    CScript a_and_b;
    a_and_b << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;

    CScript a_or_b;
    a_or_b  << OP_1 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << OP_2 << OP_CHECKMULTISIG;

    CScript escrow;
    escrow << OP_2 << ToByteVector(key[0].GetPubKey()) << ToByteVector(key[1].GetPubKey()) << ToByteVector(key[2].GetPubKey()) << OP_3 << OP_CHECKMULTISIG;

    CMutableTransaction txFrom;  // Funding transaction
    txFrom.vout.resize(3);
    txFrom.vout[0].scriptPubKey = a_and_b;
    txFrom.vout[1].scriptPubKey = a_or_b;
    txFrom.vout[2].scriptPubKey = escrow;

    CMutableTransaction txTo[3]; // Spending transaction
    for (int i = 0; i < 3; i++)
    {
        txTo[i].vin.resize(1);
        txTo[i].vout.resize(1);
        txTo[i].vin[0].prevout.n = i;
        txTo[i].vin[0].prevout.hash = txFrom.GetHash();
        txTo[i].vout[0].nValue = 1;
    }

    for (int i = 0; i < 3; i++)
    {
        BOOST_CHECK_MESSAGE(SignSignature(keystore, txFrom, txTo[i], 0), strprintf("SignSignature %d", i));
    }
}


BOOST_AUTO_TEST_SUITE_END()
