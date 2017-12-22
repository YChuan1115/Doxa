# Δoxa Binarization Framework
## Introduction
ΔBF is an image binarization framework written in C++ which focuses exclusively on local adaptive thresholding algorithms.
In English, this means that it has the ability to turn a color or gray scale image into a black and white image.

**Algorithms**
* Niblack - "An Introduction to Digital Image Processing", 1986.
* Sauvola - "Adaptive document image binarization", 1999.
* Wolf - "Extraction and Recognition of Artificial Text in Multimedia Documents", 2003.
* NICK - "Comparison of Niblack inspired Binarization methods for ancient documents", 2009.

**Optimizations**
* Shafait - "Efficient Implementation of Local Adaptive Thresholding Techniques Using Integral Images", 2008.
* Shafait LowMem

**Performance Metrics**
* Overall Accuracy
* F-Measure
* Peak Signal-To-Noise Ratio (PSNR)
* Distance-Reciprocal Distortion Measure (DRDM) - "An Objective Distortion Measure for Binary Document Images Based on Human Visual Perception", 2002.

**Native Image Support**
* Portable Pixel Map: RGBA PAM

## Overview
The goal of this library is to provide the building blocks one might use to advance the state of handwritten manuscript binarization.
What sets this binarization library apart is that it is intended to be used by those interested in experimenting with their own algorithms and enhancements.
Instead of being relegated to MATLAB, or obfuscated by mathematics in a research paper, a lot of effort has gone into exposing these binarization techniques in an open and transparent way.
A key objective in designing this framework was to make it modular and as easy to use as possible, without sacrificing speed and without depending heavily on 3rd party frameworks.
This library is also heavily unit tested to help ensure quality, and to quickly spot problems after experimenting with the codebase.

### Example
This short example shows you how easy it is to use ΔBF to process an image.

```cpp
// Read a color image
Image image;
PPM::Read(R"(C:\MyImage.pam)", image);

// Convert it to gray scale
Preprocessor::ToGreyScale(image);

// Use a binarization algorithm to convert it into black and white
Image imageSauvola(image.width, image.height);
Algorithms::Sauvola<Shafait>(imageSauvola, image, 26, 0.11);

// Save the processed image
PPM::Write(imageSauvola, R"(C:\MyImage-Sauvola.pam)");
```
<br/>
ΔBF is incredibly light weight, being a header-only library.  It can integrate easily with other 3rd party frameworks like Qt.

```cpp
// Qt has great support for working with complex file formats
// Prompt the user to select an image to open, using Qt
QString imagePath = 
	QFileDialog::getOpenFileName(
		this,
		tr("Open File"),
		"",
		tr("JPEG (*.jpg *.jpeg);;PNG (*.png)")); // Must be 32b RGBA

// Load the image into a Qt QImage
QImage qImage(imagePath);

// Operations on the ΔBF Image will directly change the QImage when set as a reference.
Image image = Image::Reference(qImage.width(), qImage.height(), (Pixel32*)qImage.bits());
Preprocessor::ToGreyScale(image);
Algorithms::Niblack<Shafait>(image, image);  // Due to Shafait, there are no conflicts writing to the same image

// Save the updated QImage to the file system, using Qt
qImage.save("binary-image.png");
```

Other examples can be found in the Demo folder, like the [PerformanceMetrics](https://github.com/brandonmpetty/Doxa/Demo/PerformanceMetrics) tool.

### Performance Analysis

These numbers were generated by running the Kumite/DimMak test in the Unit Test suite against a set of images that come with the repository.
They represent the best K and Window combination possible for each algorithm, for a target image.

| Algorithm | K     | Window | Accuracy | F-Measure | PSNR  |
| --------- |:-----:|:------:|:--------:|:---------:|:-----:|
| Niblack   | -0.65 | 124    | 96.59    | 90.20     | 14.67 |
| Sauvola   | 0.11  | 26     | 97.67    | 93.23     | 16.33 |
| Wolf      | 0.19  | 20     | 97.67    | 93.29     | 16.33 |
| NICK      | -0.11 | 42     | 97.63    | 93.05     | 16.26 |

It should be noted that the Ground Truth used to generate these numbers is, like virtually all Ground Truths, subjective and a work in progress.
A Photoshop PSD file is attached that can be used to make corrections to the Ground Truth as needed.

### Goals
* Refactor to incorporate tiling in order to reduce memory utilization
* ~~Provide the Distance Reciprocal Distortion  (DRD) metric~~
* Improve and expand the PPM image format support
* Internally process 8 bit images to reduce memory consumption

## License
CC0 - Brandon M. Petty, 2017

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8