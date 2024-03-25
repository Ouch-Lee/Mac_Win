# papar_final_polish

* [x] 先把tremor部分图和文章都改好
  * [x] 重新画一遍图，集中信息
  * [x] 内容再过一遍
  * [ ] 把fig下面的信息描述清楚
  
* [x] Introduction 部分简化

* [ ] Mechanical Design 部分润色+简化
  * [x] 第一段
  
    * [ ] table 改好
  
      [手腕自由度](https://www.researchgate.net/profile/Diar-Abdlkarim/post/Is-pronation-supination-a-movement-part-of-the-wrist-or-the-forearm/attachment/59d61f0d6cda7b8083a185fb/AS%3A273610461769741%401442245226047/image/Flexion.Extension.Pronation.Supination.jpg)：extension/Flexion + Radial deviation/Ulnar deviation








### Fig

fig_compare: 不同条件下手指末端位置对比 (a) 初始位置（实线），KF处理后位置（虚线）；(b) 肘部无托举15分钟后位置记录（实线）；有托举对比（虚线）

adaptive KF：三种状态下单个关节位置信息 (a) 手指上下摆动和保持静止 (b) 保持静止部分放大







### 删掉的历史记录

* introduction：**操纵三角需要这里再解释一遍吗？**
  —a concept of paramount importance in endoscopic surgery, characterized by the vector representing the positional and orientational relationship between two surgical instruments at their distal ends 

* Abstract
  
  Master-Slave Control celebrated for its straightforward and dependable operation, is extensively utilized in surgical robotics,  including Natural Orifice Transluminal Endoscopic Surgery (NOTES). NOTES faces the challenge of operating in confined spaces, prompting a focus on developing sophisticated designs for slave manipulators. This focus has often led to the oversight of the master console's role. Our research introduces a groundbreaking exoskeleton master console tailored for NOTES robotic systems. The exoskeleton aims to provide surgeons with comfortable arm support, enabling free hand movements during surgeries and offering intuitive control of the robotic assistant. This paper delves into the exoskeleton's design, emphasizing its ergonomic structure and practicality. We analyzed the kinematic model of both master and slave sides to develop an effective mapping strategy, demonstrating its user-friendly operation. Additionally, leveraging this model, we employed the device to detect and mitigate physiological hand tremors, considering both software and hardware aspects.
  
* introduction这一段

  Inspired by prior work, we propose an endoscopic dual-channel surgical robot model capable of actively controlling triangulation as shown in \cref{fig:DOF_relation}(c). This model incorporates flexible arms on either side, each consisting of two continuum segments. The proximal segment primarily adjusts triangulation, while the distal segment executes precise surgical tasks. The collaborative operation of these segments allows for more versatile movements. Based on the conceptual model, we have developed an exoskeleton-style surgical robot console whose DOF directly corresponds to those of the proposed surgical robot, ensuring efficient and straightforward control over the robotic. During human-machine interaction, this device intuitively maps the movements of the surgeon to surgical robot without compromising the surgeon's manual dexterity.Unlike traditional 'face-to-face' master consoles, our design utilizes a wearable exoskeleton structure, providing an intuitive user experience. This format not only enhances intuitiveness but also results in a more compact and streamlined overall structure.



* 关于肘部搭载结构：前面的废话好像有点多：

  Muscle fatigue, induced by prolonged elevation of the arm, intensifies physiological tremors, a critical concern in minimally invasive surgery. Recognizing this, commercial surgical robot consoles typically incorporate forearm supports. Our design advances this concept by introducing an elbow support structure, enhancing both fatigue reduction and control precision. This structure functions similarly to a joystick, allowing for intuitive manipulation of the console's position via an orthogonal guide rail. 

  修改版本：

  (此外，该结构另外一个功能是作为“操纵杆”，控制主体在两个正交导轨上的运动)

  \cite{ref_20_chandra2017empirical}

  Currently, our second-generation prototype is in development. Preliminary observations suggest a significant reduction in hand tremors, though rigorous empirical validation is pending. We anticipate this forthcoming evidence will robustly confirm the device's efficacy.

  我们将手臂悬空15分钟模拟医生手术时的肌肉疲劳，设置对照试验，在有无肘部支撑的情况下观察指尖震颤情况，结果在图B中展示。
  
* table

  ```latex
  % table 可以用0.5距离
  % 
  % \begin{table*}[h]
  
  % \begin{center}
  % \begin{tabular*}{\textwidth}{c@{\extracolsep{\fill}}c@{\extracolsep{\fill}}c} % 使用tabularx并设置表格宽度为页面宽度
  % \hline
  % \textbf{surgeon} & \textbf{master console} & \textbf{salve manipulator} \\
  % \hline
  % Arm Flexion/Extension & Longitudinal motion &  Extension/Retraction \\
  % % \hline
  % Arm Abduction/Adduction &  Lateral motion & Proximal deflection\\
  % % \hline
  % Wrist Dorsiflexion/Palmarflexion & Yaw rotation & Distal Lateral deflection \\
  % % \hline
  % Wrist Ulnar/Radial Deviation & Pitch rotation & Distal Vertical deflection\\
  % % \hline
  % Wrist Pronation/Supination & Rolling rotation & Instrument Rotation \\
  % % \hline
  % Fingers pinch & Finger gripper compressed & Surgical instrument closure \\
  % \hline
  % \end{tabular*}
  % \end{center}
  % \caption{motion relationship between surgeon-master console-salve manipulator}
  % \label{table_robot_system}
  % \end{table*}
  ```

  

### GPT4 NB

Reviewing this section, which focuses on the mathematical derivation of the mapping strategy, it is crucial to ensure clarity, technical accuracy, and accessibility. Here are my comments and suggestions for revision:

**Review Comments:**

1. **Mathematical Clarity**: The equations and their descriptions are detailed, but the narrative could benefit from a clearer logical flow to guide the reader through the derivation process.

2. **Notation Consistency**: Ensure consistent notation throughout the section, particularly with mathematical symbols and terms. 

3. **Figure References**: The text mentions figures (\cref{fig: axis_discribe}) to illustrate points, but it's essential to ensure these figures are described so the reader understands what they show, even without seeing them.

4. **Explanation of Terms**: Some terms and symbols (e.g., $ks$, $\phi$, $\Delta x$) are used extensively but require a clear definition within the text to ensure understanding by all readers.

5. **Contextualization of Models**: The transition from isomorphic to heterogeneous mapping and the use of specific models (like the 'Constant Curve Model') should be contextualized within the broader scope of the research.

**Suggested Revision:**

"In the derivation of our mapping strategy, we begin with the isomorphic relationship of the initial two joints, facilitating a linear mapping as follows:

\begin{equation}
\begin{bmatrix}
D_1 \\
ks_1
\end{bmatrix}
=
\begin{bmatrix}
\lambda & 0 \\
0 & \frac{\theta_{\text{max}}}{d_{\text{max}}}
\end{bmatrix}
\begin{bmatrix}
d_1 \\
d_2
\end{bmatrix}
\end{equation}

where \(\theta_{max}\) is the maximum deflection angle of the proximal section, and \(d_{max}\) signifies the lateral guide rail’s half movement range. 

For the remaining joints, we adopt Cartesian space control, avoiding the complexities of kinematics by focusing on the geometric relationship between the master and slave systems. Figure (a) illustrates the coordinate transformation from \(O\) to \(O_2\), and similarly, from \(O\) to \(O_2^a\), representing the three-link and proximal section movements, respectively.

The alignment of the z-axes in Figure (b) suggests a consistent end orientation, with a noticeable offset in the x-y plane. The geometric derivation leads to the following equations, applied using the 'Minimum Angle Theorem':

\begin{align}
\cos (ks) &= \cos (\theta_{3}) \cdot \cos (\theta_{4}) \\
\cos (\angle z_{2} O x_{0}) &= \cos (\frac{\pi}{2}-\theta_{3}) \cdot \cos (\theta_{4}) \\
\cos (\angle z_{2} O x_{0}) &= \cos (\phi) \cdot \cos (\frac{\pi}{2}-ks)
\end{align}

These equations establish the basis for our mapping function, simplified as:

\begin{equation}
\left\{
\begin{array}{l}
ks = f_{1}(c_{3} c_{4}) = \cos^{-1}(c_{3} c_{4}) \\
\phi = f_{2}(c_{3} c_{4}) = \cos^{-1}\left(\frac{c_{4} s_{3}}{s_{ks}}\right)
\end{array}
\right.
\end{equation}

In MATLAB simulations, the master and slave coordinate systems were plotted, initially showing the z-axis alignment and x-y plane deviation. By incorporating the calculated \( \Delta x \), we aligned the coordinate systems fully, validating our mapping approach."

This revision aims to guide the reader through the mathematical derivation with improved clarity, link the theoretical models to the practical implementation, and ensure the text is accessible and informative.
