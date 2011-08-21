class AbstractBase(object):
    def orgMethod(self):
        self.doThis()
        self.doThat()

class Concrete(AbstractBase):
    def doThis(self):
        print "doing this"

    def doThat(self):
        print "doing that"

x = Concrete()
x.orgMethod
