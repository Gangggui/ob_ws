
### 变量和数据类型


```python
msg = "hello python world"
msg
```




    'hello python world'



### 2.3 字符串
#### 2.3.1 修改大小写


```python
msg.title() #首字母大写
```




    'Hello Python World'




```python
msg.upper() # 全大写
```




    'HELLO PYTHON WORLD'




```python
msg.lower() # 全小写
```




    'hello python world'



#### 2.3.4 删除空白


```python
msg.rstrip() # 后面空白
```




    'hello python world'




```python
msg.lstrip() # 前面空白
```




    'hello python world'




```python
msg.strip() # 两端空白
```




    'hello python world'



## 3. 列表
### 3.1 定义
用方括号[]进行表示，逗号分隔


```python
list = ["hello", 2, 3]
list
```




    ['hello', 2, 3]



### 3.2 访问
用位置和索引: list[index]


```python
list[2]
```




    3



### 3.3 添加元素


```python
list.append("new") # 末尾添加
list
```




    ['hello', 2, 3, 'new']




```python
list.insert(2, 'world') # 在任意位置添加
list
```




    ['hello', 2, 'world', 3, 'new']



### 3.4 删除
1. 用del list[index]删除：仅删除
2. pop(index=end)语句删除：删除并弹出
3. remove(val)语句：根据值删除


```python
del list[2]
list
```




    ['hello', 2, 3, 'new']




```python
index = list.pop()
list
```




    ['hello', 2, 3]




```python
index = list.pop(0)
list
```




    [2, 3]




```python
list.remove(2)
list
```




    [3]



### 3.5 排序列表
sort()方法：永久性排序
sorted()方法：临时排序，按特定顺序显示列表元素，且不影响列表的原始排序


```python
cars = ['bmw','audi','totyota']
cars.sort()
cars
```




    ['audi', 'bmw', 'totyota']




```python
cars.sort(reverse=True)
cars
```




    ['totyota', 'bmw', 'audi']



### 3.6 列表长度
len(list)


```python
len(cars)
```




    3



### 3.7 遍历列表


```python
for iter in cars:
    print(iter)
```

    totyota
    bmw
    audi


### 3.8 数值列表
1. range(): 生成一系列的数字， range(begin, end, 步长=)
2. 最值：max(), min(), sum()
3. 列表解析：一行代码生成列表 list = [表达式 for value in range()]


```python
for value in range(1,5):
    print(value)
```

    1
    2
    3
    4



```python
for value in range(1, 11, 2):
    print(value)
```

    1
    3
    5
    7
    9



```python
list = [value*2 for value in range(1,11, 2)]
list
```




    [2, 6, 10, 14, 18]




```python
max(list)
```




    18




```python
min(list)
```




    2




```python
sum(list)
```




    50



### 3.9 列表切片
在列表中指定要使用的第一个元素和最后一个元素的索引


```python
list[1:3]
```




    [6, 10]




```python
list[:3]
```




    [2, 6, 10]




```python
list[1:]
```




    [6, 10, 14, 18]




```python
list[-2:]
```




    [14, 18]



#### 3.9.2 复制列表
列表的复制需要切片，直接用数组名赋值，导向的都是同一个列表


```python
list_new = list
list_new
```




    [2, 6, 10, 14, 18, 20]




```python
list_new2 = list[:]
```


```python
list.append(20)
list
```




    [2, 6, 10, 14, 18, 20, 20]




```python
list_new
```




    [2, 6, 10, 14, 18, 20, 20]




```python
list_new2
```




    [2, 6, 10, 14, 18, 20]



## 4 条件语句
1. 且或语句：and/or
2. 是否在列表中：in/not in


```python
age = 12
if age < 4:
    print(1)
elif age < 18:
    print(2)
else:
    print(3)
```

    2


## 5 字典
用{}表示，中间用逗号隔开


```python
alien_0 = {'color':'green', 'points':5}
alien_0
```




    {'color': 'green', 'points': 5}



### 5.1 访问



```python
alien_0['color']
```




    'green'



### 5.2 添加


```python
alien_0['x_pos'] = 0.2
alien_0
```




    {'color': 'green', 'points': 5, 'x_pos': 0.2}



### 5.3 修改字典的值


```python
if 'speed' not in alien_0:
    alien_0['speed'] = 'slow'
alien_0
```




    {'color': 'green', 'points': 5, 'x_pos': 0.2, 'speed': 'slow'}




