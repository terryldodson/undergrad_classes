import numpy as np
import pandas as pd
import pylab as pl
from sklearn import svm, datasets
from sklearn.model_selection import train_test_split 
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import classification_report
from sklearn.metrics import confusion_matrix, accuracy_score
from sklearn.svm import SVC

# By default, Sklearn forces warnings into your terminal.
# Here, we're writing a dummy function that overwrites the function
# that prints out numerical warnings.
# (You probably don't want to do this in any of your projects!)
def warn(*args, **kwargs):
    pass
import warnings
warnings.warn = warn

# Load the IRIS dataset from Sklearn
# And convert it to a dataframe that we can manage with column names.
iris = datasets.load_iris()
#print(iris)
iris = pd.DataFrame(data= np.c_[iris['data'], iris['target']],
                    columns= iris['feature_names'] + ['target'])

# Define the two parameters we want to use.
features = ['petal length (cm)', 'petal width (cm)']
#features = ['sepal length (cm)', 'sepal width (cm)']

# Separate our features from our targets.
X = iris[features]
Y = iris[['target']]

# Use Sklearn to get splits in our data for training and testing.
x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.8, random_state=0)
y_train_converted = y_train.values.ravel()

# Now, we create several instances of SVCs that utilize varying kernels.
# We're not normalizing our data here because we want to plot the support vectors.
svc     = svm.SVC(kernel='linear').fit(x_train, y_train)
poly_svc_one = svm.SVC(kernel='poly', C=100, degree=1).fit(x_train, y_train_converted)
poly_svc_two = svm.SVC(kernel='poly', C=100, degree=2).fit(x_train, y_train_converted)
poly_svc_three = svm.SVC(kernel='poly', C=10, degree=3).fit(x_train, y_train_converted)
rbf_svc_one = svm.SVC(kernel='rbf', C=10, gamma=0.1).fit(x_train, y_train_converted)
rbf_svc_two = svm.SVC(kernel='rbf', C=100, gamma=0.1).fit(x_train, y_train_converted)
rbf_svc_three = svm.SVC(kernel='rbf', C=10, gamma=0.5).fit(x_train, y_train_converted)
rbf_svc_four = svm.SVC(kernel='rbf', C=100, gamma=0.5).fit(x_train, y_train_converted)

# Now, we run our test data through our trained models.
predicted_linear = svc.predict(x_test)
predicted_poly_one = poly_svc_one.predict(x_test)
predicted_poly_two = poly_svc_two.predict(x_test)
predicted_poly_three = poly_svc_three.predict(x_test)
predicted_rbf_one = rbf_svc_one.predict(x_test)
predicted_rbf_two = rbf_svc_two.predict(x_test)
predicted_rbf_three = rbf_svc_three.predict(x_test)
predicted_rbf_four = rbf_svc_four.predict(x_test)

# Print our accuracies.
print("SVM + Linear \t\t-> " + str(accuracy_score(y_test, predicted_linear)))
print("SVM + Poly (D=1)\t-> " + str(accuracy_score(y_test, predicted_poly_one)))
print("SVM + Poly (D=2)\t-> " + str(accuracy_score(y_test, predicted_poly_two)))
print("SVM + Poly (D=3)\t-> " + str(accuracy_score(y_test, predicted_poly_three)))
print("SVM + RBF-10/0.1 \t-> " + str(accuracy_score(y_test, predicted_rbf_one)))
print("SVM + RBF-100/0.1 \t-> " + str(accuracy_score(y_test, predicted_rbf_two)))
print("SVM + RBF-10/0.5 \t-> " + str(accuracy_score(y_test, predicted_rbf_three)))
print("SVM + RBF-100/0.5 \t-> " + str(accuracy_score(y_test, predicted_rbf_four)))


# # # # # # # # # # # # #
# PLOTTING CODE STARTS  #
# # # # # # # # # # # # #

# create a mesh to plot in
h=.02 # step size in the mesh
x_min, x_max = X[features[0]].min()-1, X[features[0]].max()+1
y_min, y_max = X[features[1]].min()-1, X[features[1]].max()+1
xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                     np.arange(y_min, y_max, h))

# title for the plots
titles = ['SVC with linear kernel',
          'Poly (C=10; D=2)',
          'Poly (C=100; D=2)',
          'Poly (C=10; D=3)',
          'RBF (C=10; G=0.1)',
          'RBF (C=100; G=0.1)',
          'RBF (C=10; G=0.5)',
          'RBF (C=100; G=0.5)']


# If we wanted to set a color scheme for our plot, we could do so here.
# For example:
#   pl.set_cmap(pl.cm.Accent)

for i, clf in enumerate((svc, poly_svc_one, poly_svc_two, poly_svc_three, rbf_svc_one, rbf_svc_two, rbf_svc_three, rbf_svc_four)):
    # Plot the decision boundary. For that, we will asign a color to each
    # point in the mesh [x_min, m_max]x[y_min, y_max].
    pl.subplot(2, 4, i+1)
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])

    # Put the result into a color plot
    Z = Z.reshape(xx.shape)
    #pl.set_cmap(pl.cm.Accent)
    
    # Apply 
    pl.contourf(xx, yy, Z)
    pl.axis('tight')

    # Plot also the training points
    pl.scatter(X[features[0]], X[features[1]], c=Y['target'], edgecolor='black')

    pl.title(titles[i])

pl.axis('tight')
pl.show()

# # # # # # # # # # # # #
# PLOTTING CODE Ends  #
# # # # # # # # # # # # #


# # # # # # # # # # # # # # # # # # # # #
# Coarse Grid Search                    #
#   - Broad sweep of hyperparemeters.   #
# # # # # # # # # # # # # # # # # # # # #

# Set the parameters by cross-validation
tuned_parameters = [
    {
        'kernel': ['linear'], 
        'C': [1, 10, 100, 1000]
    },
    {
        'kernel': ['poly'], 
        'degree': [2, 3, 4],
        'C': [1, 10, 100, 1000]
    },
    {
        'kernel': ['rbf'], 
        'gamma': [1e-3, 1e-4],
        'C': [1, 10, 100, 1000]
    }
]


scores = ['precision', 'recall']

for score in scores:
    print("# Tuning hyper-parameters for %s" % score)
    print()

    clf = GridSearchCV(
        SVC(), tuned_parameters, scoring='%s_macro' % score
    )
    clf.fit(x_train, y_train)

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
