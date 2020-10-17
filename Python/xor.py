import random
import numpy as np

def sigmoid(x): #fonction sigmoide
    return 1/(1+np.exp(-x))

def sigmoid_prime(x): #derivee de la fonction sigmoide
    return sigmoid(x)*(1-sigmoid(x))


class Network:
    def __init__(self,sizes): # sizes <=> liste dont la longeur = nb layer et size[i] = nb neuron sur cette layer
        self.num_layer = len(sizes)
        self.sizes = sizes
        self.biases = [np.random.randn(y,1) for y in sizes[1:]]
        self.weights = [np.randn(y,x) for x,y in zip(sizes[:-1],sizes[1:])]

    def feedforward(self,a): # renvoie le resultat du réseau, a est l'input
        for b,w in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w,a)+b)
        return a

    def training(self,training_data,epochs,mini_batch_size,eta,test_data=None):
        """
        training data: liste de tuple (x,y) x = input data y = resultats attendu
        epoch: nombre de cycle d'entrainement
        test_data: mettre a True pour avoir un display des résultats
        eta : learning rate
        """
        if test_data:
            n_test = len(test_data)
        n = len(training_data)
        for i in xrange(epochs):
            random.shuffle(training_data) #melange des input_data
            mini_batches = [training_data[k:k + mini_batch_size] for k in xrange(0,n,mini_batch_size)]
            for mini_batch in mini_batches:
                self.update_mini_batch(mini_batch,eta)
            if test_data:
                print "Epoch {0}: {1} / {2}".format(i,self.evaluate(test_data),n_test)
            else:
                print "Epoch {0} complete".format(i)


    def update_mini_batch(self,mini_batch,eta): # change les biais et poids du réseau a l'aide de backpropagation
       mat_b = [np.zeros(b.shape) for b in self.biases]
       mat_w = [np.zeros(w.shape) for w in self.weights]
       for x,y in mini_batch:
           delta_mat_b, delta_mat_w = self.backprop(x,y)
           mat_b = [nb+dnb for nb, dnb in zip(mat_b, dalta_mat_b)]
           mat_w = [nw+dnw for nw, dnw in zip(mat_w, delta_mat_w)]
        self.weights = [w-(eta/len(mini_batch))*nw for w,nw in zip(self.weights,mat_w)]
        self.biases = [b-(eta/len(mini_batch))*nb for b,nb in zip(self.biases,mat_b)]

    def backprop(self,x,y):
        """
        retourne un tuple représentant l'appication de la descente de gradient
        pour la fonction d'efficacité du reseau
        """
        mat_b = [np.zeros(b.shape) for b in self.biases]
        mat_w = [np.zeros(w.shape) for w in self.weights]
        activation = x
        activations = [x] #enregistre toutes les activation layer par layer
        zs = [] #liste qui enregistre tous les vecteur de correction pour le réseau
        for b,w in zip(self.biases,self.weights):
            z = np.dot(w,activation) + b
            zs.append(z)
            activation = sigmoid(z)
            activations.append(activation)
            delta = self.cost_derivative(activations[-1],y) * sigmoid_prime(zs[-1])
            mat_b[-1] = delta
            mat_w[-1] = np.dot(delta,activations[-2].transpose())
            for layer_n in xrange(2,self.num_layers):
                z = zs[-layer_n]
                sp = sigmoid_prime(z)
                delta = np.dot(self.weights[-layer_n+1].transpose(),delta) * sp
                mat_b[layer_n]= delta
                mat_w[-layer_n] = np.dot(delta,activation[-layer_n-1].transpose())
            return (mat_b,mat_w)

    def evaluate(self,test_data):
        test_results = [(np.argmax(self.feedforward(x)),y) for (x,y) in test_data]
        return sum(int(x==y) for (x,y) intest_results)

    def cost_derivative(self,output_activation, y):
        return (output_activation-y)
 
