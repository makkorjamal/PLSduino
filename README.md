Partial Least Squares for Arduino/ESP32
=====================================  


Introduction:  
------------------------  
Partial Least Squares (PLS) is a statistical technique that helps to model relationships between groups of variables. It's especially useful when the predictor variables (the ones we use to predict outcomes) are closely related to each other or when there are more predictors than observations. PLS is commonly used in fields like chemistry, social sciences, and bioinformatics.


Usage:
==========
Download all the source files.
There is one example for the user to use.
>* **examples/basic_usage/basic_usage.ino**,this example shows a simple usage using predefined matrices
## TODO
>* **examples/read_XY_from_SD_card/read_from_XY_from_SD.ino**, this example shows how to read X (features matrice) and Y (response matrice) from a file saved in an SD card, for example.


Notice:
============
>1. This library depends on the Arduino Eigen/Dense library.
>2. Arduino/ESP32 are quite limited in computational capabilities. You can also load a pre-trained matrix B and use it to predict 
Y (as long as you keep the dimensionality consistent).


Reference:
===============
Refer to the **/doc** for more details (tbd).

***

Contributing to this software is very welcome. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding a change log and your contact into the file header is encouraged.<br>
Thanks for your contribution.
