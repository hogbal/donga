import random
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import MinMaxScaler

# dataset setting
DATAPATH = "./data"
synthetic_train_path = f"{DATAPATH}/synthetic_data_train.txt"
synthetic_test_path = f"{DATAPATH}/synthetic_data_test.txt"

synthetic_train_df = pd.read_csv(synthetic_train_path, names=['x','y','z','class'])
synthetic_test_df = pd.read_csv(synthetic_test_path, names=['x','y','z','class'])

synthetic_train_x = synthetic_train_df[['x','y','z']].values
synthetic_train_y = synthetic_train_df[['class']].values.reshape(-1)
synthetic_test_x = synthetic_test_df[['x','y','z']].values
synthetic_test_y = synthetic_test_df[['class']].values.reshape(-1)

scaler = MinMaxScaler()

normalization_synthetic_train_x = scaler.fit_transform(synthetic_train_x)
normalization_synthetic_test_x = scaler.fit_transform(synthetic_test_x)

real_train_path = f"{DATAPATH}/datatraining.txt"
real_test_path = f"{DATAPATH}/datatset2.txt"

real_train_df = pd.read_csv(real_train_path)
real_test_df = pd.read_csv(real_test_path)

real_train_x = real_train_df[['Temperature','Light','CO2']].values
real_train_y = real_train_df[['Occupancy']].values.reshape(-1)
real_test_x = real_test_df[['Temperature','Light','CO2']].values
real_test_y = real_test_df[['Occupancy']].values.reshape(-1)

scaler = MinMaxScaler()

normalization_real_train_x = scaler.fit_transform(real_train_x)
normalization_real_test_x = scaler.fit_transform(real_test_x)

class perceptron:
    def __init__(self, feature=3):
        self.w = np.full(feature, random.random() * 2 - 1) # -1 ~ 1 random
        self.b = 0
    
    def forward(self, x):
        return np.dot(x, self.w) + self.b
    
    def predict(self, x):
        return np.where(self.forward(x) > 0, 1, 0)
    
    def fit(self, epochs, train=None, learing_rate=0.01):
        predicts = []
        
        for epoch in range(epochs):
            # train
            for x, y in zip(train[0],train[1]):
                update = learing_rate * (y - self.predict(x))
                self.w += update * x
                self.b += update
            
            # count
            count = 0
            for x, y in zip(train[0],train[1]):
                if(self.predict(x) != y):
                    count += 1
            predicts.append(count)
        return predicts

# sysnthetic dataset
synthetic_p = perceptron(feature=3)
history = synthetic_p.fit(30, train=(normalization_synthetic_train_x, synthetic_train_y), learing_rate=0.001)
plt.plot(history)
plt.xlabel('lteration')
plt.ylabel('count')
plt.show()

print("====synthetic 학습X====")

confusion_matrix_10 = []

for i in tqdm(range(10)):
    synthetic_p = perceptron(feature=3)
    
    synthetic_y_predict = []
    for x in normalization_synthetic_test_x:
        synthetic_y_predict.append(int(synthetic_p.predict(x)))
    
    confusion_matrix_10.append(confusion_matrix(synthetic_test_y, synthetic_y_predict))

confusion_matrix_result = confusion_matrix_10[0]
for i in range(1,10):
    confusion_matrix_result += confusion_matrix_10[i]
    
confusion_matrix_result = confusion_matrix_result//10
print("\n====confusion matrix====")
print(confusion_matrix_result)

print("\n====synthetic 학습O====")

confusion_matrix_10 = []

for i in tqdm(range(10)):
    synthetic_p = perceptron(feature=3)
    synthetic_p.fit(30, train=(normalization_synthetic_train_x, synthetic_train_y), learing_rate=0.001)
    
    synthetic_y_predict = []
    for x in normalization_synthetic_test_x:
        synthetic_y_predict.append(int(synthetic_p.predict(x)))
    
    confusion_matrix_10.append(confusion_matrix(synthetic_test_y, synthetic_y_predict))

confusion_matrix_result = confusion_matrix_10[0]
for i in range(1,10):
    confusion_matrix_result += confusion_matrix_10[i]
    
confusion_matrix_result = confusion_matrix_result//10
print("\n====confusion matrix====")
print(confusion_matrix_result)

# real dataset
real_p = perceptron(feature=3)
history = real_p.fit(30, train=(normalization_real_train_x, real_train_y), learing_rate=0.001)
plt.plot(history)
plt.xlabel('lteration')
plt.ylabel('count')
plt.show()

print("\n====real 학습X====")

confusion_matrix_10 = []

for i in tqdm(range(10)):
    real_p = perceptron(feature=3)
    
    real_y_predict = []
    for x in normalization_real_test_x:
        real_y_predict.append(int(real_p.predict(x)))
    
    confusion_matrix_10.append(confusion_matrix(real_test_y, real_y_predict))

confusion_matrix_result = confusion_matrix_10[0]
for i in range(1,10):
    confusion_matrix_result += confusion_matrix_10[i]

confusion_matrix_result = confusion_matrix_result//10
print("\n====confusion matrix====")
print(confusion_matrix_result)

print("\n====real 학습O====")

confusion_matrix_10 = []

for i in tqdm(range(10)):
    real_p = perceptron(feature=3)
    real_p.fit(30, train=(normalization_real_train_x, real_train_y), learing_rate=0.001)
    
    real_y_predict = []
    for x in normalization_real_test_x:
        real_y_predict.append(int(real_p.predict(x)))
    
    confusion_matrix_10.append(confusion_matrix(real_test_y, real_y_predict))

confusion_matrix_result = confusion_matrix_10[0]
for i in range(1,10):
    confusion_matrix_result += confusion_matrix_10[i]

confusion_matrix_result = confusion_matrix_result//10
print("\n====confusion matrix====")
print(confusion_matrix_result)