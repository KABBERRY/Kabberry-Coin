// Copyright (c) 2011-2013 The Bitcoin developers
<<<<<<< Updated upstream
// Copyright (c) 2017-2019 The PIVX developers
=======
// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPTIONSMODEL_H
#define BITCOIN_QT_OPTIONSMODEL_H

#include "amount.h"

#include <QAbstractListModel>
<<<<<<< Updated upstream
#include <QSettings>
=======
>>>>>>> Stashed changes

QT_BEGIN_NAMESPACE
class QNetworkProxy;
QT_END_NAMESPACE

<<<<<<< Updated upstream
/** Interface from Qt to configuration data structure for PIVX client.
=======
/** Interface from Qt to configuration data structure for Bitcoin client.
>>>>>>> Stashed changes
   To Qt, the options are presented as a list with the different options
   laid out vertically.
   This can be changed to a tree once the settings become sufficiently
   complex.
 */
class OptionsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit OptionsModel(QObject* parent = 0);

    enum OptionID {
        StartAtStartup,      // bool
        MinimizeToTray,      // bool
        MapPortUPnP,         // bool
        MinimizeOnClose,     // bool
        ProxyUse,            // bool
        ProxyIP,             // QString
        ProxyPort,           // int
        DisplayUnit,         // BitcoinUnits::Unit
        ThirdPartyTxUrls,    // QString
        Digits,              // QString
        Theme,               // QString
        Language,            // QString
        CoinControlFeatures, // bool
        ThreadsScriptVerif,  // int
        DatabaseCache,       // int
        SpendZeroConfChange, // bool
        ZeromintEnable,      // bool
<<<<<<< Updated upstream
        ZeromintAddresses,   // bool
        ZeromintPercentage,  // int
        ZeromintPrefDenom,   // int
        HideZeroBalances,    // bool
        HideOrphans,    // bool
        AnonymizePivxAmount, //int
        ShowMasternodesTab,  // bool
        Listen,              // bool
        StakeSplitThreshold, // int
        ShowColdStakingScreen, // bool
=======
        ZeromintPercentage,  // int
        ZeromintPrefDenom,   // int
        HideZeroBalances,    // bool
        AnonymizePrimeStoneAmount, //int
        ShowMasternodesTab,  // bool
        Listen,              // bool
        StakeSplitThreshold, // int
>>>>>>> Stashed changes
        OptionIDRowCount,
    };

    void Init();
    void Reset();

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
<<<<<<< Updated upstream
    void refreshDataView();
=======
>>>>>>> Stashed changes
    /** Updates current unit in memory, settings and emits displayUnitChanged(newUnit) signal */
    void setDisplayUnit(const QVariant& value);
    /* Update StakeSplitThreshold's value in wallet */
    void setStakeSplitThreshold(int value);

    /* Explicit getters */
    bool getMinimizeToTray() { return fMinimizeToTray; }
    bool getMinimizeOnClose() { return fMinimizeOnClose; }
    int getDisplayUnit() { return nDisplayUnit; }
    QString getThirdPartyTxUrls() { return strThirdPartyTxUrls; }
    bool getProxySettings(QNetworkProxy& proxy) const;
    bool getCoinControlFeatures() { return fCoinControlFeatures; }
    const QString& getOverriddenByCommandLine() { return strOverriddenByCommandLine; }

    /* Restart flag helper */
    void setRestartRequired(bool fRequired);
    bool isRestartRequired();
    bool resetSettings;

<<<<<<< Updated upstream
    bool isColdStakingScreenEnabled() { return showColdStakingScreen; }
    bool invertColdStakingScreenStatus() {
        setData(
                createIndex(ShowColdStakingScreen, 0),
                !isColdStakingScreenEnabled(),
                Qt::EditRole
        );
        return showColdStakingScreen;
    }

    // Reset
    void setMainDefaultOptions(QSettings& settings, bool reset = false);
    void setWalletDefaultOptions(QSettings& settings, bool reset = false);
    void setNetworkDefaultOptions(QSettings& settings, bool reset = false);
    void setWindowDefaultOptions(QSettings& settings, bool reset = false);
    void setDisplayDefaultOptions(QSettings& settings, bool reset = false);

=======
>>>>>>> Stashed changes
private:
    /* Qt-only settings */
    bool fMinimizeToTray;
    bool fMinimizeOnClose;
    QString language;
    int nDisplayUnit;
    QString strThirdPartyTxUrls;
    bool fCoinControlFeatures;
<<<<<<< Updated upstream
    bool showColdStakingScreen;
    bool fHideZeroBalances;
    bool fHideOrphans;
=======
    bool fHideZeroBalances;
>>>>>>> Stashed changes
    /* settings that were overriden by command-line */
    QString strOverriddenByCommandLine;

    /// Add option to list of GUI options overridden through command line/config file
    void addOverriddenOption(const std::string& option);

signals:
    void displayUnitChanged(int unit);
    void zeromintEnableChanged(bool);
<<<<<<< Updated upstream
    void zeromintAddressesChanged(bool);
    void zeromintPercentageChanged(int);
    void preferredDenomChanged(int);
    void anonymizePivxAmountChanged(int);
    void coinControlFeaturesChanged(bool);
    void showHideColdStakingScreen(bool);
    void hideZeroBalancesChanged(bool);
    void hideOrphansChanged(bool);
=======
    void zeromintPercentageChanged(int);
    void preferredDenomChanged(int);
    void anonymizePrimeStoneAmountChanged(int);
    void coinControlFeaturesChanged(bool);
    void hideZeroBalancesChanged(bool);
>>>>>>> Stashed changes
};

#endif // BITCOIN_QT_OPTIONSMODEL_H
