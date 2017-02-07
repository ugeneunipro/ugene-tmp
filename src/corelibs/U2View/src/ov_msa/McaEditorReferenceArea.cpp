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

#include "McaEditorReferenceArea.h"
#include "McaEditor.h"
#include "McaEditorSequenceArea.h"

#include <U2Core/DNASequenceSelection.h>
#include <U2View/ADVSequenceObjectContext.h> // SANGER_TODO: rename
#include <U2Core/U2SafePoints.h>

namespace U2 {

McaEditorReferenceArea::McaEditorReferenceArea(McaEditorWgt *p, SequenceObjectContext *ctx)
    : PanView(p, ctx) {
    editor = p->getEditor();
    setLocalToolbarVisible(false);

    rowBar->hide();

    connect(p->getSequenceArea(), SIGNAL(si_visibleRangeChanged()), SLOT(sl_visibleRangeChanged()));
    connect(p->getSequenceArea(), SIGNAL(si_selectionChanged(MaEditorSelection,MaEditorSelection)),
            SLOT(sl_selectionChanged(MaEditorSelection,MaEditorSelection)));

    connect(ctx->getSequenceSelection(),
        SIGNAL(si_selectionChanged(LRegionsSelection*, const QVector<U2Region>&, const QVector<U2Region>&)),
        SLOT(sl_onSelectionChanged()));

    connect(this, SIGNAL(si_selectionChanged(U2Region)),
            p->getSequenceArea(), SLOT(sl_referenceSelectionChanged(U2Region)));
}

void McaEditorReferenceArea::sl_visibleRangeChanged() {
    int start = editor->getUI()->getSequenceArea()->getFirstVisibleBase();
    int len = editor->getUI()->getSequenceArea()->getNumVisibleBases(false);

    U2Region visRange(start, len);
    setVisibleRange(visRange);
}

void McaEditorReferenceArea::sl_selectionChanged(const MaEditorSelection &current, const MaEditorSelection &/*prev*/) {
    U2Region selection(current.x(), current.width());
    setSelection(selection);
}

void McaEditorReferenceArea::sl_onSelectionChanged() {

    DNASequenceSelection* seqSelection = ctx->getSequenceSelection();
    CHECK(seqSelection != NULL, );

    QVector<U2Region> selectedRegions = seqSelection->getSelectedRegions();
    if (selectedRegions.size() == 1) {
        // SANGER_TODO: infinite selection - the signal goes to the seq.area and returns here
//        emit si_selectionChanged(selectedRegions.first());
        coreLog.info("Selection in the reference area");
    }
}

} // namespace
