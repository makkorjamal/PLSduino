Partial Least Squares for Arduino/ESP32
=====================================  


Introduction:  
------------------------  
Partial Least Squares (PLS) is a statistical technique that helps to model relationships between groups of variables. It's especially useful when the predictor variables (the ones we use to predict outcomes) are closely related to each other or when there are more predictors than observations. PLS is commonly used in fields like chemistry, social sciences, and bioinformatics.


Usage:
==========
Download all the source files.
There are multiple examples for common workflows.
>* **examples/basic_usage/basic_usage.ino**, this example shows simple training and prediction using predefined matrices.
>* **examples/read_XY_from_SDCARD/read_XY_from_SDCARD.ino**, this example shows how to read X (feature matrix) and Y (response matrix) from CSV files stored on an SD-backed filesystem.
>* **examples/predict_from_pretrained_model_SDCARD/predict_from_pretrained_model_SDCARD.ino**, this example shows how to load a pretrained model from CSV files and call `predict()` directly without running `train()`.


Notice:
============
>1. This library depends on the Arduino Eigen/Dense library.
>2. Arduino/ESP32 are quite limited in computational capabilities. For large matrices you can skip training on-device by loading a pretrained model and calling `predict()` directly.
>3. Prediction-only mode requires **all three** model components: `B`, `meanX`, and `meanY`. Loading `B` alone is not enough because the library centers X and restores the Y offset during prediction.


CSV format:
===============
All CSV helpers expect comma-separated float values with one matrix row per line.
Blank lines are ignored.

>* **X.csv**: `n_samples x n_features`
>* **Y.csv**: `n_samples x n_outputs`
>* **B.csv**: `n_features x n_outputs`
>* **meanX.csv**: `1 x n_features`
>* **meanY.csv**: `1 x n_outputs`

The parser rejects ragged rows, empty values, and non-numeric values.


Reference:
===============
Refer to the **/doc** for more details (tbd).

***

Contributing to this software is very welcome. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding a change log and your contact into the file header is encouraged.<br>
Thanks for your contribution.
