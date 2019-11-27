# `fold`

## Примери за употреба

```
$ cat lipsum
Lorem ipsum dolor sit amet, consectetur adipiscing elit. In cursus, libero quis consectetur sagittis, velit mi auctor lorem, et varius enim nisi ut ex.

Donec porttitor felis in lorem dictum, quis ultricies nulla luctus.

$ ./fold lipsum
Lorem ipsum dolor sit amet, consectetur adipiscing elit. In cursus, libero quis 
consectetur sagittis, velit mi auctor lorem, et varius enim nisi ut ex.

Donec porttitor felis in lorem dictum, quis ultricies nulla luctus.

$ ./fold -w10 lipsum
Lorem ipsu
m dolor si
t amet, co
nsectetur 
adipiscing
elit. In 
cursus, li
bero quis 
consectetu
r sagittis
, velit mi
auctor lo
rem, et va
rius enim 
nisi ut ex
.

Donec port
titor feli
s in lorem
dictum, q
uis ultric
ies nulla 
luctus.
```