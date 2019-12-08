// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
<<<<<<< Updated upstream
=======
// Copyright (c) 2018 The PSC developers
>>>>>>> Stashed changes
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bitcoinunits.h"
#include "chainparams.h"
#include "primitives/transaction.h"

#include <QSettings>
#include <QStringList>

<<<<<<< Updated upstream
#include <iostream>

=======
>>>>>>> Stashed changes
BitcoinUnits::BitcoinUnits(QObject* parent) : QAbstractListModel(parent),
                                              unitlist(availableUnits())
{
}

QList<BitcoinUnits::Unit> BitcoinUnits::availableUnits()
{
    QList<BitcoinUnits::Unit> unitlist;
<<<<<<< Updated upstream
    unitlist.append(PIV);
    unitlist.append(mPIV);
    unitlist.append(uPIV);
=======
    unitlist.append(PSC);
    unitlist.append(mPSC);
    unitlist.append(uPSC);
>>>>>>> Stashed changes
    return unitlist;
}

bool BitcoinUnits::valid(int unit)
{
    switch (unit) {
<<<<<<< Updated upstream
    case PIV:
    case mPIV:
    case uPIV:
=======
    case PSC:
    case mPSC:
    case uPSC:
>>>>>>> Stashed changes
        return true;
    default:
        return false;
    }
}

QString BitcoinUnits::id(int unit)
{
    switch (unit) {
<<<<<<< Updated upstream
    case PIV:
        return QString("pivx");
    case mPIV:
        return QString("mpivx");
    case uPIV:
        return QString::fromUtf8("upivx");
=======
    case PSC:
        return QString("PSC");
    case mPSC:
        return QString("mPSC");
    case uPSC:
        return QString::fromUtf8("uPSC");
>>>>>>> Stashed changes
    default:
        return QString("???");
    }
}

