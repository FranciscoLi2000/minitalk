# Minitalk

这个 **Minitalk 项目** 旨在通过实现基于 UNIX 信号的进程间通信程序，帮助你掌握以下 **核心技能** 和 **系统编程知识**：

---

### **核心学习目标**
1. **UNIX 信号机制**
- 掌握 `SIGUSR1` 和 `SIGUSR2` 信号的基本用法，理解信号的发送（`kill`）、接收（`sigaction`）和处理逻辑。
- 通过信号传递数据，将字符编码为二进制信号序列（如 `SIGUSR1` 表示 `0`，`SIGUSR2` 表示 `1`），实现字符串的逐位传输。

2. **进程间通信（IPC）**
- 设计客户端（`client`）与服务器（`server`）的交互模型，理解进程 PID 的获取（`getpid`）和通信目标指定。
- 实现异步通信机制，确保服务器能持续接收并处理多个客户端的请求。

3. **异步编程与并发控制**
- 处理信号的异步性，设计状态机或缓冲区管理接收到的数据流，避免信号丢失或覆盖。
- 使用 `usleep` 或 `pause` 控制信号发送的时序，解决信号未排队（non-queued）导致的数据完整性问题。

4. **编码与解码技术**
- 将字符（如 ASCII 或 Unicode）转换为二进制流，通过信号序列传输。
- 实现数据的重组与校验（如通过校验和或确认机制），确保传输的准确性。

5. **内存管理与健壮性**
- 动态分配内存存储接收数据（如使用 `malloc`），确保无泄漏（`free`）。
- 处理非法输入（如无效 PID、非整数参数），输出标准错误信息（`Error\n`）。

6. **工程规范与调试**
- 遵循 **Norminette** 代码规范，编写模块化代码（如分离信号处理函数与主逻辑）。
- 使用调试工具（如 `printf` 日志、`strace`）分析信号传输过程，定位逻辑错误。

---

### **关键技术点解析**
#### 1. 信号编码与传输
```c
	// 客户端发送字符 'A' (ASCII 65 = 01000001)
	void	send_char(int pid, char c)
	{
		for (int i = 7; i >= 0; i--)
		{
			int bit = (c >> i) & 1;
			if (bit == 0)
				kill(pid, SIGUSR1); // 发送 0
			else
				kill(pid, SIGUSR2); // 发送 1
			usleep(100); // 等待信号处理完成
		}
	}
```
**关键点**：逐位发送字符的二进制表示，通过延时控制信号间隔。

#### 2. 服务器信号处理
```c
	// 全局变量保存接收的数据和当前处理位
	char	received_char;
	int	bit_index = 7;

	void	sig_handler(int signo)
	{
		if (signo == SIGUSR1)
		{
			received_char &= ~(1 << bit_index); // 设置当前位为 0
		}
		else if (signo == SIGUSR2)
		{
			received_char |= (1 << bit_index);  // 设置当前位为 1
		}
		bit_index--;
		if (bit_index < 0)
		{
			write(1, &received_char, 1); // 输出完整字符
			bit_index = 7;
			received_char = 0;
		}
	}
```
**关键点**：通过静态变量管理接收状态，逐位重组字符。

#### 3. 确认机制（Bonus）
```c
	// 服务器收到信号后发送确认信号
	void	sig_handler(int signo)
	{
		// 处理信号并重组数据
		kill(client_pid, SIGUSR1); // 发送确认信号
	}
```
**关键点**：通过双向信号确保每比特传输的可靠性，避免数据丢失。

---

### **工程实践与思维提升**
1. **模块化设计**
- 分离客户端和服务器的代码，封装信号处理、数据编码/解码为独立函数。
- 使用头文件（如 `minitalk.h`）定义共享数据结构和常量。

2. **防御式编程**
- 校验客户端参数（如 PID 是否为有效整数，字符串非空）。
- 处理信号冲突（如同时接收到多个信号），使用锁或状态标志避免竞态条件。

3. **性能优化**
- 调整信号发送间隔（`usleep` 时间），平衡传输速度与可靠性。
- 支持 Unicode（Bonus）需扩展编码逻辑（如 UTF-8 的多字节处理）。

---

### **项目隐喻与深层价值**
- **“信号是操作系统的基础抽象”**：通过底层信号机制实现通信，理解操作系统内核与用户进程的交互。
- **“异步编程的挑战与艺术”**：在非阻塞、事件驱动的模型中管理状态，培养复杂系统调试能力。
- **“从协议设计到实现”**：自定义简单的通信协议（如信号编码规则），掌握协议设计的核心思想。

---

### **通关要点**
1. **分步实现**
- 先实现单字符传输，再扩展为字符串。
- 添加错误处理（如无效 PID、信号丢失）和内存管理。

2. **测试策略**
- 使用多客户端并发测试服务器的稳定性。
- 验证长字符串、特殊字符（如 `\0`、Unicode）的传输准确性。

3. **代码优化**
- 减少全局变量的使用，通过参数传递状态（如 Bonus 的确认机制）。
- 使用位操作替代乘除运算，提升编解码效率。

---

通过此项目，你将从“应用层开发者”进阶为“系统级开发者”，深入理解进程间通信的底层机制，为分布式系统、实时应用开发奠定坚实基础。
