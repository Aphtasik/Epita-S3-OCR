from PIL import Image #Import avec le module Pillow pour le Traitement d'image
from numpy import array

### I - Chargement de l'image et nuance de gris

image = Image.open("HelloWorld.bmp")
bwImage = image.convert('L') #convertion en nuance de gris

### II - Convertion en noir et blanc (0/1)
"""
Il faut convertir en nuance de gris. Il faut trouver les valeurs de gris
la plus élevé et la plus basse. On creer ensuite une liste de 0/1,
0 pour les valeurs basse de nuance de gris et 1 pour les hautes
"""


greyArray = array(bwImage) #On transforme l'image en matrice #BUG: comprendre ce que renvoie greyArray et greyList
greyList = greyArray.tolist() #Puis en liste
print(greyArray)
    
#Considerant que l'image n'est que du texte unicolore
#sur un fond unicolore, on sépare le texte du fond en cherchant
#les valeurs min et max de la liste. 
maxi = max(greyList)[0]
mini = min(greyList)[0]
middle = (mini+maxi) // 2

#creation de la liste faite de 0 et 1
binList = []

for i in range(len(greyList)):
    if greyList[i] <= middle: #on prend le middle pour être sur de pas prendre le fond et le texte en mm temps #BUG voire greyArray et greyList
        binList.append(0)
    else:
        binList.append(1)



