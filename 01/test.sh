#!/bin/bash

test(){
    data=$1
    code=$2
    answer=$3
    out_ans=$(./test "$1")
    out_code=$?
    if ((code != 0))
    then
        if ((out_code == 1))
        then
            echo "ok"
        else
            echo "Expected code: 1 "
            echo "Recieved: $out_code"
        fi
    else
       if ((out_ans == answer))
        then
            echo "ok"
        else
            echo "Expected answer: $answer  (data: '$1') "
            echo "Recieved: code $out_code; answer $out_ans"
        fi 
    fi
}

test "223+2a  " 1 
test " 223    + 2a    " 1
test "2+2+2" 0 6
test "  2 +2+   2" 0 6
test "      2 + 2   +  2  " 0 6
test "2 + - 2 *-2" 0 6
test "2+--2*   -2" 1 
test "123 +- 123" 0 0
test "" 1 
test "    " 1 
test "- 100-    -200" 0 100 
test "2-3*4*2+1--2+-5/2" 0 -21
test "2-3*4+-5/2" 0 -12
test "2 + 3 / 0" 1
test "2 +" 1
test "+ 2 +" 1
# test('./test "-    4- -4"', 0, [ '0' ])
# test('./test', 1, [ 'error' ])
# test('./test 2 + 3', 1, [ 'error' ])
# test('./test "2/0"', 1, [ 'error' ])
# test('./test "2/"', 1, [ 'error' ])
# test('./test "3 + a"', 1, [ 'error' ])