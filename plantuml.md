```plantuml 
Bob -> Alice : hello 
Alice -> Wonderland: hello Wonder
land -> next: hello
next -> Last: hello 
Last -> next: hello 
next -> Wonderland : hello 
Wonderland -> Alice : hello 
Alice -> Bob: hello 
```

### 简单状态
```plantuml
[*] --> State1
    
State1 --> [*]
    
State1 : this is a string
    
State1 : this is another string
    

State1 -> State2
```

### 并发状态

```plantuml

[*] --> Active
    

state Active {
    
 [*] -> NumLockOff
    
 NumLockOff --> NumLockOn : EvNumLockPressed
    
 NumLockOn --> NumLockOff : EvNumLockPressed
    
 --
    
 [*] -> CapsLockOff
    
 CapsLockOff --> CapsLockOn : EvCapsLockPressed
    
 CapsLockOn --> CapsLockOff : EvCapsLockPressed
    
 --
    
 [*] -> ScrollLockOff
    
 ScrollLockOff --> ScrollLockOn : EvCapsLockPressed
    
 ScrollLockOn --> ScrollLockOff : EvCapsLockPressed
    
}
```

```plantuml
hide empty description
left to right direction
 
[*]-->NotLogin:首次打开app
 
state  NotLogin: 没有登录
state  LoginSuccess: 登录成功
state  LoginFail: 登录失败
 
NotLogin -->LoginSuccess: 登录
NotLogin -->LoginFail:登录
 
state LoginFail {
    state 用户不存在: ta校验
    state saas注册失败:注册saas
    state 登记用户信息失败: 登记到tiananUser
    state 参数校验失败 :校验参数
}
 
state join_state  <<join>>
LoginSuccess-->join_state:组装响应参数
LoginFail-->join_state:组装响应参数
 
join_state -->[*]:返回JSON数据到客户端
 
```

## 活动图

### 基本语法

| 元素 | 语法 | 说明 |
| --- | --- | --- |
| 开始 结束 | start stop | 开始结束活动 |
| 活动 | :活动名称; | 定义活动 |
| 条件语句 | if (条件 ?) then (yes) 换行 下一个活动 else(no) endif | 条件分支 |
| 循环语句 | repeat 换行 活动 换行 repeatwhile(条件 ？) | 先执行再判断 |
| 循环语句 | while ( 成立的条件？) 换行 活动 换行 endwhile(不成立的条件描叙) | 先判断条件在循环 |
| 改变活动的形状 | :活动\> < \] } / 竖线 | 分别得到不同的形状 |
| 并行处理 | fork fork again end fork | 并行处理 |
| 组合 | partition group名称 { 活动图语法} | 对活动进行分组 |
| 泳道 | 两根竖线包围 | 泳道 |
| 分离 | detach | 移除箭头 |

#### 1. 条件语句

```plantuml
start 
if (A) then (yes)
	:Text 1;
elseif (B) then (yes)
	:Text 2;
	stop
elseif (C) then (yes)
	:Text 3;
else (nothing)
	:Text else;
endif
stop
```

#### 2. 循环语句

```plantuml
start
while (true?) is (note)
	:read data;
	:generate diagrams;
endwhile
stop
```

#### 3. 并行语句

```plantuml
start

if (multiprocesor?) then (yes)
	fork
		:Treatment 1;
	fork again
		:Treatment 2;
	end fork
else (monoproc)
	:Treatment 1;
	:Treatment 2;
endif

stop
```

#### 4. 管道

```plantuml
|lane1|
start
:foo1;
|lane2|
:foo2;
|lane3|
:foo3;
stop
```


#### 5. switch

```plantuml
start
:获得优惠券
switch(status)
case(0)
	:全场通过;
case(1)
	:func2;
case(2)
	:func3;
endswitch
	:hello;
stop
```


#### 6. example

```plantuml
start
title 收到机械臂和丝杆移动指令
|callback|
: 解析指令内容
switch(action)
case(后臂移动)
case(前臂移动)
case(丝杆移动)
endswitch
stop
```



