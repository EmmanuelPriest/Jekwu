'''Module to find the area of cirles'''


from math import pi
'''importing math module'''

def circle_area(r):
    '''Finding the area of circles'''
    if type(r) not in [int, float]:
        raise TypeError("The radius must be a non-negative real number")

    if r < 0:
        raise ValueError("The radius cannot be negative")
    return (pi * (r ** 2))

if __name__ == "__main__":
    #Testing function
    radii = [2.1, 0, -3, 2 + 5j, True, "radius"]
    msg = "Area of circles with r = {radius} is {area}."
    for r in radii:
        A = circle_area(r)
        print(msg.format(radius=r, area=A))
