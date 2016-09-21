/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kaddressbookplugininterface.h"

#include "kaddressbook_debug.h"
#include "mainwidget.h"

#include <KActionCollection>

#include <pimcommon/genericplugin.h>

class KAddressBookPluginInterfacePrivate
{
public:
    KAddressBookPluginInterfacePrivate()
        : kaddressBookPluginInterface(new KAddressBookPluginInterface)
    {
    }

    ~KAddressBookPluginInterfacePrivate()
    {
        delete kaddressBookPluginInterface;
    }
    KAddressBookPluginInterface *kaddressBookPluginInterface;
};

Q_GLOBAL_STATIC(KAddressBookPluginInterfacePrivate, sInstance)

KAddressBookPluginInterface::KAddressBookPluginInterface(QObject *parent)
    : PimCommon::PluginInterface(parent),
      mMainWidget(Q_NULLPTR)
{
    setPluginName(QStringLiteral("kaddressbook"));
    setServiceTypeName(QStringLiteral("KAddressBook/MainViewPlugin"));
}

KAddressBookPluginInterface::~KAddressBookPluginInterface()
{

}

KAddressBookPluginInterface *KAddressBookPluginInterface::self()
{
    return sInstance->kaddressBookPluginInterface;
}

void KAddressBookPluginInterface::initializeInterfaceRequires(PimCommon::GenericPluginInterface *interface)
{
    if (!mMainWidget) {
        qCCritical(KADDRESSBOOK_LOG) << "Main windows pointer not defined";
        return;
    }
    PimCommon::GenericPluginInterface::RequireTypes requires = interface->requires();
    if (requires & PimCommon::GenericPluginInterface::CurrentItems) {
        interface->setCurrentItems(mMainWidget->collectSelectedAllContactsItem());
    }
    if (requires & PimCommon::GenericPluginInterface::Items) {
        interface->setItems(mMainWidget->selectedItems());
    }
    if (requires & PimCommon::GenericPluginInterface::CurrentCollection) {
        interface->setCurrentCollection(mMainWidget->currentAddressBook());
    }
    if (requires & PimCommon::GenericPluginInterface::Collections) {
        qCDebug(KADDRESSBOOK_LOG) << "PimCommon::GenericPluginInterface::Collections not implemented";
    }
}

void KAddressBookPluginInterface::setMainWidget(MainWidget *mainWidget)
{
    mMainWidget = mainWidget;
}

