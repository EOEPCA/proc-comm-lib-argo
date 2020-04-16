#!/usr/bin/env bash

rm *.rpm
NOW=$(date +"%Y%d%m%H%M%S")
RELEASE=SNAPSHOT${NOW}

mkdir -p @RPM_BASE@/{BUILD,RPMS,SOURCES,SPECS,SRPMS}

if [ "$1" == "master" ] || [ "$1" == "multiThread" ]; then
  RELEASE=@CPACK_PACKAGE_RELEASE@
fi

cat codelithic.spec | sed -e "s/CPACKPACKAGERELEASE/${RELEASE}/g" >codelithic.spec.out

rpmbuild -v -bb --clean codelithic.spec.out &&
  mv @RPM_BASE@/*.rpm @CMAKE_CURRENT_BINARY_DIR@/
