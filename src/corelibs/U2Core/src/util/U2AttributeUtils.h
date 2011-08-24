/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2011 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _U2_ATTRIBUTE_UTILS_H_
#define _U2_ATTRIBUTE_UTILS_H_

#include <U2Core/U2Type.h>

namespace U2 {

class U2AttributeDbi;
class U2OpStatus;

/**                                           
    U2Attribute utility functions
*/
class U2CORE_EXPORT U2AttributeUtils : public QObject {
    Q_OBJECT
private:
    U2AttributeUtils(){}
public:

    static qint64 findIntegerAttribute(U2AttributeDbi* adbi, const U2Object& obj, const QString& name, qint64 defaultVal, U2OpStatus& os);

    static double findRealAttribute(U2AttributeDbi* adbi, const U2Object& obj, const QString& name, double defaultVal, U2OpStatus& os);

    static QByteArray findByteArrayAttribute(U2AttributeDbi* adbi, const U2Object& obj, const QString& name, const QByteArray& defaultVal, U2OpStatus& os);

    static QString findStringAttribute(U2AttributeDbi* adbi, const U2Object& obj, const QString& name, const QString& defaultVal, U2OpStatus& os);

};

} //namespace


#endif
