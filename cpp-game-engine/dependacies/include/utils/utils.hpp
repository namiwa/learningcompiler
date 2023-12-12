#ifndef utils_hpp
#define utils_hpp

template <class T>
unsigned int getArrayLen(T arr[])
{
  return (unsigned int)sizeof(arr) / sizeof(float);
}

#endif // !utils_hpp