def power(x,n=2):
    y=1
    if not isinstance(x,(float,int)):
        raise TypeError('bad operand')
    while n>0:
        y=y*x
        n=n-1
    return y

def calc(*nums):
    t=0
    for n in nums:
        t=t+n
    return t

def person(name,age,**kw):
    print('name',name,'age',age,'extra',kw)

def trim(s):
    i=0
    j=0
    while i==0:
        if s[j] == ' ':
            j+=1
        else:
            i=1
    s=s[j:]
    i = 0
    j = -1
    while i==0:
        if s[j] == ' ':
            j-=1
        else:
            i=1
    return s[:len(s)+j+1]
# another helper
def helper(s):
    for i in range(len(s)):
        if s[i]!=' ':
            s=s[i:]

def findMinAndMax(L):
    if len(L) == 0:
        return (None,None)
    else:
        max = L[0]
        min = L[0]
        for i in L:
            if i > max:
                max = i
            if i <min:
                min = i
    return (max,min)

def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'

#杨辉三角
def triangles():
    L=[1]
    while True:
        yield L
        L=[0]+L+[0]
        L = [L[i]+L[i+1] for i in range(len(L)-1) ]

def judge(a):
    le=len(a)
    stack=[]
    stack.extend(range(1,a[0]))
    count=a[0]
    for num in a[1:]:
        if not stack:
            stack.extend(range(count+1,num))
            count=num
            continue
        if num!=stack[-1] and num<count:
                return False
        else:
                if num==stack[-1]:
                    del stack[-1]
                else:
                    stack.extend(range(count+1,num))
                    count=num
        return True
#利用map()函数，把用户输入的不规范的英文名字，变为首字母大写，其他小写的规范名字。
def normalize(name):
    flag=0
    for i in name:
        for j in i:
            if ord(j)>=97 and ord(j)<=122 and flag==0:
                j=j.swapcase()
            elif ord(j)>=65 and ord(j)<=90 and flag!=0:
                j=j.swapcase()
            else:
                pass
            flag+=1
    return name

#计算出素数
def _odd_iter():
    n=1
    while True:
        n=n+2
        yield n

#定义筛选器
def _not_divisible(n):
    return lambda x:x%n>0

def primes():
    yield 2
    it = _odd_iter()
    while True:
        n=next(it)
        yield n
        it = filter(_not_divisible(n),it)

#筛选出回数
def is_palindrome(n):
    n='%d' %n #转化为字符串
    length=len(n)
    len_n=length//2
    for a in range(len_n):
        if n[a] != n[length-1-a]:
            return False
    return True

#返回函数
def lazy_sum(*args):
    def sum():
        ax=0
        for i in args:
            ax=i+ax
        return ax
    return sum

def count():
    fs = []
    for i in range(1, 4):
        def f():
             return i*i
        fs.append(f)
    return fs

def createCounter():


def test():
    a=[1]
    a[0]=a[0]+1
    return a





