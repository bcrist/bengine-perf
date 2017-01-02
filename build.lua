module { name = 'perf',
   projects = {
      lib {
         src = {
            'src/*.cpp',
            pch = 'src/pch.cpp'
         },
         preprocessor = {
            'BE_PERF_IMPL'
         }
      }
   }
}
