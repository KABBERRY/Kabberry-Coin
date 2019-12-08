<<<<<<< Updated upstream
// Copyright (c) 2017-2019 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "zpivcontroldialog.h"
#include "ui_zpivcontroldialog.h"

#include "zpiv/accumulators.h"
#include "main.h"
#include "walletmodel.h"
#include "guiutil.h"


std::set<std::string> ZPivControlDialog::setSelectedMints;
std::set<CMintMeta> ZPivControlDialog::setMints;

bool CZPivControlWidgetItem::operator<(const QTreeWidgetItem &other) const {
    int column = treeWidget()->sortColumn();
    if (column == ZPivControlDialog::COLUMN_DENOMINATION || column == ZPivControlDialog::COLUMN_VERSION || column == ZPivControlDialog::COLUMN_CONFIRMATIONS)
        return data(column, Qt::UserRole).toLongLong() < other.data(column, Qt::UserRole).toLongLong();
    return QTreeWidgetItem::operator<(other);
}


ZPivControlDialog::ZPivControlDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::ZPivControlDialog),
=======
// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "zPSCcontroldialog.h"
#include "ui_zPSCcontroldialog.h"

#include "accumulators.h"
#include "main.h"
#include "walletmodel.h"

using namespace std;
using namespace libzerocoin;

std::set<std::string> zPSCControlDialog::setSelectedMints;
std::set<CMintMeta> zPSCControlDialog::setMints;

zPSCControlDialog::zPSCControlDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::zPSCControlDialog),
>>>>>>> Stashed changes
    model(0)
{
    ui->setupUi(this);
    setMints.clear();
<<<<<<< Updated upstream

    /* Open CSS when configured */
    this->setStyleSheet(GUIUtil::loadStyleSheet());

    ui->frame->setProperty("cssClass", "container-dialog");

    // Title
    ui->labelTitle->setText(tr("Select zPIV Denominations to Spend"));
    ui->labelTitle->setProperty("cssClass", "text-title-dialog");


    // Label Style
    ui->labelZPiv->setProperty("cssClass", "text-main-purple");
    ui->labelZPiv_int->setProperty("cssClass", "text-main-purple");
    ui->labelQuantity->setProperty("cssClass", "text-main-purple");
    ui->labelQuantity_int->setProperty("cssClass", "text-main-purple");

    ui->layoutAmount->setProperty("cssClass", "container-border-purple");
    ui->layoutQuantity->setProperty("cssClass", "container-border-purple");

    // Buttons

    ui->btnEsc->setText("");
    ui->btnEsc->setProperty("cssClass", "ic-close");
    ui->pushButtonAll->setProperty("cssClass", "btn-check");

    // click on checkbox
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(updateSelection(QTreeWidgetItem*, int)));
=======
    privacyDialog = (PrivacyDialog*)parent;

    // click on checkbox
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(updateSelection(QTreeWidgetItem*, int)));

>>>>>>> Stashed changes
    // push select/deselect all button
    connect(ui->pushButtonAll, SIGNAL(clicked()), this, SLOT(ButtonAllClicked()));
}

<<<<<<< Updated upstream
ZPivControlDialog::~ZPivControlDialog()
=======
zPSCControlDialog::~zPSCControlDialog()
>>>>>>> Stashed changes
{
    delete ui;
}

<<<<<<< Updated upstream
void ZPivControlDialog::setModel(WalletModel *model)
=======
void zPSCControlDialog::setModel(WalletModel *model)
>>>>>>> Stashed changes
{
    this->model = model;
    updateList();
}

<<<<<<< Updated upstream

