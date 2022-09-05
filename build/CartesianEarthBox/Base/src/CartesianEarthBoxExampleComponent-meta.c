#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "StGermain/Base/Foundation/Foundation.h"
#include "StGermain/Base/IO/IO.h"
#define MAX_CHAR_SIZE 512

const char* CartesianEarthBoxExampleComponent_Name = "CartesianEarthBoxExampleComponent";
const char* CartesianEarthBoxExampleComponent_GetName() {
	return CartesianEarthBoxExampleComponent_Name;
}

const char* CartesianEarthBoxExampleComponent_Meta = NULL;
const char* CartesianEarthBoxExampleComponent_GetMetadata() {
	return CartesianEarthBoxExampleComponent_Meta;
}
const char* CartesianEarthBoxExampleComponent_Type_GetMetadata() {
	return CartesianEarthBoxExampleComponent_Meta;
}

Dictionary* CartesianEarthBoxExampleComponent_MetaAsDictionary() {
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
	Dictionary* associations;

	meta = Dictionary_New();

	Dictionary_Add( meta, _xml, Dictionary_Entry_Value_FromString( CartesianEarthBoxExampleComponent_Meta ));

	info = Dictionary_New();
	Dictionary_Add( info, _title, Dictionary_Entry_Value_FromString( "CartesianEarthBoxExampleComponent" ));
	Dictionary_Add( info, _creator, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( info, _publisher, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( info, _rights, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( info, _source, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( info, _subject, Dictionary_Entry_Value_FromString( "CartesianEarthBox" ));
	Dictionary_Add( info, _description, Dictionary_Entry_Value_FromString( "An example component.  These metafiles will be deprecated soon.  You may ignore them." ));
	Dictionary_Add( meta, _info, Dictionary_Entry_Value_FromStruct( info ) );

	code = Dictionary_New();
	Dictionary_Add( code, _inherits, Dictionary_Entry_Value_FromString( "Stg_Component" ));
	Dictionary_Add( meta, _code, Dictionary_Entry_Value_FromStruct( code ) );

	implements = Dictionary_New();
	Dictionary_Add( implements, _reference, Dictionary_Entry_Value_FromString( "" ));
	Dictionary_Add( meta, _implements, Dictionary_Entry_Value_FromStruct( implements ) );

	parameters = Dictionary_New();
	Dictionary_Add( meta, _parameters, Dictionary_Entry_Value_FromStruct( parameters ) );

	associations = Dictionary_New();
	Dictionary_Add( meta, _associations, Dictionary_Entry_Value_FromStruct( associations ) );

	return meta;
}
Dictionary* CartesianEarthBoxExampleComponent_Type_MetaAsDictionary() {
	return CartesianEarthBoxExampleComponent_MetaAsDictionary();
}
