Get Type Basic Information
==========================

.. index::
   single: NumericTraits

Synopsis
--------


Get some basic information about a plain old data (POD) type, in this case the
*float* type.


Results
-------

Output::

  Min: 1.17549e-38
  Max: 3.40282e+38
  Zero: 0
  ZeroValue: 0
  Is -1 negative? 1
  Is 1 negative? 0
  One: 1
  Epsilon: 1.19209e-07
  Infinity: inf
  Good

Code
----

C++
...

.. literalinclude:: GetTypeBasicInformation.cxx


Classes demonstrated
--------------------

.. breathelink:: itk::NumericTraits
