// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2017-2018 The PIVX developers
<<<<<<< Updated upstream
=======
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_ASKPASSPHRASEDIALOG_H
#define BITCOIN_QT_ASKPASSPHRASEDIALOG_H

#include <QDialog>
<<<<<<< Updated upstream
#include "qt/pivx/prunnable.h"
#include "allocators.h"
#include <QCheckBox>

class WalletModel;
class PIVXGUI;
=======

class WalletModel;
>>>>>>> Stashed changes

namespace Ui
{
class AskPassphraseDialog;
<<<<<<< Updated upstream
class QCheckBox;
=======
>>>>>>> Stashed changes
}

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
<<<<<<< Updated upstream
class AskPassphraseDialog : public QDialog, public Runnable
=======
class AskPassphraseDialog : public QDialog
>>>>>>> Stashed changes
{
    Q_OBJECT

public:
    enum class Mode {
        Encrypt,         /**< Ask passphrase twice and encrypt */
        UnlockAnonymize, /**< Ask passphrase and unlock only for anonymization */
        Unlock,          /**< Ask passphrase and unlock */
        ChangePass,      /**< Ask old passphrase + new passphrase twice */
        Decrypt          /**< Ask passphrase and decrypt wallet */
    };

    // Context from where / for what the passphrase dialog was called to set the status of the checkbox
    // Partly redundant to Mode above, but offers more flexibility for future enhancements
    enum class Context {
        Unlock_Menu,    /** Unlock wallet from menu     */
        Unlock_Full,    /** Wallet needs to be fully unlocked */
        Encrypt,        /** Encrypt unencrypted wallet */
        ToggleLock,     /** Toggle wallet lock state */
        ChangePass,     /** Change passphrase */
<<<<<<< Updated upstream
        Send_PIV,       /** Send PIV */
        Send_zPIV,      /** Send zPIV */
        Mint_zPIV,      /** Mint zPIV */
        BIP_38,         /** BIP38 menu */
        Multi_Sig,      /** Multi-Signature dialog */
        Sign_Message,   /** Sign/verify message dialog */
        UI_Vote,        /** Governance Tab UI Voting */
=======
        Send_PrimeStone,       /** Send PrimeStone */
        Send_zPSC,      /** Send zPSC */
        Mint_zPSC,      /** Mint zPSC */
        BIP_38,         /** BIP38 menu */
        Multi_Sig,      /** Multi-Signature dialog */
        Sign_Message    /** Sign/verify message dialog */
>>>>>>> Stashed changes
    };

    explicit AskPassphraseDialog(Mode mode, QWidget* parent, WalletModel* model, Context context);
    ~AskPassphraseDialog();

<<<<<<< Updated upstream
    void showEvent(QShowEvent *event) override;
    void accept() override;
=======
    void accept();
>>>>>>> Stashed changes

private:
    Ui::AskPassphraseDialog* ui;
    Mode mode;
    WalletModel* model;
    Context context;
    bool fCapsLock;
<<<<<<< Updated upstream
    SecureString newpassCache = "";

    void run(int type) override;
    void onError(QString error, int type) override;
    QCheckBox *btnWatch;

    void initWatch(QWidget *parent);

private slots:
    void onWatchClicked();
    void textChanged();
    void warningMessage();
    void errorEncryptingWallet();
    bool openStandardDialog(QString title = "", QString body = "", QString okBtn = "OK", QString cancelBtn = "");

protected:
    bool event(QEvent* event) override ;
    bool eventFilter(QObject* object, QEvent* event) override;
=======

private slots:
    void textChanged();

protected:
    bool event(QEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
>>>>>>> Stashed changes
};

#endif // BITCOIN_QT_ASKPASSPHRASEDIALOG_H
