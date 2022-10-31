from EAX import EAX2
import numpy as np
from TSPLib_util import read_TSPlib

if __name__ == "__main__":
    x_position, y_position, _, Ncity = read_TSPlib("/data/EAX/GA-EAX-restart/data/fnl4461.tsp")
    print(Ncity)
    x_position = np.array(x_position)
    y_position = np.array(y_position)
    best_val = EAX2(100, 30, 182566, 100, 100, "/data/EAX/GA-EAX-restart/data/fnl4461.tsp",Ncity, x_position, y_position)
    print("Best solution is {}".format(best_val))
    #/data/EAX/GA-EAX-restart/data/fnl4461.tsp 100 30 182566 100 100