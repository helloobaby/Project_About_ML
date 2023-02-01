from sklearn.neighbors import KNeighborsClassifier
from sklearn.datasets import load_iris

X, y = load_iris(return_X_y=True)
print(X)
print(y)

# k的值随便选
knn_model = KNeighborsClassifier(n_neighbors=5)
# 训练
knn_model.fit(X,y)

# 分类结果应该是2
print(knn_model.predict([[6.3,3.5,5.4,2.4]]))
# 分类结果应该是0
print(knn_model.predict([[5.0,3.5,1.4,0.2]]))

# 多一个特征报错
#print(knn_model.predict([[6.3,3.5,5.4,2.4,3.5]]))