# Контролна работа

## Оценка

1. `0/1`:
    * (`-1`) задачата не е имплементирана (дори не е започната);
    * решението във файла `1.c` всъщност е на трета задача.

2. `0/1`:
    * (`-1`) задачата не е имплементирана (дори не е започната);
    * решението във файла `2.c` всъщност е на четвърта задача.

3. `0.8/1`:
    * (`-0.2`) ако на края на входните данни има поредица от интервали, те няма да бъдат изведени.

4. `0.2/1`:
    * (`-0.3`) объркан е редът на имплементация на канала (`pipe`): вместо `sort | uniq` е реализиран `uniq | sort`;
    * (`-0.15`) вместо да се извика функцията `execvp(3)` с втори аргумент `argv` за командата `sort`, е извикана `execlp(3)`, която не е подходяща за целта (и то по грешен начин);
    * (`-0.15`) вместо да се извика функцията `execlp(3)` с втори аргумент `argv` за командата `uniq`, е извикана `execv(3)`, която не е подходяща за целта (и то по грешен начин);
    * (`-0.1`) програмата не затваря файловите дескриптори по правилния начин;
    * (`-0.1`) изчакването на процесите да приключат трябва да се случи чак след като всички от тях бъдат създадени (тъй като иначе се предотвратява конкурентността между тях).

Сумарно: `Среден (3)`