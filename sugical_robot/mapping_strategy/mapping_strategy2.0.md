# mapping_strategy2.0

* [x] 整个映射流程，可以用如下过程描述，通过编码器测量五个关节角度信息，得到驱动空间 $\beta_1,\beta_2,\beta_3,\beta_4,\beta_5$

* [x] 将复制的并联机构简化为串联机构，【平面5bar推导】可以得到 主端关节空间  $[\theta_1, d_2, \theta_3, \theta_4, \theta_5]$ 

* [x] 结合【主从关节空间映射】得到 $[D_1, \alpha_2, \Phi_3, \alpha_4,  \Theta_5 ]$

* [x] 目前要做的，是从由常曲率参数$[D_1, \alpha_2, \Phi_3, \alpha_4,  \Theta_5 ]$ 到从端电机驱动空间【具体看论文】；



## 主从关节空间映射

新的机构构型可以简化成下图，对应的坐标系配置：

![](E:\GitHub\Mac_win\Mac_Win\sugical_robot\mapping_strategy\2.0\机构简图2.jpg)

机构简图中主端的关节空间为 $[\theta_1, d_2, \theta_3, \theta_4, \theta_5]$，从端的关节空间 $[D_1, \alpha_2, \Phi_3, \alpha_4,  \Theta_5 ]$

TODO：**这里从端的简化需要进行证明**（从端不能直接简化成这个）

__________________



之前采取的策略是将关节分为两组解耦，这样虽然简化一些计算，但是由于yaw是由 theta_1, theta_3共同决定，确定了其中一个，另外一个就也确定了，这样会丢失了一个自由度（举个例子：两个一样的平面二连杆做主从映射，目标是保持末端相同，当主端给出一个末端朝向时，从端可以有无数种构型，因为整体有两个自由度，而保持末端朝向只需要一个自由度，这个时候系统是冗余的；但当其中一个被固定时，另一个也固定了）



**总结：之前有5个自由度，但是只干了3个半的事**；因为有两个关节是冗余的，存在多解问题，可以在解空间中，找到一个满足位置约束的解；($\theta_1^t, \theta_2^t$)





所以放弃之前的分部策略，对整体进行分析：（3个姿态向量$\vec{u_R}, \vec{u_P}, \vec{u_Y}$和一个二维位置$x,y$）

对于完全同构的关节，可以从整体中剥离出来—— $\vec{u_P}, \vec{u_Y}$可直接由后面两个两对同构的转动关节独立决定，

于是映射问题就简化成了一个平面的问题：

 $\vec{u_R}$,x,y 由前三个异构自由度决定，并尝试推导新的映射

在满足一个 给定的  $\vec{u_R}$ 后，theta1和theta3仍剩余有自由度，配合d可以得到在平面上位置相等

手术中姿态的重要性大于位置（**这里有点像WBC和NSP的控制策略啊**），因此先保证三个姿态向量一致，也即保证 $\vec{u_R}$一致，此时 theta_1 和 theta_3 会有多个解，如果在这些解中再求出位置的关系（**这个地方我数学不太行**）
$$
\begin{bmatrix}
U_R \\
x_d \\
y_d
\end{bmatrix}
= 
\begin{bmatrix}
\Theta_2 - \Theta_3 \\
f_x(\Theta_2 , \Theta_3) \\
D1 + f_y(\Theta_2,  \Theta_3)
\end{bmatrix}
$$
因为$\Theta_2$和$\Theta_3$是冗余的，一一对应的话，会有一个自由度没有被利用，所以当$\theta_1$和$\theta_3$ 确定时，只需要保证
$$
\theta_1 + \theta_3 = \Theta_1
$$



**TODO**：推导 fx, fy；我是不是可以直接通过其次变换矩阵直接提取？试一下，就不用一个一个推导了



### fx\fz推导

下面是使用matlab计算出来齐次变换矩阵的结果：**感觉关于l的部分有些问题**

f_x:



-d4*(sin(alp4/2)*cos(Phi3)*(cos(alp2/2)^2 - sin(alp2/2)^2) + 2*cos(alp2/2)*cos(alp4/2)*sin(alp2/2)) - l*(cos(alp4/2)*(sin(alp4/2)*cos(Phi3)*(cos(alp2/2)^2 - sin(alp2/2)^2) + 2*cos(alp2/2)*cos(alp4/2)*sin(alp2/2)) + sin(alp4/2)*(cos(alp4/2)*cos(Phi3)*(cos(alp2/2)^2 - sin(alp2/2)^2) - 2*cos(alp2/2)*sin(alp2/2)*sin(alp4/2))) - d2*sin(alp2/2)

f_z:   // 

