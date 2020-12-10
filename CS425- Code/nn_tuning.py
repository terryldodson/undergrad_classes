# Use scikit-learn to grid search the number of neurons
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import Dense, Dropout
from sklearn.preprocessing import LabelBinarizer
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
from sklearn import datasets
from sklearn.model_selection import GridSearchCV
from keras.constraints import maxnorm

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

# (3) Perform test-train splits. Random seed selected randomly + permits reproducibility.
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
#   General Model               #
# # # # # # # # # # # # # # # # #
def DynamicModel(neurons=1, activation_func='sigmoid'):
    """ A sequential Keras model that has an input layer, one 
        hidden layer with a dymanic number of units, and an output layer."""
    model = Sequential()
    model.add(Dense(neurons, input_dim=4, activation=activation_func, name='layer_1'))
    model.add(Dense(3, activation='sigmoid', name='output_layer'))
     
    # Don't change this!
    model.compile(loss="categorical_crossentropy",
                  optimizer="adam",
                  metrics=['accuracy'])
    return model


# (6) Evaluation + HyperParameter Search
# Below, we build KerasClassifiers using our model definitions. Use verbose=2 to see
# real-time updates for each epoch.
model = KerasClassifier(
    build_fn=DynamicModel, 
    epochs=200, 
    batch_size=20, 
    verbose=0)

# (7) Define a set of unit numbers (i.e. "neurons") and activation functions
# that we want to explore.
param_grid = [
    {
        'activation_func': ['linear', 'sigmoid', 'relu', 'tanh'], 
        'neurons': [1, 5, 10, 15, 20, 25, 30]
    }
]

# (8)   Send the Keras model through GridSearchCV, and evaluate the performnce of every option in 
#       param_grid for the "neuron" value.
grid = GridSearchCV(estimator=model, param_grid=param_grid, n_jobs=-1, cv=3)
grid_result = grid.fit(X_train, y_train)

# (9) Print out a summarization of the results.
print("Best: %f using %s" % (grid_result.best_score_, grid_result.best_params_))
means = grid_result.cv_results_['mean_test_score']
stds = grid_result.cv_results_['std_test_score']
params = grid_result.cv_results_['params']
for mean, stdev, param in zip(means, stds, params):
    print("%f (%f) with: %r" % (mean, stdev, param))