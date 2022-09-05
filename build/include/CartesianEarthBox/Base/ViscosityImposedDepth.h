
#ifndef __Underworld_Rheology_ViscosityImposedDepth_h__
#define __Underworld_Rheology_ViscosityImposedDepth_h__


	/** Textual name of this class */
	extern const Type ViscosityImposedDepth_Type;

		
	/** Rheology class contents */
	#define __ViscosityImposedDepth                                            \
		__Rheology                                                         \
		/* Parameters */                        			   \
		double                                              viscosity;     \
		Bool                                                usexlim;       \
		double                                              minx;          \
		double                                              maxx;          \
		Bool                                                useylim;       \
		double                                              miny;          \
		double                                              maxy;          \
		Bool                                                usezlim;       \
		double                                              minz;          \
		double                                              maxz;          


	struct ViscosityImposedDepth { __ViscosityImposedDepth };
	
	/** Private Constructor */
	
	#ifndef ZERO
	#define ZERO 0
	#endif

	#define VISCOSITYIMPOSEDDEPTH_DEFARGS \
                RHEOLOGY_DEFARGS

	#define VISCOSITYIMPOSEDDEPTH_PASSARGS \
                RHEOLOGY_PASSARGS

	ViscosityImposedDepth* _ViscosityImposedDepth_New(  VISCOSITYIMPOSEDDEPTH_DEFARGS  );

	void* _ViscosityImposedDepth_DefaultNew( Name name );
	void  _ViscosityImposedDepth_AssignFromXML( void* rheology, Stg_ComponentFactory* cf, void* data );

	void _ViscosityImposedDepth_ModifyConstitutiveMatrix( 
		void*                                              rheology, 
		ConstitutiveMatrix*                                constitutiveMatrix,
		MaterialPointsSwarm*                               swarm,
		Element_LocalIndex                                 lElement_I,
		MaterialPoint*                                     materialPoint,
		Coord                                              xi );
#endif