```python
if alien_0['speed'] == 'slow':
    x_increment = 1
elif alien_0['speed'] == 'medium':
    x_increment = 2
else:
    x_increment = 3
x_increment
```




    1




```python
alien_0['speed'] = 'fast'
alien_0
```




    {'color': 'green', 'points': 5, 'x_pos': 0.2, 'speed': 'fast'}



### 5.4 删除
del方法


```python
del alien_0['speed']
alien_0
```




    {'color': 'green', 'points': 5, 'x_pos': 0.2}



### 5.5 遍历
1. for key, value in alien_0.item():
2. for keys in alien_0.keys():
3. for values in alien_0.values():


```python
for key, value in alien_0.items():
    print(key)
    print(value)
```

    color
    green
    points
    5
    x_pos
    0.2



```python
for keys in alien_0.keys():
    print(keys)
```

    color
    points
    x_pos



```python
for values in alien_0.values():
    print(values)
```

    green
    5
    0.2


## 6 用户输入和while循环

### 6.1 input()函数


```python
msg = input("Tell me something: ")
msg
```

    Tell me something: hello_world





    'hello_world'




```python
msg = input("Tell me your age: ")
int(msg)
```

    Tell me your age: 21





    21



## 7. 函数
### 7.1 无传参函数


```python
def hello():
    """x显示hello"""
    print('hello')
hello()
```

    hello


### 7.2 有传参函数
1. 位置实参
2. 关键字实参


```python
def hello(name, point=27):
    """显示hello name"""
    print('hello'+str(name)+'. your points is ' + str(point))
hello(',bmw')
```

    hello,bmw. your points is 27



```python
hello(', lili', 22)
```

    hello, lili. your points is 22



```python
hello(point=21, name=', lili')
```

    hello, lili. your points is 21


### 7.3 有返回值函数


```python
def get_formatted_name(first_name, last_name):
    full_name = first_name + ' ' + last_name
    return full_name.title()
musician = get_formatted_name('jimi', 'hendrix')
musician
```




    'Jimi Hendrix'




```python
def get_formatted_name(first_name, last_name = ''):
    full_name = first_name + ' ' + last_name
    return full_name.title()
musician = get_formatted_name('jimi')
musician
```




    'Jimi '



### 7.4 传列表函数
禁止列表修改：传入切片


```python
def greet_users(names):
    for index in range(0, len(names)):
        names[index] += 'hello'
        print(names[index])
usernames = ['n2','margit','ty']

greet_users(usernames)
usernames
```

    n2hello
    margithello
    tyhello

    ['n2hello', 'margithello', 'tyhello']



### 7.5 传递任意数量的实参
1. 形参名*toppings中的星号让Python创建一个名为toppings的空元组，并将收到的所有值都封装到这个元组中
2. 形参**user_info中的两个星号让Python创建一个名为user_info的空字典，并将收到的所有名称—值对都封装到这个字典中


```python
def make_pizza(*data):
    print(data)
make_pizza(2,3, "str", ['list','nice'])
```

    (2, 3, 'str', ['list', 'nice'])



```python
def build_profile(first, last, **user_info):
    """创建一个字典，其中包含我们知道的有关用户的一切"""
    profile = {}
    profile['first_name'] = first 
    profile['last_name'] = last
    for key, value in user_info.items():
        profile[key] = value
    return profile
user_profile = build_profile('albert', 'einstein',
                             location='princeton',
                             field='physics')
print(user_profile)
```

    {'first_name': 'albert', 'last_name': 'einstein', 'location': 'princeton', 'field': 'physics'}


## 8 类
### 8.1 创建和使用类


```python
class Dog():
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def sit(self):
        print(self.name.title()+" is now sitting")
    def roll(self):
        print(self.name.title()+" rolled")
```

方法__init__(): Python调用这个__init__()方法来创建Dog实例时，将自动传入实参self。每个与类相关联的方法调用都自动传递实参self，它是一个指向实例本身的引用，让实例能够访问类中的属性和方法


```python
my_dog = Dog(name='xiaohuang', age=2)
```


```python
my_dog.sit()
```

    Xiaohuang is now sitting



```python
my_dog.roll()
```

    Xiaohuang rolled


### 8.2 继承


