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

典型的BinarySearch最差需要7顆蛋，在只有兩顆的情況下，如果一樣從50層開始試，最差要試50次。但若第一顆蛋每隔10層試，先確定10位數後，第二顆蛋再每層試，這樣最差只要試19次。

- 三顆蛋

- 代碼

- 分析

---

ref:
<http://www.datagenetics.com/blog/july22012/index.html?fbclid=IwAR1Yfcop3Dm05ogZth9iFaBfVDSBTJjAuvdSaOqNRhulsJfk80eKuhQQWI0>
