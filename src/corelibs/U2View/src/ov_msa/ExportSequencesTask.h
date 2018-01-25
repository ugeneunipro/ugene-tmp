/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2017 UniPro <ugene@unipro.ru>
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

#ifndef _U2_EXPORT_SEQUENCES_TASK
#define _U2_EXPORT_SEQUENCES_TASK

#include <U2Core/DNASequence.h>
#include <U2Core/MultipleSequenceAlignment.h>
#include <U2Core/Task.h>

namespace U2 {

class PrepareSequenceObjectsTask : public Task {
public:
    PrepareSequenceObjectsTask(const MultipleSequenceAlignment& msa, const QStringList& seqNames, bool trimGaps);

    void run();

    QList<DNASequence> getSequences() const;
private:
    const MultipleSequenceAlignment msa;
    QStringList seqNames;
    bool trimGaps;
    QList<DNASequence> sequences;
};

class ExportSequencesTask : public Task {
public:
    ExportSequencesTask(const MultipleSequenceAlignment& msa, const QStringList& seqNames, bool trimGaps, bool addToProjectFlag,
        const QString& dirUrl, const DocumentFormatId& format, const QString& extension, const QString& customFileName = QString());

    void prepare();
protected:
    QList<Task*> onSubTaskFinished(Task* subTask);
private:
    const MultipleSequenceAlignment msa;
    QStringList seqNames;
    bool trimGaps;
    bool addToProjectFlag;
    QString dirUrl;
    DocumentFormatId format;
    QString extension;
    QString customFileName;
    PrepareSequenceObjectsTask *prepareObjectsTask;
};

}

#endif