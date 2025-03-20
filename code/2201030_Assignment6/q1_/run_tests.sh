#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <test_cases_file> <output_file>"
    exit 1
fi

test_cases_file="$1"
output_file="$2"

if [ ! -f "$test_cases_file" ]; then
    echo "Test cases file not found!"
    exit 1
fi

> "$output_file"

while IFS= read -r test_case || [ -n "$test_case" ]; do
    if [ -z "$test_case" ]; then
        continue
    fi

    echo "Running test case: $test_case"
    
    result=$(echo "$test_case" | ./1)

    echo "Result: $result"
    echo "--------------------------"

    echo "Test case: $test_case" >> "$output_file"
    echo "Result: $result" >> "$output_file"
    echo "--------------------------" >> "$output_file"

done < "$test_cases_file"

echo "Test execution completed! Results saved in $output_file"
