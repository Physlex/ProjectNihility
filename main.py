"""
    This is a reference for current devs to look over / reivew basic
    python while we get slowly geared up for actual development.

    This example code holds functions, conditionals, variable declaration and loops.
"""

"""
    FUNCTIONS
"""
def mainLoop(arg1: int) -> None:
    """
        Main loop for codebase
    """
    is_running = True
    count = 0
    while (is_running == True):
        if (count > arg1):
            is_running = False
            pass

        count += 1

        pass

    print(count)
    pass

def calc_mean(data_src: list[int]) -> int:
    """
        Example declaration of a for loop. Calculates the arithmetic mean of a list.  
    """
    samples_sum = int(-1)
    for i in range(len(data_src)):
        samples_sum += data_src[i]
        pass

    return (samples_sum / len(data_src))

"""
    MAIN
"""
if __name__ == "__main__":
    mean = calc_mean([1,2,3,4,5,6] * 100)
    mainLoop(mean)

    print("Wow")
    pass
