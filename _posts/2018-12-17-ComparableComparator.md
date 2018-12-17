---
layout: post
title: Comparable and Comparator!!
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

因此，若要reverse這種primitive type的array，只能透過倒著for或頭尾swap。
