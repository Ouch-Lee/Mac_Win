# git学习手册

[官网教程](https://docs.github.com/zh)

经过多次尝试，终于建立了mac和win之间的git连接，总结一下经验，同时也便于下次使用时快速查阅

## 建立本地和远程库的联系

* 首先创建一个远程库
* 建立本地ssh和远程账号之间的联系，具体可以参考[这篇](https://blog.csdn.net/FindHuni/article/details/106374506) / 如果是Win可以直接使用Git Desktop
* git init
* git clone xxx.git  (先把已有的代码克隆下来)
* git remote add origin git@github.com: 账户名/项目名.git
* 如果远程库中代码发生了改变，使用git pull  // 这里我还有一点问题
* 对于出现冲突的情况可以直接 git fetch



提交代码

git add [路径+文件名]  // 这样文件就进入了缓冲区

git commit  -m "说点什么" 

提交完后 git push origin master

这里只能用master不能用main



