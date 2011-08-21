class Singleton():
    def __init__(self, w, block):
        print "constructing"
        self._w = w
        self._block = block

    def __getattr__(self, n):
        if n in self._block:
            raise AttributeError, n
        else:
            print "have attrib " . n
            self.n

    def _foobar(self):
        print "foobarred"
    
x = Singleton('foo', 'bar')
if hasattr(Singleton, 'foo'):
    print "I have attribute foo"
else:
    print "I have attribute bar"


x._foobar()
#x.foo
getattr(x,'foobar')
#x.bar()
