TRAIN_X_PATH = "/kaggle/input/blg454e-fall-2022-term-project/train_features.csv"
TRAIN_Y_PATH = "/kaggle/input/blg454e-fall-2022-term-project/train_targets.csv"
TEST_X_PATH = "/kaggle/input/blg454e-fall-2022-term-project/test_features.csv"

OUTPUT_PATH = "/kaggle/working/submission.csv"

import math
import random as r
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.preprocessing import PolynomialFeatures
from sklearn.pipeline import Pipeline
from sklearn.linear_model import Ridge
from sklearn.model_selection import KFold
from sklearn.metrics import mean_squared_error as mse

r.seed(1)
    
def preprocess_data(X, y=None):
    """
    Can preprocess both training data (X,y) and test data(X only).
    """
    if y is None:
        df = X
    else:
        df = pd.concat([X, y], axis=1)
    df = df.drop(['sex', 'region'] , axis=1)
    
    if y is None:
        X = df
    else:
        y = df.iloc[:, -1]
        X = df.iloc[:, 0:-1]
    
    if y is not None:
        for index, row in X.iterrows():
            if row["age"] <= 23 and row["smoker"] == "no":
                y.iloc[index] = min(y.iloc[index], 5000)
            else:
                y.iloc[index] = min(y.iloc[index], 48000)
    X['bmi_30'] = X['bmi'].apply(lambda x: 1 if x <= 30 else 2)
    X['smoker'] = X['smoker'].apply(lambda x: 2 if x=="yes" else 1)
    return X, y

def load_training_data():
    X = pd.read_csv(TRAIN_X_PATH)
    y = pd.read_csv(TRAIN_Y_PATH)
    X, y = preprocess_data(X, y)
    return X, y

def load_test_data():
    test_X = pd.read_csv(TEST_X_PATH)
    test_X, _ = preprocess_data(test_X)
    return test_X

X, y = load_training_data()
test_X = load_test_data()

def kfold_cv(X, y, k=5, degree=2):
    predictions = np.array([])
    kfold = KFold(n_splits=k)
    for fold_idx, (train_indexes, test_indexes) in enumerate(kfold.split(X, y)):
        train_X, train_y = X.loc[train_indexes], y.loc[train_indexes].values.ravel()
        test_X, test_y = X.loc[test_indexes], y.loc[test_indexes]
        pipeline = Pipeline([
            ('degree' , PolynomialFeatures(degree)),
            ('scaler' , StandardScaler()),
            ('model' , Ridge())
        ])

        pipeline.fit(train_X, train_y)
                
        test_pred = pipeline.predict(test_X)
        predictions = np.concatenate((predictions, test_pred), axis=0)
                
    print(f"MSE: {mse(predictions, y)}")
    
kfold_cv(X, y, 5)

def generate_submission_csv(X, y, degree=2):
    pipeline = Pipeline([
            ('degree' , PolynomialFeatures(degree)), 
            ('scaler' , StandardScaler()),
            ('model' , Ridge())
    ])

    pipeline.fit(X, y)
    
    predicted = pipeline.predict(test_X)
        
    output_df = pd.DataFrame(columns=['predicted'])
    for idx, val in enumerate(predicted):
        output_df.loc[idx] = val
        
    with open(OUTPUT_PATH, 'w') as file:
        file.write("ID,predicted\n")
        output_df.to_csv(file, header=False)
            
generate_submission_csv(X, y)