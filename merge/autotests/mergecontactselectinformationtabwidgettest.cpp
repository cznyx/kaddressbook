/*
  Copyright (c) 2015 Montel Laurent <montel@kde.org>

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

#include "mergecontactselectinformationtabwidgettest.h"
#include "../searchduplicate/mergecontactselectinformationtabwidget.h"
#include <qtest_kde.h>

MergeContactSelectInformationTabWidgetTest::MergeContactSelectInformationTabWidgetTest(QObject *parent)
    : QObject(parent)
{

}

MergeContactSelectInformationTabWidgetTest::~MergeContactSelectInformationTabWidgetTest()
{

}

void MergeContactSelectInformationTabWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::MergeContactSelectInformationTabWidget w;
    QVERIFY(!w.tabBarVisible());
}

void MergeContactSelectInformationTabWidgetTest::shouldAddTab()
{
#if 0 //FIXME
    KABMergeContacts::MergeContactSelectInformationTabWidget w;
    w.show();
    Akonadi::Item::List lst;
    lst << Akonadi::Item(42);
    lst << Akonadi::Item(43);
    w.addNeedSelectInformationWidget(lst);
    QVERIFY(!w.tabBarVisible());
    w.addNeedSelectInformationWidget(lst);
    QVERIFY(w.tabBarVisible());
#endif
}


QTEST_KDEMAIN(MergeContactSelectInformationTabWidgetTest, GUI)