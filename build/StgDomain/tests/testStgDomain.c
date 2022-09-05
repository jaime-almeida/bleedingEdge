#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <pcu/pcu.h>
#include <StGermain/StGermain.h>
#include <StgDomain/StgDomain.h>
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/ComplexMathSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/ComplexVectorMathSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/DelaunaySuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/DimensionMacrosSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/EdgeSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/LineSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/ParallelDelaunaySuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/PlaneSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/TensorMathSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/TensorMultMathSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/TrigMathSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Geometry/tests/VectorMathSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Shape/tests/ShapeSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Mesh/tests/CartesianGeneratorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Mesh/tests/DecompSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Mesh/tests/MeshSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/ElementCellLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/GaussLayoutSingleCellSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/GaussLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/ManualParticleLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/ParticleCoordsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/ShadowSyncSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/SingleAttractorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/SingleCellLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/SpaceFillerParticleLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/SwarmDumpAndLoadSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/SwarmOutputSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/SwarmSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Swarm/tests/WithinShapeParticleLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/AllNodesVCSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/CompositeVCSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/CornerVCSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/DofLayoutSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/FieldVariableRegisterSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/OperatorFieldVariableSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/RegularMeshUtilsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/SobolGeneratorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/TimeIntegrationSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/Utils/tests/WallVCSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StgDomain/libStgDomain/tests/LibStgDomainSuite.h"


int main( int argc, char* argv[] ) {
   pcu_listener_t*   textlsnr;
   pcu_listener_t*   xmllsnr;
   PCU_Runner_Status result;

   chdir( "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/build/tests" );

   MPI_Init( &argc, &argv );
   pcu_runner_init( argc, argv );
   
#ifdef NOSHARED
   stgdomain_register_static_modules();
   StGermain_Init(&argc, &argv);
   StgDomain_Init(&argc, &argv);
#else
   StGermain_Init(&argc, &argv);
   ModulesManager_LoadModule(stgToolboxesManager, "StgDomain" );
#endif

   stJournal->firewallProducesAssert = True;
   stJournal->firewallProtected = True;

   pcu_runner_addSuite( ComplexMathSuite, ComplexMathSuite, StgDomain/Geometry );
   pcu_runner_addSuite( ComplexVectorMathSuite, ComplexVectorMathSuite, StgDomain/Geometry );
   pcu_runner_addSuite( DelaunaySuite, DelaunaySuite, StgDomain/Geometry );
   pcu_runner_addSuite( DimensionMacrosSuite, DimensionMacrosSuite, StgDomain/Geometry );
   pcu_runner_addSuite( EdgeSuite, EdgeSuite, StgDomain/Geometry );
   pcu_runner_addSuite( LineSuite, LineSuite, StgDomain/Geometry );
   pcu_runner_addSuite( ParallelDelaunaySuite, ParallelDelaunaySuite, StgDomain/Geometry );
   pcu_runner_addSuite( PlaneSuite, PlaneSuite, StgDomain/Geometry );
   pcu_runner_addSuite( TensorMathSuite, TensorMathSuite, StgDomain/Geometry );
   pcu_runner_addSuite( TensorMultMathSuite, TensorMultMathSuite, StgDomain/Geometry );
   pcu_runner_addSuite( TrigMathSuite, TrigMathSuite, StgDomain/Geometry );
   pcu_runner_addSuite( VectorMathSuite, VectorMathSuite, StgDomain/Geometry );
   pcu_runner_addSuite( ShapeSuite, ShapeSuite, StgDomain/Shape );
   pcu_runner_addSuite( CartesianGeneratorSuite, CartesianGeneratorSuite, StgDomain/Mesh );
   pcu_runner_addSuite( DecompSuite, DecompSuite, StgDomain/Mesh );
   pcu_runner_addSuite( MeshSuite, MeshSuite, StgDomain/Mesh );
   pcu_runner_addSuite( ElementCellLayoutSuite, ElementCellLayoutSuite, StgDomain/Swarm );
   pcu_runner_addSuite( GaussLayoutSingleCellSuite, GaussLayoutSingleCellSuite, StgDomain/Swarm );
   pcu_runner_addSuite( GaussLayoutSuite, GaussLayoutSuite, StgDomain/Swarm );
   pcu_runner_addSuite( ManualParticleLayoutSuite, ManualParticleLayoutSuite, StgDomain/Swarm );
   pcu_runner_addSuite( ParticleCoordsSuite, ParticleCoordsSuite, StgDomain/Swarm );
   pcu_runner_addSuite( ShadowSyncSuite, ShadowSyncSuite, StgDomain/Swarm );
   pcu_runner_addSuite( SingleAttractorSuite, SingleAttractorSuite, StgDomain/Swarm );
   pcu_runner_addSuite( SingleCellLayoutSuite, SingleCellLayoutSuite, StgDomain/Swarm );
   pcu_runner_addSuite( SpaceFillerParticleLayoutSuite, SpaceFillerParticleLayoutSuite, StgDomain/Swarm );
   pcu_runner_addSuite( SwarmDumpAndLoadSuite, SwarmDumpAndLoadSuite, StgDomain/Swarm );
   pcu_runner_addSuite( SwarmOutputSuite, SwarmOutputSuite, StgDomain/Swarm );
   pcu_runner_addSuite( SwarmSuite, SwarmSuite, StgDomain/Swarm );
   pcu_runner_addSuite( WithinShapeParticleLayoutSuite, WithinShapeParticleLayoutSuite, StgDomain/Swarm );
   pcu_runner_addSuite( AllNodesVCSuite, AllNodesVCSuite, StgDomain/Utils );
   pcu_runner_addSuite( CompositeVCSuite, CompositeVCSuite, StgDomain/Utils );
   pcu_runner_addSuite( CornerVCSuite, CornerVCSuite, StgDomain/Utils );
   pcu_runner_addSuite( DofLayoutSuite, DofLayoutSuite, StgDomain/Utils );
   pcu_runner_addSuite( FieldVariableRegisterSuite, FieldVariableRegisterSuite, StgDomain/Utils );
   pcu_runner_addSuite( OperatorFieldVariableSuite, OperatorFieldVariableSuite, StgDomain/Utils );
   pcu_runner_addSuite( RegularMeshUtilsSuite, RegularMeshUtilsSuite, StgDomain/Utils );
   pcu_runner_addSuite( SobolGeneratorSuite, SobolGeneratorSuite, StgDomain/Utils );
   pcu_runner_addSuite( TimeIntegrationSuite, TimeIntegrationSuite, StgDomain/Utils );
   pcu_runner_addSuite( WallVCSuite, WallVCSuite, StgDomain/Utils );
   pcu_runner_addSuite( LibStgDomainSuite, LibStgDomainSuite, StgDomain/libStgDomain );

   textlsnr = pcu_textoutput_create( "StgDomain", PCU_PRINT_DOCS );
   xmllsnr = pcu_xmloutput_create( "StgDomain", PCU_PRINT_DOCS, "test-results" );
   pcu_runner_associateListener( textlsnr );
   pcu_runner_associateListener( xmllsnr );
   result = pcu_runner_run();
   pcu_textoutput_destroy( textlsnr );
   pcu_xmloutput_destroy( xmllsnr );

   
#ifdef NOSHARED
   StgDomain_Finalise();
   StGermain_Finalise();
#else
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
