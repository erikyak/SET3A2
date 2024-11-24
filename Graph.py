import pandas as pd
import matplotlib.pyplot as plt

# Загрузка данных
data = pd.read_csv("result15.csv")

array_types = data["ArrayType"].unique()
sort_types = data["SortType"].unique()

# Построение графиков
for array_type in array_types:
    plt.figure(figsize=(10, 6))
    subset = data[data["ArrayType"] == array_type]
    for sort_type in sort_types:
        sort_data = subset[subset["SortType"] == sort_type]
        plt.plot(sort_data["Size"], sort_data["Time"], label=sort_type)

    plt.title(f"{array_type} Arrays")
    plt.xlabel("Array Size")
    plt.ylabel("Time (microseconds)")
    plt.legend()
    plt.grid(True)
    plt.show()
