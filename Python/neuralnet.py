import numpy as np

# AUTHOR: Mathis Guilbaud

def relu(z):
    """
    Fonction d'activation (comparaison au seuil)
    """
    a = np.maximum(0,z)
    return a


def init_param(layer_sizes): #layer sizes => list of layer sizes
    """
    Attribue des poids et biais sur chaque neuronne
    à l'aide d'un dictionnaire ou W représente les poids,B les biais
    et str(i) la couche de neurones concernée
    """
    param = {}
    for i in range(1,len(layer_sizes)):
        param['W' + str(i)] = (np.random.randn(layer_sizes[i],layer_sizes[i-1]) * 0.01)
        param['B' + str(i)] = (np.random.randn(layer_sizes[i],1) * 0.01)
    return param


def feedforward(X_train,param): #param => dict [weights x][biases y] X_train = input data
    """
    Prend valeur d'entrainement, puis applique en fonction de la layer concernée la formule
    permettant d'obtenir un résultat (fn(input * weight + bias))
    on distingue 3 cas:
    la première couche de neurone qui ne possède ni biais ni poids, on ne leur applique donc rien
    les couche médianes auxquel on applique la formules en prenant en entrée la sortie de la couche précédente ('A'+str(i-1))
    la couche de fin auxquel on applique uniquement input * poid + biais
    à noter que les élément dont la clé est A sont les réponse après la fn d'activation
    et les élément dont la clé est Z corresponde uniquement au calcul poid * input + biais
    """
    layers = len(param)//2
    values = {}
    for i in range(1,layers+1): #applying activation fn fn(x * w) + b for all data
        if i == 1:
            values['Z'+str(i)]= np.dot(param['W'+str(i)],X_train) + param['B'+str(i)]
            values['A'+str(i)]= relu(values['Z'+str(i)])
        else:
            values['Z'+str(i)]= np.dot(param['W'+str(i)],values['A'+str(i-1)]) + param['B'+str(i)]
            if i ==layers:
                values['A'+str(i)]= values['Z'+str(i)]
            else:
                values['A'+str(i)]= relu(values['Z'+str(i)])
    return values #values => dict with all data post-nn


def compute_cost(values,Y_train): #values => NN result Y_train => result expected
    """
    calcul de la fonction de coût du réseau, il s'agit d'une valeur témoignant de l'efficacité du réseau
    pour le dernier élément dont la clé est A on applique (resultat - résultats attendu)**2
    ce qui nous donne une valeur que l'on souhaite proche de 0
    """
    layers = len(values)//2
    Y_pred = values['A'+str(layers)]
    cost = 1/(2*len(Y_train)) * np.sum(np.square(Y_pred - Y_train)) #compute cost fn for each val (get_val-expec_val)**2
    return cost


def backprop(param,values,X_train,Y_train): #compute the gradient of all weights and biases
    """
    Créé un dictionnaire grads qui possède pour chaque élément une matrice représentant les corrections des poids/biais de la layer i 
    """
    layers = len(param)//2
    m = len(Y_train)
    grads = {}
    for i in range(layers,0,-1):
        if i == layers:
            dA = 1/m *(values['A'+str(i)] - Y_train)
            dZ = dA
        else:
            dA = np.dot(param['W'+str(i+1)].T,dZ)
            dZ = np.multiply(dA,np.where(values['A'+str(i)]>=0,1,0))
        if i ==1:
            grads['W'+str(i)] = 1/m * np.dot(dZ,X_train.T)
            grads['B'+str(i)] = 1/m * np.sum(dZ,axis=1,keepdims=True)
        else:
            grads['W'+str(i)] = 1/m * np.dot(dZ,values['A'+str(i-1)].T)
            grads['B'+str(i)] = 1/m * np.sum(dZ,axis=1,keepdims=True)
    return grads


def update_param(param,grads,learning_rate): #update all weight and biases
    """
    Applique les corrections calculées précédemment a chaque poids/biais de chaque layer
    en utilisant la formule w/b - cste d'apprentissage * gradient
    """
    layers = len(param)//2
    param_updated = {}
    for i in range(1,layers+1):
        param_updated['W'+str(i)]= param['W'+str(i)]- learning_rate * grads['W'+str(i)]
        param_updated['B'+str(i)]= param['B'+str(i)]- learning_rate * grads['B'+str(i)]
    return param_updated


def model(X_train,Y_train,layer_sizes,epoch,learning_rate):
    """
    fonction afin de simplifier la création du réseau de neurone,
    elle initialise le réseau et l'entraîne en utilisant les précédente fonction
    puis retourne le dictionnaire de paramètres une fois entrainé
    """
    param = init_param(layer_sizes)
    for i in range(epoch):
        values = feedforward(X_train.T,param)
        cost = compute_cost(values,Y_train.T)
        grads = backprop(param,values,X_train.T,Y_train.T)
        param = update_param(param,grads,learning_rate)
    return param

def predict(X,param):
    """
    fonction de prédiction, il s'agit tout simplement d'un feedforward avec des paramètres optimisés
    la réponse finale du réseau correspont au dernier élément ayant pour clé A
    """
    values = feedforward(X.T,param)
    prediction = values['A'+str(len(values)//2)].T
    return prediction

def xor(): #BUG tend toujours vers 0,5
    X = np.array([[0,1],[1,0],[1,1],[0,0]])
    Y = np.array([[1],[1],[0],[0]])
    layer_sizes= np.array([2,2,1])
    epoch = 1000
    learning_rate = 0.03
    param= model(X,Y,layer_sizes,epoch,learning_rate)
    print(predict(np.array([[0,1]]),param))

def alphabet():#TODO non testée, en attente de dataset
    X=[]
    Y=[
        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1],
    ]
    result = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    layer_sizes= np.array([256,40,40,26])
    epoch = 1000
    learning_rate = 0.03
    param = model(X,Y,layer_sizes,epoch,learning_rate)
    predict_letter = []
    print(predict(np.array([predict_letter]),param))


#X = np.array([[0,1,0,0,0,0,0,0,0,0,0,0,0],[1,0,0,0,0,0,0,0,0,0,0,0,0],[1,1,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0]])
#layer_sizes= np.array([13,2,1])
#epoch = 1000
#learning_rate = 0.03
#param = model(X,Y,layer_sizes,epoch,learning_rate)
#x = predict(np.array([[0,1]]),param)
#x = predict(np.array([[1,1,0,0,0,0,0,0,0,0,0,0,0]]),param)
#print(x)
