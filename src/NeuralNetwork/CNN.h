#pragma once

#include "neuralnetwork.h"





extern "C" NEURALNETWORK_API  uint32_t * CreateModel();


extern "C" NEURALNETWORK_API  int LoadModel(uint32_t * model, const char* path);


extern "C" NEURALNETWORK_API  int SetImageROI(uint32_t * model, int Roi1, int Roi2, int Roi3, int Roi4);


extern "C" NEURALNETWORK_API  float ReadImage(uint32_t * model, const char* path);


extern "C" NEURALNETWORK_API  unsigned char* ImageROI(uint32_t * model, unsigned char* LVImagePointer, int lineWidth, int height, int width);


extern "C" NEURALNETWORK_API  float ReasoningModel(uint32_t * model, unsigned char* LVImagePointer, int lineWidth, int height, int width, int channels);


extern "C" NEURALNETWORK_API  int DeleteModel(uint32_t * model);