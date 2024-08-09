Partial Least Squares for Arduino/ESP32
=====================================  


Introduction:  
------------------------  
Partial Least Squares (PLS) is a statistical method used for modeling relationships between sets of observed variables. It is particularly useful when the predictors (independent variables) are highly collinear or when the number of predictors exceeds the number of observations. PLS is commonly applied in various fields, including chemometrics, social sciences, and bioinformatics.



Usage:
==========
Download all the source files.
There is one example for user to use.
>* **examples/basic_usage/basic_usage.ino**,this example shows a simple usuage using predefined matrices
## TODO
>* **examples/read_XY_from_SD_card/read_from_XY_from_SD.ino**,this example shows how to read X (features matrice) Y (response matrice) from a file saved in an SD card for example.


Notice:
============
>1. This library depends on Arduino Eigen/Dense library.
>2. Arduino/ESP32 are quite limited in computational capabilities. You can also load a pre-trained matrix B and use it to predict 
Y (as long as you keep the dimentionality consistant).


Reference:
===============
Refer to the **/doc** to get more detail (tbd).

***

Contributing to this software is very welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.
