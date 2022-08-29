# MIT6.S081 Lab记录

## 前言

本仓库旨在于整理`MIT6.S081 2020`秋季网课的实验源代码, `Docker`环境搭建方案, 授课视频或`xv6book`中出现的`exercise`,以及我的实验解决笔记和代码.

## 1 - 关于Lab的源代码和此项目的各个分支结构

**官方Git仓库`clone`命令： `git clone git://g.csail.mit.edu/xv6-labs-2020`**

(在每个实验的分支下我也会把一些教授课堂上演示的`exercise`也写到里面)

- `main`分支：存放我的`Dockerfile`、课程笔记、其他操作系统的学习辅助资料等

- `util_solution`：存放第一个实验`Lab: Xv6 and Unix utilities`我的解决方案，解题思路，参考资料等

- [ ] `pgtbl_solution`：存放第三个实验`Lab: page tables`我的解决方案，解题思路，参考资料等

## 2 - Docker环境搭建方案

为了有最纯净做实验的感觉,我制作了一个`Docker`的镜像,直接`pull`下来简单配置一下,就可以实现在网页版的`Vscode`上做这个实验(该镜像我依旧还会优化其使用体验,敬请期待),具体效果如下:

![image](https://cdn.jsdelivr.net/gh/CalvinHaynes/ImageHub@main/BlogImage/image.5l840ak5vw00.png)

关于我是如何搭建的以及windows/linux操作系统下如何使用我的镜像,我写了一篇知乎文章,大家可以来看看:[一个玩转国外CSLab的通用环境搭建方案（附我的搭建好的MIT6.S081环境）](https://zhuanlan.zhihu.com/p/449687883)

`Dockerfile`也在`main`分支中,感兴趣的小伙伴可以自行查看

