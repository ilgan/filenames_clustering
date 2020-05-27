### Created by: I. Ganelin
### Date: 26/05/2020 

# K-means clustering of file names using Jaro and Jaro-Winkler metric in C++.

**Input:** 
* Uses file name "filelist.txt" by default

**Output:**
* j_results.txt  - Clustering results using Jaro Metric.
* jw_results.txt - Clustering results using Jaro-Winkler Metric.

Notes: I ran the code in an online tool, therefore used reduced dataset of around 200 filenames in order to increase the speed and stay within a limit of free account. The results for a full set should be different, but the code is the same.
I've also attached two sets of results files for k=4 and k=10.
Since I do not have a Linux machine, I've created cmake and two makefiles, but it hasn't been tested on Linux machine.

#### References:
[Jaro and Jaro Winkler metric code](https://github.com/TriviaMarketing/Jaro-Winkler).
[K-Means inplementation](https://github.com/marcoscastro/kmeans).