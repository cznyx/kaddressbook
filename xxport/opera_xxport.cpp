/*
    This file is part of KAddressbook.
    Copyright (c) 2003 - 2003 Daniel Molkentin <molkentin@kde.org>
                              Tobias Koenig <tokoe@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#include <qfile.h>
#include <qregexp.h>

#include <kfiledialog.h>
#include <kio/netaccess.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <ktempfile.h>
#include <kurl.h>

#include <kdebug.h>

#include "opera_xxport.h"

class OperaXXPortFactory : public XXPortFactory
{
  public:
    XXPortObject *xxportObject( KABC::AddressBook *ab, QWidget *parent, const char *name )
    {
      return new OperaXXPort( ab, parent, name );
    }
};

extern "C"
{
  void *init_libkaddrbk_opera_xxport()
  {
    return ( new OperaXXPortFactory() );
  }
}


OperaXXPort::OperaXXPort( KABC::AddressBook *ab, QWidget *parent, const char *name )
  : XXPortObject( ab, parent, name )
{
  createImportAction( i18n( "Import Opera Addressbook..." ) );
}

KABC::AddresseeList OperaXXPort::importContacts( const QString& ) const
{
  KABC::AddresseeList addrList;

  // sanity checks
  QFile file( QDir::homeDirPath() + "/.opera/contacts.adr" );
  if ( !file.open( IO_ReadOnly ) )
    return addrList;

  QTextStream stream( &file );
  stream.setEncoding( QTextStream::UnicodeUTF8 );
  QString line, key, value;
  bool parseContact = false;
  KABC::Addressee *addr = 0L;
	
  while ( !stream.atEnd() ) {
    line = stream.readLine();
    line = line.stripWhiteSpace();
    if ( line == QString::fromLatin1( "#CONTACT" ) ) {
      parseContact = true;
      addr = new KABC::Addressee;
      continue;
    } else if ( line.isEmpty() ) {
      parseContact = false;
      if ( addr && !addr->isEmpty() )
        addrList.append( *addr );
      delete addr;
      addr = 0L;
      continue;
    }

    if ( parseContact == true ) {
      int sep = line.find( '=' );
      key = line.left( sep ).lower();
      value = line.mid( sep + 1 );
      if ( key == QString::fromLatin1( "name" ) )
        addr->setNameFromString( value );
      else if ( key == QString::fromLatin1( "mail" ) ) {
        QStringList emails = QStringList::split( ",", value );

        QStringList::Iterator it = emails.begin();
        bool preferred = true;
        for ( ; it != emails.end(); ++it ) {
          addr->insertEmail( *it, preferred );
          preferred = false;
        }
      } else if ( key == QString::fromLatin1( "phone" ) )
        addr->insertPhoneNumber( KABC::PhoneNumber( value ) );
      else if ( key == QString::fromLatin1( "fax" ) )
        addr->insertPhoneNumber( KABC::PhoneNumber( value, 
                              KABC::PhoneNumber::Fax | KABC::PhoneNumber::Home ) );
      else if ( key == QString::fromLatin1( "postaladdress" ) ) {
        KABC::Address address( KABC::Address::Home );
        address.setLabel( value.replace( QRegExp( "\x02\x02" ), "\n" ) );
        addr->insertAddress( address );
      } else if ( key == QString::fromLatin1( "description" ) )
        addr->setNote( value.replace( QRegExp( "\x02\x02" ), "\n" ) );
      else if ( key == QString::fromLatin1( "url" ) )
        addr->setUrl( value );
      else if ( key == QString::fromLatin1( "pictureurl" ) ) {
        KABC::Picture pic( value );
        addr->setPhoto( pic );
      }
    }
  }

  file.close();

  return addrList;
}

#include "opera_xxport.moc"
