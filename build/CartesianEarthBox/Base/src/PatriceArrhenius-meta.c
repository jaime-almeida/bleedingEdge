#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "StGermain/Base/Foundation/Foundation.h"
#include "StGermain/Base/IO/IO.h"
#define MAX_CHAR_SIZE 512

const char* PatriceArrhenius_Name = "PatriceArrhenius";
const char* PatriceArrhenius_GetName() {
	return PatriceArrhenius_Name;
}

const char* PatriceArrhenius_Meta = NULL;
const char* PatriceArrhenius_GetMetadata() {
	return PatriceArrhenius_Meta;
}
const char* PatriceArrhenius_Type_GetMetadata() {
	return PatriceArrhenius_Meta;
}

Dictionary* PatriceArrhenius_MetaAsDictionary() {
	Dictionary* meta;
	Dictionary* info;
	Dictionary* code;
	Dictionary* implements;
	Dictionary* parameters;
	char _xml[MAX_CHAR_SIZE];
	char _title[MAX_CHAR_SIZE];
	char _creator[MAX_CHAR_SIZE];
	char _publisher[MAX_CHAR_SIZE];
	char _rights[MAX_CHAR_SIZE];
	char _source[MAX_CHAR_SIZE];
	char _subject[MAX_CHAR_SIZE];
	char _description[MAX_CHAR_SIZE];
	char _info[MAX_CHAR_SIZE];
	char _example_documentation[MAX_CHAR_SIZE];
	char _example_code[MAX_CHAR_SIZE];
	char _inherits[MAX_CHAR_SIZE];
	char _code[MAX_CHAR_SIZE];
	char _reference[MAX_CHAR_SIZE];
	char _equation[MAX_CHAR_SIZE];
	char _implements[MAX_CHAR_SIZE];
	char _name[MAX_CHAR_SIZE];
	char _type[MAX_CHAR_SIZE];
	char _default[MAX_CHAR_SIZE];
	char _parameters[MAX_CHAR_SIZE];
	char _nillable[MAX_CHAR_SIZE];
	char _documentation[MAX_CHAR_SIZE];
	char _associations[MAX_CHAR_SIZE];
	char _parameter_var[MAX_CHAR_SIZE];
	char _association_var[MAX_CHAR_SIZE];
	strcpy( _xml, "xml" ); strcpy( _title, "title" ); strcpy( _creator, "creator" ); strcpy( _publisher, "publisher" );
	strcpy( _rights, "rights" ); strcpy( _source, "source" ); strcpy( _subject, "subject" ); strcpy( _description, "description" );
	strcpy( _info, "info" ); strcpy( _example_documentation, "example-documentation" ); strcpy( _example_code, "example-code" );
	strcpy( _inherits, "inherits" ); strcpy( _code, "code" ); strcpy( _reference, "reference" ); strcpy( _equation, "equation" );
	strcpy( _implements, "_implements" ); strcpy( _name, "name" ); strcpy( _type, "type" ); strcpy( _default, "default" );
	strcpy( _parameters, "parameters" ); strcpy( _nillable, "nillable" ); strcpy( _documentation, "documentation" );
	strcpy( _associations, "associations" ); strcpy( _parameter_var, "" ); strcpy( _association_var, "" );
	Dictionary* stressExponentParam;
	Dictionary* defaultStrainRateInvariantParam;
	Dictionary* associations;
	Dictionary* StrainRateInvariantFieldAssoc;

	meta = Dictionary_New();

	Dictionary_Add( meta, _xml, Dictionary_Entry_Value_FromString( PatriceArrhenius_Meta ));

	info = Dictionary_New();
	Dictionary_Add( info, _title, Dictionary_Entry_Value_FromString( "PatriceArrhenius" ));
	Dictionary_Add( info, _creator, Dictionary_Entry_Value_FromString( "SergioZlotnik" ));
	Dictionary_Add( info, _publisher, Dictionary_Entry_Value_FromString( "MCC" ));
	Dictionary_Add( info, _rights, Dictionary_Entry_Value_FromString( "http://www.opensource.org/licenses/bsd-license.php" ));
	Dictionary_Add( info, _source, Dictionary_Entry_Value_FromString( "./Underworld/Rheology/src/" ));
	Dictionary_Add( info, _subject, Dictionary_Entry_Value_FromString( "Underworld" ));
	Dictionary_Add( info, _description, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( meta, _info, Dictionary_Entry_Value_FromStruct( info ) );

	code = Dictionary_New();
	Dictionary_Add( code, _example_code, Dictionary_Entry_Value_FromString( "Underworld/InputFiles/NonNewtonian.xml" ));
	Dictionary_Add( code, _inherits, Dictionary_Entry_Value_FromString( "Rheology" ));
	Dictionary_Add( meta, _code, Dictionary_Entry_Value_FromStruct( code ) );

	implements = Dictionary_New();
	Dictionary_Add( implements, _equation, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( meta, _implements, Dictionary_Entry_Value_FromStruct( implements ) );

	parameters = Dictionary_New();
	strcpy( _parameter_var, "stressExponent");	stressExponentParam = Dictionary_New();
	Dictionary_Add( stressExponentParam, _name, Dictionary_Entry_Value_FromString( "stressExponent" ));
	Dictionary_Add( stressExponentParam, _type, Dictionary_Entry_Value_FromString( "xsd:double" ));
	Dictionary_Add( stressExponentParam, _default, Dictionary_Entry_Value_FromString( "1.0" ));
	Dictionary_Add( stressExponentParam, _documentation, Dictionary_Entry_Value_FromString( "This is the $n$ in the equation above." ));
	Dictionary_Add( parameters, _parameter_var, Dictionary_Entry_Value_FromStruct( stressExponentParam ) );

	memset( _parameter_var, 0, 512 );
	strcpy( _parameter_var, "defaultStrainRateInvariant");	defaultStrainRateInvariantParam = Dictionary_New();
	Dictionary_Add( defaultStrainRateInvariantParam, _name, Dictionary_Entry_Value_FromString( "defaultStrainRateInvariant" ));
	Dictionary_Add( defaultStrainRateInvariantParam, _type, Dictionary_Entry_Value_FromString( "xsd:double" ));
	Dictionary_Add( defaultStrainRateInvariantParam, _default, Dictionary_Entry_Value_FromString( "0.0" ));
	Dictionary_Add( defaultStrainRateInvariantParam, _documentation, Dictionary_Entry_Value_FromString( "(optional) $\\dot\\epsilon$ for the first solve (when no previous solution exists)." ));
	Dictionary_Add( parameters, _parameter_var, Dictionary_Entry_Value_FromStruct( defaultStrainRateInvariantParam ) );

	memset( _parameter_var, 0, 512 );
	Dictionary_Add( meta, _parameters, Dictionary_Entry_Value_FromStruct( parameters ) );

	associations = Dictionary_New();
	strcpy( _association_var, "StrainRateInvariantField");	StrainRateInvariantFieldAssoc = Dictionary_New();
	Dictionary_Add( StrainRateInvariantFieldAssoc, _name, Dictionary_Entry_Value_FromString( "StrainRateInvariantField" ));
	Dictionary_Add( StrainRateInvariantFieldAssoc, _type, Dictionary_Entry_Value_FromString( "FeVariable" ));
	Dictionary_Add( StrainRateInvariantFieldAssoc, _nillable, Dictionary_Entry_Value_FromString( "false" ));
	Dictionary_Add( StrainRateInvariantFieldAssoc, _documentation, Dictionary_Entry_Value_FromString( "The field that provides the $\\dot\\epsilon$ in the equation above." ));
	Dictionary_Add( associations, _association_var , Dictionary_Entry_Value_FromStruct( StrainRateInvariantFieldAssoc ) );

	memset( _association_var, 0, 512 );
	Dictionary_Add( meta, _associations, Dictionary_Entry_Value_FromStruct( associations ) );

	return meta;
}
Dictionary* PatriceArrhenius_Type_MetaAsDictionary() {
	return PatriceArrhenius_MetaAsDictionary();
}
