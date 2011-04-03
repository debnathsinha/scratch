class Car:
    def __new__(self):
        print "New Car"

    def __init__(self):
        print "constructing car"
    
    def drive(self):
        print "driving car"

    def tuneEngine(self):
        print "Tuning engine"


class RestrictCar(Car):
    def __init__(self, w, block):
        print "Restricting Car"
        self._w = w
        self._block = block
        self._foo = "foobar"

    def drive(self):
        print "Driving restricted car"

    def __getattr__(self, n):
        print "Getting attribute" + str(n)
        raise AttributeError

c = Car()
c.drive()

rc = RestrictCar("drive","tuneEngine")
rc.drive()
print rc._foo
try:
    md = getattr(rc, "drive1")
except AttributeError:
    print "No attribute"
try:
    if md:
        md()
    else:
        print "No attrib" + str(md)
except NameError:
    print "No such name"
