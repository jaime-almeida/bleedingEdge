#include <stdlib.h>
#include <unistd.h>
#include <mpi.h>
#include <pcu/pcu.h>
#include <StGermain/StGermain.h>
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/CommonRoutinesSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/MemMonitorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/MemoryReportSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/MemorySuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/NamedObject_Register2Suite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/NamedObject_RegisterSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/ObjectListSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/PrimitiveObjectSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/Stg_asprintfSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Foundation/tests/TimeMonitorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/IO/tests/DictionarySuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/IO/tests/IO_HandlerSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/IO/tests/JournalSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/IO/tests/MPIStreamSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/IO/tests/PathUtilsSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/IO/tests/RankFormatterSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/BTreeSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/HashTableSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/IArraySuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/IMapSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/ISetSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/IndexMapSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/IndexSetSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/LinkedListIteratorSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/LinkedListSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/ListSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/MPIRoutinesSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/MaxHeapSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/MemoryPoolSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/PtrMapSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/PtrSetSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/RangeSetSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/STreeMapSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/STreeSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/SetSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Container/tests/UIntMapSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Automation/tests/CallGraphSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Automation/tests/CommSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Automation/tests/ComponentCopySuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Automation/tests/HierarchyTableSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Extensibility/tests/EntryPointSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Extensibility/tests/ExtensionSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/AbstractContextSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/ConditionFunctionSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/DictionaryCheckSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/LiveComponentRegisterSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/SetVC_Suite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/VariableAllVC_Suite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/VariableDumpStreamSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/VariableSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Base/Context/tests/Variable_RegisterSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Utils/tests/ParserSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Utils/tests/ProgressSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/Utils/tests/ScalingSuite.h"
#include "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/StGermain/libStGermain/tests/LibStGermainSuite.h"


