// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_PRIVACYDIALOG_H
#define BITCOIN_QT_PRIVACYDIALOG_H

#include "guiutil.h"

#include <QDialog>
#include <QHeaderView>
#include <QItemSelection>
#include <QKeyEvent>
#include <QMenu>
#include <QPoint>
#include <QTimer>
#include <QVariant>

class OptionsModel;
class WalletModel;

namespace Ui
{
class PrivacyDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog for requesting payment of bitcoins */
class PrivacyDialog : public QDialog
{
    Q_OBJECT

public:
 
    explicit PrivacyDialog(QWidget* parent = 0);
    ~PrivacyDialog();

    void setModel(WalletModel* model);
    
 private:
    Ui::PrivacyDialog* ui;
    QTimer* timer;
    GUIUtil::TableViewLastColumnResizingFixer* columnResizingFixer;
    WalletModel* walletModel;
    QMenu* contextMenu;
private slots:
    void on_officialWebsiteButton_clicked();   
    void on_mnVPSButton_clicked();   
    void on_mnWindowsButton_clicked();   
    void on_coinmarketcapButton_clicked();   
    void on_DiscordButton_clicked();   
    void on_GithubButton_clicked();   
};

#endif // BITCOIN_QT_PRIVACYDIALOG_H
