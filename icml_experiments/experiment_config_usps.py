import cPickle as pickle
import numpy as np
import random as random

import dist_utils


def get_experiment_name():
    return "usps"

def get_data_config():
    return DataConfig()

def get_online_config():
    return OnlineConfig()

def get_sklearn_offline_config():
    return SklearnOfflineConfig()

def load_sklearn_data(file):
    import sklearn.datasets as sklearn_datasets
    data = sklearn_datasets.load_svmlight_file(file)
    X = np.array(data[0].todense(),  dtype=np.float32)
    Y = np.array( data[1], dtype=np.int32 )
    print X.shape
    return X, Y

class DataConfig(object):
    def __init__(self):
        self.data_file_train = "source_data/usps"
        self.data_file_test = "source_data/usps.t"
        self.data_sizes = [20, 50, 100, 150, 250, 500, 1000, 2000, 5000, 7291]
        self.number_of_passes_through_data = [1,3,5,10]
        self.number_of_runs = 3
        self.bayes_accuracy = 1.0

        (self.X_train_org, self.Y_train_org) = load_sklearn_data(self.data_file_train)
        (self.X_test_org, self.Y_test_org) = load_sklearn_data(self.data_file_test)

    def load_data(self, data_size, passes_through_data):
        (X_train, Y_train) = dist_utils.generate_multi_pass_dataset(self.X_train_org, self.Y_train_org, data_size, passes_through_data)
        return (X_train, Y_train, self.X_test_org, self.Y_test_org)


class OnlineConfig(object):
    def __init__(self):
        self.number_of_trees = 100
        self.number_of_features = 8
        self.number_of_thresholds = 10
        self.split_rate = 1.2
        self.number_of_data_to_split_root = 2
        self.number_of_data_to_force_split_root = 1000
        self.use_two_streams = True
        self.null_probability = 0.5
        self.impurity_probability = 0.5
        self.min_impurity_gain = 0.001
        self.measure_tree_accuracy = False


class SklearnOfflineConfig(object):
    def __init__(self):
        self.criterion = "entropy"
        self.number_of_trees = 100
        self.number_of_features = 8
        self.max_depth = 1000
        self.min_samples_split = 10
        self.number_of_jobs = 2