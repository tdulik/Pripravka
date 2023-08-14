# Letní programátorská přípravka 2023

## Přihlašovací údaje do PC v učebnách

login: **.\student**

heslo: **student**

Poznámka: znak \ je vedle levé klávesy shift.

## Přihlašovací údaje k WIFI

Název wifi sítě: **Programatorska_pripravka**

heslo: **2023programing**

## Vývojová prostředí

- Erik Král: Visual Studio Community 2022
- Tomáš Dulík: dříve Eclipse, Codelite nebo Clion

Poznámka: V pc učebně je funkční jen Visual Studio 2019, verze 2022 nefunguje.

## Organizace kurzu

9:00: 	1. hodina
	      přestávka na kávu 10-15 minut
	      2. hodina

11: 00: obědová přestávka 60 minut

12:00 	3. hodina
	      přestávka na kávu 10-15 minut
	      4. hodina

14:00   konec

## Proměnná a její adresa

Operátor & vraci adresu promenne, například &x.

Proměnná je pojmenovaná hodnota v paměti.

## Základní typy a aritmetické operace

- Typ ```int``` reprezenuje celé číslo se znaménkem, v jazyce C má minimálně dva bajty.
- Typ ```double``` reprezentuje číslo s desetinnou čárkou (spíše plovoucí řádková čárka, anglicky floating-point, typicky s binárním exponentem) a se znaménkem. Typycky zabíra 8 bajtů.
  
Výraz 1 / 3 vrací hodnotu 0 protože oba operandy jsou celá čísla, operace dělení je potom v jazyce C celočíselná.
Naproti tomu výrazy 1 / 3.0, 1.0 / 3 nebo 1.0 / 3.0 vrací správný výsledek, protože alespoň jeden z operandů je číslo s desetinnou čárkou.

```c
double x1 = 1 / 3;
double x2 = 1 / 3.0;
double x3 = 1.0 / 3;
double x4 = 1.0 / 3.0;
```
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
 
Poznámka: V jazyce C se používá desetinná tečka, protože vychází z angličtiny.

---
Poznámky

- UNIX -> LINUX


