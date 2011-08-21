class Complex():
    def __init__(self, real, imaginary):
        self.real = real
        self.imaginary = imaginary

    def __str__(self):
        return str(self.real) + "+ i" + str(self.imaginary)

    def __add__(self, other):
        return Complex(self.real + other.real, self.imaginary + self.imaginary)

x = Complex(1,2)
y = Complex(3,4)

print x
z = x + y

print z
