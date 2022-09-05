#include <mpi.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include <Underworld/Underworld.h>
#include <CartesianEarthBox/CartesianEarthBox.h>

#include "types.h"
/*#include "RheologyClass.h"*/
#include "PatriceArrhenius.h"
/*#include "ConstitutiveMatrix.h"*/

#include <assert.h>
#include <float.h>


/* Textual name of this class */
const Type PatriceArrhenius_Type = "PatriceArrhenius";

/* Private Constructor: This will accept all the virtual functions for this class as arguments. */
PatriceArrhenius* _PatriceArrhenius_New(  PatriceArrhenius_DEFARGS  ) 
{
	PatriceArrhenius* self;

	/* Call private constructor of parent */
	assert( _sizeOfSelf >= sizeof(PatriceArrhenius) );
	self = (PatriceArrhenius*) _Rheology_New(  RHEOLOGY_PASSARGS  );
	
	return self;
}

void _PatriceArrhenius_Init( PatriceArrhenius* self, Scaling* sc, ParticleMelting* melting, FeVariable* srf, FeVariable* temp, FeVariable* pres, double n, double dsr, double A, double E, double V, double osp, double osr, double osc, double osd, double spp, double spr, double spc, double spd, double da,double dv, double de, double pc, double sm ) {

	self->scaling = sc;
	self->melting = melting;
	self->strainRateInvField = srf;
	self->temperatureField = temp;
	self->pressureField = pres;
	self->stressExponent = n;
    self->defaultStrainRateInvariant = dsr;
	self->preExponentialFactor = A;
	self->activationEnergy = E;
	self->activationVolume = V;
	self->OlSp_refP = osp;
	self->OlSp_drho = osr;
	self->OlSp_ClapS = osc;
	self->OlSp_dvis = osd;
	self->SpPe_refP = spp;
	self->SpPe_drho = spr;
	self->SpPe_ClapS = spc;
	self->SpPe_dvis = spd;
	self->SpPe_dA = da;
	self->SpPe_dV = dv;
	self->SpPe_dE = de;
	self->lm_phasechange = pc;	
	self->serp_mantle = sm;	
	Rheology_SetToNonLinear( self );
}


void _PatriceArrhenius_Build( void* _self, void* data ){
	PatriceArrhenius*  self = (PatriceArrhenius*)_self;

	_Rheology_Build( self, data );
	
   Stg_Component_Build( self->strainRateInvField, data, False );
   if( self->pressureField ) Stg_Component_Build( self->pressureField, data, False );
   if( self->temperatureField ) Stg_Component_Build( self->temperatureField, data, False );
   if( self->melting ) Stg_Component_Build( self->melting, data, False );
}

void _PatriceArrhenius_Initialise( void* _self, void* data ){
	PatriceArrhenius*  self = (PatriceArrhenius*)_self;

   _Rheology_Initialise( self, data );

   Stg_Component_Initialise( self->strainRateInvField, data, False );
   if( self->pressureField ) Stg_Component_Initialise( self->pressureField, data, False );
   if( self->temperatureField ) Stg_Component_Initialise( self->temperatureField, data, False );
   if( self->melting ) Stg_Component_Initialise( self->melting, data, False );
}

void _PatriceArrhenius_Destroy( void* _self, void* data ){
	PatriceArrhenius*  self = (PatriceArrhenius*)_self;

   Stg_Component_Destroy( self->strainRateInvField, data, False );

	_Rheology_Destroy( self, data );
}


