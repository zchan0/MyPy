def f():
    return 233

def g():
    def h():
        def p():
            c = f()
            return c
        return p()
    return h()

print g()
