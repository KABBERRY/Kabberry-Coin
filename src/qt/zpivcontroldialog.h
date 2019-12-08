// Copyright (c) 2017-2018 The PIVX developers
<<<<<<< Updated upstream
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZPIVCONTROLDIALOG_H
#define ZPIVCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zpiv/zerocoin.h"
=======
// Copyright (c) 2018-2019 The PrimeStone developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef zPSCCONTROLDIALOG_H
#define zPSCCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "primitives/zerocoin.h"
#include "privacydialog.h"
>>>>>>> Stashed changes

class CZerocoinMint;
class WalletModel;

namespace Ui {
<<<<<<< Updated upstream
class ZPivControlDialog;
}

class CZPivControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZPivControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZPivControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZPivControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZPivControlDialog : public QDialog
=======
class zPSCControlDialog;
}

class zPSCControlDialog : public QDialog
>>>>>>> Stashed changes
{
    Q_OBJECT

public:
<<<<<<< Updated upstream
    explicit ZPivControlDialog(QWidget *parent);
    ~ZPivControlDialog();
=======
    explicit zPSCControlDialog(QWidget *parent);
    ~zPSCControlDialog();
>>>>>>> Stashed changes

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
<<<<<<< Updated upstream
    Ui::ZPivControlDialog *ui;
    WalletModel* model;
=======
    Ui::zPSCControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;
>>>>>>> Stashed changes

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
<<<<<<< Updated upstream
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZPivControlWidgetItem;
=======
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
>>>>>>> Stashed changes

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

<<<<<<< Updated upstream
#endif // ZPIVCONTROLDIALOG_H
=======
#endif // zPSCCONTROLDIALOG_H
>>>>>>> Stashed changes
