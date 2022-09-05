#include <mpi.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include <Common/Common.h>

#include <string.h>
#include <math.h>

#include "types.h"
#include "Ppc_LinearDensity.h"


/* Textual name of this class */
const Type Ppc_LinearDensity_Type = "Ppc_LinearDensity";


/* Private Constructor: This will accept all the virtual functions for this class as arguments. */
Ppc_LinearDensity* _Ppc_LinearDensity_New(  PPC_LINEARDENSITY_DEFARGS  )
{
	Ppc_LinearDensity* self;
	
	assert( _sizeOfSelf >= sizeof(Ppc_LinearDensity) );
	nameAllocationType = NON_GLOBAL;
	self = (Ppc_LinearDensity*) _Ppc_New(  PPC_PASSARGS  );	
	self->_get = _get;
	return self;
}


void* _Ppc_LinearDensity_DefaultNew( Name name ) {
	/* Variables set in this function */
	SizeT                                              _sizeOfSelf = sizeof(Ppc_LinearDensity);
	Type                                                      type = Ppc_LinearDensity_Type;
	Stg_Class_DeleteFunction*                              _delete = _Ppc_LinearDensity_Delete;
	Stg_Class_PrintFunction*                                _print = _Ppc_LinearDensity_Print;
	Stg_Class_CopyFunction*                                  _copy = NULL;
	Stg_Component_DefaultConstructorFunction*  _defaultConstructor = _Ppc_LinearDensity_DefaultNew;
	Stg_Component_ConstructFunction*                    _construct = _Ppc_LinearDensity_AssignFromXML;
	Stg_Component_BuildFunction*                            _build = _Ppc_LinearDensity_Build;
	Stg_Component_InitialiseFunction*                  _initialise = _Ppc_LinearDensity_Initialise;
	Stg_Component_ExecuteFunction*                        _execute = _Ppc_LinearDensity_Execute;
	Stg_Component_DestroyFunction*                        _destroy = _Ppc_LinearDensity_Destroy;
	AllocationType                              nameAllocationType = NON_GLOBAL;
   Ppc_GetFunction*                                          _get = _Ppc_LinearDensity_Get;

	return (void*)_Ppc_LinearDensity_New(  PPC_LINEARDENSITY_PASSARGS  );
}


void _Ppc_LinearDensity_Init( void* _self, int alpha, int beta, int t, int p, double osp, double osr, double osc, double spp, double spr, double spc, int ef, double rt, double rp, double rd )
{
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Sanity check */
	self->alphaTag = alpha;
	self->betaTag = beta;
	self->temperatureTag = t;
	self->pressureTag = p;
	self->OlSp_refP = osp;
	self->OlSp_drho = osr;
	self->OlSp_ClapS = osc;
	self->SpPe_refP = spp;
	self->SpPe_drho = spr;
	self->SpPe_ClapS = spc;
	self->externalFunction = ef;
	self->referenceTemperature = rt;
	self->referencePressure = rp;
	self->referenceDensity = rd;
}


void _Ppc_LinearDensity_AssignFromXML( void* _self, Stg_ComponentFactory* cf, void* data ) {
	Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Construct parent */
	_Ppc_AssignFromXML( self, cf, data );

   _Ppc_LinearDensity_Init( 
	   self, 
		PpcManager_GetPpcFromDict( self->manager, cf, (Name)self->name, "ThermalExpansivity", "" ),
		PpcManager_GetPpcFromDict( self->manager, cf, (Name)self->name, "Compressibility", "" ),
		PpcManager_GetPpcFromDict( self->manager, cf, (Name)self->name, "Temperature", "" ),
		PpcManager_GetPpcFromDict( self->manager, cf, (Name)self->name, "Pressure", "" ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_refP", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_drho", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_ClapS", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_refP", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_drho", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_ClapS", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"ExternalFunction", 0.0 ),
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"ReferenceTemperature", 0.0 ), 
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"ReferencePressure", 0.0 ), 
		Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"ReferenceDensity", 0.0 ) );
}


void _Ppc_LinearDensity_Build( void* _self, void* data ) {
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Build parent */
	_Ppc_Build( self, data );
}

void _Ppc_LinearDensity_Initialise( void* _self, void* data ) {
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Initialize parent */
	_Ppc_Initialise( self, data );
}

