import numpy as np

inputs = np.array([[0, 0],
                    [0, 1],
                    [1, 0],
                    [1, 1]])

outputs = np.array([0,1,1,0])
outputs.reshape((4,1))

weights = np.array([[0.1],[0.2]])
bias = 0.3

def sigmoid(x,deriv=False):
    if deriv:
        return sigmoid(x) * (1- sigmoid(x))
    return 1/(1+np.exp(-x))

for epochs in range(10000):
    input_arr = inputs
    weighted_sum = np.dot(input_arr,weights) + bias
    first_output = sigmoid(weighted_sum)

    error = first_output - outputs
    total_error = np.square(np.subtract(first_output,outputs)).mean()
    #print(total_error)

    first_der = error
    second_der = sigmoid(first_output,True)
    derivative = first_der * second_der
    t_input = inputs.T
    final_derivative = np.dot(t_input,derivative)

    weights = weights - 0.05 * final_derivative

    for i in derivative:
        bias = bias - 0.05 * i

print(weights)
print(bias)

prediction = np.array([0,1])

result = np.dot(prediction,weights) + bias
res = sigmoid(result)

print(res)
