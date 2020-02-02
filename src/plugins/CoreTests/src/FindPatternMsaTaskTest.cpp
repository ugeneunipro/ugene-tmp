/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2019 UniPro <ugene@unipro.ru>
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

#include "FindPatternMsaTaskTest.h"

#include <U2Core/DocumentModel.h>
#include <U2Core/GObjectTypes.h>
#include <U2Core/MultipleSequenceAlignmentObject.h>

namespace U2 {

#define IN_OBJECT_NAME "in"
#define PATTERNS "patterns"
#define REMOVE_OVERLAPS "removeOverlaps"
#define MATCH_VALUE "matchValue"
#define MAX_RESULTS_TO_FIND "maxResultsToFind"
#define MAX_RESULT_REGEXP_LENGTH "maxResultRegExpLength"
#define ALGORITHM "algorithm"
#define EXPECTED_RESULTS_SIZE "resultsSize"
#define EXPECTED_REGIONS_IN_RESULTS "expectedRegionsInResults"

void GTest_FindPatternMsa::init(XMLTestFormat *tf, const QDomElement &el) {
    Q_UNUSED(tf);

    inputObjectName = el.attribute(IN_OBJECT_NAME);
    if (inputObjectName.isEmpty()) {
        failMissingValue(IN_OBJECT_NAME);
        return;
    }

    QStringList patterns = el.attribute(PATTERNS).split(";");
    if (patterns.isEmpty()) {
        failMissingValue(PATTERNS);
        return;
    }

    foreach(const QString & pattern, patterns) {
        settings.patterns.append(QPair<QString, QString>("", pattern));
    }

    QString tmp = el.attribute(REMOVE_OVERLAPS);
    if (!tmp.isEmpty()) {
        if (tmp.toLower() == "true") {
            settings.removeOverlaps = true;
        }
    }

    tmp = el.attribute(MATCH_VALUE);
    if (!tmp.isEmpty()) {
        bool ok = false;
        int value = tmp.toInt(&ok);
        if (ok) {
            settings.matchValue = value;
        }
    }

    tmp = el.attribute(MAX_RESULTS_TO_FIND);
    if (!tmp.isEmpty()) {
        bool ok = false;
        int value = tmp.toInt(&ok);
        if (ok) {
            settings.findSettings.maxResult2Find = value;
        }
    }
    
    tmp = el.attribute(MAX_RESULT_REGEXP_LENGTH);
    if (!tmp.isEmpty()) {
        bool ok = false;
        int value = tmp.toInt(&ok);
        if (ok) {
            settings.findSettings.maxResult2Find = value;
        }
    }

    tmp = el.attribute(ALGORITHM).toLower();
    if (tmp.isEmpty()) {
        failMissingValue(ALGORITHM);
        return;
    }

    if (tmp == "exact") {
        settings.findSettings.patternSettings = FindAlgorithmPatternSettings_Exact;
    } else if (tmp == "insdel") {
        settings.findSettings.patternSettings = FindAlgorithmPatternSettings_InsDel;
    } else if (tmp == "regexp") {
        settings.findSettings.patternSettings = FindAlgorithmPatternSettings_RegExp;
    } else if (tmp == "subst") {
        settings.findSettings.patternSettings = FindAlgorithmPatternSettings_Subst;
    } else {
        wrongValue(ALGORITHM);
    }

    tmp = el.attribute(EXPECTED_RESULTS_SIZE).toLower();
    if (!tmp.isEmpty()) {
        bool ok = false;
        int value = tmp.toInt(&ok);
        if (ok) {
            expectedResultsSize = value;
        } else {
            wrongValue(ALGORITHM);
        }
    } else {
        wrongValue(ALGORITHM);
    }

    QString expected = el.attribute(EXPECTED_REGIONS_IN_RESULTS);
    if (!expected.isEmpty()) {
        QStringList expectedList = expected.split(QRegExp("\\,"));
        foreach (QString region, expectedList) {
            QStringList bounds = region.split(QRegExp("\\.."));
            if (bounds.size() != 2) {
                stateInfo.setError(QString("wrong value for %1").arg(EXPECTED_REGIONS_IN_RESULTS));
                return;
            }
            bool startOk, finishOk;
            int start = bounds.first().toInt(&startOk), finish = bounds.last().toInt(&finishOk);
            if (!startOk || !finishOk) {
                stateInfo.setError(QString("wrong value for %1").arg(EXPECTED_REGIONS_IN_RESULTS));
                return;
            }
            start--;
            regionsToCheck.append(U2Region(start, finish - start));
        }
    }
}

void GTest_FindPatternMsa::prepare() {
    doc = getContext<Document>(this, inputObjectName);
    if (doc == NULL) {
        stateInfo.setError(QString("context not found %1").arg(inputObjectName));
        return;
    }

    QList<GObject *> list = doc->findGObjectByType(GObjectTypes::MULTIPLE_SEQUENCE_ALIGNMENT);
    if (list.size() == 0) {
        stateInfo.setError(QString("container of object with type \"%1\" is empty").arg(GObjectTypes::MULTIPLE_SEQUENCE_ALIGNMENT));
        return;
    }

    GObject *obj = list.first();
    if (obj == NULL) {
        stateInfo.setError(QString("object with type \"%1\" not found").arg(GObjectTypes::MULTIPLE_SEQUENCE_ALIGNMENT));
        return;
    }
    assert(obj != NULL);
    msaObj = qobject_cast<MultipleSequenceAlignmentObject *>(obj);
    if (msaObj == NULL) {
        stateInfo.setError(QString("error can't cast to multiple alignment from GObject"));
        return;
    }

    settings.msaObj = msaObj;
    findPatternTask = new FindPatternMsaTask(settings);
}

Task::ReportResult GTest_FindPatternMsa::report() {
    if (!findPatternTask->hasError()) {
        QMap<int, QList<U2::U2Region>> results = findPatternTask->getResults();
        if (results.size() != expectedResultsSize) {
            stateInfo.setError(QString("Expected and Actual lists of results are different: %1 %2").arg(expectedResultsSize).arg(findPatternTask->getResults().size()));
            return ReportResult_Finished;
        }
        //foreach (const U2Region &region, regionsToCheck) {
            /*
            if (results.contains(region)) {
                stateInfo.setError(QString("One of the expected regions: %1 not present in search results.").arg(region.toString()));
                return ReportResult_Finished;
            }
            */
        //}
    }
    return ReportResult_Finished;
}

QList<XMLTestFactory *> FindPatternMsaTests::createTestFactories() {
    QList<XMLTestFactory *> res;
    res.append(GTest_FindPatternMsa::createFactory());
    return res;
}

}