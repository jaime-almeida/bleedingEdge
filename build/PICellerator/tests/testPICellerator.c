#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <pcu/pcu.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include <PICellerator/PICellerator.h>
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/PopulationControl/tests/EscapedRoutineSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/Weights/tests/ConstantWeightsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/Weights/tests/DVCWeightsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/Weights/tests/IterativeWeightsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/Weights/tests/MomentBalanceWeightsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/MaterialPoints/tests/AdvectionSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/MaterialPoints/tests/MaterialComponentsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/MaterialPoints/tests/MaterialFeVariableSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/MaterialPoints/tests/PeriodicBoundariesManagerSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/Utils/tests/PCDVCSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/PICellerator/libPICellerator/tests/LibPICelleratorSuite.h"


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
   StGermain_Init(&argc, &argv);
   StgDomain_Init(&argc, &argv);
   StgFEM_Init(&argc, &argv);
   PICellerator_Init(&argc, &argv);
#else
   StGermain_Init(&argc, &argv);
   ModulesManager_LoadModule(stgToolboxesManager, "PICellerator" );
#endif

   stJournal->firewallProducesAssert = True;
   stJournal->firewallProtected = True;


   pcu_runner_addSuite( EscapedRoutineSuite, EscapedRoutineSuite, PICellerator/PopulationControl );
   pcu_runner_addSuite( ConstantWeightsSuite, ConstantWeightsSuite, PICellerator/Weights );
   pcu_runner_addSuite( DVCWeightsSuite, DVCWeightsSuite, PICellerator/Weights );
   pcu_runner_addSuite( IterativeWeightsSuite, IterativeWeightsSuite, PICellerator/Weights );
   pcu_runner_addSuite( MomentBalanceWeightsSuite, MomentBalanceWeightsSuite, PICellerator/Weights );
   pcu_runner_addSuite( AdvectionSuite, AdvectionSuite, PICellerator/MaterialPoints );
   pcu_runner_addSuite( MaterialComponentsSuite, MaterialComponentsSuite, PICellerator/MaterialPoints );
   pcu_runner_addSuite( MaterialFeVariableSuite, MaterialFeVariableSuite, PICellerator/MaterialPoints );
   pcu_runner_addSuite( PeriodicBoundariesManagerSuite, PeriodicBoundariesManagerSuite, PICellerator/MaterialPoints );
   pcu_runner_addSuite( PCDVCSuite, PCDVCSuite, PICellerator/Utils );
   pcu_runner_addSuite( LibPICelleratorSuite, LibPICelleratorSuite, PICellerator/libPICellerator );

   textlsnr = pcu_textoutput_create( "PICellerator", PCU_PRINT_DOCS );
   xmllsnr = pcu_xmloutput_create( "PICellerator", PCU_PRINT_DOCS, "test-results" );
   pcu_runner_associateListener( textlsnr );
   pcu_runner_associateListener( xmllsnr );
   result = pcu_runner_run();
   pcu_textoutput_destroy( textlsnr );
   pcu_xmloutput_destroy( xmllsnr );

   
#ifdef NOSHARED
   PICellerator_Finalise();
   StgFEM_Finalise();
   StgDomain_Finalise();
   StGermain_Finalise();
#else
   ModulesManager_UnloadModule(stgToolboxesManager, "PICellerator" );
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
