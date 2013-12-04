/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2013 UniPro <ugene@unipro.ru>
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

#ifndef _U2_ANNOTATION_H_
#define _U2_ANNOTATION_H_

#include <U2Core/U2Location.h>
#include <U2Core/U2Qualifier.h>
#include <U2Core/U2Type.h>

const QString QUALIFIER_NAME_CIGAR = "cigar";
const QString QUALIFIER_NAME_SUBJECT = "subj_seq";

namespace U2 {

class AnnotationData;
class DNATranslation;
class FeaturesTableObject;
class U2SequenceObject;
class __AnnotationGroup;

// TODO: this class should replace U2::Annotation. It should implement the interface defined below
// using U2::FeatureUtils
class U2CORE_EXPORT __Annotation {
public:
                            __Annotation( const U2DataId &featureId,
                                FeaturesTableObject *parentObject );

                            ~__Annotation( );

    U2DataId                getId( ) const;

    FeaturesTableObject *   getGObject( ) const;

    AnnotationData          getData( ) const;

    QString                 getName( ) const;

    void                    setName( const QString &name );

    bool                    isOrder( ) const;

    bool                    isJoin( ) const;

    U2Strand                getStrand( ) const;

    void                    setStrand( const U2Strand &strand );

    U2LocationOperator      getLocationOperator( ) const;

    void                    setLocationOperator( U2LocationOperator op );

    U2Location              getLocation( ) const;

    void                    setLocation( const U2Location &location );

    QVector<U2Region>       getRegions( ) const;
    /**
     * Replaces existing annotation region(s) with supplied @regions
     */
    void                    updateRegions(const QVector<U2Region> &regions );

    void                    addLocationRegion( const U2Region &reg );

    QVector<U2Qualifier>    getQualifiers( ) const;

    void                    addQualifier( const U2Qualifier &q );

    void                    removeQualifier( const U2Qualifier &q );

    __AnnotationGroup       getGroup( ) const;
    /** 
     * Appends to @res all existing qualifiers with the given @name
     */
    void                    findQualifiers( const QString &name, QList<U2Qualifier> &res ) const;
    /**
     * Returns the value of an arbitrary qualifier with the given @name.
     * Null string returns if no qualifier was found.
     */
    QString                 findFirstQualifierValue( const QString &name ) const;

    QString                 getQualifiersTip( int maxRows, U2SequenceObject *seqObj = NULL,
                                DNATranslation *complTT = NULL, DNATranslation *aminoTT = NULL) const;

    static bool             annotationLessThan( const __Annotation &first,
                                const __Annotation &second );

private:
    U2DataId                featureId;
    FeaturesTableObject *   parentObject;
};

} // namespace U2

#endif // _U2_ANNOTATION_H_