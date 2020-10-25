from PIL import Image
image = Image.open("qf.png")

"""
Toutes les fonctions ici présentent ont été faites par Quentin Fournel.
"""

"""
Cette fonction passe l'image en niveaux de gris.
"""
def gris(image):
    (largeur, hauteur) = image.size
    for i in range (largeur):
        for j in range (hauteur):
            if len(image.getpixel((i, j))) == 4 :
                (r, g, b, x) = image.getpixel((i, j))
                luminosite = int(0.299 * r + 0.587 * g + 0.114 * b)
                image.putpixel((i, j), (luminosite, luminosite, luminosite, x))
            else :
                (r, g, b) = image.getpixel((i, j))
                luminosite = int(0.299 * r + 0.587 * g + 0.114 * b)
                image.putpixel((i, j), (luminosite, luminosite, luminosite))
    image.save("test2.png")
    
image2 = Image.open("test2.png")

"""
Cette fonction construit une liste contenant le nombre de pixel par couleur.
"""
def histo(image2):
    L = 256*[0]
    (largeur, hauteur) = image2.size
    for i in range (largeur):
        for j in range (hauteur):
            if len(image2.getpixel((i, j))) == 4 :
                (r, g, b, x) = image2.getpixel((i, j))
            else :
                (r, g, b) = image2.getpixel((i, j))
            L[r] += 1
    return L

"""
Cette fonction tri une liste.
"""
def trier(L):
    for i in range(len(L)) :
        for j in range(len(L)-1) :
            if L[j] > L[j + 1] :
                (L[j], L[j+1]) = (L[j+1], L[j])
    return L

"""
Cette fonction filtre une image grâce à la technique du filtre médian.
"""
def filtre(image2):
    (largeur, hauteur) = image2.size
    for i in range (largeur):
        for j in range (hauteur):
            L = []
            if len(image2.getpixel((i, j))) == 4 :
                (r, g, b, x) = image2.getpixel((i, j))
                if i != 0 and i != largeur - 1 and j != 0 and j != hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i == 0 and j != 0 and j != hauteur - 1 :
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i == largeur - 1 and j != 0 and j != hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i, j - 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i != 0 and i != largeur - 1 and j == 0 :
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i != 0 and i != largeur - 1 and j == hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i == 0 and j == 0 :
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image3.putpixel((i, j), (med, med, med, x))
                elif i == 0 and j == hauteur - 1 :
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i == largeur - 1 and j == 0 :
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
                elif i == largeur - 1 and j == hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i, j - 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med, x))
            else :
                (r, g, b) = image2.getpixel((i, j))
                if i != 0 and i != largeur - 1 and j != 0 and j != hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i == 0 and j != 0 and j != hauteur - 1 :
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i == largeur - 1 and j != 0 and j != hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i, j - 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i != 0 and i != largeur - 1 and j == 0 :
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i != 0 and i != largeur - 1 and j == hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i == 0 and j == 0 :
                    L.append(image2.getpixel((i, j + 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L.append(image2.getpixel((i + 1, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image3.putpixel((i, j), (med, med, med))
                elif i == 0 and j == hauteur - 1 :
                    L.append(image2.getpixel((i, j - 1)))
                    L.append(image2.getpixel((i + 1, j - 1)))
                    L.append(image2.getpixel((i + 1, j)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i == largeur - 1 and j == 0 :
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i - 1, j + 1)))
                    L.append(image2.getpixel((i, j + 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
                elif i == largeur - 1 and j == hauteur - 1 :
                    L.append(image2.getpixel((i - 1, j - 1)))
                    L.append(image2.getpixel((i - 1, j)))
                    L.append(image2.getpixel((i, j - 1)))
                    L2 = trier(L)
                    med = L2[len(L2)//2]
                    image2.putpixel((i, j), (med, med, med))
    image2.save("test3.png")
    
image3 = Image.open("test3.png")

"""
Cette fonction compte le nombre de pixel d'une image.
"""
def nbPixel(image3):
    (largeur, hauteur) = image3.size
    return largeur * hauteur

"""
Cette fonction calcul un seuil qui servira pour passer l'image en noir et blanc.
"""
def seuil(image3):
    n = nbPixel(image3)
    h = histo(image3)
    res = 0
    for i in range(len(h)):
        res += (i * h[i])
    return res / n
        
"""
Cette fonction passe l'image en noir et blanc.
"""
def blackAndWhite(image3):
    m = seuil(image3)
    (largeur, hauteur) = image3.size
    for i in range (largeur):
        for j in range (hauteur):
            if len(image3.getpixel((i, j))) == 4 :
                (r, g, b, x) = image3.getpixel((i, j))
                if r > m :
                    image3.putpixel((i, j), (255, 255, 255, x))
                else :
                    image3.putpixel((i, j), (0, 0, 0, x))
            else :
                (r, g, b) = image3.getpixel((i, j))
                if r > m :
                    image3.putpixel((i, j), (255, 255, 255))
                else :
                    image3.putpixel((i, j), (0, 0, 0))
    image3.save("test3.png")