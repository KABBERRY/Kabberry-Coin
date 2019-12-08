// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
<<<<<<< Updated upstream
// Copyright (c) 2015-2019 The PIVX developers
=======
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Server/client environment: argument handling, config file parsing,
 * logging, thread wrappers
 */
#ifndef BITCOIN_UTIL_H
#define BITCOIN_UTIL_H

#if defined(HAVE_CONFIG_H)
<<<<<<< Updated upstream
#include "config/pivx-config.h"
=======
#include "config/primestone-config.h"
>>>>>>> Stashed changes
#endif

#include "compat.h"
#include "tinyformat.h"
#include "utiltime.h"

#include <exception>
#include <map>
#include <stdint.h>
#include <string>
#include <vector>

#include <boost/filesystem/path.hpp>
#include <boost/thread/exceptions.hpp>
<<<<<<< Updated upstream
#include <boost/thread/condition_variable.hpp> // for boost::thread_interrupted

//PIVX only features
=======

//PrimeStone only features
>>>>>>> Stashed changes

extern bool fMasterNode;
extern bool fLiteMode;
extern bool fEnableSwiftTX;
extern int nSwiftTXDepth;
extern int nZeromintPercentage;
extern const int64_t AUTOMINT_DELAY;
extern int nPreferredDenom;
<<<<<<< Updated upstream
extern bool fEnableZeromint;
extern bool fEnableAutoConvert;
=======
extern int nAnonymizePrimeStoneAmount;
extern int nLiquidityProvider;
extern bool fEnableZeromint;
>>>>>>> Stashed changes
extern int64_t enforceMasternodePaymentsTime;
extern std::string strMasterNodeAddr;
extern int keysLoaded;
extern bool fSucessfullyLoaded;
extern std::vector<int64_t> obfuScationDenominations;
extern std::string strBudgetMode;

extern std::map<std::string, std::string> mapArgs;
extern std::map<std::string, std::vector<std::string> > mapMultiArgs;
extern bool fDebug;
extern bool fPrintToConsole;
extern bool fPrintToDebugLog;
<<<<<<< Updated upstream
=======
extern bool fServer;
>>>>>>> Stashed changes
extern std::string strMiscWarning;
extern bool fLogTimestamps;
extern bool fLogIPs;
extern volatile bool fReopenDebugLog;

void SetupEnvironment();
bool SetupNetworking();

/** Return true if log accepts specified category */
bool LogAcceptCategory(const char* category);
/** Send a string to the log output */
int LogPrintStr(const std::string& str);

#define LogPrintf(...) LogPrint(NULL, __VA_ARGS__)

<<<<<<< Updated upstream
/** Get format string from VA_ARGS for error reporting */
template<typename... Args> std::string FormatStringFromLogArgs(const char *fmt, const Args&... args) { return fmt; }

=======
>>>>>>> Stashed changes
/**
 * When we switch to C++11, this can be switched to variadic templates instead
 * of this macro-based construction (see tinyformat.h).
 */
#define MAKE_ERROR_AND_LOG_FUNC(n)                                                              \
    /**   Print to debug.log if -debug=category switch is given OR category is NULL. */         \
    template <TINYFORMAT_ARGTYPES(n)>                                                           \
    static inline int LogPrint(const char* category, const char* format, TINYFORMAT_VARARGS(n)) \
    {                                                                                           \
        if (!LogAcceptCategory(category)) return 0;                                             \
<<<<<<< Updated upstream
        std::string _log_msg_; /* Unlikely name to avoid shadowing variables */                 \
        try {                                                                                   \
            _log_msg_ = tfm::format(format, TINYFORMAT_PASSARGS(n));                            \
        } catch (std::runtime_error &e) {                                                       \
            _log_msg_ = "Error \"" + std::string(e.what()) + "\" while formatting log message: " + FormatStringFromLogArgs(format, TINYFORMAT_PASSARGS(n));\
        }                                                                                       \
        return LogPrintStr(_log_msg_);                                                          \
=======
        return LogPrintStr(tfm::format(format, TINYFORMAT_PASSARGS(n)));                        \
>>>>>>> Stashed changes
    }                                                                                           \
    /**   Log error and return false */                                                         \
    template <TINYFORMAT_ARGTYPES(n)>                                                           \
    static inline bool error(const char* format, TINYFORMAT_VARARGS(n))                         \
    {                                                                                           \
<<<<<<< Updated upstream
        std::string _log_msg_; /* Unlikely name to avoid shadowing variables */                 \
        try {                                                                                   \
            _log_msg_ = tfm::format(format, TINYFORMAT_PASSARGS(n));                            \
        } catch (std::runtime_error &e) {                                                       \
            _log_msg_ = "Error \"" + std::string(e.what()) + "\" while formatting log message: " + FormatStringFromLogArgs(format, TINYFORMAT_PASSARGS(n));\
        }                                                                                       \
        LogPrintStr(std::string("ERROR: ") + _log_msg_ + "\n");                                 \
=======
        LogPrintStr(std::string("ERROR: ") + tfm::format(format, TINYFORMAT_PASSARGS(n)) + "\n");            \
>>>>>>> Stashed changes
        return false;                                                                           \
    }

