// Copyright (c) 2011-2014 The Bitcoin developers
<<<<<<< Updated upstream
// Copyright (c) 2017-2018 The PIVX developers
=======
// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_UTILITYDIALOG_H
#define BITCOIN_QT_UTILITYDIALOG_H

#include <QDialog>
#include <QObject>
<<<<<<< Updated upstream
#include <QMainWindow>

=======

class BitcoinGUI;
>>>>>>> Stashed changes
class ClientModel;

namespace Ui
{
class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget* parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog* ui;
    QString text;
<<<<<<< Updated upstream
=======

private slots:
    void on_okButton_accepted();
>>>>>>> Stashed changes
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    ShutdownWindow(QWidget* parent = 0, Qt::WindowFlags f = 0);
<<<<<<< Updated upstream
    static void showShutdownWindow(QMainWindow* window);
=======
    static void showShutdownWindow(BitcoinGUI* window);
>>>>>>> Stashed changes

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // BITCOIN_QT_UTILITYDIALOG_H
