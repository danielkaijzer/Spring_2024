import pandas as pd
import streamlit as st
import base64
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

st.title('Premier League Team Stats Explorer')

st.markdown("""
This app performs simple webscraping of NBA player stats data!
* **Python libraries:** base64,pandas, streamlit
* **Data source:** [fbref.com](https://fbref.com)
""")

st.sidebar.header('User Input Features')
selected_year = st.sidebar.selectbox('Year', list(reversed(range(2010,2025))))

# Web scraping of team stats
@st.cache_resource # caches data loaded so we don't have to reload every time
def load_data(year):
    url = "https://fbref.com/en/comps/9/" + str(int(year)-1) + "-" + str(year) + "/" + str(int(year)-1) + "-" + str(year) + "-Premier-League-Stats"
    html = pd.read_html(url, header=0)
    df = html[0]
    raw = df.drop(df[df.MP == 'MP'].index) # Deletes repeating headers in content
    raw = raw.fillna(0)
    teamstats = raw.drop(['Rk'], axis=1)
    return teamstats
teamstats = load_data(selected_year)

st.dataframe(teamstats)
