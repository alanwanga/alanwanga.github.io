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
public void decoratorPattern() throws IOEception {
  final ObjectOutputStream oos = new ObjectOutputStream(
                                    new BufferedOutputStream(
                                      new FileOutputStream(
                                        new File("target", "out.bin"))));
}
```

5. Flyweight Pattern

6. Singleton Pattern

7. Iterator Pattern

8. Factory Pattern

個人覺得MVC也可以算是一種精典的Design Pattern。
