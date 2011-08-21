"""
4 1 7 |3 6 9 |8 2 5 
6 3 2 |1 5 8 |9 4 7
9 5 8 |7 2 4 |3 1 6 
------+------+------
8 2 5 |4 3 7 |1 6 9 
7 9 1 |5 8 6 |4 3 2 
3 4 6 |9 1 2 |7 5 8 
------+------+------
2 8 9 |6 4 3 |5 7 1 
5 7 3 |2 9 1 |6 8 4 
1 6 4 |8 7 5 |2 9 3 
"""

test = [[4,1,7,3,6,9,8,2,5],
[6,3,2,1,5,8,9,4,7],
[9,5,8,7,2,4,3,1,6],
[8,2,5,4,3,7,1,6,9],
[7,9,1,5,8,6,4,3,2],
[3,4,6,9,1,2,7,5,8],
[2,8,9,6,4,3,5,7,1],
[5,7,3,2,9,1,6,8,4],
[1,6,4,8,7,5,2,9,3]]

def inRange(n):
    if n < 10 and n > 0:
        return True
    else:
        return False

def firstSeen(searchList, elem):
    if row in searchList:
        return False
    else:
        searchList += [elem]
        return True

def updateSums(n,pos):
    rowSum[pos[0]] += n
    colSum[pos[1]] += n
    sqSum[pos[0]%8 * 3 + pos[1]%8] += n


if __name__ == '__main__':
    print "Solving sudoku"
for i in range(0,8):
    for j in range(0,8):
            elem = test[i][j]
            box_index = int((i / 3)) * 3 + (j/3)
            #if !(inRange(elem) and firstSeen(rows[i],elem) and firstSeen(cols[j],elem) and firstSeen(boxes[ box_index ],elem)):
                #print "Not valid"
            boxes[box_index] = 1
            print boxes[box_index]
    
                
