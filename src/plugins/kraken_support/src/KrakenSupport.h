/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2018 UniPro <ugene@unipro.ru>
 * http://ugene.net
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

#ifndef _U2_KRAKEN_SUPPORT_H_
#define _U2_KRAKEN_SUPPORT_H_

#include <U2Core/ExternalToolRegistry.h>

namespace U2 {

#define ET_KRAKEN_CLASSIFY KrakenSupport::CLASSIFY_TOOL
#define ET_KRAKEN_BUILD KrakenSupport::BUILD_TOOL
#define ET_KRAKEN_TRANSLATE KrakenSupport::TRANSLATE_TOOL

class KrakenSupport : public ExternalTool {
    Q_OBJECT
public:
    KrakenSupport(const QString &name);

    QStringList getAdditionalPaths() const;

    static const QString GROUP_NAME;
    static const QString BUILD_TOOL;
    static const QString CLASSIFY_TOOL;
    static const QString TRANSLATE_TOOL;

private:
    void initBuild();
    void initClassify();
    void initTranslate();
};

}   // namespace U2

#endif // _U2_KRAKEN_SUPPORT_H_
