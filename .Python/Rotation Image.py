from PIL import Image
from math import *

image = Image.open("OL.jpg")
    
"""function that will allow us to rotate an image that is not straight."""
"""two arguments, the image as well as the angle of the rotation to be carried out"""
def rotate(image, angle): 
    (l, c) = image.size
    cos_angle = cos(angle)
    sin_angle = sin(angle)
    """We look for the middle of the image to rotate from the middle of the image."""
    midx = l/2
    midy = c/2
    """two variables that we will use to manage overruns"""
    xdebordmax = 0
    ydebordmax = 0
    """The first step is to calculate the maximum overrun in x and y"""
    for x in range (l):
        distx = x - midx
        for y in range (c):
            disty = y - midy
            x2 = (distx * cos_angle - disty * sin_angle + midx)
            y2 = (distx * sin_angle + disty * cos_angle + midy)
            x2 = int (x2)
            y2 = int (y2)
            if (0 >= x2 or x2 >= l or x2 >= c and 0 >= y2 or y2 >= c or y2 >= l):
                """We calculate our overflow"""
                xdebord = x2 - l
                ydebord = y2 - c
                """and we see if it is higher than our maximum overflow."""
                if (xdebordmax < xdebord):
                    xdebordmax = xdebord
                if (ydebord > ydebordmax):
                    ydebordmax = ydebord
            elif (0 >= x2 or x2 >= l or x2 >= c and 0 < y2 and y2 < c and y2 < l ):
                xdebord = x2 - l
                if (xdebordmax < xdebord):
                    xdebordmax = xdebord
            else:
                ydebord = y2 - c
                if (ydebord > ydebordmax):
                    ydebordmax = ydebord
    """A new image is created with larger coordinates so that there is no overshoot."""
    imagearrivee=Image.new('RGB',(l +  3* xdebordmax, c+ 3 * ydebordmax))
    (l2,c2) = imagearrivee.size
    """we remove each pixel from the old image to make it rotate and then put it on our new image create"""
    for x in range (l):
        """A rotation is carried out in relation to the centre of the image."""
        distx = x - midx
        for y in range (c):
            disty = y - midy
            x2 = (distx * cos_angle - disty * sin_angle + midx) + xdebordmax
            y2 = (distx * sin_angle + disty * cos_angle + midy) + ydebordmax
            """We transform our x2, y2 into int in order to have our values enter our matrix."""
            x2 = int (x2)
            y2 = int (y2)
            pixel = image.getpixel((x, y))
            """We check, to reassure ourselves, that our values do not come out of our matrix."""
            if (x2 < l2 and x2 < c2 and y2 < c2 and y2 < l2):
                """and finally we put our pixel in its place"""
                imagearrivee.putpixel((x2,y2), pixel)
    imagearrivee.save("OL_rotate.jpg")
    

rotate(image, 45)

