# Decoupe des lignes
def horizontalProjection(M):
    """
    Cette fonction prend une matrice M et realise une projection horizontale des 1 sur la gauche
    Elle sépare la matrice en sous matrice qui correspondent aux lignes
    Ne pas utiliser si l'image/matrice n'a pas été traité
    M : Matrice binarizé et traité
    return : matrice correspondant au projeté horizontale de M
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


#print(horizontalProjection(Mtest))


def lineSlice(M):
    horizontalProjectedM = horizontalProjection(M)
    matrixOfLines = []
    matrixOfPxl = []

    #si dans la projection on a un 0 a gauche, alors tout le reste de la liste est 0 -> interligne
    for i in range(len(horizontalProjectedM)):
        #si on a un 1 on commence a creer une matrice
        if horizontalProjectedM[i][0] == 1:
            matrixOfPxl.append(M[i])
        #si on a un 0, on a découpé notre ligne, on ajoute la matrice correspondant à une liste de matrice
        #il faut quand meme prendre en compte le cas ou on a plusieurs lignes vide et ne pas ajouter de liste vide
        elif horizontalProjectedM[i][0] == 0 and matrixOfPxl != []:
            matrixOfLines.append(matrixOfPxl)
            matrixOfPxl = []
    #on ajoute la fin si la matrice de pxl n'est pas vide
    if matrixOfPxl != []:
        matrixOfLines.append(matrixOfPxl)

    return matrixOfLines


#print(lineSlice(horizontalProjection(Mtest), Mtest))


# Decoupe des char (meme technique mais en projeté verticale)
def verticalProjection(M):
    """
    Réalise la projection verticale de 1 pour isoler les characteres
    M : Matrice correspondant à une ligne de texte
    return : matrice correspondant au projeté vertical de M
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
    for i in range(cM):
        indexOfOne = 0
        for j in range(lM):
            if M[j][i] == 1:
                projectionM[indexOfOne][i] = 1
                indexOfOne += 1

    return projectionM


#print(verticalProjection(Mtest))


def charSlice(M):
    verticalProjectedM = verticalProjection(M)
    matrixOfLines = []
    matrixOfPxl = []
    lM = len(verticalProjectedM)
    cM = len(verticalProjectedM[0])
    arrMinI = 0 #index qui sert à ne pas ajouter le début de liste dans la matrice


    for i in range(cM):
        #si le i d'avant était sur une section, on décale notre arrMinI
        if verticalProjectedM[0][i] == 1 and arrMinI == (-1):
            arrMinI = i

        #on ajoute tout dans la matrice ssi le i d'avant n'était pas déja sur une section
        elif verticalProjectedM[0][i] == 0 and arrMinI != -1:
            matrixOfPxl = []
            for j in range(lM):
                listOfPxl = []
                for k in range(arrMinI, i):
                    listOfPxl.append(M[j][k])
                matrixOfPxl.append(listOfPxl)
            matrixOfLines.append(matrixOfPxl)
            arrMinI = -1

    #pour ajouter les derniere lignes
    if arrMinI != -1:
        matrixOfPxl = []
        for j in range(lM):
            listOfPxl = []
            for k in range(arrMinI, cM):
                listOfPxl.append(M[j][k])
            matrixOfPxl.append(listOfPxl)
        matrixOfLines.append(matrixOfPxl)

    return matrixOfLines


def binarizedToChars(M):
    matrixOfLines = lineSlice(M)

    slicedCharsPerLine = []
    for i in range(len(matrixOfLines)):
        slicedCharsPerLine.append(charSlice(matrixOfLines[i]))

    return slicedCharsPerLine


Mtest = [[1,1,0,0,0],[1,1,0,1,0],[0,0,0,0,0],[1,1,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[1,0,0,1,0]]
print(binarizedToChars(Mtest))