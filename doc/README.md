Lanos 中文文档
======================================================================
本文档采用知识共享署名·相同方式共享 3.0 Unported 许可协议进行许可。<br>
反版权所有 (CC) 哆啦比猫(兰威举), 2010-2011.

此项目是 cjsp 项目（Clanjor Selfaction Project）的一个子项目——
操作系统部分。<br>
它使用 GRUB 来载入（主要）用 C 语言写成的内核。

简介
------------------------------------------------------------
Lanos 是一个 32 位不全保护模式非 UNIX 克隆的操作系统
(32-bit not-so-protected non-UNIX-clone OS)。Lanos 将
尽早实现实用功能（如，在完成屏幕管理模块后就立即实现了 printf）。
Lanos 将提供 OpenGL、数字音频(digital audio)、高分辨率、
鼠标/键盘/（可能还有）手柄驱动、多线程单进程
(single process with multi-threads)的支持。Lanos <em>可能</em>会提供
文件操作的支持，且所有应用程序（目前）必须硬编码(hard-coded)于内核。

Lanos 是一个给 hackers 的玩具。Lanos 可用于制作可引导实时（三维）动画
(bootable demoscene).

目录结构
------------------------------------------------------------
在 src/ 中（其中，带“·”的项目表示要先完成）：

 * · base/
 * · video/
 * &nbsp;&nbsp;audio/
 * · misc/
 * · keyboard/
 * &nbsp;&nbsp;mouse/
 * · include/
 * &nbsp;&nbsp;gl/
 * · app/
 * · math/

我要试一试
------------------------------------------------------------
首先，你需要获得源代码：

	git clone git://github.com/cjxgm/lanos.git

接着，编译内核（由于要 mount 软盘镜像，需要有 root 权限）：

	make

对于 bochs 用户，可以用

	make debug

来尝试运行，而对于 qemu 用户，可以用

	make qemu

尝试运行。

对了，我还要提醒你，如果你按了 ESC 键，系统会卡死（故意这样的）。


如果你试图修改代码，请<em>务必</em>将编辑器的 tab 宽度设置成 4 个空格宽！严厉打击各种不正规 tab 设置！严禁使用空格代替 tab！（在 Lanos 系统中，tab 是且只能是且必须是 4 个空格的宽度！！！！！！）

Issues
------------------------------------------------------------
（“·”表示已解决）

 * 2011/9/11 · 计时器不工作
 * 2011/9/18&nbsp;&nbsp;&nbsp;加入 1024x768x24 图形模式，但不工作

