# `tr`

## Примери за употреба

```
$ cat lipsum
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam condimentum quis magna id lacinia. bbb. ccc. eee.

$ ./tr ac bd < lipsum
Lorem ipsum dolor sit bmet, donsedtetur bdipisding elit. Nullbm dondimentum quis mbgnb id lbdinib. bbb. ddd. eee.

$ ./tr -s ac < lipsum
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam condimentum quis magna id lacinia. bbb. c. eee.

$ ./tr -s ac bd < lipsum
Lorem ipsum dolor sit bmet, donsedtetur bdipisding elit. Nullbm dondimentum quis mbgnb id lbdinib. b. d. eee.

$ ./tr -d ac < lipsum
Lorem ipsum dolor sit met, onsetetur dipising elit. Nullm ondimentum quis mgn id lini. bbb. . eee.

$ ./tr -d -s ac bd < lipsum
Lorem ipsum dolor sit met, onsetetur dipising elit. Nullm ondimentum quis mgn id lini. b. . eee.

$ ./tr -c ac bd < lipsum
ddddddddddddddddddddddadddddcddddcddddddadddddcddddddddddddddaddcdddddddddddddddddaddadddddacdddadddddddcccddddddd

$ ./tr -c -s ac < lipsum
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulam condimentum quis magna id lacinia. b. ccc. e.

$ ./tr -c -s ac bd < lipsum
dadcdcdadcdadcdadadacdadcccd

$ ./tr -c -d -s ac bd < lipsum
accacacaaacaccc
```