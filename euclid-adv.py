#!/usr/bin/python3

def bezout(a, b):
    '''An implementation of extended Euclidean algorithm.
    Returns integer x, y and gcd(a, b) for Bezout equation:
        ax + by = gcd(a, b).
    '''
    x, xx, y, yy = 1, 0, 0, 1
    while b:
        print ("начало цикла")
        print ("b=", b)

        q = a // b
        print ("q=", q)

        a, b = b, a % b
        print ("a=", a, "b=", b)

        x, xx = xx, x - xx*q
        print ("x=", x, "xx=", xx)


        y, yy = yy, y - yy*q
        print ("y=", y, "yy=", yy)

        print ("конец цикла")
        
    return (x, y)
    

a=17*17*17
b=53

(c,d)=bezout(a,b)

print ("")
print ("a=",a, "b=", b )
print ("(a) *", c, "+ (b) *",d,"=", a*c+b*d,"=НОД(a,b)")
print ("x=", c, "y=", d)


