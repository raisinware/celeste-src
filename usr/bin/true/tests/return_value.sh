#!/bin/sh
./true
if [ $? = 0 ]; then
	exit 0
fi
exit 1
