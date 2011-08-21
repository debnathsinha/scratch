def cross(A,B):
    "Cross products of elements in a and b"
    return [ a+b for a in A for b in B ]

digits = '123456789'
rows = 'ABCDEFGHI'
cols = digits
squares = cross(rows, cols)

