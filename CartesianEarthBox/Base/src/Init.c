/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
** Copyright (c) 2005-2010, Monash University
** All rights reserved.
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 		* Redistributions of source code must retain the above copyright notice,
** 			this list of conditions and the following disclaimer.
** 		* Redistributions in binary form must reproduce the above copyright
**			notice, this list of conditions and the following disclaimer in the
**			documentation and/or other materials provided with the distribution.
** 		* Neither the name of the Monash University nor the names of its contributors
**			may be used to endorse or promote products derived from this software
**			without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
** PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
** BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
** OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** Contact:
*%  Louis Moresi - Louis.Moresi(at)monash.edu
*%
*% Development Team :
*%  http://www.underworldproject.org/aboutus.html
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include <Underworld/Underworld.h>

#include "Base.h"

Stream* CartesianEarthBoxInfo  = NULL;
Stream* CartesianEarthBoxDebug = NULL;
Stream* CartesianEarthBoxError = NULL;

Bool CartesianEarthBox_Base_Init()
{
   Stg_ComponentRegister* componentRegister = Stg_ComponentRegister_Get_ComponentRegister();

   Journal_Printf( Journal_Register( Debug_Type, (Name)"Context"  ), "In: %s\n", __func__ ); /* DO NOT CHANGE OR REMOVE */

   /* Setup some streams for you to use */
   CartesianEarthBoxInfo  = Journal_Register(  Info_Type, (Name)"CartesianEarthBoxInfo"  );
   CartesianEarthBoxDebug = Journal_Register( Debug_Type, (Name)"CartesianEarthBoxDebug" );
   CartesianEarthBoxError = Journal_Register( Error_Type, (Name)"CartesianEarthBoxError" );

   /* Register your components here */
   Stg_ComponentRegister_Add( componentRegister, CartesianEarthBoxExampleComponent_Type, (Name)"0", _CartesianEarthBoxExampleComponent_DefaultNew  );
   Stg_ComponentRegister_Add( componentRegister, ViscosityImposedDepth_Type, (Name)"0", _ViscosityImposedDepth_DefaultNew  );
   Stg_ComponentRegister_Add( componentRegister, PatriceArrhenius_Type, (Name)"0", _PatriceArrhenius_DefaultNew  );

   /* Register Parents for type checking */
   RegisterParent( CartesianEarthBoxExampleComponent_Type, Stg_Component_Type );
   RegisterParent( ViscosityImposedDepth_Type, Rheology_Type );
   RegisterParent( PatriceArrhenius_Type, Rheology_Type );

   return True;
}



