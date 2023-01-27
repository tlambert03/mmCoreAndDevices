project('MMAcqEng', 'cpp', version : '0.0.1')

includes = include_directories('.') # include the main directory
MMCore_dep = dependency('MMCore', fallback: 'MMCore')

dep_main = dependency('appleframeworks', modules : ['IOKit', 'Foundation'])

exe = executable('mmacq', 'main.cpp',
  install : true,
  dependencies: [MMCore_dep, dep_main])