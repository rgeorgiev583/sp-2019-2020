# Контролна работа

## Оценка

1. `1/1`.

2. `0.9/1`:
    * (`-0.1`) изчакването на процесите да приключат трябва да се случи чак след като всички от тях бъдат създадени (тъй като иначе се предотвратява конкурентността между тях).

3. `1/1`.

4. `0.9/1`:
    * (`-0.1`) за предпочитане е `exec(3)` да се извършва в отделен процес, когато се извиква повече от една команда.  Така родителският процес ще може да изчака всички от тях да приключат.

Сумарно: `Отличен (5.8)`
