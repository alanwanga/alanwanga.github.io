---
layout: post
title: Design Pattern
---

> Design Pattern是組合使用一個或多個對象來解決公共的用例，這些用例通常包括代碼重用和擴展。

1. Builder Pattern

```
public class LibraryBook {
  public static class Builder {
    private BookType bookType = BookType.FICTION;
    private String bookName;
    
    public Builder withBookType(final BookType, bookType) {
      this.bookType = bookType;
      return this;
    }
    
    public Builder withBookName(final String bookName) {
      this.bookName = bookName;
      return this;
    }
    
    public LibraryBook build() {
      return new LibraryBook(bookType, bookName)
    }
  }
  
  private final BookType bookType;
  private final String bookName;
  
  public LibraryBook(final BookType bookType, final String bookName) {
    this.bookType = bookType;
    this.bookName = bookName;
  }
}
```
```
public void fictionLibraryBook() {
  final LibraryBook.Builder builder = new LibraryBook.Builder();
  final LibraryBook book = builder
                            .withBookName("War and Peace")
                            .build();
}
```
Builder類屬於LibraryBook的一部份，唯一的職責就是創建對象。使用constructor時，參數的順序決定了用途，而通過為每一個參數提供一個顯示的方法，就可以理解每一個值的具體用途，而且可以通過任意順序鍊式調用。build方法調用實際的constructor並返回真正的對象，這樣的constructor相當於私有的。

2. Strategy Pattern

Strategy Pattern可以理解為在代碼中使用interface，通過對接口編程而不是特定的實現編程，可以輕鬆地替換某個算法的具體實現細節，而不需要完全重寫代碼。通過和dependency injection聯合使用可以將測試代碼中的實現替換出去，也可以允許當前的實現替換為測試用模擬實現(e.g. Mockito)。

3. Template Pattern

Template Pattern的作用是將一個算法的部分步驟搞到一個子類，共同行為可以在超類中定義，不同的部分則在子類中定義。將子類的實現分離開有很多好處，我們可以根據具體需求實現子類，而不對超類做任何修改。此外，子類的實現也是代碼中的獨立單元，因此可以分離出來進行完整測試，而不需要借助超類實例。

4. Decorator Pattern

```
public void decoratorPattern() throws IOException {
  final ObjectOutputStream oos = new ObjectOutputStream(
                                    new BufferedOutputStream(
                                      new FileOutputStream(
                                        new File("out.bin"))));
  oos.writeBoolean(true);
  oos.writeInt(42);
  oos.wirteObject(new ArrayList<Integer>());
  
  oos.flush();
  oos.close();
}
```
Java中用於讀寫JVM之外的IO源的IO類廣泛使用了Decorator Pattern，例如FileOutputStream可以將文件寫入磁盤。BufferedOutputStream緩存對write的調用，然後一次性寫入多個字節。在寫入磁盤時，這樣可以獲得巨大的性能提升。ObjectOutputStream是Java內置的serialization機制，用於將對象和原生類型寫入輸出流。

5. Flyweight Pattern

Flyweight Pattern適用於有多個對象，而且其中很多對象表示的都是同一個值的情形。在這些情形下，若這些對象都是immutable，就可以共享這些值。Integer對象是immutable，當要創建Integer對象最好使用valueOf方法，這樣就可以充分利用Flyweight Pattern的好處。若是調用new，那邊總是會創建新的實例。

Null Object Pattern是Flyweight Pattern的另一種實現，像在創建binary tree這樣的數據結構時，可以共享單獨一個空對象。
```
 1
/ \
2 3
\ /
null
```

6. Singleton Pattern

Singleton Pattern指的是只允許創建一個實例的類，常用於需要向第三方提供單一入口點的場合，例如database和web服務，通過這種方式可以方便地在一個地方管理和配置多個連接。Singleton Pattern最好用在已知不會有很多並發用戶的應用，若要構建大規模scalable的網路應用，那麼單實例對象通常都是性能瓶頸的根源。

7. Iterator Pattern

```
public interface Iterator {
  public boolean hasNext();
  public Object next();
}
```
```
public interface Container {
  public Iterator getIterator();
}
```
```
public class NameRepository implements Container {
  public String names[] = {"Robert" , "John" ,"Julie" , "Lora"};
  
  @Override
  public Iterator getIterator() {
    return new NameIterator();
  }
  
  private class NameIterator implements Iterator {
    
    int index;
    
    @Override
    public boolean hasNext() {
      if(index < names.length) return true;
        return false;
    }
    
    @Override
    public Object next() {
      if(this.hasNext()) return names[index++];
        return null;
    }
}
```

8. Factory Pattern

個人覺得MVC也可以算是一種精典的Design Pattern。
