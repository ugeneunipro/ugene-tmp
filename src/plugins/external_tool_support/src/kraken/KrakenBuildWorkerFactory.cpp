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

#include <limits>

#include <QThread>

#include <U2Core/AppContext.h>
#include <U2Core/AppResources.h>
#include <U2Core/AppSettings.h>

#include <U2Designer/DelegateEditors.h>

#include <U2Lang/ActorPrototypeRegistry.h>
#include <U2Lang/BaseSlots.h>
#include <U2Lang/BaseTypes.h>
#include <U2Lang/URLAttribute.h>
#include <U2Lang/WorkflowEnv.h>

#include "GenomicLibraryDelegate.h"
#include "KrakenBuildPrompter.h"
#include "KrakenBuildTaskSettings.h"
#include "KrakenBuildWorker.h"
#include "KrakenBuildWorkerFactory.h"
#include "KrakenSupport.h"
#include "MinimizerLengthValidator.h"

namespace U2 {
namespace LocalWorkflow {

const QString KrakenBuildWorkerFactory::ACTOR_ID = "build-kraken-database";

const QString KrakenBuildWorkerFactory::OUTPUT_PORT_ID = "out";

const QString KrakenBuildWorkerFactory::MODE_ATTR_ID = "mode";
const QString KrakenBuildWorkerFactory::INPUT_DATABASE_NAME_ATTR_ID = "input-database-name";
const QString KrakenBuildWorkerFactory::NEW_DATABASE_NAME_ATTR_ID = "new-database-name";
const QString KrakenBuildWorkerFactory::GENOMIC_LIBRARY_ATTR_ID = "genomic-library";
const QString KrakenBuildWorkerFactory::SHRINK_LIMIT_ATTR_ID = "shrink-limit";
const QString KrakenBuildWorkerFactory::K_MER_LENGTH_ATTR_ID = "k-mer-length";
const QString KrakenBuildWorkerFactory::MINIMIZER_LENGTH_ATTR_ID = "minimizer-length";
const QString KrakenBuildWorkerFactory::MAXIMUM_DATABASE_SIZE_ATTR_ID = "maximum-database-size";
const QString KrakenBuildWorkerFactory::SHRINK_BLOCK_OFFSET_ATTR_ID = "shrink-block-offset";
const QString KrakenBuildWorkerFactory::CLEAN_ATTR_ID = "clean";
const QString KrakenBuildWorkerFactory::WORK_ON_DISK_ATTR_ID = "work-on-disk";
const QString KrakenBuildWorkerFactory::JELLYFISH_HASH_SIZE_ATTR_ID = "jellyfish-hash-size";
const QString KrakenBuildWorkerFactory::THREADS_NUMBER_ATTR_ID = "threads-number";

const QString KrakenBuildWorkerFactory::BUILD_MODE_TEXT = QObject::tr("Build");
const QString KrakenBuildWorkerFactory::SHRINK_MODE_TEXT = QObject::tr("Shrink");

KrakenBuildWorkerFactory::KrakenBuildWorkerFactory()
    : DomainFactory(ACTOR_ID)
{

}

Worker *KrakenBuildWorkerFactory::createWorker(Actor *actor) {
    return new KrakenBuildWorker(actor);
}

void KrakenBuildWorkerFactory::init() {
    QList<PortDescriptor *> ports;
    {
        const Descriptor outSlotDesc(BaseSlots::URL_SLOT().getId(), KrakenBuildPrompter::tr("Output URL"), KrakenBuildPrompter::tr("Output URL."));

        QMap<Descriptor, DataTypePtr> outType;
        outType[outSlotDesc] = BaseTypes::STRING_TYPE();

        const Descriptor outPortDesc(OUTPUT_PORT_ID, KrakenBuildPrompter::tr("Output Kraken database"), KrakenBuildPrompter::tr("URL to the folder with the Kraken database."));
        ports << new PortDescriptor(outPortDesc, DataTypePtr(new MapDataType(ACTOR_ID + "-out", outType)), false /*input*/, true /*multi*/);
    }

    QList<Attribute *> attributes;
    {
        const Descriptor modeDesc(MODE_ATTR_ID, KrakenBuildPrompter::tr("Mode"),
                                  KrakenBuildPrompter::tr("Select \"Build\" to create a new database from a genomic library (--build).\n\n"
                                                          "Select \"Shrink\" to shrink an existing database to have only specified number of k-mers (--shrink)."));

        const Descriptor inputDatabaseNameDesc(INPUT_DATABASE_NAME_ATTR_ID, KrakenBuildPrompter::tr("Input database name"),
                                               KrakenBuildPrompter::tr("Name of the input database that should be shrunk (corresponds to --db that is used with --shrink)."));

        const Descriptor newDatabaseNameDesc(NEW_DATABASE_NAME_ATTR_ID, KrakenBuildPrompter::tr("New database name"),
                                             KrakenBuildPrompter::tr("The name of the output Kraken database (corresponds to --db that is used with --build, and to --new-db that is used with --shrink)."));

        const Descriptor genomicLibraryDesc(GENOMIC_LIBRARY_ATTR_ID, KrakenBuildPrompter::tr("Genomic library"),
                                            KrakenBuildPrompter::tr("Genomes that should be used to build the database.\n\n"
                                                                    "The genomes should be specified in FASTA format. The sequence IDs must contain either a GI number or a taxonomy ID (see documentation for details)."));

        const Descriptor shrinkLimitDesc(SHRINK_LIMIT_ATTR_ID, KrakenBuildPrompter::tr("Shrink limit"),
                                         KrakenBuildPrompter::tr("Count of k-mers to move from the original database to a new one (--shrink)."));

        const Descriptor kMerLengthDesc(K_MER_LENGTH_ATTR_ID, KrakenBuildPrompter::tr("K-mer length"),
                                        KrakenBuildPrompter::tr("K-mer length in bp (--kmer-len)."));

        const Descriptor minimizerLengthDesc(MINIMIZER_LENGTH_ATTR_ID, KrakenBuildPrompter::tr("Minimizer length"),
                                             KrakenBuildPrompter::tr("Minimizer length in bp (--minimizer-len).\n\n"
                                                                     "The minimizers serve to keep k-mers that are adjacent in query sequences close to each other in the database, which allows Kraken to exploit the CPU cache.\n\n"
                                                                     "Changing the value of the parameter can significantly affect the speed of Kraken, and neither increasing nor decreasing of the value will guarantee faster or slower speed."));

        const Descriptor maximumDatabaseSizeDesc(MAXIMUM_DATABASE_SIZE_ATTR_ID, KrakenBuildPrompter::tr("Maximum database size"),
                                                 KrakenBuildPrompter::tr("By default, a full database build is done.\n\n"
                                                                         "To shrink the database before the full build, input the size of the database in Mb (--max-db-size). The size is specified together for the database and the index."));

        const Descriptor shrinkBlockOffsetDesc(SHRINK_BLOCK_OFFSET_ATTR_ID, KrakenBuildPrompter::tr("Shrink block offset"),
                                               KrakenBuildPrompter::tr("When shrinking, select the k-mer that is NUM positions from the end of a block of k-mers (--shrink-block-offset)."));

        const Descriptor cleanDesc(CLEAN_ATTR_ID, KrakenBuildPrompter::tr("Clean"),
                                   KrakenBuildPrompter::tr("Remove unneeded files from a built database to reduce the disk usage (--clean)."));

        const Descriptor workOnDiskDesc(WORK_ON_DISK_ATTR_ID, KrakenBuildPrompter::tr("Work on disk"),
                                        KrakenBuildPrompter::tr("Perform most operations on disk rather than in RAM (this will slow down build in most cases)."));

        const Descriptor jellyfishHashSizeDesc(JELLYFISH_HASH_SIZE_ATTR_ID, KrakenBuildPrompter::tr("Jellyfish hash size"),
                                               KrakenBuildPrompter::tr("The \"kraken-build\" tool uses the \"jellyfish\" tool. This parameter specifies the hash size for Jellyfish.\n\n"
                                                                       "Supply a smaller hash size to Jellyfish, if you encounter problems with allocating enough memory during the build process (--jellyfish-hash-size)."));

        const Descriptor threadNumberDesc(THREADS_NUMBER_ATTR_ID, KrakenBuildPrompter::tr("Number of threads"),
                                          KrakenBuildPrompter::tr("Use multiple threads (--threads)."));

        Attribute *modeAttribute = new Attribute(modeDesc, BaseTypes::STRING_TYPE(), false, KrakenBuildTaskSettings::BUILD);
        Attribute *inputDatabaseNameAttribute = new Attribute(inputDatabaseNameDesc, BaseTypes::STRING_TYPE(), true);
        Attribute *newDatabaseName = new Attribute(newDatabaseNameDesc, BaseTypes::STRING_TYPE(), true);
        Attribute *genomicLibraryAttribute = new URLAttribute(genomicLibraryDesc, BaseTypes::URL_DATASETS_TYPE(), true);
        Attribute *shrinkLimitAttribute = new Attribute(shrinkLimitDesc, BaseTypes::NUM_TYPE(), true, 100000000);
        Attribute *kMerLengthAttribute = new Attribute(kMerLengthDesc, BaseTypes::NUM_TYPE(), false, 31);
        Attribute *minimizerLengthAttribute = new Attribute(minimizerLengthDesc, BaseTypes::NUM_TYPE(), false, 15);;
        Attribute *maximumDatabaseSizeAttribute = new Attribute(maximumDatabaseSizeDesc, BaseTypes::NUM_TYPE(), false, 0);
        Attribute *shrinkBlockOffsetAttribute = new Attribute(shrinkBlockOffsetDesc, BaseTypes::NUM_TYPE(), false, 1);
        Attribute *cleanAttribute = new Attribute(cleanDesc, BaseTypes::BOOL_TYPE(), false, true);
        Attribute *workOnDiskAttribute = new Attribute(workOnDiskDesc, BaseTypes::BOOL_TYPE(), false, false);
        Attribute *jellyfishHashSizeAttribute = new Attribute(jellyfishHashSizeDesc, BaseTypes::NUM_TYPE(), false, 0);
        Attribute *threadNumberAttribute = new Attribute(threadNumberDesc, BaseTypes::NUM_TYPE(), false, AppContext::getAppSettings()->getAppResourcePool()->getIdealThreadCount());

        attributes << modeAttribute;
        attributes << inputDatabaseNameAttribute;
        attributes << newDatabaseName;
        attributes << genomicLibraryAttribute;
        attributes << shrinkLimitAttribute;
        attributes << kMerLengthAttribute;
        attributes << minimizerLengthAttribute;
        attributes << maximumDatabaseSizeAttribute;
        attributes << shrinkBlockOffsetAttribute;
        attributes << cleanAttribute;
        attributes << workOnDiskAttribute;
        attributes << jellyfishHashSizeAttribute;
        attributes << threadNumberAttribute;

        inputDatabaseNameAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::SHRINK));
        genomicLibraryAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::BUILD));
        shrinkLimitAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::SHRINK));
        maximumDatabaseSizeAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::BUILD));
        shrinkBlockOffsetAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::SHRINK));
        cleanAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::BUILD));
        jellyfishHashSizeAttribute->addRelation(new VisibilityRelation(MODE_ATTR_ID, KrakenBuildTaskSettings::BUILD));
    }

    QMap<QString, PropertyDelegate *> delegates;
    {
        QVariantMap modeValues;
        modeValues[BUILD_MODE_TEXT] = KrakenBuildTaskSettings::BUILD;
        modeValues[SHRINK_MODE_TEXT] = KrakenBuildTaskSettings::SHRINK;
        delegates[MODE_ATTR_ID] = new ComboBoxDelegate(modeValues);

        delegates[INPUT_DATABASE_NAME_ATTR_ID] = new URLDelegate("", "kraken/database", false, true, false);
        delegates[NEW_DATABASE_NAME_ATTR_ID] = new URLDelegate("", "kraken/database", false, true, true);
        delegates[GENOMIC_LIBRARY_ATTR_ID] = new GenomicLibraryDelegate();

        QVariantMap shrinkLimitProperties;
        shrinkLimitProperties["minimum"] = 1;
        shrinkLimitProperties["maximum"] = std::numeric_limits<int>::max();
        shrinkLimitProperties["accelerated"] = true;
        delegates[SHRINK_LIMIT_ATTR_ID] = new SpinBoxDelegate(shrinkLimitProperties);

        QVariantMap kMerLengthProperties;
        kMerLengthProperties["minimum"] = 3;
        kMerLengthProperties["maximum"] = 31;
        delegates[K_MER_LENGTH_ATTR_ID] = new SpinBoxDelegate(kMerLengthProperties);

        QVariantMap minimizerLengthProperties;
        minimizerLengthProperties["minimum"] = 1;
        minimizerLengthProperties["maximum"] = 30;
        delegates[MINIMIZER_LENGTH_ATTR_ID] = new SpinBoxDelegate(minimizerLengthProperties);

        QVariantMap maximumDatabaseSizeProperties;
        maximumDatabaseSizeProperties["minimum"] = 0;
        maximumDatabaseSizeProperties["maximum"] = std::numeric_limits<int>::max();
        maximumDatabaseSizeProperties["suffix"] = " Mb";
        maximumDatabaseSizeProperties["specialValueText"] = KrakenBuildPrompter::tr("No limit");
        maximumDatabaseSizeProperties["accelerated"] = true;
        delegates[MAXIMUM_DATABASE_SIZE_ATTR_ID] = new SpinBoxDelegate(maximumDatabaseSizeProperties);

        QVariantMap shrinkBlockOffsetProperties;
        shrinkBlockOffsetProperties["minimum"] = 1;
        shrinkBlockOffsetProperties["maximum"] = std::numeric_limits<int>::max();
        delegates[SHRINK_BLOCK_OFFSET_ATTR_ID] = new SpinBoxDelegate(shrinkBlockOffsetProperties);

        delegates[CLEAN_ATTR_ID] = new ComboBoxWithBoolsDelegate();
        delegates[WORK_ON_DISK_ATTR_ID] = new ComboBoxWithBoolsDelegate();

        QVariantMap jelyfishHashSizeProperties;
        jelyfishHashSizeProperties["minimum"] = 0;
        jelyfishHashSizeProperties["maximum"] = std::numeric_limits<int>::max();
        jelyfishHashSizeProperties["suffix"] = " M";
        jelyfishHashSizeProperties["specialValueText"] = KrakenBuildPrompter::tr("Auto");
        delegates[JELLYFISH_HASH_SIZE_ATTR_ID] = new SpinBoxDelegate(jelyfishHashSizeProperties);

        QVariantMap threadsNumberProperties;
        threadsNumberProperties["minimum"] = 1;
        threadsNumberProperties["maximum"] = QThread::idealThreadCount();
        delegates[THREADS_NUMBER_ATTR_ID] = new SpinBoxDelegate(threadsNumberProperties);
    }

    const Descriptor desc(ACTOR_ID, KrakenBuildPrompter::tr("Build Kraken Database"),
                          KrakenBuildPrompter::tr("Build a Kraken database from a genomic library or shrink a Kraken database."));

    ActorPrototype *proto = new IntegralBusActorPrototype(desc, ports, attributes);
    proto->setEditor(new DelegateEditor(delegates));
    proto->setPrompter(new KrakenBuildPrompter(NULL));
    proto->addExternalTool(KrakenSupport::BUILD_TOOL);
    proto->setValidator(new MinimizerLengthValidator());
    WorkflowEnv::getProtoRegistry()->registerProto(KrakenBuildPrompter::tr("NGS: Reads Classification"), proto);     // TODO: replace the category name with a constant after extracting to a separate plugin

    DomainFactory *localDomain = WorkflowEnv::getDomainRegistry()->getById(LocalDomainFactory::ID);
    localDomain->registerEntry(new KrakenBuildWorkerFactory());
}

}   // namespace LocalWorkflow
}   // namespace U2