void* _PatriceArrhenius_DefaultNew( Name name ) {
	/* Variables set in this function */
	SizeT                                                     _sizeOfSelf = sizeof(PatriceArrhenius);
	Type                                                             type = PatriceArrhenius_Type;
	Stg_Class_DeleteFunction*                                     _delete = _Rheology_Delete;
	Stg_Class_PrintFunction*                                       _print = _Rheology_Print;
	Stg_Class_CopyFunction*                                         _copy = _Rheology_Copy;
	Stg_Component_DefaultConstructorFunction*         _defaultConstructor = _PatriceArrhenius_DefaultNew;
	Stg_Component_ConstructFunction*                           _construct = _PatriceArrhenius_AssignFromXML;
	Stg_Component_BuildFunction*                                   _build = _PatriceArrhenius_Build;
	Stg_Component_InitialiseFunction*                         _initialise = _PatriceArrhenius_Initialise;
	Stg_Component_ExecuteFunction*                               _execute = _Rheology_Execute;
	Stg_Component_DestroyFunction*                               _destroy = _PatriceArrhenius_Destroy;
	Rheology_ModifyConstitutiveMatrixFunction*  _modifyConstitutiveMatrix = _PatriceArrhenius_ModifyConstitutiveMatrix;

	/* Variables that are set to ZERO are variables that will be set either by the current _New function or another parent _New function further up the hierachy */
	AllocationType  nameAllocationType = NON_GLOBAL /* default value NON_GLOBAL */;

	return (void*) _PatriceArrhenius_New(  NONNEWTONIAN_PASSARGS  );
}


void _PatriceArrhenius_AssignFromXML( void* rheology, Stg_ComponentFactory* cf, void* data ){
	PatriceArrhenius*  self = (PatriceArrhenius*)rheology;
	FeVariable* srf = NULL, *temperature=NULL, *pressure=NULL;
   Scaling *sc=NULL;
   ParticleMelting *melting=NULL;

	/* Construct Parent */
	_Rheology_AssignFromXML( self, cf, data );

   /* The scaling component */
   sc = Stg_ComponentFactory_ConstructByKey( cf, self->name, (Dictionary_Entry_Key)"Scaling", Scaling, False, data );
   if ( !sc )
      sc = Stg_ComponentFactory_ConstructByName( cf, (Name)"default_scaling", Scaling, True, data  );

	melting = Stg_ComponentFactory_ConstructByKey( cf, self->name, (Dictionary_Entry_Key)"ParticleMelting", ParticleMelting, False, data  );
	srf = Stg_ComponentFactory_ConstructByKey( cf, self->name, (Dictionary_Entry_Key)"StrainRateInvariantField", FeVariable, True, data  );
	temperature = Stg_ComponentFactory_ConstructByKey( cf, self->name, (Dictionary_Entry_Key)"TemperatureField", FeVariable, False, data  );
	pressure = Stg_ComponentFactory_ConstructByKey( cf, self->name, (Dictionary_Entry_Key)"PressureField", FeVariable, False, data  );

	_PatriceArrhenius_Init(
			self,
         sc,
         melting,
			srf,
			temperature,
			pressure,
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"StressExponent", 1.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"DefaultStrainRateInvariant", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"PreExponentialFactor", 1.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"ActivationEnergy", 1.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"ActivationVolume", 1.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_refP", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_drho", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_ClapS", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"OlSp_dvis", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_refP", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_drho", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_ClapS", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_dvis", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_dA", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_dV", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"SpPe_dE", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"lm_phasechange", 0.0 ),
			Stg_ComponentFactory_GetDouble( cf, self->name, (Dictionary_Entry_Key)"serp_mantle", 0.0 ));
}


