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

#ifndef _U2_PDB_FORMAT_H_
#define _U2_PDB_FORMAT_H_

#include <U2Core/BaseDocumentFormats.h>
#include <U2Core/DocumentModel.h>
#include <QtCore/QSharedDataPointer>

namespace U2 {

class IOAdapter;
class BioStruct3D;
class AnnotationTableObject;
class DNASequenceObject;
class AtomData;
typedef QSharedDataPointer<AtomData> SharedAtom;


class U2FORMATS_EXPORT  PDBFormat : public DocumentFormat {
    Q_OBJECT
public:
    PDBFormat(QObject* p);
    virtual DocumentFormatId getFormatId() const {return BaseDocumentFormats::PLAIN_PDB;}
    virtual const QString& getFormatName() const {return formatName;}

    virtual Document* loadDocument(IOAdapter* io, TaskStateInfo& ti, const QVariantMap& fs, DocumentLoadMode mode = DocumentLoadMode_Whole);

    virtual FormatDetectionScore checkRawData(const QByteArray& rawData, const GUrl& = GUrl()) const;
    static int getElementNumberByName(const QByteArray& elementName);
    static char getAcronymByName(const QByteArray& name);
    static QHash<QByteArray, int> createAtomNumMap();
    static void calculateBonds(BioStruct3D& bioStruct);
    static Document* createDocumentFromBioStruct3D(BioStruct3D &bioStruct, DocumentFormat* format, IOAdapterFactory* iof, const GUrl& url, TaskStateInfo& ti, const QVariantMap& fs );


private:
    
    QString formatName;
    static QHash<QByteArray,int> atomNumMap;
    static QHash<QByteArray, char> acronymNameMap;
    
    void initUtilityMaps();
    void updateSecStructChainIndexes(BioStruct3D& biostruc);
    void fillBioStruct3DAnnotationTable(AnnotationTableObject* ao, const BioStruct3D& bioStruct);


    class PDBParser {
    private:
        // Data
        IOAdapter *io;
        QString currentPDBLine;
        int currentChainIndex;
        int currentModelIndex;
        char currentChainIndentifier;
        bool flagMultipleModels, flagAtomRecordPresent;
        QHash<char, int> chainIndexMap;
        QHash<char, QByteArray> seqResMap;
        QSet<QByteArray> resIndSet;
        
        // Methods
        QByteArray getSpecValue(const QByteArray& specLine, const QByteArray& valueName);
        void parseHeader(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseCompound(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseDBRef(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseSequence(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseSecondaryStructure(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseHet(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseAtomConnections(BioStruct3D& biostruct, TaskStateInfo& ti);
        void parseAtom(BioStruct3D& biostruct, TaskStateInfo& ti);

        void createMolecule( char chainIdentifier, BioStruct3D &biostruct, int chainIndex );

        void parseModel(BioStruct3D& biostruct, TaskStateInfo& ti);
        void updateSecStructChainIndexes( BioStruct3D& biostruc );
        bool seqResContains(char chainIdentier, int residueIndex, char acronym);
        QByteArray getNextSpecLine();
    public:
        PDBParser(IOAdapter* io);
        void parseBioStruct3D(BioStruct3D& biostruct, TaskStateInfo& ts);
    };

};

}//namespace

#endif
