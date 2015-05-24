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

#include "gravatarcreatedialog.h"
#include "gravatarcreatewidget.h"
#include <QVBoxLayout>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <KConfigGroup>
#include <KGlobal>
#include <KSharedConfig>

using namespace KABGravatar;
GravatarCreateDialog::GravatarCreateDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mCreateWidget = new GravatarCreateWidget(this);
    mCreateWidget->setObjectName(QLatin1String("gravatarcreatewidget"));
    mainLayout->addWidget(mCreateWidget);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setObjectName(QLatin1String("buttonbox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    readConfig();
}

GravatarCreateDialog::~GravatarCreateDialog()
{
    writeConfig();
}

void GravatarCreateDialog::setEmail(const QString &email)
{
    mCreateWidget->setEmail(email);
}

void GravatarCreateDialog::readConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "GravatarCreateDialog");
    const QSize size = grp.readEntry("Size", QSize(300, 200));
    if (size.isValid()) {
        resize(size);
    }
}

void GravatarCreateDialog::writeConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "GravatarCreateDialog");
    grp.writeEntry("Size", size());
    grp.sync();
}