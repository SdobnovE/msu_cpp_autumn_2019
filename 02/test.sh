#!/bin/bash

test(){
    data=$1
    code=$2

    if ((data == -1))
    then
        out_ans=$(./my_prog)
    else
        out_ans=$(./my_prog $data)
    fi

    out_code=$?
    
    if ((out_code == code))
    then
        echo "ok"
    else
        echo "  Expected code: $code "
        echo "  Recieved: $out_code"
    fi 
    
}

test 20000 0
test 2 3
test -1 1
test "asd1" 1
test 29 3
test 30 4
test 429 4
test 999 5
test 1000 0
test 900000000000 2
