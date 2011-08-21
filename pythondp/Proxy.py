class Proxy:
    def __init__(self, subject):
        self.__subject = subject
    
    def __getattr__(self, name):
        print "getting attribute"
        return getattr( self.__subject, name)

class RGB:
    def __init__(self, red, green, blue):
        self.__red = red
        self.__green = green
        self.__blue = blue
        
    def Red(self):
        return self.__red

    def Green(self):
        return self.__green
    
    def Blue(self):
        return self.__blue


rgb = RGB(100, 192, 240)

p = Proxy(rgb)

#print rgb.Red()
#print rgb.Green()
#print rgb.Blue()
print p.Red()
print p.Green()
print p.Blue()
