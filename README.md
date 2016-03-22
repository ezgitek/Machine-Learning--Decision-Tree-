# Machine Learning (Decision Tree)
Cmpe 250 Data Structures&amp;Algorithms project, Bogazici University

In this project, I was supposed to implement an algorithm to classify the data points by finding the best feature to classify, i.e. implementing a decision tree for a 2-class classification problem.

A possible input:
5 10
1 88.38 85.31 72.46 49.37 74.24
0 89.86 76.20 72.19 46.95 77.00
1 89.79 86.77 68.94 49.00 76.54
0 88.47 77.91 69.91 45.78 74.93
0 87.67 76.82 68.38 48.93 78.16
1 88.03 86.85 74.12 47.80 78.66
1 90.84 86.95 73.52 45.90 74.14
0 88.80 76.66 70.94 45.59 76.06
1 88.54 85.41 69.31 45.34 77.24
1 89.51 85.92 71.34 44.21 74.33

The first integer N of the first line shows the dimensions of the data (5 features for each point), second integer K shows the number of data points (in this case, 10), and the following K lines are all data points. For example, first line is in the 1st class, and the values for its N (5) features are "88.38 85.31 72.46 49.37 74.24".

My aim is here to find the feature that splits these data points into classes 1 and 0.

As an output file, I will give the number of the feature and also the misclassification rate (when the classification is done with best threshold and feature). For this case, it's 1 0 (with zero-indexing, btw, so 1 corresponds to 2nd feature), since the second feature is giving me a misclassification rate of 0.
