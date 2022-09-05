#ifndef __Underworld_Rheology_PatriceArrhenius_h__
#define __Underworld_Rheology_PatriceArrhenius_h__

	/** Textual name of this class */
	extern const Type PatriceArrhenius_Type;
		
	/** Rheology class contents */
	#define __PatriceArrhenius \
		/* Macro defining parent goes here */ \
		__Rheology \
		/* Virtual functions go here */ \
		/* Material Parameters */\
		Scaling*                                         scaling; \
		ParticleMelting*                                    melting; \
		FeVariable*                                         strainRateInvField; \
		FeVariable*                                         temperatureField; \
		FeVariable*                                         pressureField; \
		double                                              preExponentialFactor; \
		double                                              stressExponent; \
		double                                              activationEnergy; \
		double                                              activationVolume; \
		  double 				OlSp_refP; 				 \
		  double 				OlSp_drho; 				 \
		  double 				OlSp_ClapS; 				 \
		  double 				OlSp_dvis; 				 \
		  double 				SpPe_refP; 				 \
		  double 				SpPe_drho; 				 \
		  double 				SpPe_ClapS; 				 \
		  double 				SpPe_dvis; 				 \
		  double 				SpPe_dA; 				 \
		  double 				SpPe_dV; 				 \
		  double 				SpPe_dE; 				 \
		  double 				lm_phasechange; 				 \
		  double 				serp_mantle; 				 \
      double                                              defaultStrainRateInvariant; \

	struct PatriceArrhenius { __PatriceArrhenius };
	
	/** Private Constructor: This will accept all the virtual functions for this class as arguments. */
	
	#ifndef ZERO
	#define ZERO 0
	#endif

	#define PatriceArrhenius_DEFARGS \
                RHEOLOGY_DEFARGS

	#define PatriceArrhenius_PASSARGS \
                RHEOLOGY_PASSARGS

	PatriceArrhenius* _PatriceArrhenius_New(  NONNEWTONIAN_DEFARGS  );

	/* 'Stg_Component' implementations */
	void* _PatriceArrhenius_DefaultNew( Name name ) ;
	void _PatriceArrhenius_AssignFromXML( void* rheology, Stg_ComponentFactory* cf, void* data );
   void _PatriceArrhenius_Build( void* _self, void* data );
   void _PatriceArrhenius_Initialise( void* _self, void* data );
   void _PatriceArrhenius_Destroy( void* _self, void* data );
   
	void _PatriceArrhenius_ModifyConstitutiveMatrix( 
		void*                                              rheology, 
		ConstitutiveMatrix*                                constitutiveMatrix,
		MaterialPointsSwarm*                               swarm,
		Element_LocalIndex                                 lElement_I,
		MaterialPoint*                                     materialPoint,
		Coord                                              xi );
#endif

