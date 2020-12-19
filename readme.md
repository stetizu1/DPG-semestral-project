# Ray Tracing výškových polí

Cílem této práce bylo implementovat algoritmus, který prochází paprsek promítnutý na 2D mřížku výškového pole, a hledá průsečík s tímto polem. Tento algoritmus používá výpočty délky úseků a je inspirován paperem https://www.researchgate.net/publication/220979067_Accelerating_the_ray_tracing_of_height_fields

Semestrální práce se zabývá procházením paprsků v mřížce pomocí digitalizace přímky rozšířené na 4-spojité okolí. Používá se metoda úseků. Ty se určují pomocí směrnice přímky a jejich posunutí se zjišťuje pomocí vstupního bodu paprsku. Poté se následující délka úseku přímky určí pomocí předchozího úseku a směrnice. V těchto úsecích následně hledáme pomocí výšky a aproximace za použití dvou trojúhelníků na buňku průsečík.


Program byl napsán pro Windows 10

Použitá literatura: 
* Accelerating the Ray Tracing of height fields https://www.researchgate.net/publication/220979067_Accelerating_the_ray_tracing_of_height_fields

Author:
Zuzana Štětinová, stetizu1@fel.cvut.cz

Předmět: Datové struktury pro počítačovou grafiku

Datum ukončení projektu: 19. 12. 2020