---
layout: post
title: System Design
---

System Design裡面最核心的主題之一就是如何確保scalability。

其中又可以分為
1. Vertical Scaling：Super Computer，一個諸葛亮。
2. Horizontal Scaling：Computer Cluster，三個臭皮匠。

另外，在架構上要特別小心single point of failure。

我們可以實際來思考[如何設計爬蟲系統](https://mp.weixin.qq.com/s/b9biMN_uZSQOM8DnMRieUw)。

實現load balancing，業界常用Ngnix，是一個輕量server。

---

ref:
<https://www.youtube.com/watch?v=-W9F__D3oY4>
