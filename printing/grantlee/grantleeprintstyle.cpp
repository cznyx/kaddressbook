/*
  Copyright (c) 2013, 2014 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "grantleeprintstyle.h"
#include "contactfields.h"
#include "printingwizard.h"
#include "printprogress.h"
#include "printstyle.h"
#include "contactgrantleeprintobject.h"

#include "kaddressbookgrantlee/formatter/grantleecontactutils.h"

#include <grantlee/context.h>
#include <grantlee/engine.h>
#include <grantlee/templateloader.h>

#include <KContacts/Addressee>

#include <KLocalizedString>

#include <QPrinter>
#include <QTextDocument>
#include <QFile>
#include <QDir>

using namespace KABPrinting;

QString GrantleePrintStyle::contactsToHtml(const KContacts::Addressee::List &contacts)
{
    if (!mErrorMessage.isEmpty()) {
        return mErrorMessage;
    }

    QVariantList contactsList;
    QList<ContactGrantleePrintObject *> lst;
    Q_FOREACH (const KContacts::Addressee &address, contacts) {
        ContactGrantleePrintObject *contactPrintObject = new ContactGrantleePrintObject(address);
        lst.append(contactPrintObject);
        contactsList << QVariant::fromValue(static_cast<QObject *>(contactPrintObject));
    }
    QVariantHash mapping;
    QVariantHash contactI18n;
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("birthdayi18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("anniversaryi18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("emailsi18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("websitei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("blogUrli18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("addressBookNamei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("notei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("departmenti18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("Professioni18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("officei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("manageri18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("assistanti18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("spousei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("imAddressi18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("latitudei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("longitudei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("organizationi18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("titlei18n"));
    GrantleeContactUtils::insertVariableToQVariantHash(contactI18n, QLatin1String("nextcontacti18n"));
    mapping.insert(QLatin1String("contacti18n"), contactI18n);

    Grantlee::Context context(mapping);
    context.insert(QLatin1String("contacts"), contactsList);
    const QString content = mSelfcontainedTemplate->render(&context);
    qDeleteAll(lst);
    return content;
}

GrantleePrintStyle::GrantleePrintStyle(const QString &themePath, PrintingWizard *parent)
    : PrintStyle(parent)
{
    mEngine = new Grantlee::Engine;
    mTemplateLoader = QSharedPointer<Grantlee::FileSystemTemplateLoader>(new Grantlee::FileSystemTemplateLoader);
    QFile previewFile(QString(themePath + QDir::separator() + QLatin1String("preview.png")));
    if (previewFile.exists()) {
        setPreview(previewFile.fileName());
    }

    mTemplateLoader->setTemplateDirs(QStringList() << themePath);
    mEngine->addTemplateLoader(mTemplateLoader);

    mSelfcontainedTemplate = mEngine->loadByName(QLatin1String("theme.html"));
    if (mSelfcontainedTemplate->error()) {
        mErrorMessage = mSelfcontainedTemplate->errorString() + QLatin1String("<br>");
    }

    setPreferredSortOptions(ContactFields::FormattedName, Qt::AscendingOrder);
}

GrantleePrintStyle::~GrantleePrintStyle()
{
    delete mEngine;
}

void GrantleePrintStyle::print(const KContacts::Addressee::List &contacts, PrintProgress *progress)
{
    QPrinter *printer = wizard()->printer();
    printer->setPageMargins(20, 20, 20, 20, QPrinter::DevicePixel);

    progress->addMessage(i18n("Setting up document"));

    const QString html = contactsToHtml(contacts);

    QTextDocument document;
    document.setHtml(html);

    progress->addMessage(i18n("Printing"));

    document.print(printer);

    progress->addMessage(i18nc("Finished printing", "Done"));
}

GrantleeStyleFactory::GrantleeStyleFactory(const QString &name, const QString &themePath, PrintingWizard *parent)
    : PrintStyleFactory(parent),
      mThemePath(themePath),
      mName(name)
{
}

PrintStyle *GrantleeStyleFactory::create() const
{
    return new GrantleePrintStyle(mThemePath, mParent);
}

QString GrantleeStyleFactory::description() const
{
    return mName;
}

