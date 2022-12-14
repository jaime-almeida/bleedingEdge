#! /bin/bash

# This variable needs to be set to point to the Underworld build you are using

export UWPATH=$HOME/+Codes/stgUnderworldE-local-stable  # Usually a symbolic link to most recent build !

# These variables are defined from the environment above and do not need to be changed

export UW_DIR=$UWPATH/build
export UWEXEC=$UW_DIR/bin/Underworld
export GLUCIFER=$UWPATH/build/bin/gLucifer

# These variables define the location of the OzbenchSubduction.xml file you are using ($PROJECTPATH)
# and the directory where the output is destined to be stored ($OUTPUTPATH)
# and the name of the subdirectory for this run (note, you can over-ride parameters on the
# command line and therefore run multiple experiments without changing the XML files	)

PROJECTPATH=$UWPATH/Underworld/InputFiles/+PublishedResults/SchellartEtAl-Science2010
OUTPUTPATH=$HOME/+Simulations/SchellartEtAl-Science2010-SubductionRuns
EXPTNAME=SchellartEtAl-2000kmWide

OUTPUTDIR=$OUTPUTPATH/$EXPTNAME 
INPUTDIR=$OUTPUTDIR

if [ ! -d $OUTPUTDIR ]; then 
	mkdir -p $OUTPUTDIR; 
fi
	
mkdir $OUTPUTDIR/Checkpoints >& /dev/null

OUTPUTFILE=${OUTPUTDIR}/output.txt
ERRORFILE=${OUTPUTDIR}/errormessages.txt 

openmpirun -np 3 $UWEXEC \
	$PROJECTPATH/SchellartEtAl-Science2010.xml \
	$PROJECTPATH/SchellartEtAl-Science2010-LargePerturbation.xml \
	$UWPATH/StgFEM/Apps/StgFEM_Components/MultigridForRegular.xml \
    -options_file $UWPATH/Underworld/InputFiles/options/options-uzawa-mg.opt \
    --components.uzawa.monitor=True \
    --components.uzawa.tolerance=1.0e-4 \
    --nonLinearMaxIterations=25 \
	--maxTimeSteps=$TIMESTEPS \
	--outputPath=$OUTPUTDIR \
	--dumpEvery=5 \
	--checkpointEvery=10 \
	--saveEvery=5 \
	--checkpointReadPath=$OUTPUTDIR/Checkpoints \
	--checkpointWritePath=$OUTPUTDIR/Checkpoints \
	--checkpointAppendStep=1 \
	--elementResI=96 \
	--elementResJ=48 \
	--elementResK=96 \
	--mgLevels=5 \
	--IGNORErestartTimestep=100 > $OUTPUTFILE

# Note - you can "comment out" a parameter by renaming it to something not used in the code
# (here prefixing with IGNORE)

