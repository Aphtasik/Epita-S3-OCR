def gris (image):
    (largeur, hauteur) = image.size
    for i in range (hauteur):
        for j in range (largeur):
            (r, g, b) = image.getpixel((i, j))
            luminosite = 0,299 * r + 0,587 * g + 0,114 * b
            image.putpixel((i, j), (luminosite, luminosite, luminosite))

def seuil (image):
    moyenne = 0
    nb = 0
    (largeur, hauteur) = image.size
    for i in range (hauteur):
        for j in range (largeur):
            (r, g, b) = image.getpixel((i, j))
            moyenne += r
            nb += 1
    return (moyenne / nb)
            
def blackAndWhite (newImage):
    s = seuil(newImage)
    (largeur, hauteur) = newImage.size
    for i in range (hauteur):
        for j in range (largeur):
            (r, g, b) = newImage.getpixel((i, j))
    if r >= s :
        newImage.putpixel((i, j), (255, 255, 255))
    else :
        newImage.putpixel((i, j), (0, 0, 0))
