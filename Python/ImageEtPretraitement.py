from PIL import Image #Import avec le module Pillow pour le Traitement d'image
from numpy import array

### I - Chargement de l'image et nuance de gris

image = Image.open("HelloWorld.bmp")
#image.show()
bwImage = image.convert('L') #convertion en nuance de gris

### II - Convertion en noir et blanc (0/1)
"""
Il faut convertir en nuance de gris. Il faut trouver les valeurs de gris
la plus élevé et la plus basse. On creer ensuite une liste de 0/1,
0 pour les valeurs basse de nuance de gris et 1 pour les hautes
"""

greyArray = array(bwImage)

"""
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
"""


### III - Decoupe
# Decoupe des lignes
def lineDetection(M):
    """
    Cette fonction prend une matrice M et realise une projection horizontale des 1 sur la gauche
    Elle sépare la matrice en sous matrice qui correspondent aux lignes
    Ne pas utiliser si l'image/matrice n'a pas été traité
    M : Matrice binarizé et traité
    return : projectionM : matrice correspondant au projeté horizontale de M
    """
    lM = len(M)
    cM = len(M[0])

    #Construction de la matrice projection à la bonne taille
    listOfZero = [0 for i in range(cM)]
    projectionM = []
    for i in range(lM):
        L = listOfZero[:]
        projectionM.append(L)

    #projection horizontale
    for i in range(lM):
        indexOfOne = 0
        for j in range(cM):
            if M[i][j] == 1:
                projectionM[i][indexOfOne] = 1
                indexOfOne += 1

    return projectionM


Mtest = [[1,0,1],[0,0,1],[1,0,0]]
print(lineDetection(Mtest))


def lineSlice(M):
    """
    M : matrice ayant subis le projeté horizontale
    return : liste de matrices correspondant aux lignes d'ecriture de l'image
    """
    lM = len(M)
    cM = len(M[0])
    matrixOfLines = []
    matrixOfPxl = []
    isFullOfZero = True

    for i in range(lM):
        j = 0
        isFullOfZero = True

        #si la liste est plein de 0 alors c'est une interligne
        while isFullOfZero and j<cM:
            if M[i][j] == 1:
                isFullOfZero = False
            j += 1
        
        #si c'est plein on ajoute a la matrixOfPxl pour recreer la rangé de pixel
        if not isFullOfZero:
            matrixOfPxl.append(M[i])
        else: #une interligne donc notre ligne est complete on peut tout ajouter à la matrice de lignes
            if matrixOfPxl != []: #si la lgine de pixels d'avant n'était pas deja une interligne
                matrixOfLines.append(matrixOfPxl)
                matrixOfPxl = []

    return matrixOfLines


Mtest = Mtest = [[0,0,1],[0,0,1],[0,0,0],[0,0,0],[1,0,0],[1,0,0],[0,0,0],[1,1,1],[1,1,1]]
print(lineSlice(Mtest))


# Todo: Découpe des char (meme technique mais en projeté verticale)