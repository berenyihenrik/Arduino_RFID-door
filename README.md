# Arduino RFID ajtónyitó

RFID ajtónyitó Arduino mikrokontroller segítségével

## Mi is az az Arduino?

Az Arduino egy nyílt forráskódú mikrokontroller. Ez az eszköz teszi lehetővé a hozzá kapcsolt modulok működését.
![Az egyik legnépszerűbb Arduino modell, az Arduino UNO](https://upload.wikimedia.org/wikipedia/commons/3/38/Arduino_Uno_-_R3.jpg)

## Az RFID-ról röviden

Az RFID egy azonosításhoz és adatközléshez használt technológia, melynek lényege adatok tárolása és továbbítása RFID címkék segítségével. Az RFID címkék általában apró tárgyak (pl.: kártya, kulcstatró). Működésükhöz csak az olvasó számára kell elektromos áramot biztosítani, az általa kibocsátott rádiófrekvenciás jel pedig elegendő áramot indukál a címkékben ahhoz, hogy azok választ küldjenek.
![RFID olvasó](https://www.electronics-lab.com/wp-content/uploads/2019/01/rfid.jpg)

## Projektünkben használt egyéb modulok

Projektünkben az RFID olvasón kívül megtalálhatóak különböző, az eszköz állapotának jelzésére alkalmazott modulok. Ilyenek például az apró ledek, a csipogó, valamint az LCD kijelző is. Ezek közül a legjelentősebb LCD, amely szövegesen is képes tájékoztatni eszközünk működéséről.

Az eszközhöz épített tolózár működtetéséhez pedig egy szervomotort használtunk.

## Hogyan működik?

Ha tisztáztuk azt, hogy miből is épül fel, beszéljünk arról is, hogy hogyan működik. Az eszköz képes, a már említett RFID olvasón keresztül címkéket olvasni és eldönteni, hogy engedélyezett, avagy nem engedélyezett címkéről van szó. Minden címke egyedi azonosítóval rendelkezik, ezekből egyet a programkódban már előre meghatároztunk engedélyezettként, hogy szemléltetni tudjuk az összes esetet.

## Egy kártya mindenek felett

A programkódban meghatároztunk egy kártyát, amelyet mastercardnak neveztünk el. Ez a kártya nem belépésre szolgál, hanem segítségével további címkéket tudunk hozzáadni/eltávolítani az eszközhöz a programkód megváltoztatása nélkül.

A kártyát az olvasóhoz érintve megnyílik a `mastermode` funkció, meylnek során minden újonnan odaérintett kártya hozzáadódik a programhoz, az engedélyezettek pedig kikerülnek onnan. Ennél a résznél nagy szerepe van a kijelzőnek is, hiszen nem csak a `mastermode` állapotáról ad tájékoztatást, hanem arról hogy a többi címke hozzáérintése után mi történt velük. Végül a `mastermode` a mastercard újbóli hozzáérintésével kapcsolható ki.

## Ha elmegy az áram

Az eszközünk képes zsebtelepről, valamint áramforrásról is üzemelni. Gondolnunk kellett azonban arra az esetre is, amikor áramszünet következik be, vagy lemerülnek az elemek. Szerencsére az Arduino rendelkezik Elektronikusan programozható és olvasható memóriával (**EEPROM**), így ebben tudjuk rögzíteni a tolózár állását, amelybe az eszköz az újbóli áramforrás után vissza tud állni.
