class Singleton:
    __single = None
    def __init__(self):
        if Singleton.__single:
            raise Singleton.__single

        Singleton.single = self


class Child(Singleton):
    def foo(self):
        print "child"

class Junior(Singleton):
    def foo(self):
        print "junior"


s = Singleton()
s1 = Singleton()

c = Child()
j = Junior()
