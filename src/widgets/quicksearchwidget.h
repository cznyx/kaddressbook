/*
  This file is part of KAddressBook.

  Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#ifndef QUICKSEARCHWIDGET_H
#define QUICKSEARCHWIDGET_H

#include <QWidget>

class QLineEdit;

/**
 * @short The quick search widget from the toolbar
 *
 * This widget allows the user to filter for contacts
 * that match a given string criteria.
 * The filter string the user enters here is emitted to
 * the ContactsFilterModel, which does the real filtering.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class QuickSearchWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * Creates the quick search widget.
     *
     * @param parent The parent widget.
     */
    explicit QuickSearchWidget(QWidget *parent = nullptr);

    /**
     * Destroys the quick search widget.
     */
    ~QuickSearchWidget() override;

    /**
     * Returns the size hint of the quick search widget.
     */
    QSize sizeHint() const override;

    void updateQuickSearchText(const QString &text);

public Q_SLOTS:
    void slotFocusQuickSearch();

Q_SIGNALS:
    /**
     * This signal is emitted whenever the user has changed
     * the filter string in the line edit.
     *
     * @param filterString The new filter string.
     */
    void filterStringChanged(const QString &filterString);

    /**
     * This signal is emitted whenever the user pressed the
     * arrow down key. In this case we set the focus on the
     * item view that shows the contacts, so the user can
     * navigate much faster.
     */
    void arrowDownKeyPressed();

protected:
    void keyPressEvent(QKeyEvent *) override;

private:
    void resetTimer();
    void delayedTextChanged();
    QLineEdit *mEdit = nullptr;
    QTimer *mTimer = nullptr;
};

#endif
