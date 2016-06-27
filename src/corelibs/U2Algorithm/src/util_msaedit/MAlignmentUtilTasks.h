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

#ifndef _U2_MALIGNMENT_UTIL_TASKS
#define _U2_MALIGNMENT_UTIL_TASKS

#include <U2Core/global.h>
#include <U2Core/Task.h>
#include <U2Core/MultipleSequenceAlignmentObject.h>

namespace U2 {

class DNATranslation;

/**
 Performs in-place translation of malignment object
*/

class U2ALGORITHM_EXPORT TranslateMSA2AminoTask : public Task {
    Q_OBJECT
public:
    TranslateMSA2AminoTask(MultipleSequenceAlignmentObject* obj);
    TranslateMSA2AminoTask(MultipleSequenceAlignmentObject* obj, const QString& trId );
    const MultipleSequenceAlignment& getTaskResult() { return resultMA; }
    void run();
    ReportResult report();
private:
    MultipleSequenceAlignment resultMA;
    MultipleSequenceAlignmentObject* maObj;
    DNATranslation* translation;
};


/**
 Wrapper for multiple alignment task
*/

class U2ALGORITHM_EXPORT AlignGObjectTask : public Task {
    Q_OBJECT
public:
    AlignGObjectTask(const QString& taskName, TaskFlags f, MultipleSequenceAlignmentObject* maobj)
        : Task(taskName, f), obj(maobj) {}
    virtual void setMAObject(MultipleSequenceAlignmentObject* maobj) { obj = maobj; }
    MultipleSequenceAlignmentObject* getMAObject() { return obj; }
protected:
    QPointer<MultipleSequenceAlignmentObject> obj;
};


/**
 Multi task converts alignment object to amino representation if possible.
 This allows to:
 1) speed up alignment
 2) avoid errors of inserting gaps within codon boundaries
*/

class U2ALGORITHM_EXPORT AlignInAminoFormTask : public Task {
    Q_OBJECT
    Q_DISABLE_COPY(AlignInAminoFormTask)
public:
    AlignInAminoFormTask(MultipleSequenceAlignmentObject* obj, AlignGObjectTask* alignTask, const QString& traslId);
    ~AlignInAminoFormTask();

    virtual void prepare();
    virtual void run();
    virtual ReportResult report();
protected:
    AlignGObjectTask* alignTask;
    MultipleSequenceAlignmentObject *maObj, *clonedObj;
    //MultipleSequenceAlignment bufMA;
    QString traslId;
    Document* tmpDoc;
    QMap<qint64, QList<U2MaGap> > rowsGapModel;
    QMap<qint64, QList<U2MaGap> > emptyGapModel;
};


} // U2

#endif // _U2_MALIGNMENT_UTIL_TASKS
