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

#ifndef _U2_GENOME_ALIGNER_FIND_TASK_H_
#define _U2_GENOME_ALIGNER_FIND_TASK_H_

#include "GenomeAlignerSearchQuery.h"
#include "GenomeAlignerWriteTask.h"

#include <U2Core/Task.h>
#include <U2Core/U2Region.h>
#include <U2Core/DNASequence.h>
#include <U2Core/U2AssemblyUtils.h>

#include <QtCore/QMutex>
#include <QVector>
#include <QMutex>
#include <QSemaphore>
#include <memory>

#define ResType qint64

namespace U2 {

class GenomeAlignerIndex;
class FindInPartSubTask;
class PrepareVectorsSubTask;

class SearchContext {
public:
    SearchContext(): w(-1), ptMismatches(0), nMismatches(0), absMismatches(0), bestMode(false),
        openCL(false), useCUDA(0), minReadLength(-1), maxReadLength(-1) {}
    int w;
    int ptMismatches;
    int nMismatches;
    bool absMismatches;
    bool bestMode;
    bool openCL;
    bool useCUDA;
    int minReadLength;
    int maxReadLength;
    BMType bitFilter;
    QVector<SearchQuery*> queries;
};

#define MAX_PERCENTAGE 100
class GenomeAlignerFindTask : public Task {
    Q_OBJECT
    friend class ShortReadAligner;
public:
    GenomeAlignerFindTask(GenomeAlignerIndex *i, const SearchContext &s, GenomeAlignerWriteTask *writeTask);
    ~GenomeAlignerFindTask();
    virtual void run();
    virtual void prepare();

    void loadPartForAligning(int part);
    void getDataForAligning(int &first, int &length);
    bool runOpenCLBinarySearch();

    qint64 getIndexLoadTime() const {return indexLoadTime;}

private:
    GenomeAlignerIndex *index;
    GenomeAlignerWriteTask *writeTask;
    SearchContext *settings;
    QVector<BMType> bitValuesV;
    QVector<int> readNumbersV;
    QVector<int> positionsAtReadV;
    ResType *bitMaskResults;

    int alignerTaskCount;
    int waiterCount;
    int nextElementToGive;
    qint64 indexLoadTime;
    bool partLoaded;
    bool openCLFinished;

    QMutex loadPartMutex;
    QMutex shortReadsMutex;
    QMutex waitMutex;
    QWaitCondition waiter;
    QMutex openCLMutex;

    void prepareBitValues();

    static const int ALIGN_DATA_SIZE;
};

typedef QVector<SearchQuery*>::iterator QueryIter;

class ShortReadAligner : public Task {
    Q_OBJECT
public:
    ShortReadAligner(GenomeAlignerIndex *index, SearchContext *settings, GenomeAlignerWriteTask *writeTask);
    virtual void run();
private:
    GenomeAlignerIndex *index;
    SearchContext *settings;
    GenomeAlignerWriteTask *writeTask;
};

} //U2

#endif // _U2_GENOME_ALIGNER_FIND_TASK_H_
