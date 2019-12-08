<<<<<<< Updated upstream
// Copyright (c) 2019 The PIVX developers
=======
// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "openuridialog.h"
#include "ui_openuridialog.h"

#include "guiutil.h"
#include "walletmodel.h"
<<<<<<< Updated upstream
#include "qt/pivx/qtutils.h"

#include <QUrl>
#include <QFile>
=======

#include <QUrl>
>>>>>>> Stashed changes

OpenURIDialog::OpenURIDialog(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
                                                ui(new Ui::OpenURIDialog)
{
    ui->setupUi(this);
<<<<<<< Updated upstream
    this->setStyleSheet(parent->styleSheet());
    ui->uriEdit->setPlaceholderText("pivx:");

    ui->labelSubtitle->setText("URI");
    setCssProperty(ui->labelSubtitle, "text-title2-dialog");
    setCssProperty(ui->frame, "container-dialog");
    setCssProperty(ui->labelTitle, "text-title-dialog");

    setCssBtnPrimary(ui->pushButtonOK);
    setCssBtnPrimary(ui->selectFileButton);
    setCssProperty(ui->pushButtonCancel, "btn-dialog-cancel");

    initCssEditLine(ui->uriEdit, true);
    connect(ui->pushButtonOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void OpenURIDialog::showEvent(QShowEvent *event)
{
    ui->uriEdit->setFocus();
=======
    ui->uriEdit->setPlaceholderText("primestone:");
>>>>>>> Stashed changes
}

OpenURIDialog::~OpenURIDialog()
{
    delete ui;
}

QString OpenURIDialog::getURI()
{
    return ui->uriEdit->text();
}

void OpenURIDialog::accept()
{
    SendCoinsRecipient rcp;
    if (GUIUtil::parseBitcoinURI(getURI(), &rcp)) {
        /* Only accept value URIs */
        QDialog::accept();
    } else {
<<<<<<< Updated upstream
        setCssEditLineDialog(ui->uriEdit, false, true);
=======
        ui->uriEdit->setValid(false);
>>>>>>> Stashed changes
    }
}

void OpenURIDialog::on_selectFileButton_clicked()
{
    QString filename = GUIUtil::getOpenFileName(this, tr("Select payment request file to open"), "", "", NULL);
    if (filename.isEmpty())
        return;
<<<<<<< Updated upstream

    QFile file(filename);
    if(!file.exists()) {
        inform(tr("File not found"));
        return;
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray r = file.readAll();
        if (r.size() > 200) {
            inform(tr("Parsed data too large"));
            return;
        }

        QString str = QString::fromStdString(std::string(r.constData(), r.length()));
        if (!str.startsWith("pivx")) {
            inform(tr("Invalid URI, not starting with \"pivx\" prefix"));
        }
        ui->uriEdit->setText(str);
    }
}

void OpenURIDialog::inform(const QString& str) {
    if (!snackBar) snackBar = new SnackBar(nullptr, this);
    snackBar->setText(str);
    snackBar->resize(this->width(), snackBar->height());
    openDialog(snackBar, this);
}
=======
    QUrl fileUri = QUrl::fromLocalFile(filename);
    ui->uriEdit->setText("primestone:?r=" + QUrl::toPercentEncoding(fileUri.toString()));
}
>>>>>>> Stashed changes
