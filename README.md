### The files can be compiled with the following command in the terminal: g++ MarketTick.cpp MarketDataProcessor.cpp CSVHandler.cpp MarketData.cpp -o MarketData
### And be run with: MarketData

To hold MarketTick objects an unordered_map<string, set<MarketTick>> was used. It allows a quick access to the information, which corresponds to a specific symbol. 
Furthermore a set was used to hold individual objects, since it automatically sorts the contents and allows to quickly find Moving Average.
Although unnessesary, reading from and writing to a file functionality was moved to another class (might be usefull if there are multiple classes requiring this functionality).

### It was assumed:
Shares value needs to be larger than 0
Timestamp data from a file should not be negative as negative data here might introduce errors later on because of the wrap around
Moving average function should output value for less than N number of prices if there is not enough data.
If there are corrupted entries in the input csv file the program should display an error message but continue reading valid lines
