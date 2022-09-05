#include <mpi.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include <Underworld/Underworld.h>

#include "types.h"
#include "ViscosityImposedDepth.h"
#include <assert.h>


/* Textual name of this class */
const Type ViscosityImposedDepth_Type = "ViscosityImposedDepth";

/* Private Constructor */
ViscosityImposedDepth* _ViscosityImposedDepth_New(  VISCOSITYIMPOSEDDEPTH_DEFARGS  ) 
{
	ViscosityImposedDepth* self;

	assert( _sizeOfSelf >= sizeof(ViscosityImposedDepth) );
	self = (ViscosityImposedDepth*) _Rheology_New(  RHEOLOGY_PASSARGS  );
	
	return self;
}

void* _ViscosityImposedDepth_DefaultNew( Name name ) {
	/* Variables set in this function */
	SizeT                                                     _sizeOfSelf = sizeof(ViscosityImposedDepth);
	Type                                                             type = ViscosityImposedDepth_Type;
	Stg_Class_DeleteFunction*                                     _delete = _Rheology_Delete;
	Stg_Class_PrintFunction*                                       _print = _Rheology_Print;
	Stg_Class_CopyFunction*                                         _copy = _Rheology_Copy;
	Stg_Component_DefaultConstructorFunction*         _defaultConstructor = _ViscosityImposedDepth_DefaultNew;
	Stg_Component_ConstructFunction*                           _construct = _ViscosityImposedDepth_AssignFromXML;
	Stg_Component_BuildFunction*                                   _build = _Rheology_Build;
	Stg_Component_InitialiseFunction*                         _initialise = _Rheology_Initialise;
	Stg_Component_ExecuteFunction*                               _execute = _Rheology_Execute;
	Stg_Component_DestroyFunction*                               _destroy = _Rheology_Destroy;
	Rheology_ModifyConstitutiveMatrixFunction*  _modifyConstitutiveMatrix = _ViscosityImposedDepth_ModifyConstitutiveMatrix;

	/* Variables that are set to ZERO are variables that will be set either by the current _New function or another parent _New function further up the hierachy */
	AllocationType  nameAllocationType = NON_GLOBAL /* default value NON_GLOBAL */;

	return (void*) _ViscosityImposedDepth_New(  VISCOSITYIMPOSEDDEPTH_PASSARGS  );
}

void _ViscosityImposedDepth_AssignFromXML( void* _self, Stg_ComponentFactory* cf, void* data ){
	ViscosityImposedDepth*  self = (ViscosityImposedDepth*)_self;

	/* Construct Parent */
	_Rheology_AssignFromXML( self, cf, data );
	
        self->viscosity = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"Viscosity", 10  );
        self->minx = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"minx", 0.0  );
        self->maxx = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"maxx", 0.0 );
	self->usexlim = !(self->minx == 0 && self->maxx == 0 );
        self->miny = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"miny", 0.0  );
        self->maxy = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"maxy", 0.0 );
	self->useylim = !(self->miny == 0 && self->maxy == 0 );
        self->minz = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"minz", 0.0  );
        self->maxz = Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"maxz", 0.0 );
	self->usezlim = !(self->minz == 0 && self->maxz == 0 );
}

void _ViscosityImposedDepth_ModifyConstitutiveMatrix( void*                  _self, 
						      ConstitutiveMatrix*    constitutiveMatrix,
						      MaterialPointsSwarm*   swarm,
						      Element_LocalIndex     lElement_I,
						      MaterialPoint*         materialPoint,
						      Coord                  xi )
{
	ViscosityImposedDepth* self = (ViscosityImposedDepth*) _self;
	double                 coord[3];
	double                 min[3], max[3]; 
	FeMesh*                mesh = ConstitutiveMatrix_GetMesh( constitutiveMatrix );

	/* Get coord */
        Mesh_GetGlobalCoordRange( mesh, min, max );
	FeMesh_CoordLocalToGlobal( mesh, lElement_I, xi, (double*)&coord );

	
	if( self->usexlim && (coord[I_AXIS] < self->minx || coord[I_AXIS] > self->maxx ) )
	  return;

	if( self->useylim && (coord[J_AXIS] < self->miny || coord[J_AXIS] > self->maxy ) )
	  return;

	if( self->usezlim && (coord[K_AXIS] < self->minz || coord[K_AXIS] > self->maxz ) )
	  return;

	ConstitutiveMatrix_SetIsotropicViscosity( constitutiveMatrix, self->viscosity );

}


