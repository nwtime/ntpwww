# Use gmake

BRANCH=`git branch | awk '{ print $$2}'`

include common/Makefile