```python
class Car(): 
    """一次模拟汽车的简单尝试"""
    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year
        self.odometer_reading = 0
    def get_descriptive_name(self):
        long_name = str(self.year)+' '+self.make+' '+self.model
        return long_name.title()
    def read_odometer(self):
        print("This car has "+str(self.odometer_reading)+" miles on it.")
    def update_odometer(self, mileage):
        if mileage >= self.odometer_reading:
            self.odometer_reading = mileage
        else:
            print("You can't roll back an odometer!")
    def increment_odometer(self, miles):
        self.odometer_reading+= miles
class ElectricCar(Car): 
    """电动汽车的独特之处"""
    def __init__(self, make, model, year): 
        """初始化父类的属性"""
        super().__init__(make, model, year) 

my_tesla = ElectricCar('tesla', 'model s', 2016) 
print(my_tesla.get_descriptive_name())
```

    2016 Tesla Model S


super()函数是一个特殊函数，帮助Python将父类和子类关联起来

## 9 文件和异常
### 9.1 将数据写入文件
1. 打开模式：w 写入模式；a 附加模式；r 只读模式


```python
file_name = 'pro.txt'
with open(file_name, 'w') as file_obj:
    file_obj.write("2\n")
    file_obj.write("3")
```

### 9.2 读取整个文件


```python
with open('pro.txt') as file_obj:
    contents = file_obj.read()
    print(contents.rstrip())
```

    2
    3



```python
with open("pro.txt") as file_obj:
    for line in file_obj:
        print(line.rstrip())
```

    2
    3



```python
with open("pro.txt") as file_obj:
    lines = file_obj.readlines()
    print(lines)
```

    ['2\n', '3']



```python
str = ''
for line in lines:
    str += line.rstrip()
str
```




    '23'



### 9.3 异常
使用try-except代码块


```python
try:
    print(5/0)
except ZeroDivisionError:
    print("your")
```

    your



## 10 常用模块
### 10.1 Json数据处理
使用json.dump()和json.load()

dir 方法查看支持的方法


```python
import json
numbers = [2,3,4,5,6]
filenames = 'number.json'
with open(filenames, "w") as f_obj:
    json.dump(numbers, f_obj)
```


```python
with open(filenames) as f_obj:
    number_read = json.load(f_obj)
number_read
```




    [2, 3, 4, 5, 6]



### 10.2 os.path模块
1. os.path.isfile(path) ：检测⼀个路径是否为普通⽂件
2. os.path.isdir(path)：检测⼀个路径是否为⽂件夹
3. os.path.exists(path)：检测路径是否存在
4. os.path.isabs(path)：检测路径是否为绝对路径
5. os.path.split(path)：拆分⼀个路径为 (head, tail) 两部分
6. os.path.join(a, *p)：使⽤系统的路径分隔符，将各个部分合成⼀个路径
7. os.path.abspath()：返回路径的绝对路径
8. os.path.dirname(path)：返回路径中的⽂件夹部分
9. os.path.basename(path)：返回路径中的⽂件部分
10. os.path.splitext(path)：将路径与扩展名分开
11. os.path.expanduser(path)：展开 '~' 和 '~user'


```python

```

### 10.3 os模块
- os.remove(path) 或 os.unlink(path) ：删除指定路径的⽂件。路径可以是全名，也可以是当
前⼯作⽬录下的路径。
- os.removedirs：删除⽂件，并删除中间路径中的空⽂件夹
- os.chdir(path)：将当前⼯作⽬录改变为指定的路径
- os.getcwd()：返回当前的⼯作⽬录
- os.curdir：表⽰当前⽬录的符号
- os.rename(old, new)：重命名⽂件
- os.renames(old, new)：重命名⽂件，如果中间路径的⽂件夹不存在，则创建⽂件夹
- os.listdir(path)：返回给定⽬录下的所有⽂件夹和⽂件名，不包括 '.' 和 '..' 以及⼦⽂件夹
下的⽬录。（'.' 和 '..' 分别指当前⽬录和⽗⽬录）
- os.mkdir(name)：产⽣新⽂件夹
- os.makedirs(name)：产⽣新⽂件夹，如果中间路径的⽂件夹不存在，则创建⽂件夹


```python
import os
os.getcwd()
```




    'C:\\Users\\Ganggui\\cv-python-ws'




```python
os.curdir
```




    '.'




```python
os.listdir()
```




    ['.ipynb_checkpoints',
     'cat.jpeg',
     'cat.mp4',
     'img01.jpg',
     'img02.jpg',
     'img03.jpg',
     'number.json',
     'pro.txt',
     'pyqt-01.ipynb',
     'Python01.ipynb',
     'Python_basci.ipynb',
     'Untitled.ipynb']



### 10.4 csv 模块


```python

```
