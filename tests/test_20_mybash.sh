#!/bin/bash
set -e
cd ../exercises/20_mybash
if [ ! -x ./bin/mybash ]; then
    echo "ERROR: bin/mybash not found or not executable" >&2
    echo "Directory contents:" >&2
    ls -la bin/ 2>&1 || echo "bin/ does not exist" >&2
    exit 1
fi
./bin/mybash ../../tests/mybash_cmd.sh
