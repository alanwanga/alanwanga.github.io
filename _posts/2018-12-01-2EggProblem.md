---
layout: post
title: 2 Egg problem
---

> A building has 100 floors. One of the floors is the highest floor an egg can be dropped from without breaking.

> If an egg is dropped from above that floor, it will break. If it is dropped from that floor or below, it will be completely undamaged and you can drop the egg again.

> Given two eggs, find the highest floor an egg can be dropped from without breaking, with as few drops as possible.

---

我們可以思考幾種情況

- 一顆蛋

通常思路是每一層都要試試看，最差要試100次。不過，應該也可以只試偶數層，如果沒破就繼續往上試，破了就知道臨界是減一的奇數層，這樣最差只要試50次。

- 無限顆蛋

用BinarySearch從一半的地方50層開始試，破了臨界就在1-50層，沒破就在51-100層。這樣每次可以去掉一半的可能性，log<sub>2</sub>100 = 6.6..因此，只要7顆蛋最多就可以測出2<sup>7</sup> = 128層的臨界位置，最差要試7次。

- 兩顆蛋

典型的BinarySearch最差需要7顆蛋，在只有兩顆的情況下，如果一樣從50層開始試，最差要試50次。但若第一顆蛋每10層試，先確定10位數後，第二顆蛋再每層試，這樣最差只要試19次。

我們是不是有辦法最小化最差的情況呢？根據上面的做法，若第一顆蛋在第10層就破了，最差要試9次，與試到100層才破，最差的19次之間有一段差距可以平均。我們可以每多試一個間隔，就減少一個間距，如此便可以進一步的減少最差的測試次數。

> x + (x - 1) + (x - 2) + ... + 1 >= 100

> x (x + 1) / 2 >= 100

> x >= 14

drop | floor
-----|------
1    | 14
2    | 14 + 13 = 27
3    | 27 + 12 = 39
4    | 39 + 11 = 50
5    | 50 + 10 = 60
6    | 60 + 9 = 69
7    | 69 + 8 = 76
8    | 76 + 7 = 83
9    | 83 + 6 = 89
10   | 89 + 5 = 94
11   | 94 + 4 = 98 
12   | 98 + 3 = 101 -> 100

- 三顆蛋

- 代碼

- 分析

---

ref:
<http://www.datagenetics.com/blog/july22012/index.html?fbclid=IwAR1Yfcop3Dm05ogZth9iFaBfVDSBTJjAuvdSaOqNRhulsJfk80eKuhQQWI0>
