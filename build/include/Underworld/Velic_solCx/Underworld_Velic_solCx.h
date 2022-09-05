/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
** Copyright (c) 2005-2010, Monash University 
** All rights reserved.
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
**       * Redistributions of source code must retain the above copyright notice, 
**          this list of conditions and the following disclaimer.
**       * Redistributions in binary form must reproduce the above copyright 
**         notice, this list of conditions and the following disclaimer in the 
**         documentation and/or other materials provided with the distribution.
**       * Neither the name of the Monash University nor the names of its contributors 
**         may be used to endorse or promote products derived from this software 
**         without specific prior written permission.
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
*%  Louis Moresi - Louis.Moresi@monash.edu
*%
*% Development Team :
*%  http://www.underworldproject.org/aboutus.html
**
**~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include <Underworld/Underworld.h>

#ifndef __Underworld_Velic_solCx_h__
#define __Underworld_Velic_solCx_h__

   extern const Type Underworld_Velic_solCx_Type;

   typedef struct {
      __Codelet;
      double etaA; /* Input parameters: density, viscosity A */
      double etaB; /* Input parameters: density, viscosity B */
      double xc; /* Input parameters: viscosity jump location */
      int    n;
   } Underworld_Velic_solCx;

   Index Underworld_Velic_solCx_Register( PluginsManager* pluginsManager );

   void* _Underworld_Velic_solCx_DefaultNew( Name name );

   void _Underworld_Velic_solCx_AssignFromXML( void* analyticSolution, Stg_ComponentFactory* cf, void* data );

   void _Underworld_Velic_solCx_Init( Underworld_Velic_solCx* self, double etaA, double etaB, double xc, int n );

   void Underworld_Velic_solCx_VelocityFunction( void* _context, double* coord, double* velocity );

   void Underworld_Velic_solCx_PressureFunction( void* _context, double* coord, double* pressure );

   void Underworld_Velic_solCx_StressFunction( void* _context, double* coord, double* stress );

   void Underworld_Velic_solCx_StrainRateFunction( void* _context, double* coord, double* strainRate );

   void Underworld_Velic_solCx_ViscosityFunction( void* _context, double* coord, double* viscosity );

   void _Velic_solCx(
      double pos[], 
      double _eta_A,
      double _eta_B, /* Input parameters: density, viscosity A, viscosity B */
      double _x_c,
      int _n, /* Input parameters: viscosity jump location, wavenumber in x */
      double vel[],
      double* presssure, 
      double total_stress[],
      double strain_rate[] );

#endif
