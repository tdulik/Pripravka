# Letní programátorská přípravka 2023

## Přihlašovací údaje do PC v učebnách

login: **.\student**

heslo: **student**

Poznámka: znak \ je vedle levé klávesy shift.

## Přihlašovací údaje k WIFI

Název wifi sítě: **Programatorska_pripravka**

heslo: **2023programing**

## Vývojová prostředí

- [Erik Král](https://fai.utb.cz/contacts/ing-et-ing-erik-kral-ph-d/) používá [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/).
- [Tomáš Dulík](https://fai.utb.cz/contacts/ing-tomas-dulik-ph-d/) používá Eclipse, [Codelite](https://codelite.org/) nebo [Clion](https://www.jetbrains.com/clion/).

Poznámka: V pc učebně je funkční jen Visual Studio 2019, verze 2022 nefunguje.

## Organizace kurzu

- 9:00 První blog výuky:
	- první hodina,
	- přestávka na kávu 10-15 minut,
	- druhá hodina.
- 11:00 Obědová přestávka (60 minut).
- 12:00 Druhý blog výuky:
	- třetí hodina,
	- přestávka na kávu 10-15 minut,
	- čtvrtá hodina.
- 14:00 Konec.

## Proměnná a její adresa

Operátor ```&```  vraci adresu promenne, například ```&x```.

Proměnná je pojmenovaná hodnota v paměti.

## Základní typy a aritmetické operace

- Typ ```int``` reprezenuje celé číslo se znaménkem, v jazyce C má minimálně dva bajty.
- Typ ```double``` reprezentuje číslo s desetinnou čárkou (spíše plovoucí řádková čárka, anglicky floating-point, typicky s binárním exponentem) a se znaménkem. Typicky zabíra 8 bajtů.
- pro podrobnosti viz téma "Velikost a rozsah typů int a float/double"  níže

Výraz ```1 / 3``` vrací hodnotu ```0``` protože oba operandy jsou celá čísla, operace dělení je v tomto případě celočíselná.
Naproti tomu výrazy ```1 / 3.0```, ```1.0 / 3``` nebo ```1.0 / 3.0``` vrací číslo s desetinnou čárkou, protože alespoň jeden z operandů je číslo s desetinnou čárkou.

```c
double x1 = 1 / 3;
double x2 = 1 / 3.0;
double x3 = 1.0 / 3;
double x4 = 1.0 / 3.0;
```

Poznámka: V jazyce C se používá desetinná tečka, protože vychází z angličtiny.

## Základní vstupně výstupní operace

Pro výpis typu ```int``` používáme formátovací značku **%d**.

```c
int x = 0;
printf("%d", x);
```

Pro výpis typu ```double``` používáme formátovací značku **%lf**.

```c
double x = 0.0;
printf("%lf", x);
```

Pro vstup z terminálu **bez ověření správnosti** vstupu můžeme použít funkci ```scanf_s```, která má jako parametr adresu proměnné do které ukládá převedenou hodnotu z řetězce dle formátovací značky.

```c
int x = 0;
scanf_s("%d", &x);
```

```c
double x = 0.0;
scanf_s("%lf", &x);
```

Příkazy ```printf``` a ```scanf_s``` jsou deklarované v hlavičkovém souboru **stdio.h**.
 
---
Domácí úkoly

1. Zadejte hodnoty tří celých čísel a vypište jejich průměr.

---
Poznámky

- UNIX -> LINUX
# 2. den
## Velikost a rozsah typů int a float/double

- Standard C nespecifikuje rozsahy jednotlivých podtypů ```int```. Standard C specifikuje rozsah ```int``` typů pouze takto:
  ```char <= short int <= int <= long int <= long long int```

Velikosti jakéhokoli typu si můžete vypsat pomocí operace ```sizeof```, u ```int``` typů např. takto:
```c
    printf("Velikost char=%d\n", sizeof (char));
    printf("Velikost short int=%d\n", sizeof (short int));
    printf("Velikost int=%d\n", sizeof (int));
    printf("Velikost long int=%d\n", sizeof (long int));
    printf("Velikost long long int=%d\n", sizeof (long long int));
```
Z těchto údajů si můžete rozsahy daného typu vypočítat, např.:

```c
    printf("Rozsah unsigned char=0..%d\n", (1<< (8*sizeof (char)))-1);
```
popř. využít konstant v ```limits.h```:

```c
	#include <limits.h>
	printf("Rozsah unsigned char=0..%d\n", UCHAR_MAX);
```
## Problém přetečení typů int
```c
    int x = 2147483648; //2 na 31, neboli výraz ```1<<31```, tj. hodnota 1 posunutá o 31 bitů
    char z = 128;		// 2 na 7, neboli výraz ```1<<7```
    printf("2^31 = %d\n", x); //chyba - kvůli přetečení, místo (+)2147483648 vytiskne -2147483648 !!!
    printf("z = %d\n", z); // chyba - kvůli přetečení, místo (+)128 vytiskne -128 !!!

```
Jak přetečení zabránit? Můžeme použít typ ```int``` s větším rozsahem: v případě ```x``` typ ```long long int```, v případě ```z``` např. ```unsigned char```:
```c
    long long int x = 2147483648L;
    unsigned char z = 128;
    printf("2^31 = %lld\n", x);
    printf("z = %d\n", z);
```
## Problém (ne)přesnosti typů float a double
```c
    double f = 1.0e16;
    printf("f=%lf\n", f);
    printf("f=%lf\n", f + 1);
    if (f < f + 1)
        printf("f < f+1\n");
    else printf("f neni mensi nez f+1\n");
```
Tento kód vypíše:
```
f=10000000000000000.000000
f=10000000000000000.000000
f neni mensi nez f+1
```
Čím to je? Počítá snad náš počítač chybně?

Počítač počítá správně, ale pokud máme proměnnou ```double``` obsahující velké číslo řádu 10^16,  nemůžeme takto velké číslo inkrementovat o hodnotu 1. Zkuste v tomto příkladu přičíst větší číslo - např. 100, dopadne to líp, ale výsledek stejně nebude přesně 10^16 + 100, ale nejbližší možná aproximace. 

Důvod? Reprezentace floating point-u v počítači je MANTISA * 2^EXPONENT, kde MANTISA i EXPONENT mají omezený počet bitů. Kvůli tomu hodnota floating point proměnné nemůže být přesně ta hodnota, kterou my požadujeme, ale pouze aproximace žádané hodnoty. Velikost chyby mezi žádanou a uloženou hodnotou je pak úměrná velikosti výrazu 2^EXPONENT.

## Příklad: zobrazení integer čísla v paměti počítače ve dvojkové soustavě
Proměnné typu ```int``` jsou v paměti počítače uloženy jak skupina 32 jedniček a nul, které si můžeme zobrazit např. tímto kódem:
```c
    int cislo = 9847;
    int zbytek;
    int pocet = 1;
    while (cislo > 0) {
        zbytek = cislo % 2;
        cislo = cislo / 2; 
        //printf("%d.cifra:%d\n", pocet++, zbytek);
        printf("%d", zbytek);

        pocet = pocet + 1; //pocet++; nebo pocet+=1;
    }
    printf("\n");
```
Poznámky:
- program snadno upravíme na tisk cifer v desítkové soustavě, stačí v kódu nahradit operace ```% 2``` a ```/ 2``` operacemi ```% 10``` a ```/ 10```
- cifry se tisknou netradičně od nejméně významných řádů, tzn. při tisku v desítkové soustavě, číslo 9847 se vytiskne jako posloupnost 7, 4, 8, 9
- tisk v opačném pořadí - od nejvýznamnějších řádů - vyžaduje změnu algoritmu:

```c
    int cislo = 9847;
    int zbytek;
    int pocet = 1;
    int delitel=1<<30;//max. možný dělitel, pro desítkovou soustavu =1000000000;
    while (delitel > 0) {
        printf("%d", cislo/delitel);
        cislo = cislo % delitel;
        delitel = delitel / 2; //pro desítkovou soustavu: / 10
    }
    printf("\n");
    return 0;
```

## Příklad: řešení 1 rovnice o 2 neznámých 
Řešení rovnice ax + by = 0 je funkce  y=-a*x/b , jejíž hodnoty můžeme generovat ve smyčce pro měnící se x. Výsledek můžeme tisknout do formátu CSV, který lze otevřít v Excelu, např. takto:
```program.exe > data.csv```

```c
    double a = 0.0;
    double b = 0.0;
    double x = 0.0;
    double y = 0.0;
    printf("define a:");
    scanf_s("%lf", &a);
    printf("define b:");
    scanf_s("%lf", &b);
    while (x <= 100) {
        y = sqrt((a * x) / b);
        printf("%lf\t%lf\n", x, y);
        x++;
    }
```
    
---
Domácí úkoly

Vytvořte program pro výpočet kořenů kvadratické rovnice X1,2= (-b +- sqrt(D)) / 2*a
kde D=-4*a*c

Diskriminant otestujte pomocí if, abyste nepočítali odmocninu ze záporné hodnoty.

# 3.den - pole, struct
 - src/03_01_velikost_populace.c -ukázka smyčky - výpočet velikosti populace na základě zadané porodnosti po N generacích
 - 
