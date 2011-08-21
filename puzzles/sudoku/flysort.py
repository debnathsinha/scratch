"""Sort the flights in the order of the journey
Assumption is that the trip is acyclic, since a cyclic trip
could have begun anywhere and ended anywhere
"""

unordered = [("pit","nyc"), ("nyc","bos"), ("sjc","pit")]

sources = {}
destinations = {}
for (src,dst) in unordered:
    if src in sources:
        sources[src] += 1
    else:
        sources[src] = 1
    if dst in destinations:
        destinations[dst] += 1
    else:
        destinations[dst] = 1


for src in sources:
    if src not in destinations:
        print "The originating source is: ",src
        origSrc = src

for dst in destinations:
    if dst not in sources:
        print "The final destination is: ",dst
        finalDst = dst

def findDestination(source):
    for (src,dst) in unordered:
        if src == source:
            return dst

def orderTrip(origSrc):
    src = origSrc
    while( src != finalDst ):
        print "Trip: %s->%s"%(src,findDestination(src))
        src = findDestination(src)

orderTrip(origSrc)
