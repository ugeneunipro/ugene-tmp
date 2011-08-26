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

#include <U2Core/AppContext.h>

#include <U2Core/DNAAlphabet.h>
#include <U2Core/DataBaseRegistry.h>
#include <U2Core/ExternalToolRegistry.h>

#include <U2View/MSAEditor.h>
#include <U2View/MSAEditorFactory.h>
#include <U2View/DnaAssemblyUtils.h>
#include <U2Core/MAlignmentObject.h>

#include <U2Core/GAutoDeleteList.h>
#include <U2View/AnnotatedDNAView.h>
#include <U2View/ADVSequenceObjectContext.h>
#include <U2View/ADVConstants.h>
#include <U2View/ADVUtils.h>

#include <U2Core/DNASequenceSelection.h>
#include <U2Core/DNASequenceObject.h>
#include <U2Gui/GUIUtils.h>

#include <U2Test/XMLTestFormat.h>
#include <U2Test/GTest.h>
#include <U2Test/GTestFrameworkComponents.h>

#include <QtGui/QMenu>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QFileInfo>

#include "ExternalToolSupportPlugin.h"
#include "ExternalToolSupportSettings.h"
#include "ExternalToolSupportSettingsController.h"
#include "utils/ExternalToolSupportAction.h"
#include "utils/ExternalToolValidateTask.h"
#include "ETSProjectViewItemsContoller.h"

#include "clustalw/ClustalWSupport.h"
#include "clustalw/ClustalWWorker.h"
#include "mafft/MAFFTSupport.h"
#include "mafft/MAFFTWorker.h"
#include "tcoffee/TCoffeeSupport.h"
#include "tcoffee/TCoffeeWorker.h"
#include "blast/FormatDBSupport.h"
#include "blast/BlastAllSupport.h"
#include "blast/BlastAllWorker.h"
#include "blast_plus/BlastPlusSupport.h"
#include "blast_plus/BlastPlusWorker.h"
#include "cap3/CAP3Support.h"
#include "bowtie/BowtieSupport.h"
#include "bowtie/BowtieTask.h"
#include "bowtie/BowtieSettingsWidget.h"
#include "bowtie/bowtie_tests/bowtieTests.h"

#include <U2Algorithm/CDSearchTaskFactoryRegistry.h>
#include <U2Algorithm/DnaAssemblyAlgRegistry.h>
#include <blast_plus/RPSBlastSupportTask.h>


#define EXTERNAL_TOOL_SUPPORT_FACTORY_ID "ExternalToolSupport"