void _PatriceArrhenius_ModifyConstitutiveMatrix( void* _self, ConstitutiveMatrix* constitutiveMatrix, MaterialPointsSwarm* swarm, Element_LocalIndex lElement_I, MaterialPoint* materialPoint, Coord xi ) {
  PatriceArrhenius* self = (PatriceArrhenius*) _self;
  double eII;
  double viscosity;
  double n, A, E, V, R, F;
  double pressure=0 , temperature=0;
  double os_refP=0.;
  double os_drho=0.;
  double os_cs=0.;
  double os_dv=0.;
  double sp_refP=0.;
  double sp_drho=0.;
  double sp_cs=0.; 
  double sp_dv=0.0; 
  double sp_da=1.0; 
  double sp_dvol=1.0; 
  double sp_de=0.0; 
  double pc=0.0; 
  double sm=0.0; 
   

  /* get strain rate */
  if ( !constitutiveMatrix->previousSolutionExists ) {
	 /* first solve uses default strain rate */
	 eII = self->defaultStrainRateInvariant;
  } else {
	 FeVariable_InterpolateWithinElement( self->strainRateInvField, lElement_I, xi, &eII );
  }  
  if ( eII == 0 )
	 return;


  /* 
    */

  if( self->melting ) ParticleMelting_Get( self->melting, materialPoint , MELT_FRACTION, &F );
  
  /** get parameters **/
  n = self->stressExponent;
  A = self->preExponentialFactor;
  E = self->activationEnergy;
  V = self->activationVolume;
  os_refP = self->OlSp_refP;
  os_drho = self->OlSp_drho;
  os_cs = self->OlSp_ClapS;
  os_dv = self->OlSp_dvis;
  sp_refP = self->SpPe_refP;
  sp_drho = self->SpPe_drho;
  sp_cs = self->SpPe_ClapS;
  sp_dv = self->SpPe_dvis;
  sp_da = self->SpPe_dA;
  sp_dvol = self->SpPe_dV;
  sp_de = self->SpPe_dE;
  pc = self->lm_phasechange; 
  sm = self->serp_mantle; 
  /* get gas constant **/
  R = Scaling_Scale( self->scaling, 8.314472, (UnitDefinition_Type)
      {
         2, 1,-2,-1, 0, 1
      }
      );
      
  double tsd2,p_02; 
  /** Calculate New Viscosity **/
  
     if (pc == 1.0){
		 FeVariable_InterpolateWithinElement( self->temperatureField, lElement_I, xi, &temperature );
		 FeVariable_InterpolateWithinElement( self->pressureField, lElement_I, xi, &pressure );
		 p_02 = sp_refP - sp_cs*(temperature-273.);
		 tsd2 = p_02+(temperature-273.)*sp_cs;
		 
		 if (pressure > tsd2){
			//viscosity *= sp_dv*exp( (E + pressure*V) / (n*R*temperature) );
			viscosity = 0.5 * pow( sp_da/sp_dv, -1.0/n );
		 }
		 else{
			 viscosity = 0.5 * pow( A, -1.0/n );
		 }
	 }
	 else{
		 viscosity = 0.5 * pow( A, -1.0/n );
     }
  

  /* strain rate dependency */
  if( fabs( n - 1.0 ) > 1.0e-5 )
	 viscosity *= pow( eII, 1.0/n - 1.0 );
  /* get temperature and pressure */
  if( self->temperatureField && self->pressureField ) {
     FeVariable_InterpolateWithinElement( self->temperatureField, lElement_I, xi, &temperature );
     FeVariable_InterpolateWithinElement( self->pressureField, lElement_I, xi, &pressure );
	 p_02 = sp_refP - sp_cs*(temperature-273.);
	 tsd2 = p_02+(temperature-273.)*sp_cs;
     if( temperature < 0 ) temperature=DBL_MIN;
     /* temperature and pressure dependency - arrhenius */
     
     if (pc == 1.0){
		  if (pressure > tsd2){
			      viscosity *= exp( (sp_de + pressure*sp_dvol) / (n*R*temperature) ); 
		  }
		  else{
			viscosity *= exp( (E + pressure*V) / (n*R*temperature) );	
			//printf("A = %g, eII = %g, V = %g, E = %g, n = %g, viscosity = %g\n",A,eII,V,E,n,viscosity);
		  }
	 }
	 else if (sm == 1.0){
		 if (temperature < 1473.){
			viscosity *= exp( (E + pressure*V) / (n*R*1473.) );	
		 }
		 else{
			viscosity *= exp( (E + pressure*V) / (n*R*temperature) );	
		 }
	 }
	 else{
		viscosity *= exp( (E + pressure*V) / (n*R*temperature) );		 
	 }

	 
  }


  Journal_Firewall( !isnan(viscosity), Journal_Register( Error_Type, (Name)PatriceArrhenius_Type ), "Viscosity is nan\n" );
  Journal_Firewall( viscosity>0, Journal_Register( Error_Type, (Name)PatriceArrhenius_Type ), "Viscosity is zero\n" );

  /* melt dependency 
  if( F != 0 )
	 viscosity *= exp( -a*F/n );
    */
  ConstitutiveMatrix_SetIsotropicViscosity( constitutiveMatrix, viscosity );
}


