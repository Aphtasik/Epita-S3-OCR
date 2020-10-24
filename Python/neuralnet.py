import numpy as np

def relu(z):
    a = np.maximum(0,z)
    return a

def init_param(layer_sizes): #layer sizes => list of layer sizes
    param = {}
    for i in range(1,len(layer_sizes)):
        param['W' + str(i)] = (np.random.randn(layer_sizes[i],layer_sizes[i-1]) * 0.01)
        param['B' + str(i)] = (np.random.randn(layer_sizes[i],1) * 0.01)
    return param

def feedforward(X_train,param): #param => dict [weights x][biases y] X_train = input data
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
    layers = len(values)//2
    Y_pred = values['A'+str(layers)]
    cost = 1/(2*len(Y_train)) * np.sum(np.square(Y_pred - Y_train)) #compute cost fn for each val (get_val-expec_val)**2
    return cost


def backprop(param,values,X_train,Y_train): #compute the gradient of all weights and biases
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
    layers = len(param)//2
    param_updated = {}
    for i in range(1,layers+1):
        param_updated['W'+str(i)]= param['W'+str(i)]- learning_rate * grads['W'+str(i)]
        param_updated['B'+str(i)]= param['B'+str(i)]- learning_rate * grads['B'+str(i)]
    return param_updated

### organize to make this sh*t works together

def model(X_train,Y_train,layer_sizes,epoch,learning_rate):
    param = init_param(layer_sizes)
    for i in range(epoch):
        values = feedforward(X_train.T,param)
        cost = compute_cost(values,Y_train.T)
        grads = backprop(param,values,X_train.T,Y_train.T)
        param = update_param(param,grads,learning_rate)
    return param

def predict(X,param):
    values = feedforward(X.T,param)
    prediction = values['A'+str(len(values)//2)].T
    return prediction

X = np.array([[0,1],[1,0],[1,1],[0,0]])
Y = np.array([[1],[1],[0],[0]])
layer_sizes= np.array([2,2,1])
epoch = 1000
learning_rate = 0.03
param = model(X,Y,layer_sizes,epoch,learning_rate)
predict(np.array([[0],[1]]),param)
