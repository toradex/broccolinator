import numpy as np

import tensorflow as tf

assert tf.__version__.startswith("2")

from tflite_model_maker import configs
from tflite_model_maker import image_classifier
from tflite_model_maker import ImageClassifierDataLoader
from tflite_model_maker import model_spec

import matplotlib.pyplot as plt

image_path = "./images"

data = ImageClassifierDataLoader.from_folder(image_path)
train_data, test_data = data.split(0.9)

model = image_classifier.create(train_data)

loss, accuracy = model.evaluate(test_data)

print(f"loss: {loss}, accuracy: {accuracy}")

model.export(export_dir=".")
