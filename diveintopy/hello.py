print "Hello World"

def print_hello():
    """Printing doc for hello world

    This function will print hello world
    """
    print "Hello World from function"

def join_params(params):
    """Joins the parameters"""
    return ";".join(["%s=%s" %(k,v) for k,v in params.items()])

if __name__ == "__main__":
    print_hello()
    my_params = { "server" : "localhost",
                  "user" : "root",
                  "passwd" : "root"
                  }
    print join_params(my_params)
