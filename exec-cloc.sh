#!/bin/bash

# Run cloc with forced language options for .DISABLED files
cloc \
--ignored=ignored.txt \
--force-lang="C++",cpp.DISABLED \
--force-lang="C/C++ Header",h.DISABLED \
harvest_havoc/ \
velecs/ \
libs/CMakeLists.txt \
CMakeLists.txt \
*.md

# Check if ignored.txt was created and is not empty
if [ -s ignored.txt ]; then
    cat ignored.txt
    rm ignored.txt
fi
