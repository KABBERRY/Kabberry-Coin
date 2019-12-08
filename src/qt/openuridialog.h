<<<<<<< Updated upstream
// Copyright (c) 2019 The PIVX developers
=======
// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OPENURIDIALOG_H
#define BITCOIN_QT_OPENURIDIALOG_H

#include <QDialog>
<<<<<<< Updated upstream
#include "qt/pivx/snackbar.h"
=======
>>>>>>> Stashed changes

namespace Ui
{
class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(QWidget* parent);
    ~OpenURIDialog();

    QString getURI();
<<<<<<< Updated upstream
    void showEvent(QShowEvent *event) override;

protected slots:
    void accept() override;
=======

protected slots:
    void accept();
>>>>>>> Stashed changes

private slots:
    void on_selectFileButton_clicked();

private:
    Ui::OpenURIDialog* ui;
<<<<<<< Updated upstream
    SnackBar *snackBar = nullptr;
    void inform(const QString& str);
=======
>>>>>>> Stashed changes
};

#endif // BITCOIN_QT_OPENURIDIALOG_H