<<<<<<< Updated upstream
QString BitcoinUnits::name(int unit, bool isZpiv)
{
    QString z = "";
    if(isZpiv) z = "z";
    if (Params().NetworkID() == CBaseChainParams::MAIN) {
        switch (unit) {
        case PIV:
            return z + QString("PIV");
        case mPIV:
            return z + QString("mPIV");
        case uPIV:
            return z + QString::fromUtf8("μPIV");
=======
QString BitcoinUnits::name(int unit)
{
    if (Params().NetworkID() == CBaseChainParams::MAIN) {
        switch (unit) {
        case PSC:
            return QString("PSC");
        case mPSC:
            return QString("mPSC");
        case uPSC:
            return QString::fromUtf8("μPSC");
>>>>>>> Stashed changes
        default:
            return QString("???");
        }
    } else {
        switch (unit) {
<<<<<<< Updated upstream
        case PIV:
            return z + QString("tPIV");
        case mPIV:
            return z + QString("mtPIV");
        case uPIV:
            return z + QString::fromUtf8("μtPIV");
=======
        case PSC:
            return QString("tPSC");
        case mPSC:
            return QString("mtPSC");
        case uPSC:
            return QString::fromUtf8("μtPSC");
>>>>>>> Stashed changes
        default:
            return QString("???");
        }
    }
}

QString BitcoinUnits::description(int unit)
{
    if (Params().NetworkID() == CBaseChainParams::MAIN) {
        switch (unit) {
<<<<<<< Updated upstream
        case PIV:
            return QString("PIV");
        case mPIV:
            return QString("Milli-PIV (1 / 1" THIN_SP_UTF8 "000)");
        case uPIV:
            return QString("Micro-PIV (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
=======
        case PSC:
            return QString("PSC");
        case mPSC:
            return QString("Milli-PSC (1 / 1" THIN_SP_UTF8 "000)");
        case uPSC:
            return QString("Micro-PSC (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
>>>>>>> Stashed changes
        default:
            return QString("???");
        }
    } else {
        switch (unit) {
<<<<<<< Updated upstream
        case PIV:
            return QString("TestPIVs");
        case mPIV:
            return QString("Milli-TestPIV (1 / 1" THIN_SP_UTF8 "000)");
        case uPIV:
            return QString("Micro-TestPIV (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
=======
        case PSC:
            return QString("TestPSCs");
        case mPSC:
            return QString("Milli-TestPSC (1 / 1" THIN_SP_UTF8 "000)");
        case uPSC:
            return QString("Micro-TestPSC (1 / 1" THIN_SP_UTF8 "000" THIN_SP_UTF8 "000)");
>>>>>>> Stashed changes
        default:
            return QString("???");
        }
    }
}

qint64 BitcoinUnits::factor(int unit)
{
    switch (unit) {
<<<<<<< Updated upstream
    case PIV:
        return 100000000;
    case mPIV:
        return 100000;
    case uPIV:
=======
    case PSC:
        return 100000000;
    case mPSC:
        return 100000;
    case uPSC:
>>>>>>> Stashed changes
        return 100;
    default:
        return 100000000;
    }
}

int BitcoinUnits::decimals(int unit)
{
    switch (unit) {
<<<<<<< Updated upstream
    case PIV:
        return 8;
    case mPIV:
        return 5;
    case uPIV:
=======
    case PSC:
        return 8;
    case mPSC:
        return 5;
    case uPSC:
>>>>>>> Stashed changes
        return 2;
    default:
        return 0;
    }
}

<<<<<<< Updated upstream
QString BitcoinUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators, bool cleanRemainderZeros)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if (!valid(unit)){
        return QString(); // Refuse to format invalid unit
    }
=======
QString BitcoinUnits::format(int unit, const CAmount& nIn, bool fPlus, SeparatorStyle separators)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if (!valid(unit))
        return QString(); // Refuse to format invalid unit
>>>>>>> Stashed changes
    qint64 n = (qint64)nIn;
    qint64 coin = factor(unit);
    int num_decimals = decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Use SI-style thin space separators as these are locale independent and can't be
    // confused with the decimal marker.
    QChar thin_sp(THIN_SP_CP);
    int q_size = quotient_str.size();
    if (separators == separatorAlways || (separators == separatorStandard && q_size > 4))
        for (int i = 3; i < q_size; i += 3)
            quotient_str.insert(q_size - i, thin_sp);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');

    if (num_decimals <= 0)
        return quotient_str;

<<<<<<< Updated upstream
    if(cleanRemainderZeros) {
        // Clean remainder
        QString cleanRemainder = remainder_str;
        for (int i = (remainder_str.length() - 1); i > 1; i--) {
            if (remainder_str.at(i) == QChar('0')) {
                cleanRemainder = cleanRemainder.left(cleanRemainder.lastIndexOf("0"));
            } else
                break;
        }
        return quotient_str + QString(".") + cleanRemainder;
    }

=======
>>>>>>> Stashed changes
    return quotient_str + QString(".") + remainder_str;
}


// TODO: Review all remaining calls to BitcoinUnits::formatWithUnit to
// TODO: determine whether the output is used in a plain text context
// TODO: or an HTML context (and replace with
// TODO: BtcoinUnits::formatHtmlWithUnit in the latter case). Hopefully
// TODO: there aren't instances where the result could be used in
// TODO: either context.

// NOTE: Using formatWithUnit in an HTML context risks wrapping
// quantities at the thousands separator. More subtly, it also results
// in a standard space rather than a thin space, due to a bug in Qt's
// XML whitespace canonicalisation
//
// Please take care to use formatHtmlWithUnit instead, when
// appropriate.

QString BitcoinUnits::formatWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    return format(unit, amount, plussign, separators) + QString(" ") + name(unit);
}

QString BitcoinUnits::formatHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(formatWithUnit(unit, amount, plussign, separators));
<<<<<<< Updated upstream
    str.replace(QChar(THIN_SP_CP), QString(COMMA_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}

QString BitcoinUnits::floorWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators, bool cleanRemainderZeros, bool isZPIV)
=======
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}

QString BitcoinUnits::floorWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
>>>>>>> Stashed changes
{
    QSettings settings;
    int digits = settings.value("digits").toInt();

<<<<<<< Updated upstream
    QString result = format(unit, amount, plussign, separators, cleanRemainderZeros);
    if(decimals(unit) > digits) {
        if (!cleanRemainderZeros) {
            result.chop(decimals(unit) - digits);
        } else {
            int lenght = result.mid(result.indexOf("."), result.length() - 1).length() - 1;
            if (lenght > digits) {
                result.chop(lenght - digits);
            }
        }
    }

    return result + QString(" ") + name(unit, isZPIV);
}

QString BitcoinUnits::floorHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators, bool cleanRemainderZeros, bool isZPIV)
{
    QString str(floorWithUnit(unit, amount, plussign, separators, cleanRemainderZeros, isZPIV));
    str.replace(QChar(THIN_SP_CP), QString(COMMA_HTML));
=======
    QString result = format(unit, amount, plussign, separators);
    if (decimals(unit) > digits) result.chop(decimals(unit) - digits);

    return result + QString(" ") + name(unit);
}

QString BitcoinUnits::floorHtmlWithUnit(int unit, const CAmount& amount, bool plussign, SeparatorStyle separators)
{
    QString str(floorWithUnit(unit, amount, plussign, separators));
    str.replace(QChar(THIN_SP_CP), QString(THIN_SP_HTML));
>>>>>>> Stashed changes
    return QString("<span style='white-space: nowrap;'>%1</span>").arg(str);
}

bool BitcoinUnits::parse(int unit, const QString& value, CAmount* val_out)
{
    if (!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);

    // Ignore spaces and thin spaces when parsing
    QStringList parts = removeSpaces(value).split(".");

    if (parts.size() > 2) {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if (parts.size() > 1) {
        decimals = parts[1];
    }
    if (decimals.size() > num_decimals) {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if (str.size() > 18) {
        return false; // Longer numbers will exceed 63 bits
    }
    CAmount retvalue(str.toLongLong(&ok));
    if (val_out) {
        *val_out = retvalue;
    }
    return ok;
}

QString BitcoinUnits::getAmountColumnTitle(int unit)
{
    QString amountTitle = QObject::tr("Amount");
    if (BitcoinUnits::valid(unit)) {
        amountTitle += " (" + BitcoinUnits::name(unit) + ")";
    }
    return amountTitle;
}

int BitcoinUnits::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant BitcoinUnits::data(const QModelIndex& index, int role) const
{
    int row = index.row();
    if (row >= 0 && row < unitlist.size()) {
        Unit unit = unitlist.at(row);
        switch (role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}

CAmount BitcoinUnits::maxMoney()
{
    return Params().MaxMoneyOut();
}
