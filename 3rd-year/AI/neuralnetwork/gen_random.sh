#!/bin/bash

DATASETS_DIR="./datasets"

OUTPUT_FILE="./datasets/out_random.txt"

if [ -f "$OUTPUT_FILE" ]; then
    rm "$OUTPUT_FILE"
fi

get_random_lines() {
    local file=$1
    shuf -n 100 "$file"
}

for file in $(find "$DATASETS_DIR" -type f -name "*.txt"); do
    get_random_lines "$file" >> "$OUTPUT_FILE"
done

shuf "$OUTPUT_FILE" -o "$OUTPUT_FILE"