namespace U2 {

extern "C" Q_DECL_EXPORT Plugin * U2_PLUGIN_INIT_FUNC() {
    ExternalToolSupportPlugin * plug = new ExternalToolSupportPlugin();
    return plug;
}


ExternalToolSupportPlugin::ExternalToolSupportPlugin():Plugin(tr("External tool support"),tr("Runs other external tools")) {

    //Fill ExternalToolRegistry with supported tools
    //ClustalW
    ClustalWSupport* clustalWTool=new ClustalWSupport(CLUSTAL_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(clustalWTool);

    //MAFFT
    MAFFTSupport* mAFFTTool=new MAFFTSupport(MAFFT_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(mAFFTTool);

    //T-Coffee
    TCoffeeSupport* tCoffeeTool=new TCoffeeSupport(TCOFFEE_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(tCoffeeTool);

    if (AppContext::getMainWindow()) {
        clustalWTool->getViewContext()->setParent(this);
        clustalWTool->getViewContext()->init();

        ExternalToolSupprotAction* clustalWAction = new ExternalToolSupprotAction(tr("ClustalW..."), this, QStringList(CLUSTAL_TOOL_NAME));
        connect(clustalWAction, SIGNAL(triggered()), clustalWTool, SLOT(sl_runWithExtFileSpecify()));

        mAFFTTool->getViewContext()->setParent(this);
        mAFFTTool->getViewContext()->init();

        ExternalToolSupprotAction* mAFFTAction= new ExternalToolSupprotAction(tr("MAFFT..."), this, QStringList(MAFFT_TOOL_NAME));
        connect(mAFFTAction, SIGNAL(triggered()), mAFFTTool, SLOT(sl_runWithExtFileSpecify()));

        tCoffeeTool->getViewContext()->setParent(this);
        tCoffeeTool->getViewContext()->init();

        ExternalToolSupprotAction* tCoffeeAction= new ExternalToolSupprotAction(tr("T-Coffee..."), this, QStringList(TCOFFEE_TOOL_NAME));
        connect(tCoffeeAction, SIGNAL(triggered()), tCoffeeTool, SLOT(sl_runWithExtFileSpecify()));

        //Add to menu MA
        QMenu* tools = AppContext::getMainWindow()->getTopLevelMenu(MWMENU_TOOLS);
        QMenu* toolsSubmenu = tools->findChild<QMenu*>(MWMENU_TOOLS_MALIGN);
        if(toolsSubmenu == NULL){
            toolsSubmenu = tools->addMenu(tr("Multiple alignment"));
            toolsSubmenu->setObjectName(MWMENU_TOOLS_MALIGN);
        }

        toolsSubmenu->setIcon(QIcon(":core/images/msa.png"));//bad code
        toolsSubmenu->addAction(clustalWAction);
        toolsSubmenu->addAction(mAFFTAction);
        toolsSubmenu->addAction(tCoffeeAction);
    }
    //FormatDB
    FormatDBSupport* formatDBTool = new FormatDBSupport(FORMATDB_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(formatDBTool);

    //MakeBLASTDB from BLAST+
    FormatDBSupport* makeBLASTDBTool = new FormatDBSupport(MAKEBLASTDB_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(makeBLASTDBTool);

    //BlastAll
    BlastAllSupport* blastallTool = new BlastAllSupport(BLASTALL_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(blastallTool);

    BlastPlusSupport* blastNPlusTool = new BlastPlusSupport(BLASTN_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(blastNPlusTool);
    BlastPlusSupport* blastPPlusTool = new BlastPlusSupport(BLASTP_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(blastPPlusTool);
    BlastPlusSupport* blastXPlusTool = new BlastPlusSupport(BLASTX_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(blastXPlusTool);
    BlastPlusSupport* tBlastNPlusTool = new BlastPlusSupport(TBLASTN_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(tBlastNPlusTool);
    BlastPlusSupport* tBlastXPlusTool = new BlastPlusSupport(TBLASTX_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(tBlastXPlusTool);
    BlastPlusSupport* rpsblastTool = new BlastPlusSupport(RPSBLAST_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(rpsblastTool);
    CAP3Support* cap3Tool = new CAP3Support(CAP3_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(cap3Tool);
    BowtieSupport* bowtieSupport = new BowtieSupport(BOWTIE_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(bowtieSupport);
    BowtieSupport* bowtieBuildSupport = new BowtieSupport(BOWTIE_BUILD_TOOL_NAME);
    AppContext::getExternalToolRegistry()->registerEntry(bowtieBuildSupport);


    if (AppContext::getMainWindow()) {
        ExternalToolSupprotAction* formatDBAction= new ExternalToolSupprotAction(tr("FormatDB..."), this, QStringList(FORMATDB_TOOL_NAME));
        connect(formatDBAction, SIGNAL(triggered()), formatDBTool, SLOT(sl_runWithExtFileSpecify()));

        ExternalToolSupprotAction* makeBLASTDBAction= new ExternalToolSupprotAction(tr("BLAST+ make DB..."), this, QStringList(MAKEBLASTDB_TOOL_NAME));
        connect(makeBLASTDBAction, SIGNAL(triggered()), makeBLASTDBTool, SLOT(sl_runWithExtFileSpecify()));

        blastallTool->getViewContext()->setParent(this);
        blastallTool->getViewContext()->init();

        ExternalToolSupprotAction* blastallAction= new ExternalToolSupprotAction(tr("BLAST Search..."), this, QStringList(BLASTALL_TOOL_NAME));
        connect(blastallAction, SIGNAL(triggered()), blastallTool, SLOT(sl_runWithExtFileSpecify()));

        BlastPlusSupportContext* blastPlusViewCtx = new BlastPlusSupportContext(this);
        blastPlusViewCtx->setParent(this);//may be problems???
        blastPlusViewCtx->init();
        QStringList toolList;
        toolList << BLASTN_TOOL_NAME << BLASTP_TOOL_NAME << BLASTX_TOOL_NAME << TBLASTN_TOOL_NAME << TBLASTX_TOOL_NAME << RPSBLAST_TOOL_NAME;
        ExternalToolSupprotAction* blastPlusAction= new ExternalToolSupprotAction(tr("BLAST+ Search..."), this, toolList);
        connect(blastPlusAction, SIGNAL(triggered()), blastNPlusTool, SLOT(sl_runWithExtFileSpecify()));
        
        //Add to menu NCBI Toolkit
        QMenu* tools = AppContext::getMainWindow()->getTopLevelMenu(MWMENU_TOOLS);
        QMenu* blastSubmenu = tools->addMenu(tr("BLAST"));
        blastSubmenu->setIcon(QIcon(":external_tool_support/images/ncbi.png"));
        blastSubmenu->addAction(formatDBAction);
        blastSubmenu->addAction(blastallAction);
        blastSubmenu->addAction(makeBLASTDBAction);
        blastSubmenu->addAction(blastPlusAction);
        
        ExternalToolSupprotAction* cap3Action = new ExternalToolSupprotAction(QString("Contig assembly with %1").arg(cap3Tool->getName()), this, QStringList(cap3Tool->getName()));
        connect(cap3Action, SIGNAL(triggered()), cap3Tool, SLOT(sl_runWithExtFileSpecify()));
        QMenu* assemblySumbenu = tools->findChild<QMenu*>(MWMENU_TOOLS_ASSEMBLY);
        assemblySumbenu->addAction(cap3Action);
    }

    AppContext::getCDSFactoryRegistry()->registerFactory(new CDSearchLocalTaskFactory(), CDSearchFactoryRegistry::LocalSearch);

    AppContext::getDnaAssemblyAlgRegistry()->registerAlgorithm(new DnaAssemblyAlgorithmEnv(BowtieTask::taskName, new BowtieTaskFactory(), new BowtieGUIExtensionsFactory(), true, false));

    {
        GTestFormatRegistry *tfr = AppContext::getTestFramework()->getTestFormatRegistry();
        XMLTestFormat *xmlTestFormat = qobject_cast<XMLTestFormat *>(tfr->findFormat("XML"));
        assert(NULL != xmlTestFormat);

        GAutoDeleteList<XMLTestFactory> *l = new GAutoDeleteList<XMLTestFactory>(this);
        l->qlist = BowtieTests::createTestFactories();

        foreach(XMLTestFactory *f, l->qlist) {
            bool res = xmlTestFormat->registerTestFactory(f);
            Q_UNUSED(res);
            assert(res);
        }
    }

    //Read settings
    ExternalToolSupportSettings::getExternalTools();

    //Search in tools path
#ifdef Q_OS_WIN
    QString clustalWPath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"\\tools\\clustalw2.exe");
    if(AppContext::getExternalToolRegistry()->getByName(CLUSTAL_TOOL_NAME)->getPath().isEmpty()){
        QFileInfo clustalExe(clustalWPath);
        if(clustalExe.exists()){
            AppContext::getExternalToolRegistry()->getByName(CLUSTAL_TOOL_NAME)->setPath(clustalWPath);
        }
    }

    QString cap3Path = QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"\\tools\\cap3.exe");
    if(AppContext::getExternalToolRegistry()->getByName(CAP3_TOOL_NAME)->getPath().isEmpty()){
        QFileInfo cap3Exe(cap3Path);
        if(cap3Exe.exists()){
            AppContext::getExternalToolRegistry()->getByName(CAP3_TOOL_NAME)->setPath(cap3Path);
        }
    }

    QString bowtiePath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"\\tools\\bowtie.exe");
    if(AppContext::getExternalToolRegistry()->getByName(BOWTIE_TOOL_NAME)->getPath().isEmpty()){
        QFileInfo bowtieExe(bowtiePath);
        if(bowtieExe.exists()){
            AppContext::getExternalToolRegistry()->getByName(BOWTIE_TOOL_NAME)->setPath(bowtiePath);
        }
    }

    QString bowtieBuildPath = QDir::toNativeSeparators(QCoreApplication::applicationDirPath()+"\\tools\\bowtie-build.exe");
    if(AppContext::getExternalToolRegistry()->getByName(BOWTIE_BUILD_TOOL_NAME)->getPath().isEmpty()){
        QFileInfo bowtieBuildExe(bowtieBuildPath);
        if(bowtieBuildExe.exists()){
            AppContext::getExternalToolRegistry()->getByName(BOWTIE_BUILD_TOOL_NAME)->setPath(bowtieBuildPath);
        }
    }



#endif


    QStringList envList = QProcess::systemEnvironment();
    if(envList.indexOf(QRegExp("PATH=.*",Qt::CaseInsensitive))>=0){
        QString pathEnv = envList.at(envList.indexOf(QRegExp("PATH=.*",Qt::CaseInsensitive)));
#ifdef Q_OS_LINUX
        QStringList paths = pathEnv.split("=").at(1).split(":");
#else
    #ifdef Q_OS_WIN
        QStringList paths = pathEnv.split("=").at(1).split(";");
    #else
        QStringList paths;
    #endif
#endif
        foreach(ExternalTool* curTool, AppContext::getExternalToolRegistry()->getAllEntries()){
            foreach(QString curPath, paths){
                if(curTool->getPath().isEmpty()){
                    QString exePath = curPath+"/"+curTool->getExecutableFileName();
                    QFileInfo fileExe(exePath);
                    if(fileExe.exists() && (curTool->getPath()=="")){
                        //curTool->setPath(exePath);
                        ExternalToolValidateTask* validateTask=new ExternalToolValidateTask(curTool->getName(), exePath);
                        connect(validateTask,SIGNAL(si_stateChanged()),SLOT(sl_validateTaskStateChanged()));
                        AppContext::getTaskScheduler()->registerTopLevelTask(validateTask);
                    }
                }
            }
        }
    }



    if (AppContext::getMainWindow()) {
        //Add viewer for settings
        AppContext::getAppSettingsGUI()->registerPage(new ExternalToolSupportSettingsPageController());
    }
    //Add new workers to WD
    LocalWorkflow::ClustalWWorkerFactory::init();
    LocalWorkflow::MAFFTWorkerFactory::init();
    LocalWorkflow::BlastAllWorkerFactory::init();
    LocalWorkflow::BlastPlusWorkerFactory::init();
    LocalWorkflow::TCoffeeWorkerFactory::init();

    if (AppContext::getMainWindow()) {
        //Add project view service
        services.push_back(new ExternalToolSupportService());
    }
}

ExternalToolSupportPlugin::~ExternalToolSupportPlugin(){
    ExternalToolSupportSettings::setExternalTools();
}
void ExternalToolSupportPlugin::sl_validateTaskStateChanged(){
    ExternalToolValidateTask* s=qobject_cast<ExternalToolValidateTask*>(sender());
    assert(s);
    if(s->isFinished()){
        AppContext::getExternalToolRegistry()->getByName(s->getToolName())->setValid(s->isValidTool());
        AppContext::getExternalToolRegistry()->getByName(s->getToolName())->setVersion(s->getToolVersion());
        AppContext::getExternalToolRegistry()->getByName(s->getToolName())->setPath(s->getToolPath());
    }
}
//////////////////////////////////////////////////////////////////////////
// Service
ExternalToolSupportService::ExternalToolSupportService()
: Service(Service_ExternalToolSupport, tr("External tools support"), tr("Provides support to run external tools from UGENE"), QList<ServiceType>() << Service_ProjectView)
{
    projectViewController = NULL;
}

void ExternalToolSupportService::serviceStateChangedCallback(ServiceState oldState, bool enabledStateChanged) {
    Q_UNUSED(oldState);

    if (!enabledStateChanged) {
        return;
    }
    if (isEnabled()) {
        projectViewController = new ETSProjectViewItemsContoller(this);
    } else {
        delete projectViewController; projectViewController = NULL;
    }
}

}
