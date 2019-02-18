# IJA Přednáška 2

## Projekt
Je řešený v týmu. Tým má 2-3 lidi. Děláme nějaký přehrávač šachového zápasu.

## Statické proměnné a statické metody
Používáme klíčové slovo `static`. Pokud je proměnná/metoda statická, tak nemusíme vytvářet instanci třídy pro přístup k proměnné/metodě. Statická proměnná existuje pouze jednou, nevytváří se její kopie a mají k ní přístup všechny instance dané třídy.

```java
public class Ucet {
	protected Klient majitel;
	protected double zustatek = 0; 
	protected static int pocet = 0;

	public Ucet(Klient k) {
		majitel = k;
		pocet++;
	}

	public static int pocetUctu() {
		return pocet;
	}
}
```
```java
Ucet instance01 = new Ucet(k);
Ucet instance02 = new Ucet(k);
int pocet = instance01.pocetUctu(); // = 2

pocet = Ucet.pocetUctu(); // = 2
```

V každé Java aplikaci musí existovat alespoň jedna třída a jako první metoda se volá `Main()`. Každá veřejně přístupná třída (`public`) má název souboru `*.java` (povinná přípona!). Třídy jsou organizovány do balíků (packages).

## Životní cyklus aplikace
- Máme třídu Pozdrav
- Naše třída je umístěna v souboru Pozdrav.java
- Naše třída je umístěna v balíku ija1 (musí být umístěna, jinak nám to hodí error!)

```java
package ija1;

public class Pozdrav {
	// Program spouštíme aktivací funkce 'main'
	public static void main(String[] args) {
		System.out.println("Ahoj !");
	}
}
```

Když se ukončí metoda `main`, tak se řízení předává JVM. Ten se ukončí pouze v případě, že naše metoda `main` nevytvořila další vlákna, která by v tu chvíli pracovala.

## Překlad programu - špatný příklad
1. Máme program Pokus.java
2. Přeložíme `javac Pokus.java` - vznikne Pokus.class
3. Spustíme `java Pokus`

**Neprovede se, jelikož jsme opomenuli balíky**

## Organizace tříd do balíků
Třídy jsou členěny do balíků. Ty vytvářejí stromovou strukturu. Naše třída `Pokus.java` bude v balíku `ija1`.
```
$HOME
|-- IJA
	|-- ija1
		|-- Pozdrav.java
		|-- Pozdrav.class
```
### Správný překlad
1. Jsme v adresáři $HOME/IJA
2. Přeložíme `javac ija1/Pozdrav.java`
3. Spustíme `java ija1.Pozdrav`

Kořenových adresářů může být více, než jenom jeden.

```
$HOME
|-- java
	|-- distribution
	|-- project
		|-- ija1
		|-- ija2
	|-- docs
|-- sun
	|-- distribution
	|-- examples
		|-- ija3
	|-- docs
```

V tomto případě máme 2 kořenové adresáře. Překladači můžeme specifikovat kořenový adresář přepínačem `-classpath`.

```shell
javac -classpath "$HOME/IJA"
```

Pokud chceme, aby naše `.class` soubory byly uloženy do jiného adresáře, použijeme:

```shell
# Přeložíme
javac -cp "$HOME/src" -d $HOME/cls

# Potom spouštíme jednoduše
java -classpath "$HOME/cls" ija1.Pozdrav
```

### Import tříd z balíků

```java
package homework1;
import ija1.cars.Car;
// import ija1.cars.*;

public class Homework {
	Car c;
	c = new Car();
	...
}
```

Existuje balík `java.lang`, který je importován automaticky. Obsahuje základní elementární třídy rozhraní. V tomto balíku je i třída `java.lang.System`.

## Modifikátory přístupu
- `public` - veřejný
- `protected` - chráněný
- `private` - soukromý
- neuveden - říká se lokální v balíku, nebo chráněný v balíku

### Pro třídy
- `public` - přístup k třídě neomezen
- `neveřejné - lokální v balíku` - k třídě může přistupovat libovolná třída z daného balíku

### Pro vlastnosti tříd
- `public`
- `protected` - může přistoupit třída ze stejného balíku, nebo třída odvozená v rámci dědičnosti
- `neveřejné - lokální v balíku` - nedoporučuje se v tomto kontextu vůbec dělat, protože jsou přístupné jen ze tříd stejného balíku, už ale ne z podtříd umístěných v jiném balíku
- `private` - k tomu má přístup výhradně tato třída a nikdo jiný (nezáleží na balíku, dědičnosti apod...)

### Speciální identifikátory
- `final` - záleží na kontextu, kde je použit. U třídy znamená, že od ní nelze dědit. U metody to znamená, že nemůže být předefinována/překryta. U proměnné to říká, že se jedná v podstatě o konstaktu (nelze změnit obsah té proměnné).

## Dědičnost
V postatě usnadňuje programování v tom smyslu, že je možné mezi třídami sdílet něco, co je pro ně společné (nemusím to u všech opakovat). _Odvozená třída_ má všechny vlastnosti nadtřídy - má k dispozici atributy a metody (pokud nejsou omezeny modifikátory přístupu) + to, co si třída sama nadefinuje. Konstruktory se **nedědí**!

```java
public class Vehicle {
	...
	public Vehicle (int weight, int capacity) {
		this.weight = weight;
		this.capacity = capacity;
	}
}

public class Car extends Vehicle {
	public Car (int weight, int capacity){
		this.weight = weight;
		this.capacity = capacity;
	}
}
```

Když vytvoříme instanci třídy, tak se provede inicializace objektu.

## Inicializace objektu
- Nalezení a vyvolání konstruktoru
- Vyvolání bezparametricekého konstruktoru nadřazené třídy
- Inicializace instančních proměnných
- Provedení těla konstruktoru třídy

```java
class Z {
	public Z() {System.out.println("Kon. Z");}
}

class A {
	public A() {System.out.println("Kon. A");}
}

class B extends A{
	Z z = new Z();
	public B() {System.out.println("Kon. B");}
}
```

Vytvoříme nový objekt třídy B -> vypíše se:

```java
Kon. A
Kon. Z
Kon. B

```

## Modifikace inicializace objektu
Lze volat i jiný, než bezparametrický konstruktor nadřazené třídy (musí být vždy na začátku konstruktoru potomka). `super(parametry)`. Lze volat i jiný konstruktor třídy (musí být vždy na začátku konstruktoru) `this(parametry)`.


## Problémy narušení zapouzdření
Členské proměnné je dobré definovat jako `private`. Donutí nás to vyvolat správný konstruktor nadřazené třídy. 