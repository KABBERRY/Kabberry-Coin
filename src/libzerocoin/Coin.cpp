/**
 * @file       Coin.cpp
 *
 * @brief      PublicCoin and PrivateCoin classes for the Zerocoin library.
 *
 * @author     Ian Miers, Christina Garman and Matthew Green
 * @date       June 2013
 *
 * @copyright  Copyright 2013 Ian Miers, Christina Garman and Matthew Green
 * @license    This project is released under the MIT license.
 **/
<<<<<<< Updated upstream
// Copyright (c) 2017-2019 The PIVX developers
=======
// Copyright (c) 2017-2018-2019 The PrimeStone developers
>>>>>>> Stashed changes

#include <stdexcept>
#include <iostream>
#include "Coin.h"
#include "Commitment.h"
#include "pubkey.h"

namespace libzerocoin {

//PublicCoin class
PublicCoin::PublicCoin(const ZerocoinParams* p):
<<<<<<< Updated upstream
    params(p) {
    if (this->params->initialized == false) {
        throw std::runtime_error("Params are not initialized");
    }
=======
	params(p) {
	if (this->params->initialized == false) {
		throw std::runtime_error("Params are not initialized");
	}
>>>>>>> Stashed changes
    // Assume this will get set by another method later
    denomination = ZQ_ERROR;
};

PublicCoin::PublicCoin(const ZerocoinParams* p, const CBigNum& coin, const CoinDenomination d):
<<<<<<< Updated upstream
    params(p), value(coin) {
    if (this->params->initialized == false) {
        throw std::runtime_error("Params are not initialized");
    }

    denomination = d;
    for(const CoinDenomination denom : zerocoinDenomList) {
        if(denom == d)
            denomination = d;
    }
    if (denomination == 0) {
        std::cout << "denom does not exist\n";
        throw std::runtime_error("Denomination does not exist");
    }
=======
	params(p), value(coin) {
	if (this->params->initialized == false) {
		throw std::runtime_error("Params are not initialized");
	}

	denomination = d;
	for(const CoinDenomination denom : zerocoinDenomList) {
		if(denom == d)
			denomination = d;
	}
    if(denomination == 0){
		std::cout << "denom does not exist\n";
		throw std::runtime_error("Denomination does not exist");
	}
>>>>>>> Stashed changes
};

bool PublicCoin::validate() const
{
    if (this->params->accumulatorParams.minCoinValue >= value) {
<<<<<<< Updated upstream
        return error("%s: ERROR: PublicCoin::validate value is too low: %s", __func__, value.GetDec());
    }

    if (value > this->params->accumulatorParams.maxCoinValue) {
        return error("%s: ERROR: PublicCoin::validate value is too high, max: %s, received: %s",
                __func__, this->params->accumulatorParams.maxCoinValue, value.GetDec());
    }

    if (!value.isPrime(params->zkp_iterations)) {
        return error("%s: ERROR: PublicCoin::validate value is not prime. Value: %s, Iterations: %d",
                __func__, value.GetDec(), params->zkp_iterations);
=======
        cout << "PublicCoin::validate value is too low\n";
        return false;
    }

    if (value > this->params->accumulatorParams.maxCoinValue) {
        cout << "PublicCoin::validate value is too high\n";
        return false;
    }

    if (!value.isPrime(params->zkp_iterations)) {
        cout << "PublicCoin::validate value is not prime\n";
        return false;
>>>>>>> Stashed changes
    }

    return true;
}

//PrivateCoin class
PrivateCoin::PrivateCoin(const ZerocoinParams* p, const CoinDenomination denomination, bool fMintNew): params(p), publicCoin(p) {
<<<<<<< Updated upstream
    // Verify that the parameters are valid
    if(this->params->initialized == false) {
        throw std::runtime_error("Params are not initialized");
    }
=======
	// Verify that the parameters are valid
	if(this->params->initialized == false) {
		throw std::runtime_error("Params are not initialized");
	}
>>>>>>> Stashed changes

    if (fMintNew) {
#ifdef ZEROCOIN_FAST_MINT
        // Mint a new coin with a random serial number using the fast process.
        // This is more vulnerable to timing attacks so don't mint coins when
        // somebody could be timing you.
        this->mintCoinFast(denomination);
#else
        // Mint a new coin with a random serial number using the standard process.
        this->mintCoin(denomination);
#endif
    }

    this->version = CURRENT_VERSION;
}

PrivateCoin::PrivateCoin(const ZerocoinParams* p, const CoinDenomination denomination, const CBigNum& bnSerial,
                         const CBigNum& bnRandomness): params(p), publicCoin(p)
{
        // Verify that the parameters are valid
    if(!this->params->initialized)
        throw std::runtime_error("Params are not initialized");

    this->serialNumber = bnSerial;
    this->randomness = bnRandomness;

    Commitment commitment(&p->coinCommitmentGroup, bnSerial, bnRandomness);
    this->publicCoin = PublicCoin(p, commitment.getCommitmentValue(), denomination);
}

bool PrivateCoin::IsValid()
{
    if (!IsValidSerial(params, serialNumber)) {
<<<<<<< Updated upstream
        std::cout << "Serial not valid\n";
=======
        cout << "Serial not valid\n";
>>>>>>> Stashed changes
        return false;
    }

    return getPublicCoin().validate();
}

bool GenerateKeyPair(const CBigNum& bnGroupOrder, const uint256& nPrivkey, CKey& key, CBigNum& bnSerial)
{
    // Generate a new key pair, which also has a 256-bit pubkey hash that qualifies as a serial #
    // This builds off of Tim Ruffing's work on libzerocoin, but has a different implementation
    CKey keyPair;
    if (nPrivkey == 0)
        keyPair.MakeNewKey(true);
    else
        keyPair.Set(nPrivkey.begin(), nPrivkey.end(), true);

    CPubKey pubKey = keyPair.GetPubKey();
    uint256 hashPubKey = Hash(pubKey.begin(), pubKey.end());

    // Make the first half byte 0 which will distinctly mark v2 serials
    hashPubKey >>= libzerocoin::PrivateCoin::V2_BITSHIFT;

    CBigNum s(hashPubKey);
    uint256 nBits = hashPubKey >> 248; // must be less than 0x0D to be valid serial range
    if (nBits > 12)
        return false;

    //Mark this as v2 by starting with 0xF
    uint256 nMark = 0xF;
    nMark <<= 252;
    hashPubKey |= nMark;
    s = CBigNum(hashPubKey);

    key = keyPair;
    bnSerial = s;
    return true;
}

const CPubKey PrivateCoin::getPubKey() const
{
<<<<<<< Updated upstream
    CKey key;
    key.SetPrivKey(privkey, true);
    return key.GetPubKey();
}

bool PrivateCoin::sign(const uint256& hash, std::vector<unsigned char>& vchSig) const
{
    CKey key;
    key.SetPrivKey(privkey, true);
    return key.Sign(hash, vchSig);
}

void PrivateCoin::mintCoin(const CoinDenomination denomination) {
    // Repeat this process up to MAX_COINMINT_ATTEMPTS times until
    // we obtain a prime number
    for(uint32_t attempt = 0; attempt < MAX_COINMINT_ATTEMPTS; attempt++) {

        // Generate a random serial number in the range 0...{q-1} where
        // "q" is the order of the commitment group.
        // And where the serial also doubles as a public key
        CKey key;
        CBigNum s;
=======
	CKey key;
	key.SetPrivKey(privkey, true);
	return key.GetPubKey();
}

bool PrivateCoin::sign(const uint256& hash, vector<unsigned char>& vchSig) const
{
	CKey key;
	key.SetPrivKey(privkey, true);
	return key.Sign(hash, vchSig);
}

void PrivateCoin::mintCoin(const CoinDenomination denomination) {
	// Repeat this process up to MAX_COINMINT_ATTEMPTS times until
	// we obtain a prime number
	for(uint32_t attempt = 0; attempt < MAX_COINMINT_ATTEMPTS; attempt++) {

		// Generate a random serial number in the range 0...{q-1} where
		// "q" is the order of the commitment group.
		// And where the serial also doubles as a public key
		CKey key;
		CBigNum s;
>>>>>>> Stashed changes
        bool isValid = false;
        while (!isValid) {
            isValid = GenerateKeyPair(this->params->coinCommitmentGroup.groupOrder, uint256(0), key, s);
        }

<<<<<<< Updated upstream
        // Generate a Pedersen commitment to the serial number "s"
        Commitment coin(&params->coinCommitmentGroup, s);

        // Now verify that the commitment is a prime number
        // in the appropriate range. If not, we'll throw this coin
        // away and generate a new one.
        if (coin.getCommitmentValue().isPrime(ZEROCOIN_MINT_PRIME_PARAM) &&
                coin.getCommitmentValue() >= params->accumulatorParams.minCoinValue &&
                coin.getCommitmentValue() <= params->accumulatorParams.maxCoinValue) {
            // Found a valid coin. Store it.
            this->serialNumber = s;
            this->randomness = coin.getRandomness();
            this->publicCoin = PublicCoin(params,coin.getCommitmentValue(), denomination);
            this->privkey = key.GetPrivKey();
            this->version = 2;

            // Success! We're done.
            return;
        }
    }

    // We only get here if we did not find a coin within
    // MAX_COINMINT_ATTEMPTS. Throw an exception.
    throw std::runtime_error("Unable to mint a new Zerocoin (too many attempts)");
=======
		// Generate a Pedersen commitment to the serial number "s"
		Commitment coin(&params->coinCommitmentGroup, s);

		// Now verify that the commitment is a prime number
		// in the appropriate range. If not, we'll throw this coin
		// away and generate a new one.
		if (coin.getCommitmentValue().isPrime(ZEROCOIN_MINT_PRIME_PARAM) &&
		        coin.getCommitmentValue() >= params->accumulatorParams.minCoinValue &&
		        coin.getCommitmentValue() <= params->accumulatorParams.maxCoinValue) {
			// Found a valid coin. Store it.
			this->serialNumber = s;
			this->randomness = coin.getRandomness();
			this->publicCoin = PublicCoin(params,coin.getCommitmentValue(), denomination);
			this->privkey = key.GetPrivKey();
			this->version = 2;

			// Success! We're done.
			return;
		}
	}

	// We only get here if we did not find a coin within
	// MAX_COINMINT_ATTEMPTS. Throw an exception.
	throw std::runtime_error("Unable to mint a new Zerocoin (too many attempts)");
>>>>>>> Stashed changes
}

void PrivateCoin::mintCoinFast(const CoinDenomination denomination) {

<<<<<<< Updated upstream
    // Generate a random serial number in the range 0...{q-1} where
    // "q" is the order of the commitment group.
    // And where the serial also doubles as a public key
    CKey key;
    CBigNum s;
=======
	// Generate a random serial number in the range 0...{q-1} where
	// "q" is the order of the commitment group.
	// And where the serial also doubles as a public key
	CKey key;
	CBigNum s;
>>>>>>> Stashed changes
    bool isValid = false;
    while (!isValid) {
        isValid = GenerateKeyPair(this->params->coinCommitmentGroup.groupOrder, uint256(0), key, s);
    }
<<<<<<< Updated upstream
    // Generate a random number "r" in the range 0...{q-1}
    CBigNum r = CBigNum::randBignum(this->params->coinCommitmentGroup.groupOrder);

    // Manually compute a Pedersen commitment to the serial number "s" under randomness "r"
    // C = g^s * h^r mod p
    CBigNum commitmentValue = this->params->coinCommitmentGroup.g.pow_mod(s, this->params->coinCommitmentGroup.modulus).mul_mod(this->params->coinCommitmentGroup.h.pow_mod(r, this->params->coinCommitmentGroup.modulus), this->params->coinCommitmentGroup.modulus);

    // Repeat this process up to MAX_COINMINT_ATTEMPTS times until
    // we obtain a prime number
    for (uint32_t attempt = 0; attempt < MAX_COINMINT_ATTEMPTS; attempt++) {
        // First verify that the commitment is a prime number
        // in the appropriate range. If not, we'll throw this coin
        // away and generate a new one.
        if (commitmentValue.isPrime(ZEROCOIN_MINT_PRIME_PARAM) &&
            commitmentValue >= params->accumulatorParams.minCoinValue &&
            commitmentValue <= params->accumulatorParams.maxCoinValue) {
            // Found a valid coin. Store it.
            this->serialNumber = s;
            this->randomness = r;
            this->publicCoin = PublicCoin(params, commitmentValue, denomination);
            this->privkey = key.GetPrivKey();
            this->version = 2;

            // Success! We're done.
            return;
        }

        // Generate a new random "r_delta" in 0...{q-1}
        CBigNum r_delta = CBigNum::randBignum(this->params->coinCommitmentGroup.groupOrder);

        // The commitment was not prime. Increment "r" and recalculate "C":
        // r = r + r_delta mod q
        // C = C * h mod p
        r = (r + r_delta) % this->params->coinCommitmentGroup.groupOrder;
        commitmentValue = commitmentValue.mul_mod(this->params->coinCommitmentGroup.h.pow_mod(r_delta, this->params->coinCommitmentGroup.modulus), this->params->coinCommitmentGroup.modulus);
    }

    // We only get here if we did not find a coin within
    // MAX_COINMINT_ATTEMPTS. Throw an exception.
    throw std::runtime_error("Unable to mint a new Zerocoin (too many attempts)");
=======
	// Generate a random number "r" in the range 0...{q-1}
	CBigNum r = CBigNum::randBignum(this->params->coinCommitmentGroup.groupOrder);
	
	// Manually compute a Pedersen commitment to the serial number "s" under randomness "r"
	// C = g^s * h^r mod p
	CBigNum commitmentValue = this->params->coinCommitmentGroup.g.pow_mod(s, this->params->coinCommitmentGroup.modulus).mul_mod(this->params->coinCommitmentGroup.h.pow_mod(r, this->params->coinCommitmentGroup.modulus), this->params->coinCommitmentGroup.modulus);
	
	// Repeat this process up to MAX_COINMINT_ATTEMPTS times until
	// we obtain a prime number
	for (uint32_t attempt = 0; attempt < MAX_COINMINT_ATTEMPTS; attempt++) {
		// First verify that the commitment is a prime number
		// in the appropriate range. If not, we'll throw this coin
		// away and generate a new one.
		if (commitmentValue.isPrime(ZEROCOIN_MINT_PRIME_PARAM) &&
			commitmentValue >= params->accumulatorParams.minCoinValue &&
			commitmentValue <= params->accumulatorParams.maxCoinValue) {
			// Found a valid coin. Store it.
			this->serialNumber = s;
			this->randomness = r;
			this->publicCoin = PublicCoin(params, commitmentValue, denomination);
			this->privkey = key.GetPrivKey();
			this->version = 2;

			// Success! We're done.
			return;
		}
		
		// Generate a new random "r_delta" in 0...{q-1}
		CBigNum r_delta = CBigNum::randBignum(this->params->coinCommitmentGroup.groupOrder);

		// The commitment was not prime. Increment "r" and recalculate "C":
		// r = r + r_delta mod q
		// C = C * h mod p
		r = (r + r_delta) % this->params->coinCommitmentGroup.groupOrder;
		commitmentValue = commitmentValue.mul_mod(this->params->coinCommitmentGroup.h.pow_mod(r_delta, this->params->coinCommitmentGroup.modulus), this->params->coinCommitmentGroup.modulus);
	}
		
	// We only get here if we did not find a coin within
	// MAX_COINMINT_ATTEMPTS. Throw an exception.
	throw std::runtime_error("Unable to mint a new Zerocoin (too many attempts)");
>>>>>>> Stashed changes
}

int ExtractVersionFromSerial(const CBigNum& bnSerial)
{
<<<<<<< Updated upstream
    try {
        //Serial is marked as v2 only if the first byte is 0xF
        uint256 nMark = bnSerial.getuint256() >> (256 - PrivateCoin::V2_BITSHIFT);
        if (nMark == 0xf)
            return PrivateCoin::PUBKEY_VERSION;
    } catch (const std::range_error& e) {
        //std::cout << "ExtractVersionFromSerial(): " << e.what() << std::endl;
        // Only serial version 2 appeared with this range error..
        return 2;
    }

    return 1;
=======
	//Serial is marked as v2 only if the first byte is 0xF
	uint256 nMark = bnSerial.getuint256() >> (256 - PrivateCoin::V2_BITSHIFT);
	if (nMark == 0xf)
		return PrivateCoin::PUBKEY_VERSION;

	return 2;
>>>>>>> Stashed changes
}

//Remove the first four bits for V2 serials
CBigNum GetAdjustedSerial(const CBigNum& bnSerial)
{
    uint256 serial = bnSerial.getuint256();
    serial &= ~uint256(0) >> PrivateCoin::V2_BITSHIFT;
    CBigNum bnSerialAdjusted;
    bnSerialAdjusted.setuint256(serial);
    return bnSerialAdjusted;
}


bool IsValidSerial(const ZerocoinParams* params, const CBigNum& bnSerial)
{
    if (bnSerial <= 0)
        return false;

    if (ExtractVersionFromSerial(bnSerial) < PrivateCoin::PUBKEY_VERSION)
        return bnSerial < params->coinCommitmentGroup.groupOrder;

<<<<<<< Updated upstream
    // If V2, the serial is marked with 0xF in the first 4 bits. So It's always > groupOrder.
    // This is removed for the adjusted serial - so it's always < groupOrder.
    // So we check only the bitsize here.
    return bnSerial.bitSize() <= 256;
}


bool IsValidCommitmentToCoinRange(const ZerocoinParams* params, const CBigNum& bnCommitment)
{
    return bnCommitment > BN_ZERO && bnCommitment < params->serialNumberSoKCommitmentGroup.modulus;
}


CBigNum ExtractSerialFromPubKey(const CPubKey pubkey)
{
    uint256 hashedPubkey = Hash(pubkey.begin(), pubkey.end()) >> PrivateCoin::V2_BITSHIFT;
    uint256 uintSerial = (uint256(0xF) << (256 - PrivateCoin::V2_BITSHIFT)) | hashedPubkey;
    return CBigNum(uintSerial);
}


=======
    //If V2, the serial is marked with 0xF in the first 4 bits. This is removed for the actual serial.
    CBigNum bnAdjustedSerial = GetAdjustedSerial(bnSerial);
    return bnAdjustedSerial > 0 && bnAdjustedSerial < params->coinCommitmentGroup.groupOrder;
}

>>>>>>> Stashed changes
} /* namespace libzerocoin */
