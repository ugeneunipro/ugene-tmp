include (external_tool_support.pri)

# Input
HEADERS += src/ETSProjectViewItemsContoller.h \
           src/ExternalToolManager.h \
           src/ExternalToolSupportL10N.h \
           src/ExternalToolSupportPlugin.h \
           src/ExternalToolSupportSettings.h \
           src/ExternalToolSupportSettingsController.h \
           src/RnaSeqCommon.h \
           src/RunnerTool.h \
           src/TaskLocalStorage.h \
           src/bedtools/BedtoolsIntersectTask.h \
           src/bedtools/BedToolsWorkersLibrary.h \
           src/bedtools/BedtoolsSupport.h \
           src/bedtools/BedtoolsSupportTask.h \
           src/bigWigTools/BigWigSupport.h \
           src/bigWigTools/BedGraphToBigWigTask.h \
           src/bigWigTools/BedGraphToBigWigWorker.h \
           src/blast/FormatDBSupport.h \
           src/blast/FormatDBSupportRunDialog.h \
           src/blast/FormatDBSupportTask.h \
           src/blast/PrepareInputFastaFilesTask.h \
           src/blast_plus/AlignToReferenceBlastDialog.h \
           src/blast_plus/AlignToReferenceBlastWorker.h \
           src/blast_plus/BlastDBCmdDialog.h \
           src/blast_plus/BlastDBCmdSupport.h \
           src/blast_plus/BlastDBCmdSupportTask.h \
           src/blast_plus/BlastNPlusSupportTask.h \
           src/blast_plus/BlastPlusSupport.h \
           src/blast_plus/BlastPlusSupportCommonTask.h \
           src/blast_plus/BlastPlusSupportRunDialog.h \
           src/blast_plus/BlastPlusWorker.h \
           src/blast_plus/BlastPPlusSupportTask.h \
           src/blast_plus/BlastXPlusSupportTask.h \
           src/blast_plus/RPSBlastSupportTask.h \
           src/blast_plus/TBlastNPlusSupportTask.h \
           src/blast_plus/TBlastXPlusSupportTask.h \
           src/blast_plus/align_worker_subtasks/BlastReadsSubTask.h \
           src/blast_plus/align_worker_subtasks/ComposeResultSubTask.h \
           src/blast_plus/align_worker_subtasks/FormatDBSubTask.h \
           src/blast_plus/align_worker_subtasks/PrepareReferenceSequenceTask.h \
           src/blast_plus/align_worker_subtasks/RemoveGapsFromSequenceTask.h \
           src/bowtie/bowtie_tests/bowtieTests.h \
           src/bowtie/BowtieSettingsWidget.h \
           src/bowtie/BowtieSupport.h \
           src/bowtie/BowtieTask.h \
           src/bowtie/BowtieWorker.h \
           src/bowtie2/bowtie2_tests/Bowtie2Tests.h \
           src/bowtie2/Bowtie2Support.h \
           src/bowtie2/Bowtie2Task.h \
           src/bowtie2/Bowtie2SettingsWidget.h \
           src/bowtie2/Bowtie2Worker.h \
           src/bwa/bwa_tests/bwaTests.h \
           src/bwa/BwaSettingsWidget.h \
           src/bwa/BwaSupport.h \
           src/bwa/BwaTask.h \
           src/bwa/BwaMemWorker.h \
           src/bwa/BwaWorker.h \
           src/cap3/CAP3Support.h \
           src/cap3/CAP3SupportDialog.h \
           src/cap3/CAP3SupportTask.h \
           src/cap3/CAP3Worker.h \
           src/ceas/CEASReportWorker.h \
           src/ceas/CEASSettings.h \
           src/ceas/CEASSupport.h \
           src/ceas/CEASSupportTask.h \
           src/clustalo/ClustalOSupport.h \
           src/clustalo/ClustalOSupportRunDialog.h \
           src/clustalo/ClustalOSupportTask.h \
           src/clustalo/ClustalOWorker.h \
           src/clustalw/ClustalWSupport.h \
           src/clustalw/ClustalWSupportRunDialog.h \
           src/clustalw/ClustalWSupportTask.h \
           src/clustalw/ClustalWWorker.h \
           src/conduct_go/ConductGOSettings.h \
           src/conduct_go/ConductGOSupport.h \
           src/conduct_go/ConductGOTask.h \
           src/conduct_go/ConductGOWorker.h \
           src/conservation_plot/ConservationPlotSettings.h \
           src/conservation_plot/ConservationPlotSupport.h \
           src/conservation_plot/ConservationPlotTask.h \
           src/conservation_plot/ConservationPlotWorker.h \
           src/cufflinks/CuffdiffSupportTask.h \
           src/cufflinks/CuffdiffWorker.h \
           src/cufflinks/CufflinksSettings.h \
           src/cufflinks/CufflinksSupport.h \
           src/cufflinks/CufflinksSupportTask.h \
           src/cufflinks/CufflinksWorker.h \
           src/cufflinks/CuffmergeSupportTask.h \
           src/cufflinks/CuffmergeWorker.h \
           src/cufflinks/GffreadSupportTask.h \
           src/cufflinks/GffreadWorker.h \
           src/custom_tools/CustomToolConfigParser.h \
           src/custom_tools/ImportCustomToolsTask.h \
           src/custom_tools/ImportExternalToolDialog.h \
           src/custom_tools/LoadCustomExternalToolsTask.h \
           src/custom_tools/RegisterCustomToolTask.h \
           src/cutadapt/CutadaptSupport.h \
           src/cutadapt/CutadaptWorker.h \
           src/fastqc/FastqcSupport.h \
           src/fastqc/FastqcTask.h \
           src/fastqc/FastqcWorker.h \
           src/hmmer/ConvertAlignment2StockholmTask.h \
           src/hmmer/HmmerBuildDialog.h \
           src/hmmer/HmmerBuildFromFileTask.h \
           src/hmmer/HmmerBuildFromMsaTask.h \
           src/hmmer/HmmerBuildSettings.h \
           src/hmmer/HmmerBuildTask.h \
           src/hmmer/HmmerBuildTaskTest.h \
           src/hmmer/HmmerBuildWorker.h \
           src/hmmer/HmmerParseSearchResultsTask.h \
           src/hmmer/HmmerSearchDialog.h \
           src/hmmer/HmmerSearchSettings.h \
           src/hmmer/HmmerSearchTask.h \
           src/hmmer/HmmerSearchTaskTest.h \
           src/hmmer/HmmerSearchWorker.h \
           src/hmmer/HmmerSupport.h \
           src/hmmer/HmmerTests.h \
           src/hmmer/PhmmerSearchDialog.h \
           src/hmmer/PhmmerSearchSettings.h \
           src/hmmer/PhmmerSearchTask.h \
           src/hmmer/PhmmerSearchTaskTest.h \
           src/java/JavaSupport.h \
           src/macs/MACSSettings.h \
           src/macs/MACSSupport.h \
           src/macs/MACSTask.h \
           src/macs/MACSWorker.h \
           src/mafft/MafftAddToAlignmentTask.h \
           src/mafft/MAFFTSupport.h \
           src/mafft/MAFFTSupportRunDialog.h \
           src/mafft/MAFFTSupportTask.h \
           src/mafft/MAFFTWorker.h \
           src/mrbayes/MrBayesDialogWidget.h \
           src/mrbayes/MrBayesSupport.h \
           src/mrbayes/MrBayesTask.h \
           src/mrbayes/MrBayesTests.h \
           src/peak2gene/Gene2PeakFormatLoader.h \
           src/peak2gene/Peak2GeneFormatLoader.h \
           src/peak2gene/Peak2GeneSettings.h \
           src/peak2gene/Peak2GeneSupport.h \
           src/peak2gene/Peak2GeneTask.h \
           src/peak2gene/Peak2GeneWorker.h \
           src/perl/PerlSupport.h \
           src/phyml/PhyMLDialogWidget.h \
           src/phyml/PhyMLSupport.h \
           src/phyml/PhyMLTask.h \
           src/phyml/PhyMLTests.h \
           src/python/PythonSupport.h \
           src/R/RSupport.h \
           src/samtools/BcfToolsSupport.h \
           src/samtools/SamToolsExtToolSupport.h \
           src/samtools/TabixSupport.h \
           src/samtools/TabixSupportTask.h \
           src/seqpos/SeqPosSettings.h \
           src/seqpos/SeqPosSupport.h \
           src/seqpos/SeqPosTask.h \
           src/seqpos/SeqPosWorker.h \
           src/snpeff/SnpEffDatabaseDelegate.h \
           src/snpeff/SnpEffDatabaseListModel.h \
           src/snpeff/SnpEffDatabaseListTask.h \
           src/snpeff/SnpEffSupport.h \
           src/snpeff/SnpEffTask.h \
           src/snpeff/SnpEffWorker.h \
           src/spades/SpadesDelegate.h \
           src/spades/SpadesPortRelationDescriptor.h \
           src/spades/SpadesSettingsWidget.h \
           src/spades/SpadesSlotRelationDescriptor.h \
           src/spades/SpadesSupport.h \
           src/spades/SpadesTask.h \
           src/spades/SpadesTaskTest.h \
           src/spades/SpadesWorker.h \
           src/spidey/SpideySupport.h \
           src/spidey/SpideySupportTask.h \
           src/stringtie/StringtieGeneAbundanceReportPrompter.h \
           src/stringtie/StringtieGeneAbundanceReportTask.h \
           src/stringtie/StringtieGeneAbundanceReportWorker.h \
           src/stringtie/StringtieGeneAbundanceReportWorkerFactory.h \
           src/stringtie/StringTieSupport.h \
           src/stringtie/StringTieTask.h \
           src/stringtie/StringTieWorker.h \
           src/tcoffee/TCoffeeSupport.h \
           src/tcoffee/TCoffeeSupportRunDialog.h \
           src/tcoffee/TCoffeeSupportTask.h \
           src/tcoffee/TCoffeeWorker.h \
           src/tophat/TopHatSettings.h \
           src/tophat/TopHatSupport.h \
           src/tophat/TopHatSupportTask.h \
           src/tophat/TopHatWorker.h \
           src/trimmomatic/TrimmomaticDelegate.h \
           src/trimmomatic/TrimmomaticLogParser.h \
           src/trimmomatic/TrimmomaticPrompter.h \
           src/trimmomatic/TrimmomaticStep.h \
           src/trimmomatic/TrimmomaticSupport.h \
           src/trimmomatic/TrimmomaticTask.h \
           src/trimmomatic/TrimmomaticWorker.h \
           src/trimmomatic/TrimmomaticWorkerFactory.h \
           src/trimmomatic/steps/AvgQualStep.h \
           src/trimmomatic/steps/CropStep.h \
           src/trimmomatic/steps/HeadCropStep.h \
           src/trimmomatic/steps/IlluminaClipStep.h \
           src/trimmomatic/steps/LeadingStep.h \
           src/trimmomatic/steps/MaxInfoStep.h \
           src/trimmomatic/steps/MinLenStep.h \
           src/trimmomatic/steps/SlidingWindowStep.h \
           src/trimmomatic/steps/ToPhred33Step.h \
           src/trimmomatic/steps/ToPhred64Step.h \
           src/trimmomatic/steps/TrailingStep.h \
           src/trimmomatic/util/LengthSettingsWidget.h \
           src/trimmomatic/util/LineEditHighlighter.h \
           src/trimmomatic/util/NoSettingsWidget.h \
           src/trimmomatic/util/QualitySettingsWidget.h \
           src/utils/AlignMsaAction.h \
           src/utils/BaseShortReadsAlignerWorker.h \
           src/utils/BlastDBSelectorWidgetController.h \
           src/utils/BlastRunCommonDialog.h \
           src/utils/BlastTaskSettings.h \
           src/utils/CistromeDelegate.h \
           src/utils/ExportTasks.h \
           src/utils/ExternalToolSearchTask.h \
           src/utils/ExternalToolSupportAction.h \
           src/utils/ExternalToolUtils.h \
           src/utils/ExternalToolValidateTask.h \
           src/utils/OutputCollector.h \
           src/vcftools/VcfConsensusSupport.h \
           src/vcftools/VcfConsensusSupportTask.h \
           src/vcftools/VcfConsensusWorker.h \
           src/vcfutils/VcfutilsSupport.h

