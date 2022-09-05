#!/bin/bash
#Run provided mercurial command in all directories
#Usage: ./hg-all.sh [command]
#Prompts for password

check-errs()
{
  # Function. Parameter 1 is the return code
  # Para. 2 is text to display on failure.
  if [ ${1} -gt 1 ]; then
      echo "ERROR # ${1} : ${2}"
      exit ${1}
  fi
}


if [ "${*}" == "" ]; then
   echo "Usage: hg-all.sh [mercurial command]"
   echo "Example: hg-all.sh st -m"
   exit
fi

#Process current dir and first level of subdirs excluding .hg
wd=`pwd`
for f in `find . -maxdepth 1 -type d \( ! -iname ".hg" \)`
do
    #skip if no .hg folder
    ls $f/.hg &> /dev/null
    if [ "${?}" -ne "0" ]; then
        continue 
    fi

    cd $f
    echo ""
    echo "[ $f ]"

    hg ${*} 
    check-errs $? "hg ${*} failed"
    cd $wd
done
