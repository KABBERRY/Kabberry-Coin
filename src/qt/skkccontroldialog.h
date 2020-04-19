// Copyright (c) 2017-2020 The PIVX developers
// Copyright (c) 2018-2020 The Kabberry developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef sKKCCONTROLDIALOG_H
#define sKKCCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "skkc/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class sKKCControlDialog;
}

class CsKKCControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CsKKCControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CsKKCControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CsKKCControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class sKKCControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sKKCControlDialog(QWidget *parent);
    ~sKKCControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::sKKCControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CsKKCControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // sKKCCONTROLDIALOG_H
