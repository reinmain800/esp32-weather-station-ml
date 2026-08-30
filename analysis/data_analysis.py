import pandas as pd
import numpy as np
import matplotlib.pylab as plt
import seaborn as sns
import sqlite3

plt.style.use('ggplot')

conn = sqlite3.connect("data/weather_measurements.db")

df = pd.read_sql_query(
    "SELECT * FROM weather_measurements", conn
)

x_values = df['ID']
y_values = df['Temperature']

fig ,ax = plt.subplots()

ax.set_title('Temperature')
ax.set_ylabel('Temperature (celsius)', fontsize = 14)
ax.set_xlabel('ID', fontsize = 14)

ax.tick_params(labelsize = 6)

ax.scatter(x_values, y_values, c = y_values, cmap = plt.cm.Blues)

print(df.describe())

plt.show()

conn.close()
