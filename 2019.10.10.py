from test_func import *
# extra = {'city': 'Beijing', 'job': 'Engineer'}

#汉诺塔
def move(n, a, b, c):
    if n == 1:
        print(a, '-->', c)
    elif n >= 2:
        move(n-1,a,c,b)
        print(a, '-->', c)
        move(n-1,b,a,c)
    else:
        pass

if __name__ == '__main__':
    # move(2,'a','b','c')
# print(trim('  dasdasd  ')+'wwww')
#     print(findMinAndMax([1,2,3,4]))
#     print(judge([2,1,3,4]))
#     L1 = ['adam', 'LISA', 'barT']
#     L2 = normalize(L1)
#     pass
#     a=_odd_iter()
#     for n in primes():
#         if n<=100:
#             print(n)
#         else:
#             break
#     a=filter(is_palindrome,range(1,1000))
#     print(list(a))



