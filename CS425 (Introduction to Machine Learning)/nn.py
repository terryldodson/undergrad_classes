from sklearn import datasets
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense
from sklearn.preprocessing import LabelBinarizer
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score

# (0) Hide as many warnings as possible!
import os
import tensorflow as tf
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
tf.get_logger().setLevel('INFO')
tf.compat.v1.disable_eager_execution()

# (1) Read in the Iris dataset.
iris = datasets.load_iris()
iris_data_df = pd.DataFrame(data=iris.data, columns=iris.feature_names,
                       dtype=np.float32)

# (2) Create an encoder that "binarizes" target labels.
# e.g. We have 3 target classes. When we instantiate and use fit_transform() on an 
#      encoder, the function returns a N x 3 dataframe. Each row in this new dataframe 
#      will be equal to 0 or 1 based on whether the target class is true.
encoder = LabelBinarizer() 
target = encoder.fit_transform(iris.target)
iris_target_df = pd.DataFrame(data=target, columns=iris.target_names)

# (3) Perform test-train splits.
X_train,X_test,y_train,y_test = train_test_split(iris_data_df,
                                                 iris_target_df,
                                                 test_size=0.30)
 
 # (4) Perform standardization on our data.
scaler = MinMaxScaler(feature_range=(0,1))
X_train = pd.DataFrame(scaler.fit_transform(X_train),
                               columns=X_train.columns,
                               index=X_train.index)
X_test = pd.DataFrame(scaler.transform(X_test),
                           columns=X_test.columns,
                           index=X_test.index)


# (5) Build Keras models.
# # # # # # # # # # # # # # # # # 
#   Model 1:   A Baseline Model #
# # # # # # # # # # # # # # # # #
def BaselineModel():
    """ A sequential Keras model that has an input layer, one 
        hidden layer, and an output layer."""
    model = Sequential()
    model.add(Dense(4, input_dim=4, activation='sigmoid', name='layer_1'))
    model.add(Dense(3, activation='sigmoid', name='output_layer'))
     
    # Don't change this!
    model.compile(loss="categorical_crossentropy",
                  optimizer="adam",
                  metrics=['accuracy'])
    return model


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#   Model 2:   A Model with a Second Hidden Layer (sigmoid) #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
def AlternativeModel1():
    """ A sequential Keras model that has an input layer, two 
        hidden layers, and an output layer."""
    model = Sequential()
    model.add(Dense(4, input_dim=4, activation='sigmoid', name='layer_1'))
    model.add(Dense(4, activation='sigmoid', name='layer_2'))
    model.add(Dense(3, activation='sigmoid', name='output_layer'))
    
    # Don't change this!
    model.compile(loss="categorical_crossentropy",
                  optimizer="adam",
                  metrics=['accuracy'])
    return model

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#   Model 3:   A Model with a Second Hidden Layer (tanh)  #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
def AlternativeModel2():
    """ A sequential Keras model that has an input layer, two 
        hidden layers, and an output layer."""
    model = Sequential()
    model.add(Dense(4, input_dim=4, activation='sigmoid', name='layer_1'))
    model.add(Dense(4, activation='tanh', name='layer_2'))
    # model.add(Dense(10, activation='tanh', name='layer_3'))
    # model.add(Dense(10, activation='tanh', name='layer_4'))
    model.add(Dense(3, activation='sigmoid', name='output_layer'))
    
    # Don't change this!
    model.compile(loss="categorical_crossentropy",
                  optimizer="adam",
                  metrics=['accuracy'])
    return model

# (6) Model Evaluations
# Below, we build KerasClassifiers using our model definitions. Use verbose=2 to see
# real-time updates for each epoch.

# - - Model 1 - - 
estimator = KerasClassifier(
        build_fn=BaselineModel,
        epochs=200, batch_size=20,
        verbose=0)
kfold = KFold(n_splits=5, shuffle=True)
print("- - - - - - - - - - - - - ")
for i in range(0,10):
    results = cross_val_score(estimator, X_train, y_train, cv=kfold)
    print("(MODEL 1 : RUN " + str(i) +") Performance: mean: %.2f%% std: (%.2f%%)" % (results.mean()*100, results.std()*100))

# - - Model 2 - - 
estimator = KerasClassifier(
        build_fn=AlternativeModel1,
        epochs=200, batch_size=20,
        verbose=0)
kfold = KFold(n_splits=5, shuffle=True)
print("- - - - - - - - - - - - - ")
for i in range(0,10):
    results = cross_val_score(estimator, X_train, y_train, cv=kfold)
    print("(MODEL 2 : RUN " + str(i) +") Performance: mean: %.2f%% std: (%.2f%%)" % (results.mean()*100, results.std()*100))

# - - Model 3 - - 
estimator = KerasClassifier(
        build_fn=AlternativeModel2,
        epochs=200, batch_size=20,
        verbose=0)
kfold = KFold(n_splits=5, shuffle=True)
print("- - - - - - - - - - - - - ")
for i in range(0,10):
    results = cross_val_score(estimator, X_train, y_train, cv=kfold)
    print("(MODEL 3 : RUN " + str(i) +") Performance: mean: %.2f%% std: (%.2f%%)" % (results.mean()*100, results.std()*100))
