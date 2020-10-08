from PIL import Image #Import avec le module Pillow pour le Traitement d'image
from numpy import array

### I - Chargement de l'image et nuance de gris

image = Image.open("HelloWorld.bmp")
image.show()
bwImage = image.convert('L') #convertion en nuance de gris

### II - Convertion en noir et blanc (0/1)
"""
Il faut convertir en nuance de gris. Il faut trouver les valeurs de gris
la plus élevé et la plus basse. On creer ensuite une liste de 0/1,
0 pour les valeurs basse de nuance de gris et 1 pour les hautes
"""

greyArray = array(bwImage)
print(greyArray)
    
#Considerant que l'image n'est que du texte unicolore
#sur un fond unicolore, on sépare le texte du fond en cherchant
#les valeurs min et max de la liste.

def findextrem (mat):
    maxi = mat[0][0]
    mini = mat[0][0]
    for i in mat:
        for j in range(1,len(mat[0])):
            if i[j] > maxi:
                maxi = i[j]
            if i[j] < mini:
                mini = i[j]
    return maxi,mini


extrem = (findextrem(greyArray))[0]

middle = (extrem[0]-extrem[1])*2

#creation de la liste faite de 0 et 1

def buildbinlist (mat):
    binList = []
    for i in mat:
        for j in i:
            if mat[i][j] <= middle: #on prend le middle pour être sur de pas prendre le fond et le texte en mm temps #BUG voire greyArray et greyList
                binList.append(0)
            else:
                binList.append(1)
    return binList


print(builbinlist(greyArray))
