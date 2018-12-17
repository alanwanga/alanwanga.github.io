---
layout: post
title: Comparable and Comparator
---

Java提供了兩個幫助排序的接口Comparable和Comparator，兩者之間有什麼區別？

Comparable接口用於自然排序，而Comparator接口則用於需要對排列的順序進行精淮控制的情形。

> 自然排序：從小到大的順序排列數字或按照字母表的順序排列字符。

不接受Comparator對象的排序方法採用自然排序，如int array：
```
@Test
public void sortInts() {
  int[] numbers = {-3, -5, 1};
  int[] expected = {-5, -3, 1};
  
  Arrays.sort(numbers);
  assertArrayEquals(expected, numbers);
}
```
因此，若要reverse這種primitive type的array，只能透過逆向for或頭尾swap。

對於Object array，要排序的類型必實現Comparable接口：
```
@Test
public void sortObjects() {
  String[] strings = {"z", "xy", "x", "abc"};
  Stirng[] expected = {"abc", "x", "xy", "z"};
  
  Arrays.sort(strings);
  assertArrayEquals(expected, strings);
}
```
由於String類實現了Comparable接口，因此排序結果和期待一樣。若要排序的類型沒有實現Comparable接口，則會拋出ClassCastException。

若要自定義排序方法，可以實現Arrays.sort或是Collections.sort方法所需要的Comparator接口。這個接口有兩個方法，一個是實現財型T比較的int compare(T o1, o2)，另一個是boolean equals(Object o)方法。compare方法返回一個int值，可以有3種狀態：
1. 為負，則第一個參數應該排在第二個參數之前。
2. 為0，則兩個參數相等。
3. 為正，則第二個參數應該排在第一個參數之前。