FORMS += src/ETSSettingsWidget.ui \
         src/blast/FormatDBSupportRunDialog.ui \
         src/blast_plus/AlignToReferenceBlastDialog.ui \
         src/blast_plus/BlastDBCmdDialog.ui \
         src/bowtie/BowtieBuildSettings.ui \
         src/bowtie/BowtieSettings.ui \
         src/bowtie2/Bowtie2Settings.ui \
         src/bwa/BwaBuildSettings.ui \
         src/bwa/BwaSettings.ui \
         src/bwa/BwaMemSettings.ui \
         src/bwa/BwaSwSettings.ui \
         src/cap3/CAP3SupportDialog.ui \
         src/clustalo/ClustalOSupportRunDialog.ui \
         src/clustalw/ClustalWSupportRunDialog.ui \
         src/custom_tools/ImportExternalToolDialog.ui \
         src/hmmer/HmmerBuildDialog.ui \
         src/hmmer/HmmerSearchDialog.ui \
         src/hmmer/PhmmerSearchDialog.ui \
         src/mafft/MAFFTSupportRunDialog.ui \
         src/mrbayes/MrBayesDialog.ui \
         src/phyml/PhyMLDialog.ui \
         src/snpeff/SnpEffDatabaseDialog.ui \
         src/spades/SpadesInputData.ui \
         src/spades/SpadesSettings.ui \
         src/tcoffee/TCoffeeSupportRunDialog.ui \
         src/trimmomatic/TrimmomaticPropertyDialog.ui \
         src/trimmomatic/steps/IlluminaClipAdditionalSettingsDialog.ui \
         src/trimmomatic/steps/IlluminaClipSettingsWidget.ui \
         src/trimmomatic/steps/MaxInfoSettingsWidget.ui \
         src/trimmomatic/steps/SlidingWindowSettingsWidget.ui \
         src/trimmomatic/util/LengthSettingsWidget.ui \
         src/trimmomatic/util/QualitySettingsWidget.ui \
         src/utils/BlastAllSupportDialog.ui \
         src/utils/BlastDBSelectorWidget.ui

