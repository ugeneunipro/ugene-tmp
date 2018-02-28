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

#ifndef _U2_ENSEMBLE_CLASSIFICATION_H_
#define _U2_ENSEMBLE_CLASSIFICATION_H_

#include <U2Lang/LocalDomain.h>
#include <U2Lang/WorkflowUtils.h>

namespace U2 {
namespace LocalWorkflow {

class EnsembleClassificationPrompter;
typedef PrompterBase<EnsembleClassificationPrompter> EnsembleClassificationBase;

class EnsembleClassificationPrompter : public EnsembleClassificationBase {
    Q_OBJECT
public:
    EnsembleClassificationPrompter(Actor* p = 0) : EnsembleClassificationBase(p) {}
protected:
    QString composeRichDoc();
};

class EnsembleClassificationWorker: public BaseWorker {
    Q_OBJECT
public:
    EnsembleClassificationWorker(Actor *a);
protected:
    void init();
    Task * tick();
    void cleanup() {}

private:

protected:
    IntegralBus *input;
    IntegralBus *output;
    QString outputFile;
    bool tripleInput;
};

class EnsembleClassificationWorkerFactory : public DomainFactory {
    static const QString ACTOR_ID;
public:
    static void init();
    static void cleanup();
    EnsembleClassificationWorkerFactory() : DomainFactory(ACTOR_ID) {}
    Worker* createWorker(Actor* a) { return new EnsembleClassificationWorker(a); }
};

} //LocalWorkflow
} //U2

#endif
