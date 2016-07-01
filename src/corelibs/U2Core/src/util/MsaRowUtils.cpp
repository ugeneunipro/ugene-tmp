/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
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

#include <U2Core/U2SafePoints.h>

#include "MsaRowUtils.h"

namespace U2 {

/** Gap character */
#define MAlignment_GapChar '-'

int MsaRowUtils::getRowLength(const QByteArray &seq, const U2MaRowGapModel &gaps) {
    return seq.length() + getGapsLength(gaps);
}

int MsaRowUtils::getGapsLength(const U2MaRowGapModel &gaps) {
    int length = 0;
    foreach (const U2MaGap &elt, gaps) {
        length += elt.gap;
    }
    return length;
}

char MsaRowUtils::charAt(const QByteArray &seq, const U2MaRowGapModel &gaps, int pos) {
    if (pos < 0 || pos >= getRowLength(seq, gaps)) {
        return MAlignment_GapChar;
    }

    int gapsLength = 0;
    foreach (const U2MaGap &gap, gaps) {
        // Current gap is somewhere further in the row
        if (gap.offset > pos) {
            break;
        }
        // Inside the gap
        else if ((pos >= gap.offset) && (pos < gap.offset + gap.gap)) {
            return MAlignment_GapChar;
        }
        // Go further in the row, calculating the current gaps length
        else {
            gapsLength += gap.gap;
        }
    }

    if (pos >= gapsLength + seq.length()) {
        return MAlignment_GapChar;
    }

    int index = pos - gapsLength;
    bool indexIsInBounds = (index < seq.length()) && (index >= 0);

    SAFE_POINT(indexIsInBounds,
        QString("Internal error detected in MultipleSequenceAlignmentRow::charAt,"
        " row length is '%1', gapsLength is '%2'!").arg(getRowLength(seq, gaps)).arg(index), MAlignment_GapChar);
    return seq[index];
}

qint64 MsaRowUtils::getRowLengthWithoutTrailing(const QByteArray &seq, const U2MaRowGapModel &gaps) {
    int rowLength = getRowLength(seq, gaps);
    int rowLengthWithoutTrailingGap = rowLength;
    if (!gaps.isEmpty()) {
        if (MAlignment_GapChar == charAt(seq, gaps, rowLength - 1)) {
            U2MaGap lastGap = gaps.last();
            rowLengthWithoutTrailingGap -= lastGap.gap;
        }
    }
    return rowLengthWithoutTrailingGap;
}

int MsaRowUtils::getUngappedPosition(const U2MaRowGapModel &gaps, int pos, bool allowGapInPos) {
    if (isGap(gaps, pos) && !allowGapInPos) {
        return -1;
    }

    int gapsLength = 0;
    foreach (const U2MaGap &gap, gaps) {
        if (gap.offset < pos) {
            if (allowGapInPos) {
                gapsLength += (gap.offset + gap.gap < pos) ? gap.gap : gap.gap - (gap.offset + gap.gap - pos);
            } else {
                gapsLength += gap.gap;
            }
        } else {
            break;
        }
    }
    return (pos - gapsLength);
}

int MsaRowUtils::getCoreStart(const U2MaRowGapModel &gaps) {
    if (!gaps.isEmpty() && gaps.first().offset == 0) {
        return gaps.first().gap;
    }
    return 0;
}

void MsaRowUtils::addOffsetToGapModel(U2MaRowGapModel &gapModel, int offset) {
    if (0 == offset) {
        return;
    }

    if (!gapModel.isEmpty()) {
        U2MaGap &firstGap = gapModel[0];
        if (0 == firstGap.offset) {
            firstGap.gap += offset;
        } else {
            SAFE_POINT(offset >= 0, "Negative gap offset", );
            U2MaGap beginningGap(0, offset);
            gapModel.insert(0, beginningGap);
        }

        // Shift other gaps
        if (gapModel.count() > 1) {
            for (int i = 1; i < gapModel.count(); ++i) {
                qint64 newOffset = gapModel[i].offset + offset;
                SAFE_POINT(newOffset >= 0, "Negative gap offset", );
                gapModel[i].offset = newOffset;
            }
        }
    } else {
        SAFE_POINT(offset >= 0, "Negative gap offset", );
        U2MaGap gap(0, offset);
        gapModel.append(gap);
    }
}

void MsaRowUtils::shiftGapModel(U2MaRowGapModel &gapModel, int shiftSize) {
    CHECK(shiftSize > 0, );
    for (int i = 0; i < gapModel.size(); i++) {
        gapModel[i].offset += shiftSize;
    }
}

bool MsaRowUtils::isGap(const U2MaRowGapModel &gapModel, int position) {
    foreach (const U2MaGap &gap, gapModel) {
        if (gap.offset <= position && position < gap.offset + gap.gap) {
            return true;
        }
        if (position < gap.offset) {
            return false;
        }
    }
    return false;
}

void MsaRowUtils::chopGapModel(U2MaRowGapModel &gapModel, int maxLength) {
    while (!gapModel.isEmpty() && gapModel.last().offset >= maxLength) {
        gapModel.removeLast();
    }
    if (!gapModel.isEmpty() && gapModel.last().offset + gapModel.last().gap > maxLength) {
        gapModel.last().gap = maxLength - gapModel.last().offset;
    }
}

} // U2
