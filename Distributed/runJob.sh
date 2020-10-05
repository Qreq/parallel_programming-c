#!/bin/bash
if [".$1" == ""]; then
	echo "Positional paramter 1 is empty"
else
mpirun -machinefile /home/370user30/370CT/Distributed/machines --map-by ppr:4:node $1

fi