//Update the tree widget
void ZPivControlDialog::updateList()
=======
//Update the tree widget
void zPSCControlDialog::updateList()
>>>>>>> Stashed changes
{
    // need to prevent the slot from being called each time something is changed
    ui->treeWidget->blockSignals(true);
    ui->treeWidget->clear();

    // add a top level item for each denomination
    QFlags<Qt::ItemFlag> flgTristate = Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsTristate;
<<<<<<< Updated upstream
    std::map<libzerocoin::CoinDenomination, int> mapDenomPosition;
    for (auto denom : libzerocoin::zerocoinDenomList) {
        CZPivControlWidgetItem* itemDenom(new CZPivControlWidgetItem);
=======
    map<libzerocoin::CoinDenomination, int> mapDenomPosition;
    for (auto denom : libzerocoin::zerocoinDenomList) {
        QTreeWidgetItem* itemDenom(new QTreeWidgetItem);
>>>>>>> Stashed changes
        ui->treeWidget->addTopLevelItem(itemDenom);

        //keep track of where this is positioned in tree widget
        mapDenomPosition[denom] = ui->treeWidget->indexOfTopLevelItem(itemDenom);

        itemDenom->setFlags(flgTristate);
        itemDenom->setText(COLUMN_DENOMINATION, QString::number(denom));
<<<<<<< Updated upstream
        itemDenom->setData(COLUMN_DENOMINATION, Qt::UserRole, QVariant((qlonglong) denom));
    }

    // select all unused coins - including not mature and mismatching seed. Update status of coins too.
    std::set<CMintMeta> set;
    model->listZerocoinMints(set, true, false, true, true);
=======
    }

    // select all unused coins - including not mature. Update status of coins too.
    std::set<CMintMeta> set;
    model->listZerocoinMints(set, true, false, true);
>>>>>>> Stashed changes
    this->setMints = set;

    //populate rows with mint info
    int nBestHeight = chainActive.Height();
<<<<<<< Updated upstream
    //map<CoinDenomination, int> mapMaturityHeight = GetMintMaturityHeight();
    for (const CMintMeta& mint : setMints) {
        // assign this mint to the correct denomination in the tree view
        libzerocoin::CoinDenomination denom = mint.denom;
        CZPivControlWidgetItem *itemMint = new CZPivControlWidgetItem(ui->treeWidget->topLevelItem(mapDenomPosition.at(denom)));
=======
    map<CoinDenomination, int> mapMaturityHeight = GetMintMaturityHeight();
    for (const CMintMeta& mint : setMints) {
        // assign this mint to the correct denomination in the tree view
        libzerocoin::CoinDenomination denom = mint.denom;
        QTreeWidgetItem *itemMint = new QTreeWidgetItem(ui->treeWidget->topLevelItem(mapDenomPosition.at(denom)));
>>>>>>> Stashed changes

        // if the mint is already selected, then it needs to have the checkbox checked
        std::string strPubCoinHash = mint.hashPubcoin.GetHex();

        if (setSelectedMints.count(strPubCoinHash))
            itemMint->setCheckState(COLUMN_CHECKBOX, Qt::Checked);
        else
            itemMint->setCheckState(COLUMN_CHECKBOX, Qt::Unchecked);

        itemMint->setText(COLUMN_DENOMINATION, QString::number(mint.denom));
<<<<<<< Updated upstream
        itemMint->setData(COLUMN_DENOMINATION, Qt::UserRole, QVariant((qlonglong) denom));
        itemMint->setText(COLUMN_PUBCOIN, QString::fromStdString(strPubCoinHash));
        itemMint->setText(COLUMN_VERSION, QString::number(mint.nVersion));
        itemMint->setData(COLUMN_VERSION, Qt::UserRole, QVariant((qlonglong) mint.nVersion));
=======
        itemMint->setText(COLUMN_PUBCOIN, QString::fromStdString(strPubCoinHash));
        itemMint->setText(COLUMN_VERSION, QString::number(mint.nVersion));
>>>>>>> Stashed changes

        int nConfirmations = (mint.nHeight ? nBestHeight - mint.nHeight : 0);
        if (nConfirmations < 0) {
            // Sanity check
            nConfirmations = 0;
        }

        itemMint->setText(COLUMN_CONFIRMATIONS, QString::number(nConfirmations));
<<<<<<< Updated upstream
        itemMint->setData(COLUMN_CONFIRMATIONS, Qt::UserRole, QVariant((qlonglong) nConfirmations));

        {
            LOCK(pwalletMain->zpivTracker->cs_spendcache);

            CoinWitnessData *witnessData = pwalletMain->zpivTracker->GetSpendCache(mint.hashStake);
            if (witnessData->nHeightAccStart > 0  && witnessData->nHeightAccEnd > 0) {
                int nPercent = std::max(0, std::min(100, (int)((double)(witnessData->nHeightAccEnd - witnessData->nHeightAccStart) / (double)(nBestHeight - witnessData->nHeightAccStart - 220) * 100)));
                QString percent = QString::number(nPercent) + QString("%");
                itemMint->setText(COLUMN_PRECOMPUTE, percent);
            } else {
                itemMint->setText(COLUMN_PRECOMPUTE, QString("0%"));
            }
        }

        // check for maturity
        // Always mature, public spends doesn't require any new accumulation.
        bool isMature = true;
        //if (mapMaturityHeight.count(mint.denom))
        //    isMature = mint.nHeight < mapMaturityHeight.at(denom);

        // disable selecting this mint if it is not spendable - also display a reason why
        bool fSpendable = isMature && nConfirmations >= Params().Zerocoin_MintRequiredConfirmations() && mint.isSeedCorrect;
=======

        // check for maturity
        bool isMature = false;
        if (mapMaturityHeight.count(mint.denom))
            isMature = mint.nHeight < mapMaturityHeight.at(denom);

        // disable selecting this mint if it is not spendable - also display a reason why
        bool fSpendable = isMature && nConfirmations >= Params().Zerocoin_MintRequiredConfirmations();
>>>>>>> Stashed changes
        if(!fSpendable) {
            itemMint->setDisabled(true);
            itemMint->setCheckState(COLUMN_CHECKBOX, Qt::Unchecked);

            //if this mint is in the selection list, then remove it
            if (setSelectedMints.count(strPubCoinHash))
                setSelectedMints.erase(strPubCoinHash);

<<<<<<< Updated upstream
            std::string strReason = "";
            if(nConfirmations < Params().Zerocoin_MintRequiredConfirmations())
                strReason = strprintf("Needs %d more confirmations", Params().Zerocoin_MintRequiredConfirmations() - nConfirmations);
            else if (model->getEncryptionStatus() == WalletModel::EncryptionStatus::Locked)
                strReason = "Your wallet is locked. Impossible to precompute or spend zPIV.";
            else if (!mint.isSeedCorrect)
                strReason = "The zPIV seed used to mint this zPIV is not the same as currently hold in the wallet";
=======
            string strReason = "";
            if(nConfirmations < Params().Zerocoin_MintRequiredConfirmations())
                strReason = strprintf("Needs %d more confirmations", Params().Zerocoin_MintRequiredConfirmations() - nConfirmations);
            else if (model->getEncryptionStatus() == WalletModel::EncryptionStatus::Locked)
                strReason = "Your wallet is locked. Impossible to precompute or spend coin.";
            else if (!mint.isSeedCorrect)
                strReason = "The seed used to mint this is not the same as currently hold in the wallet";
>>>>>>> Stashed changes
            else
                strReason = strprintf("Needs %d more mints added to network", Params().Zerocoin_RequiredAccumulation());

            itemMint->setText(COLUMN_ISSPENDABLE, QString::fromStdString(strReason));
        } else {
            itemMint->setText(COLUMN_ISSPENDABLE, QString("Yes"));
        }
    }

    ui->treeWidget->blockSignals(false);
    updateLabels();
}

// Update the list when a checkbox is clicked
<<<<<<< Updated upstream
void ZPivControlDialog::updateSelection(QTreeWidgetItem* item, int column)
=======
void zPSCControlDialog::updateSelection(QTreeWidgetItem* item, int column)
>>>>>>> Stashed changes
{
    // only want updates from non top level items that are available to spend
    if (item->parent() && column == COLUMN_CHECKBOX && !item->isDisabled()){

        // see if this mint is already selected in the selection list
        std::string strPubcoin = item->text(COLUMN_PUBCOIN).toStdString();
        bool fSelected = setSelectedMints.count(strPubcoin);

        // set the checkbox to the proper state and add or remove the mint from the selection list
        if (item->checkState(COLUMN_CHECKBOX) == Qt::Checked) {
            if (fSelected) return;
            setSelectedMints.insert(strPubcoin);
        } else {
            if (!fSelected) return;
            setSelectedMints.erase(strPubcoin);
        }
        updateLabels();
    }
}

// Update the Quantity and Amount display
<<<<<<< Updated upstream
void ZPivControlDialog::updateLabels()
=======
void zPSCControlDialog::updateLabels()
>>>>>>> Stashed changes
{
    int64_t nAmount = 0;
    for (const CMintMeta& mint : setMints) {
        if (setSelectedMints.count(mint.hashPubcoin.GetHex()))
            nAmount += mint.denom;
    }

    //update this dialog's labels
<<<<<<< Updated upstream
    ui->labelZPiv_int->setText(QString::number(nAmount));
    ui->labelQuantity_int->setText(QString::number(setSelectedMints.size()));

    //update PrivacyDialog labels
    //privacyDialog->setZPivControlLabels(nAmount, setSelectedMints.size());
}

std::vector<CMintMeta> ZPivControlDialog::GetSelectedMints()
=======
    ui->labelzPSC_int->setText(QString::number(nAmount));
    ui->labelQuantity_int->setText(QString::number(setSelectedMints.size()));

    //update PrivacyDialog labels
    //privacyDialog->setzPSCControlLabels(nAmount, setSelectedMints.size());
}

std::vector<CMintMeta> zPSCControlDialog::GetSelectedMints()
>>>>>>> Stashed changes
{
    std::vector<CMintMeta> listReturn;
    for (const CMintMeta& mint : setMints) {
        if (setSelectedMints.count(mint.hashPubcoin.GetHex()))
            listReturn.emplace_back(mint);
    }

    return listReturn;
}

// select or deselect all of the mints
<<<<<<< Updated upstream
void ZPivControlDialog::ButtonAllClicked()
=======
void zPSCControlDialog::ButtonAllClicked()
>>>>>>> Stashed changes
{
    ui->treeWidget->blockSignals(true);
    Qt::CheckState state = Qt::Checked;
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); i++) {
        if(ui->treeWidget->topLevelItem(i)->checkState(COLUMN_CHECKBOX) != Qt::Unchecked) {
            state = Qt::Unchecked;
            break;
        }
    }

    //much quicker to start from scratch than to have QT go through all the objects and update
    ui->treeWidget->clear();

    if (state == Qt::Checked) {
        for(const CMintMeta& mint : setMints)
            setSelectedMints.insert(mint.hashPubcoin.GetHex());
    } else {
        setSelectedMints.clear();
    }

    updateList();
}
