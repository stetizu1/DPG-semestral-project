# Ray Tracing výškových polí

Cílem této práce bylo implementovat algoritmus, který prochází paprsek promítnutý na 2D mřížku výškového pole, a hledá průsečík s tímto polem. Tento algoritmus je inspirován paperem https://www.researchgate.net/publication/220979067_Accelerating_the_ray_tracing_of_height_fields.

Algoritmus funguje na principu procházení paprsků promítnutých na mřížku, která je základem výškového pole. Klíčovým problémem je identifikace buněk v rámci mřížky, jimiž průmět paprsku prochází. Ta je provedena metodou úseků, jež digitalizuje paprsek promítnutý na mřížku a určí buňky v 8-spojitém okolí, což následně algoritmus rozšířuje na 4-spojité, neboť potřebujeme všechny buňky, kterými paprsek prochází. Kompletní sekvenci úseků (a tedy buněk) je možné určit rekurentní rovnicí pouze na základě směrnice a posunu paprsku v bodě, v němž vstupuje do mřížky. V nalezených úsecích hledáme průsečík s výškovým polem, a to primárně pomocí porovnání maximální výšky buňky a minimální výšky paprsku v rámci buňky, a následně, pokud je průsečík možný, hledáme průsečík paprsku a trojúhelníků, které aproximují tvar výškového pole.


Program byl napsán pro Windows 10

Program lze spustit bez parametrů (což vykreslí scénu 0), s jedním nebo se 2 parametry. První parametr je číslo scény (0, 1 nebo 2), druhý cesta k výškové mapě (když je vynechán, použije se výchozí mapa patřící k dané scéně). Pro ukázkové mapy lze použít i přiložené soubory ve složce bat.

Použitá literatura: Accelerating the Ray Tracing of height fields https://www.researchgate.net/publication/220979067_Accelerating_the_ray_tracing_of_height_fields

Autor: Zuzana Štětinová, stetizu1@fel.cvut.cz

Předmět: Datové struktury pro počítačovou grafiku

Datum ukončení projektu: 21. 12. 2020