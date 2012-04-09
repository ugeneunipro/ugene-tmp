/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2012 UniPro <ugene@unipro.ru>
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

#include "GTTestsFromProjectView.h"
#include "api/GTGlobals.h"
#include "api/GTKeyboardDriver.h"
#include "api/GTMouseDriver.h"
#include "api/GTMenu.h"
#include "GTUtilsProject.h"
#include "GTUtilsDocument.h"
#include "GTUtilsLog.h"
#include "GTUtilsApp.h"
#include "GTUtilsToolTip.h"
#include "GTUtilsDialog.h"
#include "GTUtilsMdi.h"
#include "GTUtilsProjectTreeView.h"
#include "GTUtilsMdi.h"
#include <U2View/AnnotatedDNAViewFactory.h>
#include <U2View/MSAEditorFactory.h>
#include <api/GTFileDialog.h>


namespace U2{

namespace GUITest_common_scenarios_project_sequence_exporting_from_project_view{

GUI_TEST_CLASS_DEFINITION(test_0004) {
    GTFileDialog::openFile(os, dataDir + "samples/CLUSTALW/", "HIV-1.aln");
    GTGlobals::sleep(100);
    GTUtilsProject::exportToSequenceFormat(os, "HIV-1.aln", dataDir + " _common_data/scenarios/sandbox/", "export1.fa");
    GTGlobals::sleep(100);
    if (! GTUtilsDocument::getDocument(os, "export1.fa")) {
        GTFileDialog::openFile(os, dataDir + " _common_data/scenarios/sandbox/", "export1.fa");
    }

    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "export1.fa"));
    GTMouseDriver::doubleClick(os);
    ///TODO: check [s] ru131 has '-' symbols at the end of sequence
}

GUI_TEST_CLASS_DEFINITION(test_0005) {
    GTFileDialog::openFile(os, dataDir + "/samples/CLUSTALW/", "COI.aln");
    // Test not completed
}

GUI_TEST_CLASS_DEFINITION(test_0006) {
    const QString doc1("1.gb"), doc2("2.gb");

    GTFileDialog::openFile(os, testDir + "_common_data/scenarios/project/", "proj4.uprj");
    GTGlobals::sleep(1000);

    QTreeWidgetItem *item1 = GTUtilsProjectTreeView::findItem(os, doc1);
    QTreeWidgetItem *item2 = GTUtilsProjectTreeView::findItem(os, doc2);
    if (item1 == NULL || item2 == NULL) {
        os.setError("Project view with document \"1.gb\" and \"2.gb\" is not opened");
        return;
    }

    if (GTUtilsDocument::isDocumentLoaded(os, doc1) || GTUtilsDocument::isDocumentLoaded(os, doc2)) {
        os.setError("Documents is not unload");
        return;
    }

    GTUtilsApp::checkUGENETitle(os, "proj4 UGENE");

    GTMouseDriver::moveTo(os, GTUtilsProjectTreeView::getItemCenter(os, "NC_001363 features"));
    GTMouseDriver::doubleClick(os);
    GTGlobals::sleep(1000);

    GObjectViewWindow *activeWindow = qobject_cast<GObjectViewWindow*> (GTUtilsMdi::activeWindow(os));
    if (! activeWindow->getViewName().contains("NC_001363")) {
        os.setError("NC_001363 sequence has been not opened in sequence view");
        return;
    }
    // Test not completed
}

} // namespace
} // namespace U2
