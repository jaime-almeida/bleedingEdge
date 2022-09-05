#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <pcu/pcu.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include <StgFEM/StgFEM.h>
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Discretisation/tests/C2GeneratorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Discretisation/tests/ElementTypeRegisterSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Discretisation/tests/ElementTypeSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Discretisation/tests/FeEquationNumberSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Discretisation/tests/FeVariableSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Discretisation/tests/TrilinearElementTypeSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/SLE/SystemSetup/tests/ContextSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/SLE/SystemSetup/tests/SolutionVectorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/SLE/SystemSetup/tests/StiffnessMatrixSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/SLE/ProvidedSystems/AdvectionDiffusion/tests/LumpedMassMatrixSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/SLE/ProvidedSystems/AdvectionDiffusion/tests/UpwindXiSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Assembly/tests/IsoviscousStiffnessSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/libStgFEM/tests/LibStgFEMSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgFEM/Utils/tests/SemiLagrangianIntegratorSuite.h"


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
   StGermain_Init(&argc, &argv);
   StgDomain_Init(&argc, &argv);
   StgFEM_Init(&argc, &argv);
#else
   StGermain_Init(&argc, &argv);
   ModulesManager_LoadModule(stgToolboxesManager, "StgFEM" );
#endif

   stJournal->firewallProducesAssert = True;
   stJournal->firewallProtected = True;

   pcu_runner_addSuite( C2GeneratorSuite, C2GeneratorSuite, StgFEM/Discretisation );
   pcu_runner_addSuite( ElementTypeRegisterSuite, ElementTypeRegisterSuite, StgFEM/Discretisation );
   pcu_runner_addSuite( ElementTypeSuite, ElementTypeSuite, StgFEM/Discretisation );
   pcu_runner_addSuite( FeEquationNumberSuite, FeEquationNumberSuite, StgFEM/Discretisation );
   pcu_runner_addSuite( FeVariableSuite, FeVariableSuite, StgFEM/Discretisation );
   pcu_runner_addSuite( TrilinearElementTypeSuite, TrilinearElementTypeSuite, StgFEM/Discretisation );
   pcu_runner_addSuite( ContextSuite, ContextSuite, StgFEM/SLE/SystemSetup );
   pcu_runner_addSuite( SolutionVectorSuite, SolutionVectorSuite, StgFEM/SLE/SystemSetup );
   pcu_runner_addSuite( StiffnessMatrixSuite, StiffnessMatrixSuite, StgFEM/SLE/SystemSetup );
   pcu_runner_addSuite( LumpedMassMatrixSuite, LumpedMassMatrixSuite, StgFEM/SLE/ProvidedSystems/AdvectionDiffusion );
   pcu_runner_addSuite( UpwindXiSuite, UpwindXiSuite, StgFEM/SLE/ProvidedSystems/AdvectionDiffusion );
   pcu_runner_addSuite( IsoviscousStiffnessSuite, IsoviscousStiffnessSuite, StgFEM/Assembly );
   pcu_runner_addSuite( LibStgFEMSuite, LibStgFEMSuite, StgFEM/libStgFEM );
   pcu_runner_addSuite( SemiLagrangianIntegratorSuite, SemiLagrangianIntegratorSuite, StgFEM/Utils );

   textlsnr = pcu_textoutput_create( "StgFEM", PCU_PRINT_DOCS );
   xmllsnr = pcu_xmloutput_create( "StgFEM", PCU_PRINT_DOCS, "test-results" );
   pcu_runner_associateListener( textlsnr );
   pcu_runner_associateListener( xmllsnr );
   result = pcu_runner_run();
   pcu_textoutput_destroy( textlsnr );
   pcu_xmloutput_destroy( xmllsnr );

   
#ifdef NOSHARED
   StgFEM_Finalise();
   StgDomain_Finalise();
   StGermain_Finalise();
#else
   ModulesManager_UnloadModule(stgToolboxesManager, "StgFEM" );
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
