#!/bin/bash

for file in server/database/*.db; do
    if [ -f "$file" ]; then
        > "$file"
    fi
done
