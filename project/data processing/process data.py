import pandas as pd

pre_data = pd.read_csv(r"project\data processing\concat_all_data.csv", header=0, encoding='utf-8')
print(pre_data.head())
print(pre_data.tail())
