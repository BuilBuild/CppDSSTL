https://www.kancloud.cn/wizardforcel/gdb-tips-100/146771

ctrl + x + a 进入tui
b xx 打印断点
i b 打印断点信息
i threads 打印所有线程
thread x 进入某个线程
bt x 进入某个栈帧
info functions 显示所有函数 （info functions regex[info functions thre*]）
使用gdb调试遇到函数时，使用step命令（缩写为s）可以进入函数（函数必须有调试信息）。
“set step-mode on”命令，这样gdb就不会跳过没有调试信息的函数
“finish”命令，这样函数会继续执行完，并且打印返回值，然后等待输入接下来的命令。
call 命令 执行函数
i frame 打印堆栈信息
i registers 打印寄存器信息
disassemble func 打印func函数汇编
如果要打印函数局部变量的值，可以使用“bt full”命令（bt是backtrace的缩写）。首先我们在函数fun_a里打上断点，当程序断住时，显示调用栈信息,“bt full n”，意思是从内向外显示n个栈桢，及其局部变量
用gdb调试程序时，如果想查看进程的内存映射信息，可以使用“i proc mappings”命令

命令行 
gdb attach pid 在命令行中gdb到某个线程
