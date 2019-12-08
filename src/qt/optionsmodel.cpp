// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
<<<<<<< Updated upstream
// Copyright (c) 2015-2019 The PIVX developers
=======
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#if defined(HAVE_CONFIG_H)
<<<<<<< Updated upstream
#include "config/pivx-config.h"
=======
#include "config/primestone-config.h"
>>>>>>> Stashed changes
#endif

#include "optionsmodel.h"

#include "bitcoinunits.h"
#include "guiutil.h"

#include "amount.h"
#include "init.h"
#include "main.h"
#include "net.h"
#include "txdb.h" // for -dbcache defaults
#include "util.h"

#ifdef ENABLE_WALLET
#include "masternodeconfig.h"
<<<<<<< Updated upstream
#include "wallet/wallet.h"
#include "wallet/walletdb.h"
#endif

#include <QNetworkProxy>
=======
#include "wallet.h"
#include "walletdb.h"
#endif

#include <QNetworkProxy>
#include <QSettings>
>>>>>>> Stashed changes
#include <QStringList>

OptionsModel::OptionsModel(QObject* parent) : QAbstractListModel(parent)
{
    Init();
}

void OptionsModel::addOverriddenOption(const std::string& option)
{
    strOverriddenByCommandLine += QString::fromStdString(option) + "=" + QString::fromStdString(mapArgs[option]) + " ";
}

// Writes all missing QSettings with their default values
void OptionsModel::Init()
{
    resetSettings = false;
    QSettings settings;

    // Ensure restart flag is unset on client startup
    setRestartRequired(false);

    // These are Qt-only settings:

    // Window
<<<<<<< Updated upstream
    setWindowDefaultOptions(settings);

    // Display
=======
    if (!settings.contains("fMinimizeToTray"))
        settings.setValue("fMinimizeToTray", false);
    fMinimizeToTray = settings.value("fMinimizeToTray").toBool();

    if (!settings.contains("fMinimizeOnClose"))
        settings.setValue("fMinimizeOnClose", false);
    fMinimizeOnClose = settings.value("fMinimizeOnClose").toBool();

    // Display
    if (!settings.contains("nDisplayUnit"))
        settings.setValue("nDisplayUnit", BitcoinUnits::PSC);
    nDisplayUnit = settings.value("nDisplayUnit").toInt();

    if (!settings.contains("strThirdPartyTxUrls"))
        settings.setValue("strThirdPartyTxUrls", "");
    strThirdPartyTxUrls = settings.value("strThirdPartyTxUrls", "").toString();

>>>>>>> Stashed changes
    if (!settings.contains("fHideZeroBalances"))
        settings.setValue("fHideZeroBalances", true);
    fHideZeroBalances = settings.value("fHideZeroBalances").toBool();

<<<<<<< Updated upstream
    if (!settings.contains("fHideOrphans"))
        settings.setValue("fHideOrphans", true);
    fHideOrphans = settings.value("fHideOrphans").toBool();

=======
>>>>>>> Stashed changes
    if (!settings.contains("fCoinControlFeatures"))
        settings.setValue("fCoinControlFeatures", false);
    fCoinControlFeatures = settings.value("fCoinControlFeatures", false).toBool();

<<<<<<< Updated upstream
    if (!settings.contains("fShowColdStakingScreen"))
        settings.setValue("fShowColdStakingScreen", false);
    showColdStakingScreen = settings.value("fShowColdStakingScreen", false).toBool();

    if (!settings.contains("fZeromintEnable"))
        settings.setValue("fZeromintEnable", true);
    fEnableZeromint = settings.value("fZeromintEnable").toBool();

    if (!settings.contains("fEnableAutoConvert"))
        settings.setValue("fEnableAutoConvert", true);
    fEnableAutoConvert = settings.value("fEnableAutoConvert").toBool();

=======
    // if (!settings.contains("fZeromintEnable"))
        settings.setValue("fZeromintEnable", false);
    fEnableZeromint = settings.value("fZeromintEnable").toBool();
    
>>>>>>> Stashed changes
    if (!settings.contains("nZeromintPercentage"))
        settings.setValue("nZeromintPercentage", 10);
    nZeromintPercentage = settings.value("nZeromintPercentage").toLongLong();

    if (!settings.contains("nPreferredDenom"))
        settings.setValue("nPreferredDenom", 0);
    nPreferredDenom = settings.value("nPreferredDenom", "0").toLongLong();

<<<<<<< Updated upstream
    if (!settings.contains("fShowMasternodesTab"))
        settings.setValue("fShowMasternodesTab", masternodeConfig.getCount());

    // Main
    setMainDefaultOptions(settings);

// Wallet
#ifdef ENABLE_WALLET
    setWalletDefaultOptions(settings);
#endif

    // Network
    setNetworkDefaultOptions(settings);
    // Display
    setDisplayDefaultOptions(settings);

    language = settings.value("language").toString();
}

