import pickle

import lib.scripts.experiment_readers as reader
import lib.scripts.experiment_instance as inst


def serialize(filename, object):
  with open(filename, 'wb') as f:
    pickle.dump(object, f)


def deserialize(filename):
  with open(filename,'rb') as f:
    return pickle.load(f)


serialize("test_serialization.txt", [1,2,3,4])
