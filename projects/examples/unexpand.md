# `unexpand`

## Примери за употреба

С `\t` се обознава символ за табулация.  Може да използвате `xxd`, за да проверите дали има такива символи в изхода на командата.  (ASCII кодът на символа за табулация в шестнайсетична бройна система е `09`.)

```
$ cat dong
\tfoo bar
    baz\tquux
        lel        lol

$ ./unexpand dong
\tfoo bar
    baz\tquux
\tlel        lol

$ ./unexpand -a dong
\tfoo bar
    baz\tquux
\tlel\tlol

$ ./unexpand -t4 dong
\tfoo bar
\tbaz\tquux
\t\tlel    \tlol

$ ./unexpand -a -t4 dong
\tfoo bar
\tbaz\tquux
\t\tlel\t\tlol
```