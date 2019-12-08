/**
 * @file       Accumulator.cpp
 *
 * @brief      Accumulator and AccumulatorWitness classes for the Zerocoin library.
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
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes

#include <sstream>
#include <iostream>
#include "Accumulator.h"
#include "ZerocoinDefines.h"

namespace libzerocoin {

//Accumulator class
Accumulator::Accumulator(const AccumulatorAndProofParams* p, const CoinDenomination d): params(p) {
<<<<<<< Updated upstream
    if (!(params->initialized)) {
        throw std::runtime_error("Invalid parameters for accumulator");
    }
    denomination = d;
    this->value = this->params->accumulatorBase;
}

Accumulator::Accumulator(const ZerocoinParams* p, const CoinDenomination d, const CBigNum bnValue) {
    this->params = &(p->accumulatorParams);
    denomination = d;

    if (!(params->initialized)) {
        throw std::runtime_error("Invalid parameters for accumulator");
    }

    if(bnValue != 0)
        this->value = bnValue;
    else
        this->value = this->params->accumulatorBase;
=======
	if (!(params->initialized)) {
		throw std::runtime_error("Invalid parameters for accumulator");
	}
    denomination = d;
	this->value = this->params->accumulatorBase;
}

Accumulator::Accumulator(const ZerocoinParams* p, const CoinDenomination d, const CBigNum bnValue) {
	this->params = &(p->accumulatorParams);
    denomination = d;

	if (!(params->initialized)) {
		throw std::runtime_error("Invalid parameters for accumulator");
	}

	if(bnValue != 0)
		this->value = bnValue;
	else
		this->value = this->params->accumulatorBase;
>>>>>>> Stashed changes
}

void Accumulator::increment(const CBigNum& bnValue) {
    // Compute new accumulator = "old accumulator"^{element} mod N
    this->value = this->value.pow_mod(bnValue, this->params->accumulatorModulus);
}

void Accumulator::accumulate(const PublicCoin& coin) {
<<<<<<< Updated upstream
    // Make sure we're initialized
    if(!(this->value)) {
        std::cout << "Accumulator is not initialized" << "\n";
        throw std::runtime_error("Accumulator is not initialized");
    }

    if(this->denomination != coin.getDenomination()) {
        std::cout << "Wrong denomination for coin. Expected coins of denomination: ";
=======
	// Make sure we're initialized
	if(!(this->value)) {
        std::cout << "Accumulator is not initialized" << "\n";
		throw std::runtime_error("Accumulator is not initialized");
	}

	if(this->denomination != coin.getDenomination()) {
		std::cout << "Wrong denomination for coin. Expected coins of denomination: ";
>>>>>>> Stashed changes
        std::cout << this->denomination;
        std::cout << ". Instead, got a coin of denomination: ";
        std::cout << coin.getDenomination();
        std::cout << "\n";
<<<<<<< Updated upstream
        throw std::runtime_error("Wrong denomination for coin");
    }

    if(coin.validate()) {
        increment(coin.getValue());
    } else {
        std::cout << "Coin not valid\n";
        throw std::runtime_error("Coin is not valid");
    }
}

CoinDenomination Accumulator::getDenomination() const {
    return this->denomination;
}

const CBigNum& Accumulator::getValue() const {
    return this->value;
=======
		throw std::runtime_error("Wrong denomination for coin");
	}

	if(coin.validate()) {
		increment(coin.getValue());
	} else {
		std::cout << "Coin not valid\n";
        throw std::runtime_error("Coin is not valid");
	}
}

CoinDenomination Accumulator::getDenomination() const {
	return this->denomination;
}

const CBigNum& Accumulator::getValue() const {
	return this->value;
>>>>>>> Stashed changes
}

//Manually set accumulator value
void Accumulator::setValue(CBigNum bnValue) {
<<<<<<< Updated upstream
    this->value = bnValue;
}

void Accumulator::setInitialValue() {
    this->value = this->params->accumulatorBase;
}

Accumulator& Accumulator::operator += (const PublicCoin& c) {
    this->accumulate(c);
    return *this;
}

bool Accumulator::operator == (const Accumulator rhs) const {
    return this->value == rhs.value;
=======
	this->value = bnValue;
}

Accumulator& Accumulator::operator += (const PublicCoin& c) {
	this->accumulate(c);
	return *this;
}

bool Accumulator::operator == (const Accumulator rhs) const {
	return this->value == rhs.value;
>>>>>>> Stashed changes
}

//AccumulatorWitness class
AccumulatorWitness::AccumulatorWitness(const ZerocoinParams* p,
                                       const Accumulator& checkpoint, const PublicCoin coin): witness(checkpoint), element(coin) {
}

void AccumulatorWitness::resetValue(const Accumulator& checkpoint, const PublicCoin coin) {
    this->witness.setValue(checkpoint.getValue());
    this->element = coin;
}

void AccumulatorWitness::AddElement(const PublicCoin& c) {
<<<<<<< Updated upstream
    if(element.getValue() != c.getValue()) {
        witness += c;
    }
=======
	if(element.getValue() != c.getValue()) {
		witness += c;
	}
>>>>>>> Stashed changes
}

//warning check pubcoin value & denom outside of this function!
void AccumulatorWitness::addRawValue(const CBigNum& bnValue) {
        witness.increment(bnValue);
}

const CBigNum& AccumulatorWitness::getValue() const {
<<<<<<< Updated upstream
    return this->witness.getValue();
}

const PublicCoin& AccumulatorWitness::getPublicCoin() const {
    return this->element;
}

bool AccumulatorWitness::VerifyWitness(const Accumulator& a, const PublicCoin &publicCoin) const {
    Accumulator temp(witness);
    temp += element;
    if (!(temp == a)) {
        return error("%s : failed verify temp does not equal a", __func__);
    } else if (this->element != publicCoin) {
        return error("%s : failed verify pubcoins not equal", __func__);
    }

    return true;
=======
	return this->witness.getValue();
}

bool AccumulatorWitness::VerifyWitness(const Accumulator& a, const PublicCoin &publicCoin) const {
	Accumulator temp(witness);
	temp += element;
    // if (!(temp == a)) {
    //     std::cout << "VerifyWitness: failed verify temp does not equal a\n";
    //     return false;
    // } else if (this->element != publicCoin) {
    //     std::cout << "VerifyWitness: failed verify pubcoins not equal\n";
    //     return false;
    // }

	return true;
>>>>>>> Stashed changes
}

AccumulatorWitness& AccumulatorWitness::operator +=(
    const PublicCoin& rhs) {
<<<<<<< Updated upstream
    this->AddElement(rhs);
    return *this;
=======
	this->AddElement(rhs);
	return *this;
>>>>>>> Stashed changes
}

} /* namespace libzerocoin */