TINYFORMAT_FOREACH_ARGNUM(MAKE_ERROR_AND_LOG_FUNC)

/**
 * Zero-arg versions of logging and error, these are not covered by
 * TINYFORMAT_FOREACH_ARGNUM
 */
static inline int LogPrint(const char* category, const char* format)
{
    if (!LogAcceptCategory(category)) return 0;
    return LogPrintStr(format);
}
static inline bool error(const char* format)
{
    LogPrintStr(std::string("ERROR: ") + format + "\n");
    return false;
}

double double_safe_addition(double fValue, double fIncrement);
double double_safe_multiplication(double fValue, double fmultiplicator);
<<<<<<< Updated upstream
void PrintExceptionContinue(const std::exception* pex, const char* pszThread);
=======
void PrintExceptionContinue(std::exception* pex, const char* pszThread);
>>>>>>> Stashed changes
void ParseParameters(int argc, const char* const argv[]);
void FileCommit(FILE* fileout);
bool TruncateFile(FILE* file, unsigned int length);
int RaiseFileDescriptorLimit(int nMinFD);
void AllocateFileRange(FILE* file, unsigned int offset, unsigned int length);
bool RenameOver(boost::filesystem::path src, boost::filesystem::path dest);
bool TryCreateDirectory(const boost::filesystem::path& p);
boost::filesystem::path GetDefaultDataDir();
<<<<<<< Updated upstream
const boost::filesystem::path &GetDataDir(bool fNetSpecific = true);
void ClearDatadirCache();
=======
const boost::filesystem::path& GetDataDir(bool fNetSpecific = true);
>>>>>>> Stashed changes
boost::filesystem::path GetConfigFile();
boost::filesystem::path GetMasternodeConfigFile();
#ifndef WIN32
boost::filesystem::path GetPidFile();
void CreatePidFile(const boost::filesystem::path& path, pid_t pid);
#endif
void ReadConfigFile(std::map<std::string, std::string>& mapSettingsRet, std::map<std::string, std::vector<std::string> >& mapMultiSettingsRet);
#ifdef WIN32
boost::filesystem::path GetSpecialFolderPath(int nFolder, bool fCreate = true);
#endif
boost::filesystem::path GetTempPath();
void ShrinkDebugFile();
void runCommand(std::string strCommand);

inline bool IsSwitchChar(char c)
{
#ifdef WIN32
    return c == '-' || c == '/';
#else
    return c == '-';
#endif
}

/**
 * Return string argument or default value
 *
 * @param strArg Argument to get (e.g. "-foo")
 * @param default (e.g. "1")
 * @return command-line argument or default value
 */
std::string GetArg(const std::string& strArg, const std::string& strDefault);

/**
 * Return integer argument or default value
 *
 * @param strArg Argument to get (e.g. "-foo")
 * @param default (e.g. 1)
 * @return command-line argument (0 if invalid number) or default value
 */
int64_t GetArg(const std::string& strArg, int64_t nDefault);

/**
 * Return boolean argument or default value
 *
 * @param strArg Argument to get (e.g. "-foo")
 * @param default (true or false)
 * @return command-line argument or default value
 */
bool GetBoolArg(const std::string& strArg, bool fDefault);

/**
 * Set an argument if it doesn't already have a value
 *
 * @param strArg Argument to set (e.g. "-foo")
 * @param strValue Value (e.g. "1")
 * @return true if argument gets set, false if it already had a value
 */
bool SoftSetArg(const std::string& strArg, const std::string& strValue);

/**
 * Set a boolean argument if it doesn't already have a value
 *
 * @param strArg Argument to set (e.g. "-foo")
 * @param fValue Value (e.g. false)
 * @return true if argument gets set, false if it already had a value
 */
bool SoftSetBoolArg(const std::string& strArg, bool fValue);

/**
 * Format a string to be used as group of options in help messages
 *
 * @param message Group name (e.g. "RPC server options:")
 * @return the formatted string
 */
std::string HelpMessageGroup(const std::string& message);

/**
 * Format a string to be used as option description in help messages
 *
 * @param option Option message (e.g. "-rpcuser=<user>")
 * @param message Option description (e.g. "Username for JSON-RPC connections")
 * @return the formatted string
 */
std::string HelpMessageOpt(const std::string& option, const std::string& message);

void SetThreadPriority(int nPriority);
void RenameThread(const char* name);

/**
 * .. and a wrapper that just calls func once
 */
template <typename Callable>
void TraceThread(const char* name, Callable func)
{
<<<<<<< Updated upstream
    std::string s = strprintf("pivx-%s", name);
=======
    std::string s = strprintf("primestone-%s", name);
>>>>>>> Stashed changes
    RenameThread(s.c_str());
    try {
        LogPrintf("%s thread start\n", name);
        func();
        LogPrintf("%s thread exit\n", name);
    } catch (boost::thread_interrupted) {
        LogPrintf("%s thread interrupt\n", name);
        throw;
    } catch (std::exception& e) {
        PrintExceptionContinue(&e, name);
        throw;
    } catch (...) {
        PrintExceptionContinue(NULL, name);
        throw;
    }
}

#endif // BITCOIN_UTIL_H
