#!/bin/bash
for file in testfiles/*.txt; do
    echo "Testfile: $file"
	./projet $file
done
