# PARC

header-only arguement parcer for pet projects written in C

## Installing

Download **include/parc.h** to your includes folder

or 

`git clone ac1dloop/parc`
`cd parc`
`mkdir build && cd build`
`cmake .. && make install`

## Usage guide

include header

`#include <parc.h>`

instantiate parc

`ParcItem* p = parc_parse(argc, argv);`

get input

`char* pw = parc_str(p, "password", "qwerty");`

if user doesn't enter anything default value is returned

`printf("i know your password is %s\n", pw);`
`printf("send me money\n");`

dont forget to free

`free(pw);`
`parc_free(p);`