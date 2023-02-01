#https://scikit-learn.org/stable/modules/classes.html#module-sklearn.tree
#https://scikit-learn.org/stable/modules/tree.html#tree

from sklearn.tree import DecisionTreeClassifier
from sklearn.datasets import load_iris

X, y = load_iris(return_X_y=True)

tree = DecisionTreeClassifier()

tree.fit(X,y)

# 分类结果应该是2
print(tree.predict([[6.3,3.5,5.4,2.4]]))
# 分类结果应该是0
print(tree.predict([[5.0,3.5,1.4,0.2]]))