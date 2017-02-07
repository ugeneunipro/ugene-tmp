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

#include "McaEditor.h"
#include "MaEditorFactory.h"
#include "McaEditorSequenceArea.h"
#include "McaEditorReferenceArea.h"
#include "McaEditorOverviewArea.h"
#include "MaEditorNameList.h"

#include "view_rendering/MaEditorWgt.h"
#include <U2View/ADVSequenceObjectContext.h>// SANGER_TODO: do not forget to rename the header

#include <QToolBar>

#include <U2Core/AppContext.h>
#include <U2Core/U2OpStatusUtils.h>
#include <U2Core/DNASequenceObject.h>

#include <U2Gui/GUIUtils.h>
#include <U2Gui/OptionsPanel.h>
#include <U2Gui/OPWidgetFactoryRegistry.h>

namespace U2 {

McaEditor::McaEditor(const QString &viewName,
                     MultipleChromatogramAlignmentObject *obj,
                     U2SequenceObject* ref)
    : MaEditor(McaEditorFactory::ID, viewName, obj),
      referenceObj(ref),
      referenceCtx(NULL)
{
    showChromatograms = true; // SANGER_TODO: check if there are chromatograms

    // SANGER_TODO: set new proper icon
    showChromatogramsAction = new QAction(QIcon(":/core/images/graphs.png"), tr("Show/hide chromatogram(s)"), this);
    showChromatogramsAction->setObjectName("chromatograms");
    showChromatogramsAction->setCheckable(true);
    showChromatogramsAction->setChecked(showChromatograms);
    connect(showChromatogramsAction, SIGNAL(triggered(bool)), SLOT(sl_showHideChromatograms(bool)));

    U2OpStatusImpl os;
    foreach (const MultipleChromatogramAlignmentRow& row, obj->getMca()->getMcaRows()) {
        // SANGER_TODO: tmp
        chromVisibility.insert(obj->getMca()->getRowIndexByRowId(row->getRowId(), os), row->getRowId() % 2 == 0 ? true : false);
    }

    if (ref) {
        objects.append(referenceObj);
        onObjectAdded(referenceObj);

        referenceCtx = new SequenceObjectContext(referenceObj, this);
    }
}

void McaEditor::buildStaticToolbar(QToolBar* tb) {
    tb->addAction(zoomInAction);
    tb->addAction(zoomOutAction);
    tb->addAction(zoomToSelectionAction);
    tb->addAction(resetFontAction);

    tb->addAction(showOverviewAction);
    tb->addAction(showChromatogramsAction);
    tb->addAction(changeFontAction);
    tb->addAction(saveScreenshotAction);

    GObjectView::buildStaticToolbar(tb);
}

void McaEditor::buildStaticMenu(QMenu* m) {
    // SANGER_TODO: review the menus and toolbar
//    MaEditor::buildStaticMenu(m);
}

int McaEditor::getRowHeight() const {
    QFontMetrics fm(font, ui);
    int chromHeigth = 100; // SANGER_TODO: set const chrom height
    return (fm.height() + chromHeigth * showChromatograms)* zoomMult;
}

bool McaEditor::getShowChromatogram() const {
    return showChromatograms;
}

bool McaEditor::isChromVisible(qint64 rowId) const {
    return chromVisibility[rowId];
}

void McaEditor::toggleChromVisibility(qint64 rowId) {
    chromVisibility[rowId] = !chromVisibility[rowId];
    emit si_completeUpdate();
}

void McaEditor::sl_onContextMenuRequested(const QPoint & pos) {
    Q_UNUSED(pos);

    if (ui->childAt(pos) != NULL) {
        // ignore context menu request if overview area was clicked on
        if (ui->getOverviewArea()->isOverviewWidget(ui->childAt(pos))) {
            return;
        }
    }

    QMenu m;

    addCopyMenu(&m);
    addViewMenu(&m);
    addExportMenu(&m);

    m.addSeparator();

    emit si_buildPopupMenu(this, &m);

    GUIUtils::disableEmptySubmenus(&m);

    m.exec(QCursor::pos());
}

void McaEditor::sl_showHideChromatograms(bool show) {
    showChromatograms = show;
    foreach (qint64 key, chromVisibility.keys()) {
        chromVisibility[key] = show;
    }

    emit si_completeUpdate();
}

QWidget* McaEditor::createWidget() {
    Q_ASSERT(ui == NULL);
    ui = new McaEditorWgt(this);

    QString objName = "mca_editor_" + maObject->getGObjectName();
    ui->setObjectName(objName);

    connect(ui , SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(sl_onContextMenuRequested(const QPoint &)));

    initActions();

    optionsPanel = new OptionsPanel(this);
    OPWidgetFactoryRegistry *opWidgetFactoryRegistry = AppContext::getOPWidgetFactoryRegistry();

    QList<OPFactoryFilterVisitorInterface*> filters;
    filters.append(new OPFactoryFilterVisitor(ObjViewType_ChromAlignmentEditor));

    QList<OPWidgetFactory*> opWidgetFactories = opWidgetFactoryRegistry->getRegisteredFactories(filters);
    foreach (OPWidgetFactory *factory, opWidgetFactories) {
        optionsPanel->addGroup(factory);
    }

    qDeleteAll(filters);

    return ui;
}

McaEditorWgt::McaEditorWgt(McaEditor *editor)
    : MaEditorWgt(editor) {
    initActions();
    initWidgets();

    QWidget* placeHolder1 = createLabelWidget();
    QWidget* placeHolder2 = createLabelWidget();

    QWidget *label = createLabelWidget(tr("Reference")); // SANGER_TODO: write sequence name
    nameAreaLayout->insertWidget(0, label);
    // SANGER_TODO: connect the lavel height with the panview height

    McaEditorReferenceArea* refArea = new McaEditorReferenceArea(this, getEditor()->referenceCtx);

    seqAreaLayout->addWidget(placeHolder1, 0, 0);
    seqAreaLayout->addWidget(refArea, 0, 1);
    seqAreaLayout->addWidget(placeHolder2, 0, 2);
}

McaEditorSequenceArea* McaEditorWgt::getSequenceArea() const {
    return qobject_cast<McaEditorSequenceArea*>(seqArea);
}

void McaEditorWgt::initSeqArea(GScrollBar* shBar, GScrollBar* cvBar) {
    seqArea = new McaEditorSequenceArea(this, shBar, cvBar);
}

void McaEditorWgt::initOverviewArea() {
    overviewArea = new McaEditorOverviewArea(this);
}

void McaEditorWgt::initNameList(QScrollBar* nhBar) {
    nameList = new McaEditorNameList(this, nhBar);
}

} // namespace
