# IPP Přednáška 2
## Projekt - (20 + 5 bodů)
Za úkol budeme mít naprogramovat 2 skripty v PHP a jeden v Pythonu (na PHPčko prý budeme mít i nějakou přednášku od externisty).  
Budeme implementovat interpret. Lexikální a parser bude v PHPčku a interpret v Pythonu. Komunikaci mezi nimi bude zajišťovat XML.

**Zadání projektu** - https://wis.fit.vutbr.cz/FIT/st/cfs.php/course/IPP-IT/projects/2018-2019/Zadani/ipp19spec.pdf

### Typické chyby projektu
- Nedodržení návratových kódů
- Máme si dát pozor na rozdíl mezi `return` a `exit`
- Výpis debugu na výstup (to dělaj jenom kokoti)
- Dávat si pozor na verzi interpretu
- Plagiátorství :kappa:

### Termíny
`06.03.2019` - Pokusné odevzdání 1. úlohy  
`13.03.2019` - Odevzdání první úlohy  
`18/19.3.2019` - Půlsemestrální zkouška  
`03.04.2019` - Pokusné odevzdání 2. úlohy  
`11.04.2019` - Odevzdání 2. úlohy

## Principy OOP
### Motivace
- **Modelování** - tvorba abstrakce reálného systému
- **Abstrakce** _(Black box)_
	- skrývání vnitřní struktury (máme pouze veřejný protokol)
	- kvalita apod...

Abstraktní datový typ měl tu nevýhodu, že jsme s daty mohli komunikovat přímo a přes rozhraní. U objektu toto už není možné a máme dostupné pouze rozhraní.  

Každý jazyk má svůj vlastní OOJ model. 

### Model výpočtu
- Proměnná
- Konstrukt objektu
- Zaslání zprávy

Kromě parametrů se posílá do funkcí i kontext. Volaná metoda tedy nemá přístup pouze k parametrům, které ji byly poskytnuty, ale i ke _stavu_(?) programu

### Zapouzdření
V podstatě se jedná o uvažřenost vůči okolním objektům (používáme modifikátory viditelnosti). Přistupujeme pouze přes veřejný protokol.  
Protokol příjemce rozhodne o reakci na zprávu:
- **Invokace** - odpovídající metody a navrácení výsledné hodnoty odesílateli
- **Chyba** - Nerozumí zprávě (_DoesNotUnderstand_)

```
receiver.name(arg1, arg2);
receiver.name(arg1, arg2)
$receiver->name($arg1, $arg2);
...
```

Jak je to, když posílám zprávu sám sobě? Dá se použít **intérní** protokol, kde se dá navíc i přistupovat k atributu. Používáme klíčová slova `this`, `self` apod...

```
this.attr = this.attr + 1;
self.attr = self.attr + 1;
$this->setAttr($this->getAttr() + 1);
self attr: self attr + 1.
```

### Polymorfismus
Stejnou zprávu můžeme zaslat různým objektům. Protokol umožňuje **individuální reakci**.  
Například zaslání zprávy **MLUV**:
- Objekt pes: "Haf haf haf..."
- Objekt kočka: "Mňau mňau mňau..."
- Objekt muž: "Baník pyčo"
- Objekt žena: "Nejdeš na pivo"

Existují dva typy vazeb:
- Brzká
- Pozdní

Většina OOJ, které myslí principy OOP vážně, používají _pozdní_.

### Dědičnost
Nemusíme v každém objektu definovat všechny metody, aby rozuměli stejné množině zpráv. Stačí použít dědičnost.  
_Definice_: Dědičnost je sdílení společných položek (od předků) + individuální položky (v potomcích)

### Vytváření nových objektů
1. **Vytvoření prázdného objektu** + úprava položek
2. **Kopie objektu** + úprava položek
	- _Prototyp_ = klonovaný objekt
3. **Vytváření pomocí "šablony"** + naplnění atributů
	- Je tu ovšem nutnost vytvořit "šablonu" - třída

### Třída
- Je to šablona pro vytváření nových objektů (instancí).
- Třída obsahující
	- seznam atributů v instancích
	- implementaci metod _(je-li třída objekt první kategorie, komunikujeme s ní též zasíláním **třídních zpráv**)_

Příklad:  
**ShopProduct.php**
```php
<?php
class ShopProduct {
	private $title;
	protected $price = 0;

	public function setTitle($1){
		$this->title = $t;
	}

	public function getTitle(){
		return $this->title;
	}
}
```

**test_ShopProduct.php**
```php
<?php
require_once "ShopProduct.php";
$p1 = new ShopProduct();
$p1->setTitle("Catch 22");
$p2 = clone $p1;
$p1->type = "book";

$p3 = $p1;
$p3->SetTitle("Star Wars");
print "P1: {$p1->getTitle()}\n"
if(isset($p2->type))
	print "P2: {$p2->type}\n"
		//skipped
```

### Klasifikace OOJ
#### Dle přístupu k vytváření objektů
- Beztřídní OOJ
- Třídní OOJ

#### Dle čistoty objektového modelu
- Čisté (vše, jako objekt)
- Hybridní (míchaní s jinými paradigmaty, doplněny objekty)

#### Dle platformy pro běh OO programů
- Překládané (efektivita běhu, více zdrojového textu)
- Interpretované (pomalé, velmi flexibilní)
- Částečně interpretované (mezikód, virtuální stroj)

#### Dle uložení dat v paměti

#### Dle dědičnosti (počet přímých předků)
- Jednoduchá
- Vícenásobná

#### Dle předmětu dědění
- Dědičnost implementace
	- Třídní dědičnost
	- Delegace
- Dědičnost rozhraní

#### Dle způsobu určení typů (opakování)
- Beztypové
- Netypované
- Typované

#### Dle důslednosti kontroly typů
- Silvě typované (type-safe)
- Slabě typované (implicitní konverze)

#### Dle doby kontroly typů
- Staticky typované (compile)
- Dynamicky typované (runtime)