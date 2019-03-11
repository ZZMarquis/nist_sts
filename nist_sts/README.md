# nist-sts

This is a slightly updated version of [NIST Statistical Test Suite (STS)](http://csrc.nist.gov/groups/ST/toolkit/rng/documentation_software.html) tool for randomness testing. Main reason for this fork is that the original source code provided by NIST doesn't compile cleanly on Windows using MSVC. Main reason is that MSVC doesn't provide erf() and erfc() functions in standard math library. I've added implementation of these functions and created a project file. You should be now able to compile STS using standard Microsoft Visual C/C++ suite.

##Building
This version should compile cleanly under MSVC 2008. I haven't tested it under other versions and MSVC Express, but it's ANSI C so it should work.

The solution is configured to compile using extended instruction set (SSE2) and optimize for speed.

After build is completed you will get a single _assess.exe_ binary which is the test suite.

## Usage
You probably still want to [download](http://csrc.nist.gov/groups/ST/toolkit/rng/documentation_software.html) the original NIST ZIP distribution and use their test files. Reason why I'm not including them here is that the archive is over 40 MB big and most of that is the test data.

After unpacking the ZIP place _assess.exe_ in the top directory. The program expects to have the subdirectories _experiments, templates_ etc in the same directory. 

STS has somewhat old school terminal interface. Simple tutorial can be found in section 5-1 of [NIST SP800-22](http://csrc.nist.gov/groups/ST/toolkit/rng/documents/SP800-22rev1a.pdf).

Remember that testing results are written to _experiments\AlgorithmTesting\finalAnalysisReport.txt_ if you load tested data from a file. STS has a number of built-in generators, in which case the report will be written to a corresponding subdirectory of _experiments_.
  
  
  
PS:the directories:data/experiments/templates are from https://download.csdn.net/download/yuanhunhai/8985409