SOURCES += src/ETSProjectViewItemsContoller.cpp \
           src/ExternalToolManager.cpp \
           src/ExternalToolSupportPlugin.cpp \
           src/ExternalToolSupportSettings.cpp \
           src/ExternalToolSupportSettingsController.cpp \
           src/RnaSeqCommon.cpp \
           src/RunnerTool.cpp \
           src/TaskLocalStorage.cpp \
           src/bedtools/BedtoolsIntersectTask.cpp \
           src/bedtools/BedToolsWorkersLibrary.cpp \
           src/bedtools/BedtoolsSupport.cpp \
           src/bedtools/BedtoolsSupportTask.cpp \
           src/bigWigTools/BigWigSupport.cpp \
           src/bigWigTools/BedGraphToBigWigTask.cpp \
           src/bigWigTools/BedGraphToBigWigWorker.cpp \
           src/blast/FormatDBSupport.cpp \
           src/blast/FormatDBSupportRunDialog.cpp \
           src/blast/FormatDBSupportTask.cpp \
           src/blast/PrepareInputFastaFilesTask.cpp \
           src/blast_plus/AlignToReferenceBlastDialog.cpp \
           src/blast_plus/AlignToReferenceBlastWorker.cpp \
           src/blast_plus/BlastDBCmdDialog.cpp \
           src/blast_plus/BlastDBCmdSupport.cpp \
           src/blast_plus/BlastDBCmdSupportTask.cpp \
           src/blast_plus/BlastNPlusSupportTask.cpp \
           src/blast_plus/BlastPlusSupport.cpp \
           src/blast_plus/BlastPlusSupportCommonTask.cpp \
           src/blast_plus/BlastPlusSupportRunDialog.cpp \
           src/blast_plus/BlastPlusWorker.cpp \
           src/blast_plus/BlastPPlusSupportTask.cpp \
           src/blast_plus/BlastXPlusSupportTask.cpp \
           src/blast_plus/RPSBlastSupportTask.cpp \
           src/blast_plus/TBlastNPlusSupportTask.cpp \
           src/blast_plus/TBlastXPlusSupportTask.cpp \
           src/blast_plus/align_worker_subtasks/BlastReadsSubTask.cpp \
           src/blast_plus/align_worker_subtasks/ComposeResultSubTask.cpp \
           src/blast_plus/align_worker_subtasks/FormatDBSubTask.cpp \
           src/blast_plus/align_worker_subtasks/PrepareReferenceSequenceTask.cpp \
           src/blast_plus/align_worker_subtasks/RemoveGapsFromSequenceTask.cpp \
           src/bowtie/bowtie_tests/bowtieTests.cpp \
           src/bowtie/BowtieSettingsWidget.cpp \
           src/bowtie/BowtieSupport.cpp \
           src/bowtie/BowtieTask.cpp \
           src/bowtie/BowtieWorker.cpp \
           src/bowtie2/bowtie2_tests/Bowtie2Tests.cpp \
           src/bowtie2/Bowtie2Support.cpp \
           src/bowtie2/Bowtie2Task.cpp \
           src/bowtie2/Bowtie2SettingsWidget.cpp \
           src/bowtie2/Bowtie2Worker.cpp \
           src/bwa/bwa_tests/bwaTests.cpp \
           src/bwa/BwaSettingsWidget.cpp \
           src/bwa/BwaSupport.cpp \
           src/bwa/BwaTask.cpp \
           src/bwa/BwaMemWorker.cpp \
           src/bwa/BwaWorker.cpp \
           src/cap3/CAP3Support.cpp \
           src/cap3/CAP3SupportDialog.cpp \
           src/cap3/CAP3SupportTask.cpp \
           src/cap3/CAP3Worker.cpp \
           src/ceas/CEASReportWorker.cpp \
           src/ceas/CEASSettings.cpp \
           src/ceas/CEASSupport.cpp \
           src/ceas/CEASSupportTask.cpp \
           src/clustalo/ClustalOSupport.cpp \
           src/clustalo/ClustalOSupportRunDialog.cpp \
           src/clustalo/ClustalOSupportTask.cpp \
           src/clustalo/ClustalOWorker.cpp \
           src/clustalw/ClustalWSupport.cpp \
           src/clustalw/ClustalWSupportRunDialog.cpp \
           src/clustalw/ClustalWSupportTask.cpp \
           src/clustalw/ClustalWWorker.cpp \
           src/conduct_go/ConductGOSettings.cpp \
           src/conduct_go/ConductGOSupport.cpp \
           src/conduct_go/ConductGOTask.cpp \
           src/conduct_go/ConductGOWorker.cpp \
           src/conservation_plot/ConservationPlotSettings.cpp \
           src/conservation_plot/ConservationPlotSupport.cpp \
           src/conservation_plot/ConservationPlotTask.cpp \
           src/conservation_plot/ConservationPlotWorker.cpp \
           src/cufflinks/CuffdiffSupportTask.cpp \
           src/cufflinks/CuffdiffWorker.cpp \
           src/cufflinks/CufflinksSettings.cpp \
           src/cufflinks/CufflinksSupport.cpp \
           src/cufflinks/CufflinksSupportTask.cpp \
           src/cufflinks/CufflinksWorker.cpp \
           src/cufflinks/CuffmergeSupportTask.cpp \
           src/cufflinks/CuffmergeWorker.cpp \
           src/cufflinks/GffreadSupportTask.cpp \
           src/cufflinks/GffreadWorker.cpp \
           src/custom_tools/CustomToolConfigParser.cpp \
           src/custom_tools/ImportCustomToolsTask.cpp \
           src/custom_tools/ImportExternalToolDialog.cpp \
           src/custom_tools/LoadCustomExternalToolsTask.cpp \
           src/custom_tools/RegisterCustomToolTask.cpp \
           src/cutadapt/CutadaptSupport.cpp \
           src/cutadapt/CutadaptWorker.cpp \
           src/fastqc/FastqcSupport.cpp \
           src/fastqc/FastqcTask.cpp \
           src/fastqc/FastqcWorker.cpp \
           src/hmmer/ConvertAlignment2StockholmTask.cpp \
           src/hmmer/HmmerBuildDialog.cpp \
           src/hmmer/HmmerBuildFromFileTask.cpp \
           src/hmmer/HmmerBuildFromMsaTask.cpp \
           src/hmmer/HmmerBuildSettings.cpp \
           src/hmmer/HmmerBuildTask.cpp \
           src/hmmer/HmmerBuildTaskTest.cpp \
           src/hmmer/HmmerBuildWorker.cpp \
           src/hmmer/HmmerParseSearchResultsTask.cpp \
           src/hmmer/HmmerSearchDialog.cpp \
           src/hmmer/HmmerSearchSettings.cpp \
           src/hmmer/HmmerSearchTask.cpp \
           src/hmmer/HmmerSearchTaskTest.cpp \
           src/hmmer/HmmerSearchWorker.cpp \
           src/hmmer/HmmerSupport.cpp \
           src/hmmer/PhmmerSearchDialog.cpp \
           src/hmmer/PhmmerSearchSettings.cpp \
           src/hmmer/PhmmerSearchTask.cpp \
           src/hmmer/PhmmerSearchTaskTest.cpp \
           src/java/JavaSupport.cpp \
           src/macs/MACSSettings.cpp \
           src/macs/MACSSupport.cpp \
           src/macs/MACSTask.cpp \
           src/macs/MACSWorker.cpp \
           src/mafft/MafftAddToAlignmentTask.cpp \
           src/mafft/MAFFTSupport.cpp \
           src/mafft/MAFFTSupportRunDialog.cpp \
           src/mafft/MAFFTSupportTask.cpp \
           src/mafft/MAFFTWorker.cpp \
           src/mrbayes/MrBayesDialogWidget.cpp \
           src/mrbayes/MrBayesSupport.cpp \
           src/mrbayes/MrBayesTask.cpp \
           src/mrbayes/MrBayesTests.cpp \
           src/peak2gene/Gene2PeakFormatLoader.cpp \
           src/peak2gene/Peak2GeneFormatLoader.cpp \
           src/peak2gene/Peak2GeneSettings.cpp \
           src/peak2gene/Peak2GeneSupport.cpp \
           src/peak2gene/Peak2GeneTask.cpp \
           src/peak2gene/Peak2GeneWorker.cpp \
           src/perl/PerlSupport.cpp \
           src/phyml/PhyMLDialogWidget.cpp \
           src/phyml/PhyMLSupport.cpp \
           src/phyml/PhyMLTask.cpp \
           src/phyml/PhyMLTests.cpp \
           src/python/PythonSupport.cpp \
           src/R/RSupport.cpp \
           src/samtools/BcfToolsSupport.cpp \
           src/samtools/SamToolsExtToolSupport.cpp \
           src/samtools/TabixSupportTask.cpp \
           src/samtools/TabixSupport.cpp \
           src/seqpos/SeqPosSettings.cpp \
           src/seqpos/SeqPosSupport.cpp \
           src/seqpos/SeqPosTask.cpp \
           src/seqpos/SeqPosWorker.cpp \
           src/snpeff/SnpEffDatabaseDelegate.cpp \
           src/snpeff/SnpEffDatabaseListModel.cpp \
           src/snpeff/SnpEffDatabaseListTask.cpp \
           src/snpeff/SnpEffSupport.cpp \
           src/snpeff/SnpEffTask.cpp \
           src/snpeff/SnpEffWorker.cpp \
           src/spades/SpadesDelegate.cpp \
           src/spades/SpadesPortRelationDescriptor.cpp \
           src/spades/SpadesSettingsWidget.cpp \
           src/spades/SpadesSlotRelationDescriptor.cpp \
           src/spades/SpadesSupport.cpp \
           src/spades/SpadesTask.cpp \
           src/spades/SpadesTaskTest.cpp \
           src/spades/SpadesWorker.cpp \
           src/spidey/SpideySupport.cpp \
           src/spidey/SpideySupportTask.cpp \
           src/stringtie/StringtieGeneAbundanceReportPrompter.cpp \
           src/stringtie/StringtieGeneAbundanceReportTask.cpp \
           src/stringtie/StringtieGeneAbundanceReportWorker.cpp \
           src/stringtie/StringtieGeneAbundanceReportWorkerFactory.cpp \
           src/stringtie/StringTieSupport.cpp \
           src/stringtie/StringTieTask.cpp \
           src/stringtie/StringTieWorker.cpp \
           src/tcoffee/TCoffeeSupport.cpp \
           src/tcoffee/TCoffeeSupportRunDialog.cpp \
           src/tcoffee/TCoffeeSupportTask.cpp \
           src/tcoffee/TCoffeeWorker.cpp \
           src/tophat/TopHatSettings.cpp \
           src/tophat/TopHatSupport.cpp \
           src/tophat/TopHatSupportTask.cpp \
           src/tophat/TopHatWorker.cpp \
           src/trimmomatic/TrimmomaticDelegate.cpp \
           src/trimmomatic/TrimmomaticLogParser.cpp \
           src/trimmomatic/TrimmomaticPrompter.cpp \
           src/trimmomatic/TrimmomaticStep.cpp \
           src/trimmomatic/TrimmomaticSupport.cpp \
           src/trimmomatic/TrimmomaticTask.cpp \
           src/trimmomatic/TrimmomaticWorker.cpp \
           src/trimmomatic/TrimmomaticWorkerFactory.cpp \
           src/trimmomatic/steps/AvgQualStep.cpp \
           src/trimmomatic/steps/CropStep.cpp \
           src/trimmomatic/steps/HeadCropStep.cpp \
           src/trimmomatic/steps/IlluminaClipStep.cpp \
           src/trimmomatic/steps/LeadingStep.cpp \
           src/trimmomatic/steps/MaxInfoStep.cpp \
           src/trimmomatic/steps/MinLenStep.cpp \
           src/trimmomatic/steps/SlidingWindowStep.cpp \
           src/trimmomatic/steps/ToPhred33Step.cpp \
           src/trimmomatic/steps/ToPhred64Step.cpp \
           src/trimmomatic/steps/TrailingStep.cpp \
           src/trimmomatic/util/LengthSettingsWidget.cpp \
           src/trimmomatic/util/LineEditHighlighter.cpp \
           src/trimmomatic/util/NoSettingsWidget.cpp \
           src/trimmomatic/util/QualitySettingsWidget.cpp \
           src/utils/AlignMsaAction.cpp \
           src/utils/BlastDBSelectorWidgetController.cpp \
           src/utils/BaseShortReadsAlignerWorker.cpp \
           src/utils/BlastRunCommonDialog.cpp \
           src/utils/BlastTaskSettings.cpp \
           src/utils/CistromeDelegate.cpp \
           src/utils/ExportTasks.cpp \
           src/utils/ExternalToolSearchTask.cpp \
           src/utils/ExternalToolSupportAction.cpp \
           src/utils/ExternalToolUtils.cpp \
           src/utils/ExternalToolValidateTask.cpp \
           src/utils/OutputCollector.cpp \
           src/vcftools/VcfConsensusSupport.cpp \
           src/vcftools/VcfConsensusSupportTask.cpp \
           src/vcftools/VcfConsensusWorker.cpp \
           src/vcfutils/VcfutilsSupport.cpp

RESOURCES += external_tool_support.qrc
TRANSLATIONS += transl/russian.ts
