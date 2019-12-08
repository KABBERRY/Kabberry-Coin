// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
<<<<<<< Updated upstream
// Copyright (c) 2017-2018 The PIVX developers
=======
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_INIT_H
#define BITCOIN_INIT_H

#include <string>

class CScheduler;
class CWallet;
<<<<<<< Updated upstream
class CzPIVWallet;
=======
class CzPSCWallet;
>>>>>>> Stashed changes

namespace boost
{
class thread_group;
} // namespace boost

extern CWallet* pwalletMain;
<<<<<<< Updated upstream
extern CzPIVWallet* zwalletMain;
=======
extern CzPSCWallet* zwalletMain;
>>>>>>> Stashed changes

void StartShutdown();
bool ShutdownRequested();
/** Interrupt threads */
<<<<<<< Updated upstream
void Interrupt();
void Shutdown();
void PrepareShutdown();
bool AppInit2();

/** Initialize PIVX core: Basic context setup.
 *  @note This can be done before daemonization. Do not call Shutdown() if this function fails.
 *  @pre Parameters should be parsed and config file should be read.
 */
bool AppInitBasicSetup();
=======
void Interrupt(boost::thread_group& threadGroup);
void Shutdown();
void PrepareShutdown();
bool AppInit2(boost::thread_group& threadGroup, CScheduler& scheduler);
>>>>>>> Stashed changes

/** The help message mode determines what help message to show */
enum HelpMessageMode {
    HMM_BITCOIND,
    HMM_BITCOIN_QT
};

/** Help for options shared between UI and daemon (for -help) */
std::string HelpMessage(HelpMessageMode mode);
/** Returns licensing information (for -version) */
std::string LicenseInfo();

#endif // BITCOIN_INIT_H