void _Ppc_LinearDensity_Delete( void* _self ) {
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Delete parent */
	_Ppc_Delete( self );
}

void _Ppc_LinearDensity_Print( void* _self, Stream* stream ) {
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Print parent */
	_Ppc_Print( self, stream );
}

void _Ppc_LinearDensity_Execute( void* _self, void* data ) {
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Execute parent */
	_Ppc_Execute( self, data );
}

void _Ppc_LinearDensity_Destroy( void* _self, void* data ) {
   Ppc_LinearDensity* self = (Ppc_LinearDensity*)_self;

	/* Destroy parent */
	_Ppc_Destroy( self, data );
}

/* 
 * Public functions 
 *
 */

int _Ppc_LinearDensity_Get( void* _self, Element_LocalIndex lElement_I, IntegrationPoint* particle, double* result ) {
  Ppc_LinearDensity* self = (Ppc_LinearDensity*) _self;
  double density, alpha, beta, T, P, T0, P0, external;
  double t_term = 0.0;
  double p_term = 0.0; 
  int err;

  /*PT alpha */
  double p1,p2,p3,p4,p5,alphaT,facP,Palpha,pressure;
  p1 = -8.0588e-13;
  p2 = 4.8899e-9;
  p3 = -1.0538e-5;
  p4 = 0.010476;
  p5 = 0.46947;
  facP = 0.4191/15;
  
  double os_refP=0.;
  double os_drho=0.;
  double os_cs=0.;
  double sp_refP=0.;
  double sp_drho=0.;
  double sp_cs=0.; 

  /* Reference density */
  density = self->referenceDensity;
  external = self->externalFunction;
  os_refP = self->OlSp_refP;
  os_drho = self->OlSp_drho;
  os_cs = self->OlSp_ClapS;
  sp_refP = self->SpPe_refP;
  sp_drho = self->SpPe_drho;
  sp_cs = self->SpPe_ClapS;
  //printf("%g ",external);
	
  /** Pressure dependence **/
  err = PpcManager_Get( self->manager, lElement_I, particle, self->pressureTag, &pressure );
  /** Temperature dependence **/
  err = PpcManager_Get( self->manager, lElement_I, particle, self->temperatureTag, &T );
  if( !err ) {
	 T0 = self->referenceTemperature;
	 /* get thermal expansivity */
	 err = PpcManager_Get( self->manager, lElement_I, particle, self->alphaTag, &alpha );
	 if( err )
		alpha = 0;
	 
	if (external == 1){
		//printf("%g ",pressure);
		if(pressure > 0.){
			Palpha=pressure;
		}
		else{
			Palpha = 0.;
		}
		alphaT = ((pow(T,4)*p1+pow(T,3)*p2+pow(T,2)*p3+pow(T,1)*p4+p5)/((Palpha/1e9)*facP+1.))*1e-5;
		//printf("%g %g %g | ",alphaT,Palpha,T);
		t_term = alphaT*(T - T0);
	}
	else {
		t_term = alpha*(T - T0); 
	}
  }
  

  /** Pressure dependence **/
  err = PpcManager_Get( self->manager, lElement_I, particle, self->pressureTag, &P );
  if( !err ) {
	 P0 = self->referencePressure;
	 /* get compressibility */
	 err = PpcManager_Get( self->manager, lElement_I, particle, self->betaTag, &beta );
	 if( err )
		beta = 0;

	 p_term = beta*(P - P0);
  }
  
  double tsd,p_0,tsd2,p_02;
  if (os_drho != 0.0){
	  p_02=0.;tsd2=0.;p_0=0.;tsd=0.;
	  p_0 = os_refP - os_cs*(T-273.);
	  tsd = p_0+(T-273.)*os_cs;

	  p_02 = sp_refP - sp_cs*(T-273.);
	  tsd2 = p_02+(T-273.)*sp_cs;	  
	  if (pressure > tsd && pressure <= tsd2){
	    density = (density + os_drho)* ( 1 + p_term - t_term );
	  }
	  else if (pressure > tsd2){
		density = (density + os_drho + sp_drho)* ( 1 + p_term - t_term ); 
	  }
	  else{
        density = (density )* ( 1 + p_term - t_term );
	  }
  }
  else{
    density = density * ( 1 + p_term - t_term );
  }

  result[0] = density;
  
  return 0;
}
