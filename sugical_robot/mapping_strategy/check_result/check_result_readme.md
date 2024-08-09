# check_result_readme

## 代码说明

* 
* five_joint_arm_simu_code：用于在matlab中绘制主端结构
* get_T_con_from_mapping：字面意思，根据[theta3,theta_4,thtea_5]得到从端对应旋转矩阵
* master_DH_model： 所有以这个开头的均为在matlab中绘制图像
* slave_DH_model: 为了推导末端在x,z方向上的分量，可以试着先把末端的其次变换矩阵求出来
* modified_DH  +  standard_DH 这是为了求解单个齐次变换
* 





为了验证论文映射的正确性，需要干一下几件事

* 总结主从两端的简易DH表
* 根据这个DH在matlab中绘制机器人模型





## 构建主从端 DH表

![](E:\GitHub\Mac_win\Mac_Win\sugical_robot\mapping_strategy\vscode_draw\handel_DH_ver5.png)

| i    | link | $a_{i-1}$ | $\alpha_{i-1}$ | $d_i$                                 | $\theta_i$                                      |
| ---- | ---- | --------- | -------------- | ------------------------------------- | ----------------------------------------------- |
| 1    | 0=>1 | 0         | $\pi/2$        | 0                                     | <font color = red>$\theta_1^*  $</font>         |
| 2    | 1=>2 | 0         | $-\pi/2$       | <font color = red>**$d_2^*$**</font > | 0                                               |
| 3    | 2=>3 | 0         | $\pi/2$        | h                                     | <font color = red>$\theta_3^* + \pi/2 $</font>  |
| 4    | 3=>4 | 0         | $\pi/2$        | 0                                     | <font color = red>$\theta_4^*  + \pi/2 $</font> |
| 5    | 4=>5 | 0         | $\pi/2$        | $l$                                   | <font color = red>$\theta_5^* + \pi/2 $</font>  |

单独分析连杆部分

以下是**modified**版本 DH建模（根据建模方法编写了一个modified_DH函数，用于计算给定四个参数时的其次变换矩阵）

| i    | $a_{i-1}$ | $\alpha_{i-1}$ | $d_i $ | $\theta_i$           |
| ---- | --------- | -------------- | ------ | -------------------- |
| 3    | 0         | $\pi/2$        | h      | $\theta_3^* + \pi/2$ |
| 4    | 0         | $-\pi/2$       | 0      | $\theta_4^* - \pi/2$ |
| 5    | 0         | $-\pi/2$       | l      | $\theta_5^* $        |

成功计算了末端的位姿



## 构建从端DH表

<img src="E:\GitHub\Mac_win\Mac_Win\sugical_robot\mapping_strategy\vscode_draw\surgicak_arm_DH_ver2.png" style="zoom:20%;" />

虽然论文用的std方法，但是md方法肯定也是一样的

注：为了方便表达，之后 ks 统统记为 \alpha

7-29发现从端与主端坐标系规定不同， 略作修改；



| link(i) | $a_{i-1}$ | $\alpha_{i-1}$ | $d_i$ | $\theta_i$   |
| ------- | --------- | -------------- | ----- | ------------ |
| 0=>1    | 0         | 0              | $D_1$ | 0            |
| 1=>2    | 0         | $\pi/2$        | 0     | $\alpha_2/2$ |
| 2=>3    | 0         | $-\pi/2$       | $d_2$ | 0            |
| 3=>4    | 0         | $\pi/2$        | 0     | $\alpha_2/2$ |
| 4=>5    | 0         | $-\pi/2$       | 0     | $\Phi_3$     |
| 5=>6    | 0         | $\pi/2$        | 0     | $\alpha_4/2$ |
| 6=>7    | 0         | $-\pi/2$       | $d_4$ | 0            |
| 7=>8    | 0         | $\pi/2$        | 0     | $\alpha_4/2$ |
| 8=>9    | 0         | $-\pi/2$       | 0     | $-\Phi_3$    |
| 9=>10   | 0         | 0              | $l$   | $\Theta_5$   |

$d_2 =  \frac{2s_1}{\alpha_2} sin(\alpha_2/2)$ ; $d_4 =  \frac{2s_2}{\alpha_4} sin(\alpha_4/2)$

## md 法对连续体建模

先生成std法的table，然后用gpt生成的std函数验证一下没问题

下面是尝试使用md法构建的table

| link | $a_{i-1}$ | $\alpha_{i-1}$ |  $d_i$  |  $\theta_i$   |
| :--: | :-------: | :------------: | :-----: | :-----------: |
|  1   |     0     |       0        |    0    | $\theta_1 ^*$ |
|  2   |     0     |     -pi/2      |    0    | $\theta_2^*$  |
|  3   |     0     |      pi/2      | $d_3^*$ |       0       |
|  4   |     0     |     -pi/2      |    0    | $\theta_4^*$  |
|  5   |     0     |      pi/2      |    0    | $\theta_5^*$  |



# DH method

![](https://img-blog.csdn.net/20180414065511108?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjcxNzAxOTU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)



![](https://img-blog.csdn.net/20180414065938233?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvcXFfMjcxNzAxOTU=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

相同点是，至少关节和连杆之间的关系是一样的：

* n个关节的机器人，有n+1 个连杆，关节 i 连接 连杆i-1 和 连杆 i，也就是关节 i 在连杆 i-1 的末端，负责驱动连杆i 
* 两种方法dh参数的第i行，实际上都是描述坐标系 {O_i-1} 到 坐标系{O_i} 之间的变化

## Standard_DH

* 首先也是坐标系z_i 的配置，标准法规定z_i是关节i+1的驱动轴，关节i被驱动，坐标系Oi会跟着运动
* 然后x轴需要与前一个坐标系z轴垂直且相交，上面说是与前一个z叉乘（我看是不是）分三种情况讨论

四个参数：

*  **a** 是轴 $z_i$ 与 $z_{i+1}$之间沿轴线 $x_{i+1}$ 之间的距离
*  **$\alpha$** 是垂直于 $x_{i+1}$ 平面测得两个z轴之间的夹角，正向从 i 到 i+1
*  **d** 是从坐标系i原点o到轴线 $x_{i+1}$与$z_i$交点 o' 之间的距离
*  **$\theta$** 是垂直于$z_i$平面从两个x轴之间的夹角，同样遵循从低到高为＋



## Modified_DH

之前总结过std_DH的建模方法，这一次看看md_DH:

* 首先是坐标系z的配置，同样是z_i 对应关节轴i，不过关节轴i对应连杆i的起始端
* x_i的配置略有不同，x_i 由关节轴 i 、i+1 共同决定，由关节轴 i 指向 i+1（a_i，两个关节轴的公垂线） ，当a_i = 0时，也即两个坐标系重合时， x_i = z_i+1 x z_i
* y就是右手定则确定了

四个参数：

* $a_i$ : zi 到 zi+1 沿 xi 的距离
* $\alpha_i$ : zi => zi+1 的角度，以 xi 为轴
* $d_i$ :xi-1 到到xi 沿 zi的距离
* $\theta_i$  :   xi-1 到 xi 绕 zi 旋转的角度

前面两个是从zi到 z_i+1，参考轴都是 x i :

后面两个参数 是x  i-1 到 xi, 参考轴是 zi 

所以表格四个参数是 $a_{i-1}$$\alpha_{i-1}$$d_i $$\theta_i$ => 最后四个参数其实还是描述 $\{O_{i-1}\}$ 到 $\{O_{i}\}$

