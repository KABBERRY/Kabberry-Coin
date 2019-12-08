// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
<<<<<<< Updated upstream
// Copyright (c) 2015-2018 The PIVX developers
=======
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The PrimeStone developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "intro.h"
#include "ui_intro.h"

#include "guiutil.h"

#include "util.h"
<<<<<<< Updated upstream
#include "qt/pivx/qtutils.h"
=======
>>>>>>> Stashed changes

#include <boost/filesystem.hpp>

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

/* Minimum free space (in bytes) needed for data directory */
static const uint64_t GB_BYTES = 1000000000LL;
static const uint64_t BLOCK_CHAIN_SIZE = 1LL * GB_BYTES;

/* Check free space asynchronously to prevent hanging the UI thread.

   Up to one request to check a path is in flight to this thread; when the check()
   function runs, the current path is requested from the associated Intro object.
   The reply is sent back through a signal.

   This ensures that no queue of checking requests is built up while the user is
   still entering the path, and that always the most recently entered path is checked as
   soon as the thread becomes available.
*/
class FreespaceChecker : public QObject
{
    Q_OBJECT

public:
    FreespaceChecker(Intro* intro);

    enum Status {
        ST_OK,
        ST_ERROR
    };

public slots:
    void check();

signals:
    void reply(int status, const QString& message, quint64 available);

private:
    Intro* intro;
};

#include "intro.moc"

FreespaceChecker::FreespaceChecker(Intro* intro)
{
    this->intro = intro;
}

void FreespaceChecker::check()
{
    namespace fs = boost::filesystem;
    QString dataDirStr = intro->getPathToCheck();
    fs::path dataDir = GUIUtil::qstringToBoostPath(dataDirStr);
    uint64_t freeBytesAvailable = 0;
    int replyStatus = ST_OK;
    QString replyMessage = tr("A new data directory will be created.");

    /* Find first parent that exists, so that fs::space does not fail */
    fs::path parentDir = dataDir;
    fs::path parentDirOld = fs::path();
    while (parentDir.has_parent_path() && !fs::exists(parentDir)) {
        parentDir = parentDir.parent_path();

        /* Check if we make any progress, break if not to prevent an infinite loop here */
        if (parentDirOld == parentDir)
            break;

        parentDirOld = parentDir;
    }

    try {
        freeBytesAvailable = fs::space(parentDir).available;
        if (fs::exists(dataDir)) {
            if (fs::is_directory(dataDir)) {
                QString separator = "<code>" + QDir::toNativeSeparators("/") + tr("name") + "</code>";
                replyStatus = ST_OK;
                replyMessage = tr("Directory already exists. Add %1 if you intend to create a new directory here.").arg(separator);
            } else {
                replyStatus = ST_ERROR;
                replyMessage = tr("Path already exists, and is not a directory.");
            }
        }
<<<<<<< Updated upstream
    } catch (const fs::filesystem_error& e) {
=======
    } catch (fs::filesystem_error& e) {
>>>>>>> Stashed changes
        /* Parent directory does not exist or is not accessible */
        replyStatus = ST_ERROR;
        replyMessage = tr("Cannot create data directory here.");
    }
    emit reply(replyStatus, replyMessage, freeBytesAvailable);
}


