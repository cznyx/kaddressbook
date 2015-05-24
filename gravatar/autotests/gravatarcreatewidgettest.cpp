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

#include "gravatarcreatewidgettest.h"
#include <qtest.h>
#include "../widgets/gravatarcreatewidget.h"
#include <QLabel>
#include <QPushButton>

GravatarCreateWidgetTest::GravatarCreateWidgetTest(QObject *parent)
    : QObject(parent)
{

}

GravatarCreateWidgetTest::~GravatarCreateWidgetTest()
{

}

void GravatarCreateWidgetTest::shouldHaveDefaultValue()
{
    KABGravatar::GravatarCreateWidget widget;
    QLabel *lab = widget.findChild<QLabel *>(QLatin1String("emaillabel"));
    QVERIFY(lab);

    QLabel *emaillabel = widget.findChild<QLabel *>(QLatin1String("email"));
    QVERIFY(emaillabel);

    QPushButton *searchGravatar = widget.findChild<QPushButton *>(QLatin1String("search"));
    QVERIFY(searchGravatar);
}

void GravatarCreateWidgetTest::shouldEnableDisableSearchButton()
{
    KABGravatar::GravatarCreateWidget widget;
    QPushButton *searchGravatar = widget.findChild<QPushButton *>(QLatin1String("search"));
    QVERIFY(!searchGravatar->isEnabled());

    widget.setEmail(QLatin1String("foo"));
    QVERIFY(searchGravatar->isEnabled());

    widget.setEmail(QString());
    QVERIFY(!searchGravatar->isEnabled());

    widget.setEmail(QLatin1String("s"));
    QVERIFY(searchGravatar->isEnabled());

    widget.setEmail(QLatin1String(" "));
    QVERIFY(!searchGravatar->isEnabled());
}

QTEST_MAIN(GravatarCreateWidgetTest)