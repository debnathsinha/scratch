def buildConnectionString(params):
    """Function documentation.
    Return string"""
    return ";".join(["%s=%s" % (k,v) for k,v in params.items()])

def fib(n):
    print "n=",n
    if n > 1:
        return fib(n-1)+ fib(n-2)
    else:
        return 0


if __name__ == "__main__":
    myParams = {"server":"myserver", \
                    "dbase":"beerfund", \
                    "uid":"sinha", \
                    "pwd":"secret" \
                    }
    print buildConnectionString(myParams)

    print "fib=", fib(5)
