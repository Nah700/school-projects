#!/bin/bash

PORT_FILE="/tmp/port.txt"
DEFAULT_PORT=1024

if [ -f "$PORT_FILE" ]; then
    PORT=$(<"$PORT_FILE")
else
    PORT=$DEFAULT_PORT
fi

PORT2=$((PORT + 1))
echo $PORT2 > "$PORT_FILE"
printf "RUN_SERVER.SH : Server started on \e[4;34m\e[1;94mport %d\e[0m\n" $PORT
LD_LIBRARY_PATH=$PWD/libs/myteams/ ./myteams_server $PORT