D1 + d4*(cos(alp4/2)*(cos(alp2/2)^2 - sin(alp2/2)^2) - 2*cos(alp2/2)*sin(alp2/2)*sin(alp4/2)*cos(Phi3)) + d2*cos(alp2/2) + l*(cos(alp4/2)*(cos(alp4/2)*(cos(alp2/2)^2 - sin(alp2/2)^2) - 2*cos(alp2/2)*sin(alp2/2)*sin(alp4/2)*cos(Phi3)) - sin(alp4/2)*(sin(alp4/2)*(cos(alp2/2)^2 - sin(alp2/2)^2) + 2*cos(alp2/2)*cos(alp4/2)*sin(alp2/2)*cos(Phi3)))


$$
p_x = -d_2 \sin \left( \frac{\alpha_2}{2} \right) - d_4( \sin \left( \frac{\alpha_4}{2} \right) \cos(\Phi_3) \cos(\alpha_2) + \cos(\frac{\alpha_4}{2})\sin(\alpha_2)) - l (\sin(\alpha_4) \cos(\Phi_3) \cos(\alpha_2) + \cos(\alpha_4) \sin(\alpha_2) )
 \\

p_z = D_1 + d_2 \cos \left( \frac{\alpha_2}{2} \right) + d_4 \cos(\alpha_2) \cos(\alpha_4) - d_4 \cos(\Phi_3) \sin(\alpha_2) \sin(\alpha_4) + l \cos(\alpha_2) \cos(\alpha_4) - l \cos(\Phi_3) \sin(\alpha_2) \sin(\alpha_4)
$$

```latex
\begin{align*}
p_x &= d_2 \sin \left( \frac{\alpha_2}{2} \right) + d_4 \sin \left( \frac{\alpha_4}{2} \right) \cos(\Phi_3) \cos(\alpha_2) + l \cos(\alpha_4) \cos(\Phi_3) \cos(\alpha_2) + l \sin(\alpha_4) \cos(\alpha_2) \\
p_z &= D_1 + d_2 \cos \left( \frac{\alpha_2}{2} \right) + d_4 \cos(\alpha_2) \cos(\alpha_4) - d_4 \cos(\Phi_3) \sin(\alpha_2) \sin(\alpha_4) + l \cos(\alpha_2) \cos(\alpha_4) - l \cos(\Phi_3) \sin(\alpha_2) \sin(\alpha_4)
\end{align*}
```



但是有一个问题是，我想要的是 $f_x(d_2, \theta_3^e)$ ，而现在得到的是 $f_x(d_2, \Phi_3, \alpha_4)$

好在可以推导出 $\theta_3^e$ 和 $\Phi_3, \alpha_4$ 之间的关系 

不需要推导，也推导不出来，虽然现在fx是由$\Phi_3, \alpha_4$ 表示，但是其实还可以用 $\theta_3, \theta_4$表示（问题就简单很多了），但是这个$\theta_3$还不是$\theta_3^e$，因为$\theta_3^e$等效的是连续体偏转 $\alpha_4$的数值，而只讨论位置的时候末端位置对应的是偏转 $\alpha_4 /2$ ，因此有多引出了一个变量 $\theta_3^f$

两者之间满足的关系是：
$$
c_{\theta_3^e} c_4 = c_{\alpha_2} \\
c_{\theta_3^f} c_4 = c_{\alpha_2/2}
$$
由此可以得到
$$
\theta_3^f = c^{-1}(A * c_{\theta_3^e}) \\
A = \frac{c_{\alpha_2/2}}{c_{\alpha_2}}
$$

$$
P_x = f_x (\alpha_2, \theta_3^f)
$$

______________________

上面推不出来，那就暴力求解把

把fx中三个参数全部用 $\theta_3^e$表示，整理得到一个关于 $\theta_3^e$ 的函数；关于\alpha4和 Phi3的推导，其实之前一直没有完全规定清楚；7-29号重新真正的说清楚

theta3 规定为绕 z3 转动角度，theta4为绕z4转动的角度，两个轴的方向见drawio文件，通俗来说，theta3是偏航左转角度，theta4是俯仰朝上的角度

Phi3规定为器械绕轴转动的角度，具体来说，就是初始的x轴$x_0^s$与转动后的x轴$x_1^s$ 形成的角度，为了满足alpha4 右手定则，规定$x_1^s$与$z_6^s$共轴。

alpha4 规定为转动Phi3后，绕$z_6^s$转动角度，具体轴方向见文件。

由此推导出新的公式：(仅针对theta3,theta4都大于零)
$$
\alpha_2 = A - \theta_3^e\\
\alpha_4 = c^{-1} (c_{\theta_3^e} * c_4) \\
\Phi_3 =  c^{-1}(c_4 s_{\theta_3^e} / s_(\alpha_4)) \\
\Delta x = c^{-1}(c_3 s_{\Phi_3}) + \Phi_3 - \pi/2
$$




将fx单独用 \theta_3^e 表示

