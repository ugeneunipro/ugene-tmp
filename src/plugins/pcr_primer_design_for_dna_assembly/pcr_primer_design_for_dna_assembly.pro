include (pcr_primer_design_for_dna_assembly.pri)

HEADERS += src/tasks/FindPresenceOfUnwantedParametersTask.h \
           src/tasks/FindUnwantedIslandsTask.h \
           src/tasks/PCRPrimerDesignForDNAAssemblyTask.h \
           src/PCRPrimerDesignForDNAAssemblyOPSavableTab.h \
           src/PCRPrimerDesignForDNAAssemblyOPWidget.h \
           src/PCRPrimerDesignForDNAAssemblyOPWidgetFactory.h \
           src/PCRPrimerDesignForDNAAssemblyPlugin.h \
           src/PCRPrimerDesignForDNAAssemblyTaskSettings.h \

SOURCES += src/tasks/FindPresenceOfUnwantedParametersTask.cpp \
           src/tasks/FindUnwantedIslandsTask.cpp \
           src/tasks/PCRPrimerDesignForDNAAssemblyTask.cpp \
           src/PCRPrimerDesignForDNAAssemblyOPSavableTab.cpp \
           src/PCRPrimerDesignForDNAAssemblyOPWidget.cpp \
           src/PCRPrimerDesignForDNAAssemblyOPWidgetFactory.cpp \
           src/PCRPrimerDesignForDNAAssemblyPlugin.cpp \

FORMS +=   src/PCRPrimerDesignForDNAAssemblyOPWidget.ui \

TRANSLATIONS += transl/russian.ts

#RESOURCES += pcr_primer_design_for_dna_assembly.qrc
