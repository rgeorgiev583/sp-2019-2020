# `strings`

## Примери за употреба

```
$ xxd hello
00000000: 0000 4869 2e00 0000 0000 4865 6c6c 6f00  ..Hi......Hello.
00000010: 0000 0077 6f72 6c64 2100 0000            ...world!...

$ ./strings hello
Hello
world!

$ ./strings -n2 hello
Hi.
Hello
world!
```