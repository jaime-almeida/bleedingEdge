#!/bin/bash
#Run mercurial pull and update in all directories
#Usage: ./pull+update-all.sh [username]
#Prompts for password

check-errs()
{
  # Function. Parameter 1 is the return code
  # Para. 2 is text to display on failure.
  if [ "${1}" -ne "0" ]; then
      echo "ERROR # ${1} : ${2}"
      exit ${1}
  fi
}

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
    echo "-------- Processing [ $f ] ---------------------------------------"

    #strip start of hg paths output to get repository name
    paths=`hg paths | sed 's/default = https:\/\///'`

    hg pull 
    check-errs $? "hg pull failed"
    hg update 
    check-errs $? "hg update failed"
    cd $wd
done
