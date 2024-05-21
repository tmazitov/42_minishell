### ECHO ####

### HANDLED ####
echo hello world
echo "hello world"
echo 'hello world'
echo hello'world'
echo hello""world
echo ''
echo "$PWD"
echo '$PWD'
echo "aspas ->'"
echo "aspas -> ' "
echo 'aspas ->"'
echo 'aspas -> " '
echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<"
echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $ \ <<'
echo "exit_code ->$? user ->$USER home -> $HOME"
echo 'exit_code ->$? user ->$USER home -> $HOME'
echo "$"
echo '$'
echo $
echo $?
echo $?HELLO

echo $ '1234var'

echo hello$1world
echo $"$var"
echo $'1234var'
echo $eli hello$eli
###############

### NOT HANDLED ###
echo $1
echo $2
echo $3
echo $4
echo $5
echo $6
echo $7
echo $8
echo $9

##################

### PWD ####

### HANDLED ###

PWD
pwd 
pwd oi

###############

### SET ###

### HANDLED ###

var=hello
"var"="123"
var=hello"world$test"
var=hello"world $test"
var='helloworld'
var=wefdsaf'hello'
var="12345"678
var="hello"
var=$"$var"
var=$"var"
var="$VAR"
var=$HOME
var="hello world"
var='hello world'
var='hello world' A
###############

### NOT HANDLED ###
var=hello world=hello
var= 12345
###################

### EXPORT ###

### HANDLED ###

export
export var1 var2 var3
export hello
export HELLO=123
export HELLO=123 A (A is not seen in env but seen in cmd export)
export HELLO-=123
export HELLO="123 A-"
export HELLO="214321""$HOME"'1231234214' var="2asdfwefasf""$PWD"
export A-
export hello world
export =
export 123
###############

### NOT HANDLED ###

##################

### NOT HANDLED ###
./noexist.sh
###################

#### CD #####

### HANDLED ###
cd $PWD
cd $PWD hi 
cd 123123
###############


unset
unset HELLO
unset HELLO1 HELLO2
unset HOME
unset PATH
unset SHELL
exit 123
exit 298
exit +100
exit "+100"
exit +"100"
exit -100
exit "-100"
exit -"100"
exit hello
exit 42 world