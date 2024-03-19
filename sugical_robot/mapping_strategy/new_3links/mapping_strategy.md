# mapping strategy

高效的映射策略可以带给surgeon更好的手术体验，从而提升手术安全性；主从式手术机器人的映射策略主要分为同构映射和异构映射；同构映射也即主从两端构型相同或者大致相似，对应的关节之间可以直接进行线性映射，而异构映射通常需要借助主从两端正逆运动学建立映射关系。虽然该结构在自由度布局时尽量保持了同构关系，但是由于主端为刚性连杆，而从端surgical arm由柔性的continuum构成，因此主端“three-link”和从端surgical arm为异构映射。This section mainly introduce the mapping strategy from master console to slave arm, 也即从端驱动空间[theta 1 ... theta 5] 到从端构型空间。（从端到底是构型空间还是驱动空间？）

常规的DH建模法对连续体模型并不适合，这里采用前人提出的“Constant Curve Modle”，该模型使用 ks 描述末端偏离轴心的偏转角度，使用phi描述由偏转引起的绕轴心的旋转。

A well-designed mapping approach can enhance a surgeon's overall experience and ultimately bolster surgical safety. In the context of master-slave surgical robotics, mapping strategies typically fall into two categories: isomorphic mapping and heterogeneous mapping. Isomorphic mapping involves directly translating the master-slave configuration when both ends share similar joints, while heterogeneous mapping often necessitates employing forward and inverse kinematics to establish a mapping relationship between master and slave ends. Despite efforts to maintain an isomorphic relationship in the layout of degrees of freedom, differences arise due to the rigid structure of the main end and the flexible continuum of the slave end surgical arm. Consequently, the mapping between the master's "three-link" structure and the slave's surgical arm structure differs. This section primarily focuses on elucidating the mapping strategy from the master console to the slave arm, specifically transitioning from the slave's drive space [theta 1 ... theta 5] to its configuration space.



前面两个关节符合同构关系，可直接建立线性映射关系如下：
$$
\Theta_1 , \Theta_2 = {} 
$$
对于后面3个异构关节，我们采用传统的笛卡尔空间增量控制方法，但是在求解过程中并没有借助中从两端的正逆运动学，而是通过两者之间的几何关系推导得到简洁的解析解，避免了复杂的计算。以下简单介绍推导过程：

isomorphism or isomerism

For the subsequent three heterogeneous joints, we employ the conventional Cartesian space incremental control method. However, during the solution process, we eschew dependence on the forward and inverse kinematics of both central ends. Instead, we derive a straightforward solution based on the geometric relationship between them. The following section provides a succinct overview of the derivation process:



DH部分删除的内容：

```
Figure 4 displays the integrated kinematic diagram of the master-slave system. For the rigid linkage structure in the master console, we adhere to the Denavit-Hartenberg (DH) convention, assigning coordinate systems to each joint. Applying the conventional DH method to the slave-end flexible continuum introduces significant computational complexity. Instead, we employ a constant curvature model, which is better suited for continuum modeling \cite{ref_22_jones2006kinematics}. Within this model, \(ks\) denotes the continuum's deflection angle from the axis, while \(\phi\) represents the rotational angle resulting from the superposition of two orthogonal deflections. For a proximal section, \(\phi\) is zero.

\begin{figure}[htbp] % 设置图片浮动位置
    \centering % 图片居中
    \includegraphics[width=0.5\textwidth]{ieeeconf/master-slave_DH.jpg} % 插入图片，替换 example-image 为你的图片文件名
    \caption{Integrated kinematic drawing of master  console(a) and slave manipulator(b),  Coordinates were set up and attached to each of the joints on the basis of the Denavit-Hatenberg (D-H) convention} % 图片标题
    \label{fig:example} % 图片标签，用于交叉引用
\end{figure}

For the distal sub-mapping task,
we need to keep the end poses of the three-link and proximal section the same. One approach ensures their rotation matrices R are identical. Directly solving for this condition algebraically is computationally intensive and may not always yield a solution. Thus, we adopt a geometric method to address this challenge, offering a practical solution without the drawbacks associated with algebraic resolution.
```



```
The ‘minimum angle theorem’ : When point \(A\) is projected onto plane \(BOC\), the projection line \(AB\) coincides with \(BO\) , and the projection of 
\(BC\) onto plane \(boc\) coincides with \(BO\), thus forming two angles,\(\angle ABC\) and \(\angle OBA\), \(\angle OBc\) respectively. The cosine of the angle between them can be expressed as: \(cos \angle ABC = cos \angle OBC \cdot cos \angle OBA\). 

\begin{figure}[htbp] % 设置图片浮动位置
    \centering % 图片居中
    \includegraphics[width=0.5\textwidth]{ieeeconf/minimun_angle.png} % 插入图片，替换 example-image 为你的图片文件名
    \caption{Explanation of 'minimum angle theorem'} % 图片标题
    \label{fig:example} % 图片标签，用于交叉引用
\end{figure}
```



偏转修改：

The main link's final x-axis corresponds to $x_{2}$, hence the angle with \(OC\) is $\theta_3$, corresponding to $\angle1$ in the diagram. The end effector's final x-axis corresponds to $x_{2}^{a}$, hence the angle with \(OB\)  is $ks$, corresponding to $\angle2$ in the diagram.
To solve for the angle $\Delta x$ between $x_{2}^{a}$ and $x_{1}$, it is also necessary to rely on projection relations and the law of cosines. By drawing auxiliary line \(OQ\) as the projection of \(OP\) on plane \(OBA\), three sets of equations can be obtained:

fig(b)中每个角度在fig(a)中都能找到对应的角度，POx_2 对应x0Ox2为thata3，记为角1；

角BOX2^a 对应x1^a O x2^a为\ks，记为角2

Specifically, angle \text{POx}_2POx2 corresponds to \text{x}_0 \text{Ox}_2x0Ox2 as \theta_3*θ*3, denoted as Angle 1. Angle \text{BOX}_2^aBOX2*a* corresponds to \text{x}_1^a \text{Ox}_2^ax1*a*Ox2*a* as \ks\ks, recorded as Angle 2.