void OptionsModel::refreshDataView(){
    emit dataChanged(index(0), index(rowCount(QModelIndex()) - 1));
}

void OptionsModel::setMainDefaultOptions(QSettings& settings, bool reset){
=======
    if (!settings.contains("nAnonymizePrimeStoneAmount"))
        settings.setValue("nAnonymizePrimeStoneAmount", 1000);

    nAnonymizePrimeStoneAmount = settings.value("nAnonymizePrimeStoneAmount").toLongLong();

    if (!settings.contains("fShowMasternodesTab"))
        settings.setValue("fShowMasternodesTab", masternodeConfig.getCount());

>>>>>>> Stashed changes
    // These are shared with the core or have a command-line parameter
    // and we want command-line parameters to overwrite the GUI settings.
    //
    // If setting doesn't exist create it with defaults.
    //
    // If SoftSetArg() or SoftSetBoolArg() return false we were overridden
    // by command-line and show this in the UI.
<<<<<<< Updated upstream
    // Main
    if (!settings.contains("nDatabaseCache") || reset)
=======

    // Main
    if (!settings.contains("nDatabaseCache"))
>>>>>>> Stashed changes
        settings.setValue("nDatabaseCache", (qint64)nDefaultDbCache);
    if (!SoftSetArg("-dbcache", settings.value("nDatabaseCache").toString().toStdString()))
        addOverriddenOption("-dbcache");

<<<<<<< Updated upstream
    if (!settings.contains("nThreadsScriptVerif") || reset)
=======
    if (!settings.contains("nThreadsScriptVerif"))
>>>>>>> Stashed changes
        settings.setValue("nThreadsScriptVerif", DEFAULT_SCRIPTCHECK_THREADS);
    if (!SoftSetArg("-par", settings.value("nThreadsScriptVerif").toString().toStdString()))
        addOverriddenOption("-par");

<<<<<<< Updated upstream
    if(reset){
        refreshDataView();
    }
}

void OptionsModel::setWalletDefaultOptions(QSettings& settings, bool reset){
    if (!settings.contains("bSpendZeroConfChange") || reset)
        settings.setValue("bSpendZeroConfChange", false);
    if (!SoftSetBoolArg("-spendzeroconfchange", settings.value("bSpendZeroConfChange").toBool()))
        addOverriddenOption("-spendzeroconfchange");

    if (!settings.contains("nStakeSplitThreshold") || reset)
        settings.setValue("nStakeSplitThreshold", CWallet::STAKE_SPLIT_THRESHOLD);

    if (reset){
        setStakeSplitThreshold(CWallet::STAKE_SPLIT_THRESHOLD);
        refreshDataView();
    }
}