int main( int argc, char* argv[] ) {
   pcu_listener_t*   textlsnr;
   pcu_listener_t*   xmllsnr;
   PCU_Runner_Status result;

   chdir( "/home/jalmeida/uw_home/software/bleedingEdge_nimbus/build/tests" );

   MPI_Init( &argc, &argv );
   pcu_runner_init( argc, argv );
   StGermain_Init(&argc, &argv);
   stJournal->firewallProducesAssert = True;
   stJournal->firewallProtected = True;

   pcu_runner_addSuite( CommonRoutinesSuite, CommonRoutinesSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( MemMonitorSuite, MemMonitorSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( MemoryReportSuite, MemoryReportSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( MemorySuite, MemorySuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( NamedObject_Register2Suite, NamedObject_Register2Suite, StGermain/Base/Foundation );
   pcu_runner_addSuite( NamedObject_RegisterSuite, NamedObject_RegisterSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( ObjectListSuite, ObjectListSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( PrimitiveObjectSuite, PrimitiveObjectSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( Stg_asprintfSuite, Stg_asprintfSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( TimeMonitorSuite, TimeMonitorSuite, StGermain/Base/Foundation );
   pcu_runner_addSuite( DictionarySuite, DictionarySuite, StGermain/Base/IO );
   pcu_runner_addSuite( IO_HandlerSuite, IO_HandlerSuite, StGermain/Base/IO );
   pcu_runner_addSuite( JournalSuite, JournalSuite, StGermain/Base/IO );
   pcu_runner_addSuite( MPIStreamSuite, MPIStreamSuite, StGermain/Base/IO );
   pcu_runner_addSuite( PathUtilsSuite, PathUtilsSuite, StGermain/Base/IO );
   pcu_runner_addSuite( RankFormatterSuite, RankFormatterSuite, StGermain/Base/IO );
   pcu_runner_addSuite( BTreeSuite, BTreeSuite, StGermain/Base/Container );
   pcu_runner_addSuite( HashTableSuite, HashTableSuite, StGermain/Base/Container );
   pcu_runner_addSuite( IArraySuite, IArraySuite, StGermain/Base/Container );
   pcu_runner_addSuite( IMapSuite, IMapSuite, StGermain/Base/Container );
   pcu_runner_addSuite( ISetSuite, ISetSuite, StGermain/Base/Container );
   pcu_runner_addSuite( IndexMapSuite, IndexMapSuite, StGermain/Base/Container );
   pcu_runner_addSuite( IndexSetSuite, IndexSetSuite, StGermain/Base/Container );
   pcu_runner_addSuite( LinkedListIteratorSuite, LinkedListIteratorSuite, StGermain/Base/Container );
   pcu_runner_addSuite( LinkedListSuite, LinkedListSuite, StGermain/Base/Container );
   pcu_runner_addSuite( ListSuite, ListSuite, StGermain/Base/Container );
   pcu_runner_addSuite( MPIRoutinesSuite, MPIRoutinesSuite, StGermain/Base/Container );
   pcu_runner_addSuite( MaxHeapSuite, MaxHeapSuite, StGermain/Base/Container );
   pcu_runner_addSuite( MemoryPoolSuite, MemoryPoolSuite, StGermain/Base/Container );
   pcu_runner_addSuite( PtrMapSuite, PtrMapSuite, StGermain/Base/Container );
   pcu_runner_addSuite( PtrSetSuite, PtrSetSuite, StGermain/Base/Container );
   pcu_runner_addSuite( RangeSetSuite, RangeSetSuite, StGermain/Base/Container );
   pcu_runner_addSuite( STreeMapSuite, STreeMapSuite, StGermain/Base/Container );
   pcu_runner_addSuite( STreeSuite, STreeSuite, StGermain/Base/Container );
   pcu_runner_addSuite( SetSuite, SetSuite, StGermain/Base/Container );
   pcu_runner_addSuite( UIntMapSuite, UIntMapSuite, StGermain/Base/Container );
   pcu_runner_addSuite( CallGraphSuite, CallGraphSuite, StGermain/Base/Automation );
   pcu_runner_addSuite( CommSuite, CommSuite, StGermain/Base/Automation );
   pcu_runner_addSuite( ComponentCopySuite, ComponentCopySuite, StGermain/Base/Automation );
   pcu_runner_addSuite( HierarchyTableSuite, HierarchyTableSuite, StGermain/Base/Automation );
   pcu_runner_addSuite( EntryPointSuite, EntryPointSuite, StGermain/Base/Extensibility );
   pcu_runner_addSuite( ExtensionSuite, ExtensionSuite, StGermain/Base/Extensibility );
   pcu_runner_addSuite( AbstractContextSuite, AbstractContextSuite, StGermain/Base/Context );
   pcu_runner_addSuite( ConditionFunctionSuite, ConditionFunctionSuite, StGermain/Base/Context );
   pcu_runner_addSuite( DictionaryCheckSuite, DictionaryCheckSuite, StGermain/Base/Context );
   pcu_runner_addSuite( LiveComponentRegisterSuite, LiveComponentRegisterSuite, StGermain/Base/Context );
   pcu_runner_addSuite( SetVC_Suite, SetVC_Suite, StGermain/Base/Context );
   pcu_runner_addSuite( VariableAllVC_Suite, VariableAllVC_Suite, StGermain/Base/Context );
   pcu_runner_addSuite( VariableDumpStreamSuite, VariableDumpStreamSuite, StGermain/Base/Context );
   pcu_runner_addSuite( VariableSuite, VariableSuite, StGermain/Base/Context );
   pcu_runner_addSuite( Variable_RegisterSuite, Variable_RegisterSuite, StGermain/Base/Context );
   pcu_runner_addSuite( ParserSuite, ParserSuite, StGermain/Utils );
   pcu_runner_addSuite( ProgressSuite, ProgressSuite, StGermain/Utils );
   pcu_runner_addSuite( ScalingSuite, ScalingSuite, StGermain/Utils );
   pcu_runner_addSuite( LibStGermainSuite, LibStGermainSuite, StGermain/libStGermain );

   textlsnr = pcu_textoutput_create( "StGermain", PCU_PRINT_DOCS );
   xmllsnr = pcu_xmloutput_create( "StGermain", PCU_PRINT_DOCS, "test-results" );
   pcu_runner_associateListener( textlsnr );
   pcu_runner_associateListener( xmllsnr );
   result = pcu_runner_run();
   pcu_textoutput_destroy( textlsnr );
   pcu_xmloutput_destroy( xmllsnr );

   StGermain_Finalise();
   pcu_runner_finalise();
   MPI_Finalize();
   if ( result == PCU_RUNNER_ALLPASS ) {
      return EXIT_SUCCESS;
   }
   else {
      return EXIT_FAILURE;
   }
}
