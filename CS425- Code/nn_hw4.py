from sklearn import datasets
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from sklearn.model_selection import GridSearchCV
from sklearn.svm import SVC
from keras.layers import Dense
from sklearn.preprocessing import LabelBinarizer
from keras.wrappers.scikit_learn import KerasClassifier
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
from sklearn.metrics import confusion_matrix, accuracy_score

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
def BaselineModel(activation, units):
    """ A sequential Keras model that has an input layer, one 
        hidden layer, and an output layer."""
    model = Sequential()
    model.add(Dense(units=4, input_dim=4, activation='sigmoid', name='input_layer'))
    model.add(Dense(units=4, activation='sigmoid', name='hidden_layer_1'))
    model.add(Dense(units=4, activation='sigmoid', name='hidden_layer_2'))
    model.add(Dense(units=4, activation='sigmoid', name='hidden_layer_3'))
    model.add(Dense(units=4, activation='sigmoid', name='hidden_layer_4'))
    model.add(Dense(units=3, activation='sigmoid', name='output_layer'))
     
    # Don't change this!
    model.compile(loss="categorical_crossentropy",
                  optimizer="adam",
                  metrics=['accuracy'])
    return model

# (6) Model Evaluations
# Below, we build KerasClassifiers using our model definitions. Use verbose=2 to see
# real-time updates for each epoch.

model = KerasClassifier(build_fn=BaselineModel, verbose=0)

# - - Model 1 - - 
estimator = KerasClassifier(
        build_fn=BaselineModel,
        epochs=200, batch_size=20,
        verbose=0)
kfold = KFold(n_splits=5, shuffle=True)
print("- - - - - - - - - - - - - ")
for i in range(0,10):
    results = cross_val_score(estimator, X_train, y_train, cv=kfold)
    print("(MODEL 1 : RUN " + str(i) +") Performance mean: %.2f%% std: (%.2f%%)" % (results.mean()*100, results.std()*100))
    
# # # # # # # # # # # # #
# PLOTTING CODE Ends  #
# # # # # # # # # # # # #


# # # # # # # # # # # # # # # # # # # # #
# Coarse Grid Search                    #
#   - Broad sweep of hyperparemeters.   #
# # # # # # # # # # # # # # # # # # # # #

# Set the parameters by cross-validation
'''tuned_parameters = [
    {
        'units': [1, 2, 5, 10, 15, 20, 25, 30],
        'activation': ['linear', 'sigmoid', 'tanh', 'relu']
    }
]'''

activation = ['relu', 'tanh', 'sigmoid', 'linear']
units = [1, 2, 5, 10, 15, 20, 25, 30]
param_grid = dict(activation=activation, units=units)

scores = ['precision', 'recall']

for score in scores:
    print("# Tuning hyper-parameters for %s" % score)
    print()

    clf = GridSearchCV(
        estimator=model, param_grid=param_grid, scoring='%s_macro' % score
    )
    clf.fit(X_train, y_train)

    print("Best parameters set found on development set:")
    print()
    print(clf.best_params_)
    print()
    print("Grid scores on development set:")
    print()
    means = clf.cv_results_['mean_test_score']
    stds = clf.cv_results_['std_test_score']
    for mean, std, params in zip(means, stds, clf.cv_results_['params']):
        print("%0.3f (+/-%0.03f) for %r"
              % (mean, std * 2, params))
    print()

    print("Detailed classification report:")
    print()
    print("The model is trained on the full development set.")
    print("The scores are computed on the full evaluation set.")
    print()
    y_true, y_pred = y_test, clf.predict(x_test)
    print(classification_report(y_true, y_pred))
    print()
