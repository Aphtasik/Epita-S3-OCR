def horizontalProjection(M):
    """
    Prend la matrice M et réalise la projection horizontale.
    M : Matrixe binarizé et traité
    return : List : Liste correspondant au nb de 1 pour chaque ligne de pixel
    """
    lM = len(M)
    cM = len(M[0])
    L = []

    for i in range(lM):
        sumInLineOfPxl = 0
        for j in range(cM):
            if M[i][j] == 1:
                sumInLineOfPxl+=1

        L.append(sumInLineOfPxl)

    return L


def verticalProjection(M):
    """
    Prend la matrice M et réalise la projection vertical.
    M : Matrixe binarizé et traité
    return : List : Liste correspondant au nb de 1 pour chaque ligne de pixel
    """
    lM = len(M)
    cM = len(M[0])
    L = []

    for i in range(cM):
        sumInLineOfPxl = 0
        for j in range(lM):
            if M[j][i] == 1:
                sumInLineOfPxl+=1

        L.append(sumInLineOfPxl)

    return L


"""def lineSlice(M):
    horizontalProjectedM = horizontalProjection(M)
    lHPM = len(horizontalProjectedM)
    matrixOfPixel = []

    for i in range(lHPM):
        
        if horizontalProjectedM[i] != 0:
            matrixOfPixel.append(horizontalProjectedM[i])

        elif horizontalProjectedM[i]"""




MTest = [[1,0,0,1],[0,0,0,0],[0,1,1,1]]
print(horizontalProjection(MTest))
print()
print(verticalProjection(MTest))