#!/bin/bash
# delete .svn directories recursive
rm -rf `find . -type d -name .svn`

#find . -name .svn -print0 | xargs -0 rm -rf

