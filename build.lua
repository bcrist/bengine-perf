module 'perf' {
   lib {
      src {
         'src/*.cpp',
         pch_src 'src/pch.cpp'
      },
      define 'BE_PERF_IMPL',
      link_project 'core'
   }
}
