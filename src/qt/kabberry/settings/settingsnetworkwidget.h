// Copyright (c) 2019 The PIVX developers
// Copyright (c) 2019-2020 The Kabberry developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SETTINGSNETWORKWIDGET_H
#define SETTINGSNETWORKWIDGET_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "qt/kabberry/pwidget.h"

namespace Ui {
class SettingsNetworkWidget;
}

class SettingsNetworkWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsNetworkWidget(KabberryGUI* _window, QWidget *parent = nullptr);
    ~SettingsNetworkWidget();

    void setMapper(QDataWidgetMapper *mapper);

private:
    Ui::SettingsNetworkWidget *ui;
};

#endif // SETTINGSNETWORKWIDGET_H
