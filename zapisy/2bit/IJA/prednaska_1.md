# IJA Přednáška 1
Existuje JVM. Občas dokáže překompilovat kód, který pracuje ještě rychleji, než C++, prý to i někdo dokonce zkoušel. Jelikož jsme frajeři, tak budeme používat JavaSE 8.

## JAVA platformu tvoří
- Java Virtual Machine
- Překladač a další nástroje
- Základní knihovna tříd (Java Core API)

## Základní pojmy

### Třída
```java
int obsah(int x, int y){
    return x * y;
}
```
Z implementace výše nemusíme vědět, jestli se jedná o obsah obdelníku. Není to naprosto zřejmé… Proto je lepší způsob jako argument té funkce nedávat nějaké hodnoty, ale nějakou strukturu, která bude ten geometrický útvar jasně vymezovat.
```java
struct Obdelnik {
    int x, y;
}

int obsah(struct Obdelnik o){
    return o.x * o.y;
}
```
Když bychom tyhle dva přístupy spojili, tak pak je to z hlediska čitelnosti kódu asi nejjasnější.
```java
struct Obdelnik {
    int x, y;
    int obsah() { return x * y }
}
```
Současně s Třídou vzniká abstrakce a zapouzdření.
- **Abstrakce** - objekt je abstrakcí (zjednodušením) části řešené domény
- **Zapouzdření** - seskupení souvisejících idejí do jedné jednotky

Zapouzdření s sebou nese ještě další vlastnosti, které mohou/nemusí být použity - záleží na programátorovi. Například stav objektu je editovatejný (dostupný) pouze prostřednictvím rozhraní.
```java
public class Obdelnik {
    protected int x;
    protected int y;
    public int obsah() { return x * y}
}
```
Protected v této ukázce znamená, že né každý může “zvenku” upravit, nebo přečíst, hodnotu.
Třída je tedy:
- vzor popisující strukturu a chování objektů stejného druhu
- definuje typ objektu
- deklaruje proměnné (atributy) a metody objektu
- může deklarovat proměnné (atributy) a metody třídy

### Objekt
Jedná se o instance dané třídy

Objekty spolu komunikují prostřednictvím zpráv (v podstatě metoda na straně příjemce).
V momentě, kdy vytváříme objekt třídy, používáme operátor new. Ten neudělá nic jiného, než jenom, že vytvoří prázdný objekt (vymezí paměťový prostor) a poté se volá konstruktor, který tento prostor zaplní daty.

### Konstruktor
Můžeme přetěžovat konstruktory. Nedává moc smysl mít prázdný konstruktor - možná se tomu vyhýbat.
