#ifndef _U2_STRUCTURAL_ALIGNER_PLUGIN_H_
#define _U2_STRUCTURAL_ALIGNER_PLUGIN_H_

#include <U2Core/PluginModel.h>
#include <U2Test/XMLTestUtils.h>

namespace U2 {

class StructuralAlignerPlugin : public Plugin {
    Q_OBJECT

public:
    StructuralAlignerPlugin();
    ~StructuralAlignerPlugin();

};  // class StructuralAlignerPlugin

class StructualAlignerTests {
public:
    static QList<XMLTestFactory*> createTestFactories();
};  // class StructualAlignerTests

}   // namespace U2

#endif  // #ifndef _U2_STRUCTURAL_ALIGNER_PLUGIN_H_
