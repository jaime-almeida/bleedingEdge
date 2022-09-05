

#include "mpi.h"
#include "petsc.h"
#include "petscvec.h"
#include "petscmat.h"
#include "petscksp.h"
#include "petscsnes.h"

int
dummy_func() {
  PetscInitialize(NULL, NULL, NULL, NULL);
PetscFinalize();
return 0;
}