Intro::Intro(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
                                ui(new Ui::Intro),
                                thread(0),
                                signalled(false)
{
    ui->setupUi(this);
<<<<<<< Updated upstream
    this->setStyleSheet(GUIUtil::loadStyleSheet());

    setCssProperty(ui->frame, "container-welcome-step2");
    setCssProperty(ui->container, "container-welcome-stack");
    setCssProperty(ui->frame_2, "container-welcome");
    setCssProperty(ui->label_2, "text-title-welcome");
    setCssProperty(ui->label_4, "text-intro-white");
    setCssProperty(ui->sizeWarningLabel, "text-intro-white");
    setCssProperty(ui->freeSpace, "text-intro-white");
    setCssProperty(ui->errorMessage, "text-intro-white");

    setCssProperty({ui->dataDirDefault, ui->dataDirCustom}, "radio-welcome");
    setCssProperty(ui->dataDirectory, "edit-primary-welcome");
    ui->dataDirectory->setAttribute(Qt::WA_MacShowFocusRect, 0);
    setCssProperty(ui->ellipsisButton, "btn-dots-welcome");
    setCssBtnPrimary(ui->pushButtonOk);
    setCssBtnSecondary(ui->pushButtonCancel);

    connect(ui->pushButtonOk, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->pushButtonCancel, SIGNAL(clicked()), this, SLOT(close()));

=======
>>>>>>> Stashed changes
    ui->sizeWarningLabel->setText(ui->sizeWarningLabel->text().arg(BLOCK_CHAIN_SIZE / GB_BYTES));
    startThread();
}

Intro::~Intro()
{
    delete ui;
    /* Ensure thread is finished before it is deleted */
    emit stopThread();
    thread->wait();
}

QString Intro::getDataDirectory()
{
    return ui->dataDirectory->text();
}

void Intro::setDataDirectory(const QString& dataDir)
{
    ui->dataDirectory->setText(dataDir);
    if (dataDir == getDefaultDataDirectory()) {
        ui->dataDirDefault->setChecked(true);
        ui->dataDirectory->setEnabled(false);
        ui->ellipsisButton->setEnabled(false);
<<<<<<< Updated upstream
        updateDataDirStatus(false);
=======
>>>>>>> Stashed changes
    } else {
        ui->dataDirCustom->setChecked(true);
        ui->dataDirectory->setEnabled(true);
        ui->ellipsisButton->setEnabled(true);
<<<<<<< Updated upstream
        updateDataDirStatus(true);
=======
>>>>>>> Stashed changes
    }
}

QString Intro::getDefaultDataDirectory()
{
    return GUIUtil::boostPathToQString(GetDefaultDataDir());
}

bool Intro::pickDataDirectory()
{
    namespace fs = boost::filesystem;
    QSettings settings;
    /* If data directory provided on command line, no need to look at settings
       or show a picking dialog */
    if (!GetArg("-datadir", "").empty())
        return true;
    /* 1) Default data directory for operating system */
    QString dataDir = getDefaultDataDirectory();
    /* 2) Allow QSettings to override default dir */
    dataDir = settings.value("strDataDir", dataDir).toString();

<<<<<<< Updated upstream

    if (!fs::exists(GUIUtil::qstringToBoostPath(dataDir)) || GetBoolArg("-choosedatadir", false)) {
        // If current default data directory does not exist, let the user choose one
=======
    if (!fs::exists(GUIUtil::qstringToBoostPath(dataDir)) || GetBoolArg("-choosedatadir", false)) {
        /* If current default data directory does not exist, let the user choose one */
>>>>>>> Stashed changes
        Intro intro;
        intro.setDataDirectory(dataDir);
        intro.setWindowIcon(QIcon(":icons/bitcoin"));

        while (true) {
            if (!intro.exec()) {
<<<<<<< Updated upstream
                // Cancel clicked
=======
                /* Cancel clicked */
>>>>>>> Stashed changes
                return false;
            }
            dataDir = intro.getDataDirectory();
            try {
                TryCreateDirectory(GUIUtil::qstringToBoostPath(dataDir));
                break;
<<<<<<< Updated upstream
            } catch (const fs::filesystem_error& e) {
                QMessageBox::critical(0, tr("PIVX Core"),
                    tr("Error: Specified data directory \"%1\" cannot be created.").arg(dataDir));
                // fall through, back to choosing screen
=======
            } catch (fs::filesystem_error& e) {
                QMessageBox::critical(0, tr("PrimeStone"),
                    tr("Error: Specified data directory \"%1\" cannot be created.").arg(dataDir));
                /* fall through, back to choosing screen */
>>>>>>> Stashed changes
            }
        }

        settings.setValue("strDataDir", dataDir);
    }
<<<<<<< Updated upstream

    /* Only override -datadir if different from the default, to make it possible to
     * override -datadir in the pivx.conf file in the default data directory
     * (to be consistent with pivxd behavior)
     */

=======
    /* Only override -datadir if different from the default, to make it possible to
     * override -datadir in the primestone.conf file in the default data directory
     * (to be consistent with primestoned behavior)
     */
>>>>>>> Stashed changes
    if (dataDir != getDefaultDataDirectory())
        SoftSetArg("-datadir", GUIUtil::qstringToBoostPath(dataDir).string()); // use OS locale for path setting
    return true;
}

void Intro::setStatus(int status, const QString& message, quint64 bytesAvailable)
{
    switch (status) {
    case FreespaceChecker::ST_OK:
        ui->errorMessage->setText(message);
        ui->errorMessage->setStyleSheet("");
        break;
    case FreespaceChecker::ST_ERROR:
        ui->errorMessage->setText(tr("Error") + ": " + message);
<<<<<<< Updated upstream
        ui->errorMessage->setStyleSheet("QLabel { color: #f84444 }");
=======
        ui->errorMessage->setStyleSheet("QLabel { color: #800000 }");
>>>>>>> Stashed changes
        break;
    }
    /* Indicate number of bytes available */
    if (status == FreespaceChecker::ST_ERROR) {
        ui->freeSpace->setText("");
    } else {
        QString freeString = tr("%1 GB of free space available").arg(bytesAvailable / GB_BYTES);
        if (bytesAvailable < BLOCK_CHAIN_SIZE) {
            freeString += " " + tr("(of %1 GB needed)").arg(BLOCK_CHAIN_SIZE / GB_BYTES);
            ui->freeSpace->setStyleSheet("QLabel { color: #800000 }");
        } else {
            ui->freeSpace->setStyleSheet("");
        }
        ui->freeSpace->setText(freeString + ".");
    }
    /* Don't allow confirm in ERROR state */
<<<<<<< Updated upstream
    ui->pushButtonOk->setEnabled(status != FreespaceChecker::ST_ERROR);
}

void Intro::updateDataDirStatus(bool enabled){
    if(enabled){
        setCssProperty(ui->dataDirectory, "edit-primary-welcome", true);
    } else {
        setCssProperty(ui->dataDirectory, "edit-primary-welcome-disabled", true);

    }
=======
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(status != FreespaceChecker::ST_ERROR);
>>>>>>> Stashed changes
}

void Intro::on_dataDirectory_textChanged(const QString& dataDirStr)
{
    /* Disable OK button until check result comes in */
<<<<<<< Updated upstream
    ui->pushButtonOk->setEnabled(false);
=======
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
>>>>>>> Stashed changes
    checkPath(dataDirStr);
}

void Intro::on_ellipsisButton_clicked()
{
    QString dir = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(0, "Choose data directory", ui->dataDirectory->text()));
    if (!dir.isEmpty())
        ui->dataDirectory->setText(dir);
}

void Intro::on_dataDirDefault_clicked()
{
    setDataDirectory(getDefaultDataDirectory());
<<<<<<< Updated upstream
    updateDataDirStatus(false);
=======
>>>>>>> Stashed changes
}

void Intro::on_dataDirCustom_clicked()
{
    ui->dataDirectory->setEnabled(true);
    ui->ellipsisButton->setEnabled(true);
<<<<<<< Updated upstream
    updateDataDirStatus(true);
=======
>>>>>>> Stashed changes
}

void Intro::startThread()
{
    thread = new QThread(this);
    FreespaceChecker* executor = new FreespaceChecker(this);
    executor->moveToThread(thread);

    connect(executor, SIGNAL(reply(int, QString, quint64)), this, SLOT(setStatus(int, QString, quint64)));
    connect(this, SIGNAL(requestCheck()), executor, SLOT(check()));
    /*  make sure executor object is deleted in its own thread */
    connect(this, SIGNAL(stopThread()), executor, SLOT(deleteLater()));
    connect(this, SIGNAL(stopThread()), thread, SLOT(quit()));

    thread->start();
}

void Intro::checkPath(const QString& dataDir)
{
    mutex.lock();
    pathToCheck = dataDir;
    if (!signalled) {
        signalled = true;
        emit requestCheck();
    }
    mutex.unlock();
}

QString Intro::getPathToCheck()
{
    QString retval;
    mutex.lock();
    retval = pathToCheck;
    signalled = false; /* new request can be queued now */
    mutex.unlock();
    return retval;
}
