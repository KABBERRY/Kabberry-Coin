// Copyright (c) 2019 The PIVX developers
// Copyright (c) 2019-2020 The Kabberry developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLKKCWIDGET_H
#define COINCONTROLKKCWIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlKKCWidget;
}

class CoinControlKKCWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlKKCWidget(QWidget *parent = nullptr);
    ~CoinControlKKCWidget();

private:
    Ui::CoinControlKKCWidget *ui;
};

#endif // COINCONTROLKKCWIDGET_H
