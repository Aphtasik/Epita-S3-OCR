def horizontalProjection(M):
    """
    Prend la matrice binarize M et realise la projection horizontale, un histogramme qui compte
    le nombre de 1 sur chaque ligne de la matrice M binarize

    Parametres :
    M : Matrixe binarize
    return : List : Liste correspondant au nb de 1 pour chaque ligne de pixel
    """
    lM = len(M)
    cM = len(M[0])
    L = []

    for i in range(lM): #on compte le nombre de 1
        sumInLineOfPxl = 0
        for j in range(cM):
            if M[i][j] == 1:
                sumInLineOfPxl+=1

        L.append(sumInLineOfPxl)

    return L


def verticalProjection(M):
    """
    Prend la matrice binarize M et realise la projection horizontale, un histogramme qui compte
    le nombre de 1 sur chaque colonne de la matrice M binarize.

    Parametres :
    M : Matrice binarize
    return : List : Liste correspondant au nb de 1 pour chaque colonne de pixel
    """
    lM = len(M)
    cM = len(M[0])
    L = []

    for i in range(cM): #on compte le nombre de 1
        sumInLineOfPxl = 0
        for j in range(lM):
            if M[j][i] == 1:
                sumInLineOfPxl+=1

        L.append(sumInLineOfPxl)

    return L


def lineSlice(M):
    """
    Prend une matrice binarize M (image), retire les lignes composees de 0 (interligne)
    pour renvoyer une liste de matrices (liste de ligne de texte).

    Parametres :
    M : Matrice : La matrice binarize a traiter
    return : liste de matrices : Une liste des lignes du texte
    """
    horizontalProjectedM = horizontalProjection(M)
    lHPM = len(horizontalProjectedM)
    matrixOfPixel = []
    matrixOfLines = []

    for i in range(lHPM): #Paroucours de la liste projection
        
        if horizontalProjectedM[i] != 0: #si il y a des 1 sur la ligne de pxls
            matrixOfPixel.append(M[i])

        elif horizontalProjectedM[i] == 0 and matrixOfPixel != []: #sinon, et que on a crée une ligne de texte
            matrixOfLines.append(matrixOfPixel)
            matrixOfPixel = []

    
    if matrixOfPixel != []: #a la fin, on ajoute les dernieres lignes de pixels
        matrixOfLines.append(matrixOfPixel)

    return matrixOfLines


def charSlice(M):
    """
    Prend une matrice binarize M (une ligne), retire les colonnes composees de 0 (petit espace entre chaque char)
    pour renvoyer une liste de matrices (liste de chars de la ligne).

    Parametres :
    M : Matrice : La matrice binarize a traiter
    return : liste de matrices : Une liste des chars de la ligne traite
    """
    verticalProjectedM = verticalProjection(M)
    lM = len(M) #lM = len(verticalProjectedM)
    cM = len(M[0])
    arrMinI = (-1)
    charsInLines = []

    for i in range(cM): #on parcours les colonnes de verticalProjected
        if verticalProjectedM[i] != 0 and arrMinI == (-1): #si y'a des 1 sur la colonne et il n'y avait rien avant => début de bout de char
            arrMinI = i

        elif verticalProjectedM[i] == 0 and arrMinI != (-1): #si y'a pas de 1 sur la colonne et il y avait quelque chose avant => fin du char
            charMatrix = [] #on cumulera toute les lignes de pixeles du char la dedans

            for j in range(lM): #on parcours la matrice entre arrMinI et i pour découper le char
                lineOfPixel = [] #une ligne de pixel du caractere
                for k in range(arrMinI, i):
                    lineOfPixel.append(M[j][k])
                charMatrix.append(lineOfPixel)
            charsInLines.append(charMatrix)
            arrMinI = (-1)

    
    if arrMinI != (-1):
        charMatrix = [] #on cumulera toute les lignes de pixeles du char la dedans

        for j in range(lM): #on parcours la matrice entre arrMinI et i pour découper le char
            lineOfPixel = [] #une ligne de pixel du caractere
            for k in range(arrMinI, i):
                lineOfPixel.append(M[j][k])
            charMatrix.append(lineOfPixel)
        charsInLines.append(charMatrix)
        arrMinI = (-1)
                
    return charsInLines


def binarizedToChars(M):
    """
    Assemble le tout pour renvoyer une liste de liste de matrice (oui c'est complique)
    correspondant aux chars pour chaque ligne du texte

    Parametres:
    M : Matrice : Image de base
    return : liste de liste de matrice : les chars pour chaque ligne du texte
    """
    matrixOfLine = lineSlice(M)
    listOfChars = []

    for i in range(len(matrixOfLine)):
        listOfChars.append(charSlice(matrixOfLine[i]))

    return listOfChars

        



MTest = [[0,0,0,0,0,0],[1,0,0,1,1,0],[1,0,0,0,1,0],[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,1,1,0],[0,0,0,0,0,0]]
print(horizontalProjection(MTest))
print()
print(verticalProjection(MTest))
print()
print(lineSlice(MTest))
print()

Mtest2 = [[1,0,0,1,1,0],[1,0,0,0,1,0],[0,0,0,1,1,0]]
print(charSlice(lineSlice(Mtest2)))
print()
print(binarizedToChars(MTest))
