def f():
    x = 0
    if x == 0:
        print 99
        x = 17
        def g():
            if x:
                print x
                return
            else:
                print 2
        g()
        print 101
f()
print 17

def p():
    print 111
    return 222
print p()
