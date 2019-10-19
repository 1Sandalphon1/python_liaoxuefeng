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