void OptionsModel::setNetworkDefaultOptions(QSettings& settings, bool reset){
    if (!settings.contains("fUseUPnP") || reset)
=======
// Wallet
#ifdef ENABLE_WALLET
    if (!settings.contains("bSpendZeroConfChange"))
        settings.setValue("bSpendZeroConfChange", false);
    if (!SoftSetBoolArg("-spendzeroconfchange", settings.value("bSpendZeroConfChange").toBool()))
        addOverriddenOption("-spendzeroconfchange");
#endif
    if (!settings.contains("nStakeSplitThreshold"))
        settings.setValue("nStakeSplitThreshold", 1);


    // Network
    if (!settings.contains("fUseUPnP"))
>>>>>>> Stashed changes
        settings.setValue("fUseUPnP", DEFAULT_UPNP);
    if (!SoftSetBoolArg("-upnp", settings.value("fUseUPnP").toBool()))
        addOverriddenOption("-upnp");

<<<<<<< Updated upstream
    if (!settings.contains("fListen") || reset)
=======
    if (!settings.contains("fListen"))
>>>>>>> Stashed changes
        settings.setValue("fListen", DEFAULT_LISTEN);
    if (!SoftSetBoolArg("-listen", settings.value("fListen").toBool()))
        addOverriddenOption("-listen");

<<<<<<< Updated upstream
    if (!settings.contains("fUseProxy") || reset)
        settings.setValue("fUseProxy", false);
    if (!settings.contains("addrProxy") || reset)
=======
    if (!settings.contains("fUseProxy"))
        settings.setValue("fUseProxy", false);
    if (!settings.contains("addrProxy"))
>>>>>>> Stashed changes
        settings.setValue("addrProxy", "127.0.0.1:9050");
    // Only try to set -proxy, if user has enabled fUseProxy
    if (settings.value("fUseProxy").toBool() && !SoftSetArg("-proxy", settings.value("addrProxy").toString().toStdString()))
        addOverriddenOption("-proxy");
    else if (!settings.value("fUseProxy").toBool() && !GetArg("-proxy", "").empty())
        addOverriddenOption("-proxy");

<<<<<<< Updated upstream
    if(reset){
        refreshDataView();
    }
}

void OptionsModel::setWindowDefaultOptions(QSettings& settings, bool reset){
    if (!settings.contains("fMinimizeToTray") || reset)
        settings.setValue("fMinimizeToTray", false);
    fMinimizeToTray = settings.value("fMinimizeToTray").toBool();

    if (!settings.contains("fMinimizeOnClose") || reset)
        settings.setValue("fMinimizeOnClose", false);
    fMinimizeOnClose = settings.value("fMinimizeOnClose").toBool();

    if(reset){
        refreshDataView();
    }
}

void OptionsModel::setDisplayDefaultOptions(QSettings& settings, bool reset){
    if (!settings.contains("nDisplayUnit") || reset)
        settings.setValue("nDisplayUnit", BitcoinUnits::PIV);
    nDisplayUnit = settings.value("nDisplayUnit").toInt();
    if (!settings.contains("digits") || reset)
        settings.setValue("digits", "2");
    if (!settings.contains("theme") || reset)
        settings.setValue("theme", "");
    if (!settings.contains("fCSSexternal") || reset)
        settings.setValue("fCSSexternal", false);
    if (!settings.contains("language") || reset)
=======
    // Display
    if (!settings.contains("digits"))
        settings.setValue("digits", "2");
    if (!settings.contains("theme"))
        settings.setValue("theme", "");
    if (!settings.contains("fCSSexternal"))
        settings.setValue("fCSSexternal", false);
    if (!settings.contains("language"))
>>>>>>> Stashed changes
        settings.setValue("language", "");
    if (!SoftSetArg("-lang", settings.value("language").toString().toStdString()))
        addOverriddenOption("-lang");

<<<<<<< Updated upstream
    if (settings.contains("fZeromintEnable") || reset)
        SoftSetBoolArg("-enablezeromint", settings.value("fZeromintEnable").toBool());
    if (settings.contains("fEnableAutoConvert") || reset)
        SoftSetBoolArg("-enableautoconvertaddress", settings.value("fEnableAutoConvert").toBool());
    if (settings.contains("nZeromintPercentage") || reset)
        SoftSetArg("-zeromintpercentage", settings.value("nZeromintPercentage").toString().toStdString());
    if (settings.contains("nPreferredDenom") || reset)
        SoftSetArg("-preferredDenom", settings.value("nPreferredDenom").toString().toStdString());
    if (settings.contains("nAnonymizePivxAmount") || reset)
        SoftSetArg("-anonymizepivxamount", settings.value("nAnonymizePivxAmount").toString().toStdString());

    if (!settings.contains("strThirdPartyTxUrls") || reset)
        settings.setValue("strThirdPartyTxUrls", "");
    strThirdPartyTxUrls = settings.value("strThirdPartyTxUrls", "").toString();

    if(reset){
        refreshDataView();
    }
=======
    if (settings.contains("fZeromintEnable"))
        SoftSetBoolArg("-enablezeromint", settings.value("fZeromintEnable").toBool());
    if (settings.contains("nZeromintPercentage"))
        SoftSetArg("-zeromintpercentage", settings.value("nZeromintPercentage").toString().toStdString());
    if (settings.contains("nPreferredDenom"))
        SoftSetArg("-preferredDenom", settings.value("nPreferredDenom").toString().toStdString());
    if (settings.contains("nAnonymizePrimeStoneAmount"))
        SoftSetArg("-anonymizeprimestoneamount", settings.value("nAnonymizePrimeStoneAmount").toString().toStdString());

    language = settings.value("language").toString();
>>>>>>> Stashed changes
}

