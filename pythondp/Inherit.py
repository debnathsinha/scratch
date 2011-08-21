class Base(object):
    def __init__(self):
        print "init base"
        
    def foo(self):
        print "foo from base"

    def staticFoo():
        print "static foo from Base"

    stat = staticmethod(staticFoo)


class Derived(Base):
    def __init__(self):
        print "init derived"

    def foo(self):
        print "foo from derived"

    def staticFoo():
        print "static foo from Derived"

    stat = staticmethod(staticFoo)


x = Derived()
x.foo()
y = Base()
y.foo()
Base.stat()
Derived.stat()
