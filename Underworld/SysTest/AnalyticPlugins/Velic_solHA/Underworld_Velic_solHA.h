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

#ifndef __Underworld_Velic_solHA_h__
#define __Underworld_Velic_solHA_h__

   extern const Type Underworld_Velic_solHA_Type;

   typedef struct {
      __Codelet;
      double sigma;
      double eta;
      double dx;
      double dy;
      double x0;
      double y0;
   } Underworld_Velic_solHA;

   Index Underworld_Velic_solHA_Register( PluginsManager* pluginsManager );

   void* _Underworld_Velic_solHA_DefaultNew( Name name );

   void _Underworld_Velic_solHA_AssignFromXML( void* analyticSolution, Stg_ComponentFactory* cf, void* data );

   void _Underworld_Velic_solHA_Init( Underworld_Velic_solHA* self, double sigma, double eta, double dx, double dy, double x0, double y0 );

   void Underworld_Velic_solHA_VelocityFunction( void* _context, double* coord, double* velocity );

   void Underworld_Velic_solHA_PressureFunction( void* _context, double* coord, double* pressure );

   void Underworld_Velic_solHA_StressFunction( void* _context, double* coord, double* stress );

   void Underworld_Velic_solHA_StrainRateFunction( void* _context, double* coord, double* strainRate );

   void _Velic_solHA( 
      double pos[],
      double _sigma,
      double _eta,
      double _dx,
      double _dy,
      double _x_0,
      double _y_0,
      double vel[],
      double* presssure, 
      double total_stress[],
      double strain_rate[] );

#endif
