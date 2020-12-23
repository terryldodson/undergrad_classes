import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler

#reading in provided data
data = pd.read_csv("auto-mpg.csv")

#creating a list of the features I would like to extract
col_list = ["cylinders", "displacement",
            "horsepower", "weight", "acceleration", "year", "origin"]

x = data.loc[:, col_list].values
y = data.loc[:,['mpg']].values

# Standardizing the features
x = StandardScaler().fit_transform(x)


pca = PCA(n_components=4)
principalComponents = pca.fit_transform(x)
principalDf = pd.DataFrame(data = principalComponents
             , columns = ['principal component 1', 'principal component 2', 'principal component 3', 'principal component 4'])

finalDf = pd.concat([principalDf, data[['mpg']]], axis = 1)

'''
fig = plt.figure(figsize = (8,8))
ax = fig.add_subplot(1,1,1) 
ax.set_xlabel('Principal Component 1', fontsize = 15)
ax.set_ylabel('Principal Component 2', fontsize = 15)
ax.set_title('2 component PCA', fontsize = 20)
targets = ['Iris-setosa', 'Iris-versicolor', 'Iris-virginica']
colors = ['r', 'g', 'b']
for target, color in zip(targets,colors):
    indicesToKeep = finalDf['target'] == target
    ax.scatter(finalDf.loc[indicesToKeep, 'principal component 1']
               , finalDf.loc[indicesToKeep, 'principal component 2']
               , c = color
               , s = 50)
ax.legend(targets)
ax.grid()
plt.show()'''

print("How much of our variance is explained?")
print(pca.explained_variance_ratio_)
print()
print() 

print("Which features matter most?")
print(abs(pca.components_))