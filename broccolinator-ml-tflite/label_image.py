# Work derived form tensor-flow lite sample with the following license:
#
# Copyright 2018 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import time

import numpy as np
from PIL import Image
import tflite_runtime.interpreter as tflite
import datetime

def load_labels(filename):
  with open(filename, 'r') as f:
    return [line.strip() for line in f.readlines()]

def predict_image(img):

  model_file="./model/model.tflite"
  label_file="./model/labels.txt"
  input_mean=127.5
  input_std=127.5  

  interpreter = tflite.Interpreter(model_path=model_file)
  interpreter.allocate_tensors()

  input_details = interpreter.get_input_details()
  output_details = interpreter.get_output_details()

  labels = load_labels(label_file)

  # check the type of the input tensor
  floating_model = input_details[0]['dtype'] == np.float32

  # NxHxWxC, H:1, W:2
  height = input_details[0]['shape'][1]
  width = input_details[0]['shape'][2]

  # crop image to square format

  owidth, oheight = img.size

  side=min(owidth,oheight)

  dw=(owidth-side)>>1
  dh=(oheight-side)>>1

  img = img.crop((dw,dh,owidth-dw,oheight-dh))
  img = img.resize((width, height))

  # add N dim
  input_data = np.expand_dims(img, axis=0)

  if floating_model:
    input_data = (np.float32(input_data) - input_mean) / input_std

  interpreter.set_tensor(input_details[0]['index'], input_data)

  start_time = time.time()
  interpreter.invoke()
  stop_time = time.time()

  output_data = interpreter.get_tensor(output_details[0]['index'])
  results = np.squeeze(output_data)

  top_k = results.argsort()[-5:][::-1]

  result=[]

  for i in top_k:
    result.append({
      'tagName': labels[i],
      'probability': np.float64(round(results[i],8)) })

    response = { 
      'created': datetime.datetime.utcnow().isoformat(),
      'predictions': result 
      }

  return response