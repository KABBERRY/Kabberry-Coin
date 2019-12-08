// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2015-2017 The PIVX developers
<<<<<<< Updated upstream
=======
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "core_io.h"

#include "primitives/block.h"
#include "primitives/transaction.h"
#include "script/script.h"
#include "serialize.h"
#include "streams.h"
#include <univalue.h>
#include "util.h"
#include "utilstrencodings.h"
#include "version.h"

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/assign/list_of.hpp>

<<<<<<< Updated upstream
=======
using namespace boost;
using namespace boost::algorithm;
using namespace std;
>>>>>>> Stashed changes

CScript ParseScript(std::string s)
{
    CScript result;

<<<<<<< Updated upstream
    static std::map<std::string, opcodetype> mapOpNames;
=======
    static map<string, opcodetype> mapOpNames;
>>>>>>> Stashed changes

    if (mapOpNames.empty()) {
        for (int op = 0; op <= OP_ZEROCOINSPEND; op++) {
            // Allow OP_RESERVED to get into mapOpNames
            if (op < OP_NOP && op != OP_RESERVED)
                continue;

            const char* name = GetOpName((opcodetype)op);
            if (strcmp(name, "OP_UNKNOWN") == 0)
                continue;
<<<<<<< Updated upstream
            std::string strName(name);
            mapOpNames[strName] = (opcodetype)op;
            // Convenience: OP_ADD and just ADD are both recognized:
            boost::algorithm::replace_first(strName, "OP_", "");
=======
            string strName(name);
            mapOpNames[strName] = (opcodetype)op;
            // Convenience: OP_ADD and just ADD are both recognized:
            replace_first(strName, "OP_", "");
>>>>>>> Stashed changes
            mapOpNames[strName] = (opcodetype)op;
        }
    }

<<<<<<< Updated upstream
    std::vector<std::string> words;
    boost::algorithm::split(words, s, boost::algorithm::is_any_of(" \t\n"), boost::algorithm::token_compress_on);
=======
    vector<string> words;
    split(words, s, is_any_of(" \t\n"), token_compress_on);
>>>>>>> Stashed changes

    for (std::vector<std::string>::const_iterator w = words.begin(); w != words.end(); ++w) {
        if (w->empty()) {
            // Empty string, ignore. (boost::split given '' will return one word)
<<<<<<< Updated upstream
        } else if (all(*w, boost::algorithm::is_digit()) ||
                   (boost::algorithm::starts_with(*w, "-") && all(std::string(w->begin() + 1, w->end()), boost::algorithm::is_digit()))) {
            // Number
            int64_t n = atoi64(*w);
            result << n;
        } else if (boost::algorithm::starts_with(*w, "0x") && (w->begin() + 2 != w->end()) && IsHex(std::string(w->begin() + 2, w->end()))) {
            // Raw hex data, inserted NOT pushed onto stack:
            std::vector<unsigned char> raw = ParseHex(std::string(w->begin() + 2, w->end()));
            result.insert(result.end(), raw.begin(), raw.end());
        } else if (w->size() >= 2 && boost::algorithm::starts_with(*w, "'") && boost::algorithm::ends_with(*w, "'")) {
=======
        } else if (all(*w, is_digit()) ||
                   (starts_with(*w, "-") && all(string(w->begin() + 1, w->end()), is_digit()))) {
            // Number
            int64_t n = atoi64(*w);
            result << n;
        } else if (starts_with(*w, "0x") && (w->begin() + 2 != w->end()) && IsHex(string(w->begin() + 2, w->end()))) {
            // Raw hex data, inserted NOT pushed onto stack:
            std::vector<unsigned char> raw = ParseHex(string(w->begin() + 2, w->end()));
            result.insert(result.end(), raw.begin(), raw.end());
        } else if (w->size() >= 2 && starts_with(*w, "'") && ends_with(*w, "'")) {
>>>>>>> Stashed changes
            // Single-quoted string, pushed as data. NOTE: this is poor-man's
            // parsing, spaces/tabs/newlines in single-quoted strings won't work.
            std::vector<unsigned char> value(w->begin() + 1, w->end() - 1);
            result << value;
        } else if (mapOpNames.count(*w)) {
            // opcode, e.g. OP_ADD or ADD:
            result << mapOpNames[*w];
        } else {
<<<<<<< Updated upstream
            throw std::runtime_error("script parse error");
=======
            throw runtime_error("script parse error");
>>>>>>> Stashed changes
        }
    }

    return result;
}

bool DecodeHexTx(CTransaction& tx, const std::string& strHexTx)
{
    if (!IsHex(strHexTx))
        return false;

<<<<<<< Updated upstream
    std::vector<unsigned char> txData(ParseHex(strHexTx));
=======
    vector<unsigned char> txData(ParseHex(strHexTx));
>>>>>>> Stashed changes
    CDataStream ssData(txData, SER_NETWORK, PROTOCOL_VERSION);
    try {
        ssData >> tx;
    } catch (const std::exception&) {
        return false;
    }

    return true;
}

bool DecodeHexBlk(CBlock& block, const std::string& strHexBlk)
{
    if (!IsHex(strHexBlk))
        return false;

    std::vector<unsigned char> blockData(ParseHex(strHexBlk));
    CDataStream ssBlock(blockData, SER_NETWORK, PROTOCOL_VERSION);
    try {
        ssBlock >> block;
    } catch (const std::exception&) {
        return false;
    }

    return true;
}

<<<<<<< Updated upstream
uint256 ParseHashUV(const UniValue& v, const std::string& strName)
{
    std::string strHex;
    if (v.isStr())
        strHex = v.getValStr();
    return ParseHashStr(strHex, strName); // Note: ParseHashStr("") throws a std::runtime_error
=======
uint256 ParseHashUV(const UniValue& v, const string& strName)
{
    string strHex;
    if (v.isStr())
        strHex = v.getValStr();
    return ParseHashStr(strHex, strName); // Note: ParseHashStr("") throws a runtime_error
>>>>>>> Stashed changes
}

uint256 ParseHashStr(const std::string& strHex, const std::string& strName)
{
    if (!IsHex(strHex)) // Note: IsHex("") is false
<<<<<<< Updated upstream
        throw std::runtime_error(strName + " must be hexadecimal string (not '" + strHex + "')");
=======
        throw runtime_error(strName + " must be hexadecimal string (not '" + strHex + "')");
>>>>>>> Stashed changes

    uint256 result;
    result.SetHex(strHex);
    return result;
}

<<<<<<< Updated upstream
std::vector<unsigned char> ParseHexUV(const UniValue& v, const std::string& strName)
{
    std::string strHex;
    if (v.isStr())
        strHex = v.getValStr();
    if (!IsHex(strHex))
        throw std::runtime_error(strName + " must be hexadecimal string (not '" + strHex + "')");
=======
vector<unsigned char> ParseHexUV(const UniValue& v, const string& strName)
{
    string strHex;
    if (v.isStr())
        strHex = v.getValStr();
    if (!IsHex(strHex))
        throw runtime_error(strName + " must be hexadecimal string (not '" + strHex + "')");
>>>>>>> Stashed changes
    return ParseHex(strHex);
}
