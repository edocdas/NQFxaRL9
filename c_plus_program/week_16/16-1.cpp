template <typename T>
void swap(T *a, T *b)
{
  T buf = *a;
  *a = *b;
  *b = buf;
}

int main()
{}
