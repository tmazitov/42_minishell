#!/bin/bash
env=$(env)
export=$(export)

while [ 1 ];
do
    echo $env "\n"
    echo "####################################################"
    rprint "cvccvc"
    rprint "cvcvvc"
    rprint "Cvccvc"
    rprint "Vccvcvc"
    rprint "Cvnvn"
    genPatternStrings $1;
   sleep 1
done

function cprint () {
    typ=$1
    case $typ in 
        v) alpha="aeiouy" ;;
        c) alpha="bcdfghjklmnpqrstvwxz" ;;
        V) alpha="AEIOUY" ;;        
        C) alpha="BCDFGHJKLMNPQRSTVWXZ" ;;
        n) alpha="0123456789" ;;
        *) echo "** Undefined **" ; exit 1 ;;
    esac
    len=${#alpha}
    r=$((RANDOM%len))
    echo -en ${alpha:r:1}
}

function rprint () {
    code=$1
    for i in $(seq 1 ${#code})
    do 
        c=${code:i-1:1}
        cprint $c
    done
    echo
}

function v() {
    s=aeoiuy
    p=$((RANDOM % ${#s}))
    echo -n ${s:$p:1}
}

function c() {
    s=bcdfghjklmnpqrstvwxz
    p=$((RANDOM % ${#s}))
    echo -n ${s:$p:1}
}

function genPatternStrings() {
    for i in $(eval echo {0..$1}); do
        echo `c;v;c;c;v;c;`
    done
}