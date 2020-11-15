import matplotlib.pyplot as plt #sert pour l'affichage de graphes
import tensorflow as tf #librairie de réseau de neurone
import numpy as np #opération sur les matrice
import sys

IMG_WIDTH = 15
IMG_HEIGHT= 15

#TODO ajouter une dataset de caractères

target_name = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9']

#création du modele

model = tf.keras.models.Sequential()
model.add(tf.keras.layers.Flatten(input_shape=[IMG_WIDTH,IMG_HEIGHT])) #transfome la matrice a deux dimensions qu'est l'image en array a une dimension

#ajout des différentes couches de neurones

model.add(tf.keras.layers.Dense(256, activation="relu")) #première couche de neurones percepteurs
model.add(tf.keras.layers.Dense(128, activation="relu")) #couche intermediaire de neurones
model.add(tf.keras.layers.Dense(36, activation="softmax")) #couche des neurones résultats, softmax permet d'avoir une somme des proba des neurones de sortie a 1

#compilation du modele 

model.compile(
        loss="sparse_categorical_crossentropy",
        optimizer="sgd"
        metrics["accuracy"]
        )

#training du modele

history = model.fit(images,targets,epoch=10) #entrainement du modele avec images la matrices d'images target l'array de sortie attendues et epoch le nombre d'entrainements

#stat

loss_curve = history.history["loss"]
accuracy_curve = history.history["acc"]
plt.plot(loss_curve)
plt.title("Loss")
plt.show()

plt.plot(accuracy_curve)
plt.title("accuracy")
plt.show()

