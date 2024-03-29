Dilate a binary image
=====================

.. index::
  single: BinaryBallStructuringElement
  single: BinaryDilateImageFilter
  pair: mathematical morphology; dilation
  pair: BinaryBallStructuringElement; SetRadius

.. seealso:: dilation; erosion


Synopsis
--------

Dilate regions by using a specified kernel, also known as a structuring element.
In this example, the white regions are enlarged.


Results
-------

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

  Input binary image.

.. figure:: DilateABinaryImageOutputBaseline.png
  :scale: 50%
  :alt: Dilated output.

  Dilated output.


Code
----

C++
...

.. literalinclude:: DilateABinaryImage.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryDilateImageFilter itk::BinaryBallStructuringElement
