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

public void fictionLibraryBook() {
  final LibraryBook.Builder builder = new LibraryBook.Builder();
  final LibraryBook book = builder
    .withBookName("War and Peace")
    .build();
}
```
Builder類屬於LibraryBook的一部份，唯一的職責就是創建對象。使用constructor時，參數的順序決定了用途，而通過為每一個參數提供一個顯示的方法，就可以理解每一個值的具體用途，而且可以通過任意順序調用。build方法調用實際的constructor並返回真正的對象，這樣的constructor相當於私有的。

2. Strategy Pattern

3. Template Pattern

4. Decorator Pattern

5. Flyweight Pattern

6. Singleton Pattern

7. Iterator Pattern

8. Factory Pattern

個人覺得MVC也可以算是一種精典的Design Pattern。