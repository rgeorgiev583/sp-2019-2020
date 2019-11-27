# `kill`

## Примери за употреба

### Пример 1.

```
$ yes > /dev/null &
[1] 12512

$ kill 12512

$ ps
  PID TTY          TIME CMD
12494 pts/0    00:00:00 bash
12515 pts/0    00:00:00 ps
18969 pts/0    00:00:06 zsh
[1]+  Terminated              yes > /dev/null
```

## Пример 2.

```
$ yes > /dev/null &
[1] 12819

$ kill -9 12819

$ ps
  PID TTY          TIME CMD
12494 pts/0    00:00:00 bash
12926 pts/0    00:00:00 ps
18969 pts/0    00:00:06 zsh
[1]+  Killed                  yes > /dev/null
```

## Пример 3.

```
$ yes > /dev/null &
[1] 13192

$ yes > /dev/null &
[2] 13193

$ kill -SIGKILL 13192 13193 

$ ps
  PID TTY          TIME CMD
12494 pts/0    00:00:00 bash
13295 pts/0    00:00:00 ps
18969 pts/0    00:00:06 zsh
[1]-  Killed                  yes > /dev/null
[2]+  Killed                  yes > /dev/null
```