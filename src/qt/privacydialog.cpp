// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "privacydialog.h"
#include "ui_privacydialog.h"

#include "addressbookpage.h"
#include "addresstablemodel.h"
#include "bitcoinunits.h"
#include "coincontroldialog.h"
#include "libzerocoin/Denominations.h"
#include "optionsmodel.h"
#include "sendcoinsentry.h"
#include "walletmodel.h"
#include "coincontrol.h"
#include "zPSCcontroldialog.h"
#include "spork.h"
#include "askpassphrasedialog.h"

#include <QClipboard>
#include <QSettings>
#include <utilmoneystr.h>
#include <QtWidgets>
#include <primitives/deterministicmint.h>
#include <accumulators.h>
#include <QDesktopServices>
#include <QUrl>
PrivacyDialog::PrivacyDialog(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint | Qt::WindowCloseButtonHint),
                                                          ui(new Ui::PrivacyDialog),
                                                          walletModel(0)
                                                        
{
    ui->setupUi(this);
    #ifndef Q_OS_MAC
    /*ui->officialWebsiteButton->setIcon(QIcon(":/icons/Manuals_icon"));
    ui->mnVPSButton->setIcon(QIcon(":/icons/Manuals_icon"));
    ui->mnWindowsButton->setIcon(QIcon(":/icons/Manuals_icon"));
    ui->coinmarketcapButton->setIcon(QIcon(":/icons/Manuals_icon"));
    ui->DiscordButton->setIcon(QIcon(":/icons/Manuals_icon"));
    ui->GithubButton->setIcon(QIcon(":/icons/Manuals_icon"));
    */
    ui->officialWebsiteButton->setIcon(QIcon(":/icons/Manuals_icon.png"));
    ui->mnVPSButton->setIcon(QIcon(":/icons/Manuals_icon.png"));
    ui->mnWindowsButton->setIcon(QIcon());
    ui->coinmarketcapButton->setIcon(QIcon());
    ui->DiscordButton->setIcon(QIcon());
    ui->GithubButton->setIcon(QIcon());
    #endif
    //this->setStyleSheet("{background-image: url(:/src/qt/res/images/walletFrame_bg.png);}");
    //QIcon(":/icons/receiving_addresses")
}
void PrivacyDialog::setModel(WalletModel* walletModel)
{
    this->walletModel = walletModel;

}

void PrivacyDialog::on_officialWebsiteButton_clicked()
{
    QString link = "https://primestone.global/primestone-cryptocurrency-wallet-platform/";
    QDesktopServices::openUrl(QUrl(link));
}
void PrivacyDialog::on_mnVPSButton_clicked()
{
    QString link = "https://primestone.global/wp-content/uploads/2018/11/Masternode_VPS-ENG.pdf";
    QDesktopServices::openUrl(QUrl(link));
}
void PrivacyDialog::on_mnWindowsButton_clicked()
{
    QString link = "https://primestone.global/wp-content/uploads/2018/08/MasterNode-ENG.pdf";
    QDesktopServices::openUrl(QUrl(link));
}
void PrivacyDialog::on_coinmarketcapButton_clicked()
{
    QString link = "https://coinmarketcap.com/currencies/primestone";
    QDesktopServices::openUrl(QUrl(link));
}
void PrivacyDialog::on_DiscordButton_clicked()
{
    QString link = "https://discord.gg/rjyTX7g";
    QDesktopServices::openUrl(QUrl(link));
}
void PrivacyDialog::on_GithubButton_clicked()
{
    QString link = "https://github.com/Primestonecoin";
    QDesktopServices::openUrl(QUrl(link));
}

PrivacyDialog::~PrivacyDialog()
{
    delete ui;
}
