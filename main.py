"""
    or: a or b
    and: a and b
    equivalence: a == b
    relational: >, <, <=, >=
"""

"""
    FUNCTIONS
"""
def mainLoop():
    """
        Main loop for codebase
    """
    is_running = True
    count = 0
    while (is_running == True):
        count = count + 1
        if (count == 2):
            is_running = False

        print("True")
    pass

"""
    MAIN
"""
if __name__ == "__main__":
    mainLoop()
    print("Wow")
    pass