最终化简出这样一个结果：
$$
p_x = -d_2 \sin \left( \frac{A - x}{2} \right) - d_4 \left( \sin \left( \frac{\cos^{-1}(c_{x} c_{4})}{2} \right) \cos \left( \cos^{-1} \left( \frac{c_{4} \sin{x}}{\sin(\cos^{-1}(c_{x} c_{4}))} \right) \right) \cos(A - x) + \cos \left( \frac{\cos^{-1}(c_{x} c_{4})}{2} \right) \sin(A - x) \right) - l \left( \sin(\cos^{-1}(c_{x} c_{4})) \cos \left( \cos^{-1} \left( \frac{c_{4} \sin{x}}{\sin(\cos^{-1}(c_{x} c_{4}))} \right) \right) \cos(A - x) + \cos(\cos^{-1}(c_{x} c_{4})) \sin(A - x) \right) \\
\alpha_2 = A - x; \\
       \alpha_4 = c^{-1}(cos(x) * c_4); \\
d_2 = (2s_1 / \alpha_2) * sin(\alpha_2 / 2); \\
d_4 = (2s_2 / \alpha_4) * sin(\alpha_4 / 2);  \\
$$


```latex
p_x = d_2 \sin \left( \frac{A - x}{2} \right) + d_4 \left( \sin \left( \frac{\cos^{-1}(c_{x} c_{4})}{2} \right) \cos \left( \cos^{-1} \left( \frac{c_{4} \sin{x}}{\sin(\cos^{-1}(c_{x} c_{4}))} \right) \right) \cos(A - x) + \cos \left( \frac{\cos^{-1}(c_{x} c_{4})}{2} \right) \sin(A - x) \right) + l \left( \sin(\cos^{-1}(c_{x} c_{4})) \cos \left( \cos^{-1} \left( \frac{c_{4} \sin{x}}{\sin(\cos^{-1}(c_{x} c_{4}))} \right) \right) \cos(A - x) + \cos(\cos^{-1}(c_{x} c_{4})) \sin(A - x) \right)
```



这样一个结果很难有解析解，尝试使用解析法求解 px与theta_3之间的关系，然后构建一个链，需要完成以下任务：

* [x] 编写函数求解这个非线性方程的解（先把fx的方程检查以下，说不定可以简化）；

  * [x] 需要给一组输入值  $\theta_m = [-\pi/6, 10, \pi/3, 0, 0] $，也即给定主端关节，和对应末端的位置；先要把主从大小配合一下，之后再搞缩放 主端长度

* [x] 求解完之后，给出一组主端的关节空间，验证从端是否相同

* [x] 求解D1：用pz _m - pz_s，两者的差值，就是D1，验证代码及其结果在 E:\GitHub\Mac_win\Mac_Win\sugical_robot\mapping_strategy\check_result\check_nolinear_solve.m

* [ ] 要不要做个图像？可能有点费时间，公式以及足够验证其正确性

* [ ] 从驱动空间，到关节空间还没有推导

  



$f_x$ 是由两段在x轴上的贡献决定

## 主端5bar驱动空间到关节空间

这里主要推导一下从主端驱动空间 $[\beta_1, \beta_2, \beta_3]$到关节空间 $[\theta_1, d_2, \theta_3]$的求解过程；

其中 $\beta$ 定义为连杆与水平线行程的夹角？

$\Delta \theta$ 描述的测量值 beta3 到理想值 theta3 的沿逆时针方向的夹角
$$
\theta_1 = \tan^{-1} \frac{l_5/2- x_c}{y_c} \\
\theta_3 = \lambda_3 - \Delta\theta \\
where,  \Delta\theta =  \theta_1 +  \lambda_4' - 0.2\pi \\
$$
其中，theta_1 表示五连杆末端点与中心位置O坐标系形成的夹角，theta3表示坐标系3与坐标系2之间的夹角；而α5表示电机实际转动的角度（这里电机实际转动的角度不等于theta3，所以需要推导）

需要简单的验证一下上述结果

通过对两种结构建模，然后



## CCP参数到单元关节参数

根据目前从端连续体逆运动学建模，绳长 $L$ 是和单元关节的参数 $\beta_1, \beta_2$ 关联的，因此还要搭建$\Theta_s$ 到关节参数的映射

关节参数记作$\Beta_s$，
$$
\Beta_s = {\beta_2, \beta_3,\beta_4}
$$
满足如下关系:
$$
\beta_2 = \frac{\alpha_2}{n_p}  \\
\beta_3 = \tan^{-1} (\tan(\alpha_4 / n_d)\cos(\Phi_3) \\
\beta_4 = s^{-1} (\sin {(\alpha_4 / n_d)}  \sin{\Phi_3} )
\\ n_p = 8;
\\ n_d = 6;
$$


### 基于WBC的零空间控制方法

这个方法的核心就是，将需要控制的目标进行分组，分组完以后求解对应的雅可比矩阵（其实没有太搞懂为什么是求雅可比矩阵）

[知乎](https://zhuanlan.zhihu.com/p/164738620)
