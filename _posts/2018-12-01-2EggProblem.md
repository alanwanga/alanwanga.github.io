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
通常思路是每一層都要試試看，最差要試100次。不過，我想應該也可以只試偶數層，如果沒破就繼續往上試，破了就知道臨界是減一的奇數層，這樣最要試50次。

- 無限顆蛋

- 兩顆蛋

- 三顆蛋

- 代碼

- 分析

---

ref:
<http://www.datagenetics.com/blog/july22012/index.html?fbclid=IwAR1Yfcop3Dm05ogZth9iFaBfVDSBTJjAuvdSaOqNRhulsJfk80eKuhQQWI0>
