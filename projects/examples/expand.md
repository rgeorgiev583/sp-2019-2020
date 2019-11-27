# `expand`

## Примери за употреба

С `\t` се обознава символ за табулация.  Може да използвате `xxd`, за да проверите дали има такива символи в изхода на командата.  (ASCII кодът на символа за табулация в шестнайсетична бройна система е `09`.)

```
$ cat dong
\tfoo bar
    baz\tquux
        lel        lol

$ ./expand dong
        foo bar
    baz        quux
        lel        lol

$ ./expand -i dong
        foo bar
    baz\tquux
        lel        lol

$ ./expand -t4 dong
    foo bar
    baz    quux
        lel        lol

$ ./expand -i -t4 dong
    foo bar
    baz\tquux
        lel        lol
```