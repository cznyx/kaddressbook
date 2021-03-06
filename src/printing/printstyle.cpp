/*
  This file is part of KAddressBook.
  Copyright (c) 1996-2002 Mirko Boehm <mirko@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

  As a special exception, permission is given to link this program
  with any edition of Qt, and distribute the resulting executable,
  without including the source code for Qt in the source distribution.
*/

#include "printstyle.h"
#include "printingwizard.h"

#include "kaddressbook_debug.h"

#include <QPushButton>
#include <QPixmap>
#include <QWidget>
#include <QStandardPaths>

using namespace KABPrinting;

PrintStyle::PrintStyle(PrintingWizard *parent)
    : QObject(parent)
    , mWizard(parent)
{
    mSortField = KAddressBookImportExport::KAddressBookImportExportContactFields::GivenName;
    mSortOrder = Qt::AscendingOrder;
}

PrintStyle::~PrintStyle()
{
}

const QPixmap &PrintStyle::preview() const
{
    return mPreview;
}

void PrintStyle::setPreview(const QPixmap &image)
{
    mPreview = image;
}

bool PrintStyle::setPreview(const QString &fileName)
{
    QPixmap preview;

    const QString path = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("kaddressbook/printing/") + fileName);
    if (path.isEmpty()) {
        qCDebug(KADDRESSBOOK_LOG) << "cannot locate preview image " << fileName << " in appdata";
        return false;
    } else {
        if (preview.load(path)) {
            setPreview(preview);
            return true;
        } else {
            qCDebug(KADDRESSBOOK_LOG) << "preview at '" << path << "' cannot be loaded.";
            return false;
        }
    }
}

PrintingWizard *PrintStyle::wizard() const
{
    return mWizard;
}

void PrintStyle::addPage(QWidget *page, const QString &title)
{
    if (!mPageList.contains(page)) {     // not yet in the list
        mPageList.append(page);
        mPageTitles.append(title);

        KPageWidgetItem *item = new KPageWidgetItem(page, title);
        mPageItems.insert(page, item);
        mWizard->addPage(item);
        mWizard->setAppropriate(item, false);
    }
}

void PrintStyle::showPages()
{
    QWidget *wdg = nullptr;

    for (QWidget *wdg2 : qAsConst(mPageList)) {
        mWizard->setAppropriate(mPageItems[ wdg2 ], true);
        wdg = wdg2;
    }
    mWizard->nextButton()->setEnabled(wdg);
    mWizard->finishButton()->setEnabled(!wdg);
}

void PrintStyle::hidePages()
{
    for (QWidget *wdg : qAsConst(mPageList)) {
        mWizard->setAppropriate(mPageItems[ wdg ], false);
    }
}

void PrintStyle::setPreferredSortOptions(KAddressBookImportExport::KAddressBookImportExportContactFields::Field field, Qt::SortOrder sortOrder)
{
    mSortField = field;
    mSortOrder = sortOrder;
}

KAddressBookImportExport::KAddressBookImportExportContactFields::Field PrintStyle::preferredSortField() const
{
    return mSortField;
}

Qt::SortOrder PrintStyle::preferredSortOrder() const
{
    return mSortOrder;
}

PrintStyleFactory::PrintStyleFactory(PrintingWizard *parent)
    : mParent(parent)
{
}

PrintStyleFactory::~PrintStyleFactory()
{
}
