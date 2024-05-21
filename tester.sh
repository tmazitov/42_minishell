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
###############

### NOT HANDLED ###
var="hello world"
var='hello world'
var='hello world' A
var=hello world=hello
var= 12345
###################

### EXPORT ###

### HANDLED ###

export
export var1 var2 var3
export hello
export HELLO=123
export HELLO=123 A
###############

### NOT HANDLED ###

export A-
export HELLO="123 A-"
export hello world
export HELLO-=123
export =
export 123

##################