#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <pcu/pcu.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <gLucifer/gLucifer.h>
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/gLucifer/Base/tests/gLuciferBaseSuite.h"


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
   gLucifer_register_static_modules();
   StGermain_Init(&argc, &argv);
   StgDomain_Init(&argc, &argv);
   StgFEM_Init(&argc, &argv);
   gLucifer_Init(&argc, &argv);
#else
   StGermain_Init(&argc, &argv);
   ModulesManager_LoadModule(stgToolboxesManager, "gLucifer" );
#endif
   stJournal->firewallProducesAssert = True;
   stJournal->firewallProtected = True;

   pcu_runner_addSuite( gLuciferBaseSuite, gLuciferBaseSuite, gLucifer/Base );

   textlsnr = pcu_textoutput_create( "gLucifer", PCU_PRINT_DOCS );
   xmllsnr = pcu_xmloutput_create( "gLucifer", PCU_PRINT_DOCS, "test-results" );
   pcu_runner_associateListener( textlsnr );
   pcu_runner_associateListener( xmllsnr );
   result = pcu_runner_run();
   pcu_textoutput_destroy( textlsnr );
   pcu_xmloutput_destroy( xmllsnr );

   #ifdef NOSHARED
   gLucifer_Finalise();
   StgFEM_Finalise();
   StgDomain_Finalise();
   StGermain_Finalise();
#else
   ModulesManager_UnloadModule(stgToolboxesManager, "gLucifer" );
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
