from PIL import Image #Import avec le module Pillow pour le Traitement d'image
from numpy import array

### I - Chargement de l'image
image = Image.open("HelloWorld.bmp")
x, y = image.size #taille de l'image

### II - Convertion en noir et blanc (0/1)
"""
Il faut convertir en nuance de gris. Il faut trouver les valeurs de gris
la plus élevé et la plus basse. On creer ensuite une liste de 0/1,
0 pour les valeurs basse de nuance de gris et 1 pour les hautes
"""
 
bwImage = image.convert('L') #convertion nuance de gris
bwImage.show() #a suppr