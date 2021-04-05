#!/bin/bash
read_sources () {
        FILES=/etc/apt/sources.list.d/
        cd $FILES
        awk '{ print $2 }' ../sources.list
        for f in *.list 

        do
            awk '{ print $2 }' $f 
        done
 }

read_sources | grep http | sed -e 's|^[^/]*//||' -e 's|/.*$||' | uniq
