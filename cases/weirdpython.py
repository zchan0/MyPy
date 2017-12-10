x = 5

def f():
    print x
    x = 1

def g():
    x = 1
    print x

def h():
    def p():
        y = x + 1
        print y
    p()

g()
h()
f()
