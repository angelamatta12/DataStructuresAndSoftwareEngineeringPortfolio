#!/usr/bin/env bash

set -euo pipefail

make -B debug

# run_test <input> <flags> <expected>
function run_test() {
  read -a args <<< "$2"
  ./zombbb_debug "${args[@]}" < "$1" > ./out.txt
  cmp -s ./out.txt $3 && echo "[PASSED] $1 <=> $3" || (echo "[FAILED] $1 <=> $3" && echo "*** Test case failed, exiting ***" && exit 1)
}

# exec_test <input>
function exec_test() {
  echo "exec: $1"
  ./zombbb_debug         < "$1" > /dev/null
  ./zombbb_debug -v      < "$1" > /dev/null
  ./zombbb_debug -m      < "$1" > /dev/null
  ./zombbb_debug -vm     < "$1" > /dev/null
  ./zombbb_debug -s 10   < "$1" > /dev/null
  ./zombbb_debug -vs 10  < "$1" > /dev/null
  ./zombbb_debug -ms 10  < "$1" > /dev/null
  ./zombbb_debug -vms 10 < "$1" > /dev/null
}


# Starter code tests (make sure to adjust the paths if your starter code test cases aren't in the same place)
run_test  ./starter-files/spec.txt          '-vms 10'   ./starter-files/spec-out-vms10.txt
run_test  ./starter-files/Sample-small.txt  '-vms 10'   ./starter-files/Sample-small-out-vms10.txt
run_test  ./starter-files/Sample-large.txt  '-vms 100'  ./starter-files/Sample-large-out-vms100.txt

# If you get any correct output/student output in the Autograder, add them here like this:
run_test  ./test-5-s.txt                    '-s 100'    ./out-test-5-s.txt

# Add your own test cases here (the ones you submit):
exec_test ./test-0-s.txt
exec_test ./test-1-m.txt
exec_test ./test-2-v.txt
exec_test ./test-3-s.txt
exec_test ./test-4-s.txt
exec_test ./test-5-s.txt
