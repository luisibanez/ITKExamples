Erode a binary image
====================

.. index::
  single: BinaryBallStructuringElement
  single: BinaryErodeImageFilter
  pair: mathematical morphology; erosion
  pair: BinaryBallStructuringElement; SetRadius

.. seealso:: erosion; dilation


Synopsis
--------
Erode regions by using a specified kernel, also known as a structuring element.  In this example, the white regions shrink.


Results
-------

.. figure:: Yinyang.png
  :scale: 50%
  :alt: Input yin-yang image.

  Input binary image.

.. figure:: ErodeABinaryImageOutputBaseline.png
  :scale: 50%
  :alt: Eroded output.

  Eroded output.


Code
----

C++
...

.. literalinclude:: ErodeABinaryImage.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::BinaryErodeImageFilter itk::BinaryBallStructuringElement
