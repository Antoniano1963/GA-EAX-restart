import numpy as np


def change_TSBlib_to_dataset(filepath):
    dimension = 0
    next_data = False
    dataset = []
    dataset.append(list())
    max_number = -1
    with open(filepath, "r") as f:
        data = f.readlines()
        for line in data:
            split_line = line.split()
            if "DIMENSION" in split_line[0]:
                dimension = int(split_line[1])
            if "EOF" in split_line[0]:
                next_data = False
            if next_data:
                dataset[0].append([float(split_line[1]), float(split_line[2])])
                max_number = max(max_number, float(split_line[1]), float(split_line[2]))
            if "NODE_COORD_SECTION" in split_line[0]:
                next_data = True
    print(dataset)
    divide_number = 1
    while(divide_number < max_number):
        divide_number = divide_number * 10
    for i in range(len(dataset[0])):
        sub_list = dataset[0][i]
        dataset[0][i] = [sub_list[0]/divide_number, sub_list[1]/divide_number]
    return dataset[0]



def read_TSPlib(filepath):
    Ncity = 0
    next_data = False
    X_position = []
    Y_position = []
    max_number = -1
    with open(filepath, "r") as f:
        data = f.readlines()
        for line in data:
            split_line = line.split()
            if "DIMENSION" in split_line[0]:
                Ncity = int(split_line[2])
            if "EOF" in split_line[0]:
                next_data = False
            if next_data:
                X_position.append(float(split_line[1]))
                Y_position.append(float(split_line[2]))
                max_number = max(max_number, float(split_line[1]), float(split_line[2]))
            if "NODE_COORD_SECTION" in split_line[0]:
                next_data = True
    return X_position, Y_position, max_number, Ncity