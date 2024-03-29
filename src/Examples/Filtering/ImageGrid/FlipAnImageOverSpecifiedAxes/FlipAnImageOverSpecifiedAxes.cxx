/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkFlipImageFilter.h"

int main(int argc, char* argv[])
{
  if( argc != 4 )
    {
    std::cerr << "Usage: " << argv[0];
    std::cerr << " <InputFileName> <OutputFileName> <AxisToFlip>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned Dimension = 2;

  typedef unsigned char                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType >   ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::FlipImageFilter< ImageType >   FlipImageFilterType;

  FlipImageFilterType::Pointer flipFilter
          = FlipImageFilterType::New ();
  flipFilter->SetInput( reader->GetOutput() );

  FlipImageFilterType::FlipAxesArrayType flipAxes;
  if( atoi( argv[3] ) == 0 )
    {
    flipAxes[0] = true;
    flipAxes[1] = false;
    }
  else
    {
    flipAxes[0] = false;
    flipAxes[1] = true;
    }

  flipFilter->SetFlipAxes( flipAxes );

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( flipFilter->GetOutput() );

  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cerr << "Error: " << e << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}