void OptionsModel::Reset()
{
    QSettings settings;

    // Remove all entries from our QSettings object
    settings.clear();
<<<<<<< Updated upstream
    resetSettings = true; // Needed in pivx.cpp during shotdown to also remove the window positions
=======
    resetSettings = true; // Needed in primestone.cpp during shotdown to also remove the window positions
>>>>>>> Stashed changes

    // default setting for OptionsModel::StartAtStartup - disabled
    if (GUIUtil::GetStartOnSystemStartup())
        GUIUtil::SetStartOnSystemStartup(false);
}

int OptionsModel::rowCount(const QModelIndex& parent) const
{
    return OptionIDRowCount;
}

// read QSettings values and return them
QVariant OptionsModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::EditRole) {
        QSettings settings;
        switch (index.row()) {
        case StartAtStartup:
            return GUIUtil::GetStartOnSystemStartup();
        case MinimizeToTray:
            return fMinimizeToTray;
        case MapPortUPnP:
#ifdef USE_UPNP
            return settings.value("fUseUPnP");
#else
            return false;
#endif
        case MinimizeOnClose:
            return fMinimizeOnClose;

        // default proxy
        case ProxyUse:
            return settings.value("fUseProxy", false);
        case ProxyIP: {
            // contains IP at index 0 and port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            return strlIpPort.at(0);
        }
        case ProxyPort: {
            // contains IP at index 0 and port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            return strlIpPort.at(1);
        }

#ifdef ENABLE_WALLET
        case SpendZeroConfChange:
            return settings.value("bSpendZeroConfChange");
        case ShowMasternodesTab:
            return settings.value("fShowMasternodesTab");
#endif
        case StakeSplitThreshold:
            if (pwalletMain)
                return QVariant((int)pwalletMain->nStakeSplitThreshold);
            return settings.value("nStakeSplitThreshold");
        case DisplayUnit:

            return nDisplayUnit;
        case ThirdPartyTxUrls:
            return strThirdPartyTxUrls;
        case Digits:
            return settings.value("digits");
        case Theme:
            return settings.value("theme");
        case Language:
            return settings.value("language");
        case CoinControlFeatures:
            return fCoinControlFeatures;
<<<<<<< Updated upstream
        case ShowColdStakingScreen:
            return showColdStakingScreen;
=======
>>>>>>> Stashed changes
        case DatabaseCache:
            return settings.value("nDatabaseCache");
        case ThreadsScriptVerif:
            return settings.value("nThreadsScriptVerif");
        case HideZeroBalances:
            return settings.value("fHideZeroBalances");
<<<<<<< Updated upstream
        case HideOrphans:
            return settings.value("fHideOrphans");
        case ZeromintEnable:
            return QVariant(fEnableZeromint);
        case ZeromintAddresses:
            return QVariant(fEnableAutoConvert);
=======
        case ZeromintEnable:
            return QVariant(fEnableZeromint);
>>>>>>> Stashed changes
        case ZeromintPercentage:
            return QVariant(nZeromintPercentage);
        case ZeromintPrefDenom:
            return QVariant(nPreferredDenom);
<<<<<<< Updated upstream
=======
        case AnonymizePrimeStoneAmount:
            return QVariant(nAnonymizePrimeStoneAmount);
>>>>>>> Stashed changes
        case Listen:
            return settings.value("fListen");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

// write QSettings values
bool OptionsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    bool successful = true; /* set to false on parse error */
    if (role == Qt::EditRole) {
        QSettings settings;
        switch (index.row()) {
        case StartAtStartup:
            successful = GUIUtil::SetStartOnSystemStartup(value.toBool());
            break;
        case MinimizeToTray:
            fMinimizeToTray = value.toBool();
            settings.setValue("fMinimizeToTray", fMinimizeToTray);
            break;
        case MapPortUPnP: // core option - can be changed on-the-fly
            settings.setValue("fUseUPnP", value.toBool());
            MapPort(value.toBool());
            break;
        case MinimizeOnClose:
            fMinimizeOnClose = value.toBool();
            settings.setValue("fMinimizeOnClose", fMinimizeOnClose);
            break;

        // default proxy
        case ProxyUse:
            if (settings.value("fUseProxy") != value) {
                settings.setValue("fUseProxy", value.toBool());
                setRestartRequired(true);
            }
            break;
        case ProxyIP: {
            // contains current IP at index 0 and current port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            // if that key doesn't exist or has a changed IP
            if (!settings.contains("addrProxy") || strlIpPort.at(0) != value.toString()) {
                // construct new value from new IP and current port
                QString strNewValue = value.toString() + ":" + strlIpPort.at(1);
                settings.setValue("addrProxy", strNewValue);
                setRestartRequired(true);
            }
        } break;
        case ProxyPort: {
            // contains current IP at index 0 and current port at index 1
            QStringList strlIpPort = settings.value("addrProxy").toString().split(":", QString::SkipEmptyParts);
            // if that key doesn't exist or has a changed port
            if (!settings.contains("addrProxy") || strlIpPort.at(1) != value.toString()) {
                // construct new value from current IP and new port
                QString strNewValue = strlIpPort.at(0) + ":" + value.toString();
                settings.setValue("addrProxy", strNewValue);
                setRestartRequired(true);
            }
        } break;
#ifdef ENABLE_WALLET
        case SpendZeroConfChange:
            if (settings.value("bSpendZeroConfChange") != value) {
                settings.setValue("bSpendZeroConfChange", value);
                setRestartRequired(true);
            }
            break;
        case ShowMasternodesTab:
            if (settings.value("fShowMasternodesTab") != value) {
                settings.setValue("fShowMasternodesTab", value);
                setRestartRequired(true);
            }
            break;
#endif
        case StakeSplitThreshold:
            settings.setValue("nStakeSplitThreshold", value.toInt());
            setStakeSplitThreshold(value.toInt());
            break;
        case DisplayUnit:
            setDisplayUnit(value);
            break;
        case ThirdPartyTxUrls:
            if (strThirdPartyTxUrls != value.toString()) {
                strThirdPartyTxUrls = value.toString();
                settings.setValue("strThirdPartyTxUrls", strThirdPartyTxUrls);
                setRestartRequired(true);
            }
            break;
        case Digits:
            if (settings.value("digits") != value) {
                settings.setValue("digits", value);
                setRestartRequired(true);
            }
            break;
        case Theme:
            if (settings.value("theme") != value) {
                settings.setValue("theme", value);
                setRestartRequired(true);
            }
            break;
        case Language:
            if (settings.value("language") != value) {
                settings.setValue("language", value);
                setRestartRequired(true);
            }
            break;
        case ZeromintEnable:
            fEnableZeromint = value.toBool();
            settings.setValue("fZeromintEnable", fEnableZeromint);
            emit zeromintEnableChanged(fEnableZeromint);
            break;
<<<<<<< Updated upstream
        case ZeromintAddresses:
            fEnableAutoConvert = value.toBool();
            settings.setValue("fEnableAutoConvert", fEnableAutoConvert);
            emit zeromintAddressesChanged(fEnableAutoConvert);
=======
>>>>>>> Stashed changes
        case ZeromintPercentage:
            nZeromintPercentage = value.toInt();
            settings.setValue("nZeromintPercentage", nZeromintPercentage);
            emit zeromintPercentageChanged(nZeromintPercentage);
            break;
        case ZeromintPrefDenom:
            nPreferredDenom = value.toInt();
            settings.setValue("nPreferredDenom", nPreferredDenom);
            emit preferredDenomChanged(nPreferredDenom);
            break;
        case HideZeroBalances:
            fHideZeroBalances = value.toBool();
            settings.setValue("fHideZeroBalances", fHideZeroBalances);
            emit hideZeroBalancesChanged(fHideZeroBalances);
            break;
<<<<<<< Updated upstream
        case HideOrphans:
            fHideOrphans = value.toBool();
            settings.setValue("fHideOrphans", fHideOrphans);
            emit hideOrphansChanged(fHideOrphans);
=======

        case AnonymizePrimeStoneAmount:
            nAnonymizePrimeStoneAmount = value.toInt();
            settings.setValue("nAnonymizePrimeStoneAmount", nAnonymizePrimeStoneAmount);
            emit anonymizePrimeStoneAmountChanged(nAnonymizePrimeStoneAmount);
>>>>>>> Stashed changes
            break;
        case CoinControlFeatures:
            fCoinControlFeatures = value.toBool();
            settings.setValue("fCoinControlFeatures", fCoinControlFeatures);
            emit coinControlFeaturesChanged(fCoinControlFeatures);
            break;
<<<<<<< Updated upstream
        case ShowColdStakingScreen:
            this->showColdStakingScreen = value.toBool();
            settings.setValue("fShowColdStakingScreen", this->showColdStakingScreen);
            emit showHideColdStakingScreen(this->showColdStakingScreen);
            break;
=======
>>>>>>> Stashed changes
        case DatabaseCache:
            if (settings.value("nDatabaseCache") != value) {
                settings.setValue("nDatabaseCache", value);
                setRestartRequired(true);
            }
            break;
        case ThreadsScriptVerif:
            if (settings.value("nThreadsScriptVerif") != value) {
                settings.setValue("nThreadsScriptVerif", value);
                setRestartRequired(true);
            }
            break;
        case Listen:
            if (settings.value("fListen") != value) {
                settings.setValue("fListen", value);
                setRestartRequired(true);
            }
            break;
        default:
            break;
        }
    }

    emit dataChanged(index, index);

    return successful;
}

/** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
void OptionsModel::setDisplayUnit(const QVariant& value)
{
    if (!value.isNull()) {
        QSettings settings;
        nDisplayUnit = value.toInt();
        settings.setValue("nDisplayUnit", nDisplayUnit);
        emit displayUnitChanged(nDisplayUnit);
    }
}

/* Update StakeSplitThreshold's value in wallet */
void OptionsModel::setStakeSplitThreshold(int value)
{
    // XXX: maybe it's worth to wrap related stuff with WALLET_ENABLE ?
    uint64_t nStakeSplitThreshold;

    nStakeSplitThreshold = value;
    if (pwalletMain && pwalletMain->nStakeSplitThreshold != nStakeSplitThreshold) {
        CWalletDB walletdb(pwalletMain->strWalletFile);
        LOCK(pwalletMain->cs_wallet);
        {
            pwalletMain->nStakeSplitThreshold = nStakeSplitThreshold;
            if (pwalletMain->fFileBacked)
                walletdb.WriteStakeSplitThreshold(nStakeSplitThreshold);
        }
    }
}


bool OptionsModel::getProxySettings(QNetworkProxy& proxy) const
{
    // Directly query current base proxy, because
    // GUI settings can be overridden with -proxy.
    proxyType curProxy;
    if (GetProxy(NET_IPV4, curProxy)) {
        proxy.setType(QNetworkProxy::Socks5Proxy);
        proxy.setHostName(QString::fromStdString(curProxy.proxy.ToStringIP()));
        proxy.setPort(curProxy.proxy.GetPort());

        return true;
    } else
        proxy.setType(QNetworkProxy::NoProxy);

    return false;
}

void OptionsModel::setRestartRequired(bool fRequired)
{
    QSettings settings;
    return settings.setValue("fRestartRequired", fRequired);
}

bool OptionsModel::isRestartRequired()
{
    QSettings settings;
    return settings.value("fRestartRequired", false).toBool();
}
