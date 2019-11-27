# `paste`

## Примери за употреба

```
$ cat foo
foo
bar
baz
quux

$ cat top
top
pol
pet
pot
lel

$ ./paste foo top
foo\ttop
bar\tpol
baz\tpet
quux\tpot
\tlel

$ ./paste -d' ' foo top
foo top
bar pol
baz pet
quux pot
 lel

$ ./paste -d' ' -s foo top
foo bar baz quux
top pol pet pot lel
```