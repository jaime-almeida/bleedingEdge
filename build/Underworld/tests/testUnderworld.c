#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <pcu/pcu.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include <Underworld/Underworld.h>
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Rheology/tests/ByerleeYieldingSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Rheology/tests/ConstitutiveMatrixSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Rheology/tests/DirectorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Rheology/tests/TestHasYieldedFlagSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Rheology/tests/ViscousSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Rheology/tests/VonMisesYieldingSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Utils/tests/PpcManagerSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/Underworld/Utils/tests/USOSuite.h"


int main( int argc, char* argv[] ) {
   pcu_listener_t*   textlsnr;
   pcu_listener_t*   xmllsnr;
   PCU_Runner_Status result;

   chdir( "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/build/tests" );

   MPI_Init( &argc, &argv );
   pcu_runner_init( argc, argv );
   
#ifdef NOSHARED
   stgdomain_register_static_modules();
   stgfem_register_static_modules();
   picellerator_register_static_modules();
   underworld_register_static_modules();
   StGermain_Init(&argc, &argv);
   StgDomain_Init(&argc, &argv);
   StgFEM_Init(&argc, &argv);
   PICellerator_Init(&argc, &argv);
   Underworld_Init(&argc, &argv);
#else
   StGermain_Init(&argc, &argv);
   ModulesManager_LoadModule(stgToolboxesManager, "Underworld" );
#endif

   stJournal->firewallProducesAssert = True;
   stJournal->firewallProtected = True;

   pcu_runner_addSuite( ByerleeYieldingSuite, ByerleeYieldingSuite, Underworld/Rheology );
   pcu_runner_addSuite( ConstitutiveMatrixSuite, ConstitutiveMatrixSuite, Underworld/Rheology );
   pcu_runner_addSuite( DirectorSuite, DirectorSuite, Underworld/Rheology );
   pcu_runner_addSuite( TestHasYieldedFlagSuite, TestHasYieldedFlagSuite, Underworld/Rheology );
   pcu_runner_addSuite( ViscousSuite, ViscousSuite, Underworld/Rheology );
   pcu_runner_addSuite( VonMisesYieldingSuite, VonMisesYieldingSuite, Underworld/Rheology );
   pcu_runner_addSuite( PpcManagerSuite, PpcManagerSuite, Underworld/Utils );
   pcu_runner_addSuite( USOSuite, USOSuite, Underworld/Utils );

   textlsnr = pcu_textoutput_create( "Underworld", PCU_PRINT_DOCS );
   xmllsnr = pcu_xmloutput_create( "Underworld", PCU_PRINT_DOCS, "test-results" );
   pcu_runner_associateListener( textlsnr );
   pcu_runner_associateListener( xmllsnr );
   result = pcu_runner_run();
   pcu_textoutput_destroy( textlsnr );
   pcu_xmloutput_destroy( xmllsnr );

   
#ifdef NOSHARED
   Underworld_Finalise();
   PICellerator_Finalise();
   StgFEM_Finalise();
   StgDomain_Finalise();
   StGermain_Finalise();
#else
   ModulesManager_UnloadModule(stgToolboxesManager, "Underworld" );
   StGermain_Finalise();
#endif

   pcu_runner_finalise();
   MPI_Finalize();
   if ( result == PCU_RUNNER_ALLPASS ) {
      return EXIT_SUCCESS;
   }
   else {
      return EXIT_FAILURE;
   }
}
