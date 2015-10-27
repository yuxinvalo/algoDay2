#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <assert.h>
# define MAX_COLUMN 80

unsigned int_width(int i)
{
  int n = 0;
  if ( i <= 0)
    ++n;

  while (i != 0)
    {
      ++n;
      i /=10;
    }

  return n;
}

unsigned ints_width(const int* tab, unsigned count)
{
  int result = 0;
  for (int i = 0; i < count; ++i)
    {
      if (int_width(tab[i]) > result)
	result = int_width(tab[i]);
    }

  return result;
}

#if 0
void print_int_array(FILE* out, const int* tab, unsigned count)
{
  int maxWidth = ints_width(tab, count);
  int column = 0;;
  for ( int x = 0; x < int_width(count - 1) - 1; x++)
    {
      fprintf(out," ");
      column ++;
    }
  fprintf(out, "%s%i%s","[", 0, "]");
  column += 3;

  for (int i = 0; i < count; ++i)
    {
      int width = int_width(tab[i]);
      int space = maxWidth - width;

      if (column + maxWidth >= 80)
	{
	  column = 0;
	  fprintf(out,"\n");

	  for (int x = 0; x < int_width(count - 1) - int_width(i); x++)
	    {
	      fprintf(out, " ");
	      column ++;
	    }
	  fprintf(out,"%s%i%s","[", i, "]");
	  column += 3;
	}

      for (int j = 0; j < space; j++)
	fprintf(out," ");

      fprintf(out," ");
      fprintf(out,"%i", tab[i]);
      column += maxWidth + 1;
    }
  fprintf(out,"\n");
}
#endif
void printWhiteSpace(FILE* out, unsigned int count)
{
  for (unsigned int i = 0; i < count ; ++i)
  {
    fprintf(out, " ");
  }
}

void printOneInt(FILE*out, const int num, const unsigned int int_width, const unsigned int max_width)
{
  printWhiteSpace(out, max_width - int_width);
  fprintf(out, "%d", num);
}

void print_int_array(FILE* out, const int* tab, unsigned count)
{
  unsigned int max_width = ints_width(tab, count);
 // unsigned int leadingIndex = 0;
  unsigned int numOfIntsInTheRow;
  unsigned int indexWidth = int_width(count - 1);
for (unsigned int i = 0; i < count;)
  {
    numOfIntsInTheRow = (MAX_COLUMN - int_width(count - 1) - 2) / (max_width + 1);
    printWhiteSpace(out, indexWidth - int_width(i));
    fprintf(out, "[");
    fprintf(out, "%d", i);
    fprintf(out, "]");
    for (unsigned int j = i; j < i + numOfIntsInTheRow && j < count; ++j)
    {
      fprintf(out, " ");
			printOneInt(out, tab[j], int_width(tab[j]), max_width);
    }
    fprintf(out, "\n");
    i += numOfIntsInTheRow;
}
}

void insert_sort(int* tab, unsigned count)
{
  int temp = 0;
  int j = 0;
  for (int i = 0; i < count; i++)
    {
      j = i;

      while (j > 0 && tab[j] < tab[j - 1])
	{
	  temp = tab[j];
	  tab[j] = tab[j - 1];
	  tab[j-1] = temp;
	  j--;
	}
    }
}

void insert_sort_cmp(int* tab, unsigned count, int (*cmp)(int a, int b))
{
  int temp = 0;
  int j = 0;
  for (int i = 0; i < count; i++)
    {
      j = i;

      while (j > 0 && cmp(tab[j- 1], tab[j]) == 1)
	{
	  temp = tab[j];
	  tab[j] = tab[j - 1];
	  tab[j-1] = temp;
	  j--;
	}
    }
}

int decreasing(int a, int b)
{
  if (a > b)
    return -1;
  return a < b;
}

unsigned cmp_count; // number of comparisons performed

int increasing(int a, int b)
{
  ++cmp_count;
  if (a < b)
    return -1;
  return a > b;
}

#define my_test(val) \
  cmp_count = 0; \
  printf("linear_search(a, %u, %d, increasing) = %u\n", \
	 asize, (val), binary_search(a, asize, (val), increasing)); \
  printf("\twith %u comparisons\n", cmp_count);

unsigned linear_search(const int* tab, unsigned count, int val, int (*cmp)(int a, int b))
{
  int index = 0;
  for (index = 0; index < count; index ++)
    {
      if (cmp(val, tab[index]) == -1)
	  return  index;

      if (tab[index] == val)
	return index;
      
    }
  return index;
}


#if 0
unsigned binary_search(int* tab, unsigned count, int val, int (*cmp)(int a, int b))
{
  int left = 0;
  int right = count;
  int middle = 0;
  
  while (left < right)
    {
      middle = (left + right) / 2;
      if (val == tab[middle])
	{
	  cmp(val, tab[middle]);
	  printf("yolo\n");
	  return middle;
	}
      else if (cmp(val, tab[middle]) == -1)
	right = middle;
      else
	left = middle+ 1;
    }
  printf("swag\n");
  return left;
}
#endif
unsigned binary_search(int* tab, unsigned count, int val, int (*cmp)(int a, int b))
{

 int lower = 0;
  int upper = count - 1;
  int mid;
  int compareRet;

  do {
    mid = (upper + lower) / 2;
//    printf("%d\n", mid);
    compareRet = (*cmp)(tab[mid], val);
    // tab[mid] > val 
    if (compareRet == 1)
    {
      upper = mid - 1;
    } else if (compareRet == -1) // tab[mid] < val
    {
      lower = mid + 1;
    } else
    {
      break;
    }
  } while (lower <= upper);
  return (compareRet == -1) ? count : mid;
}




void bs_insert_sort_cmp(int* tab, unsigned count, int (*cmp)(int a, int b))
{
  int temp = 0;
//  int aux = 0;
  int x;
  
  for(int i = 1; i < count; i++)
    {
      temp = binary_search(tab, count, tab[i], cmp);
 //     aux = tab[i];
      
      for (x = i -1; i > temp; x--);
      {
	tab[x + 1] = tab[x];
      }
      tab[temp]= 0;
    }
}


int main()
{
 int a[] = { 1, 2, 3, 4, 5, 6, 9, 12, 15, 20, 25, 35, 38, 40, 41 };
  unsigned asize = sizeof(a) / sizeof(*a);
  puts("a[]:");
  print_int_array(stdout, a, asize);
  my_test(0);
  my_test(6);
  my_test(8);
  my_test(41);
  my_test(42);
	return 0;
/*
  srand(0);
  const unsigned tsize = 50000;
  int tab1[tsize];
  int tab2[tsize];
  for (unsigned i = 0; i < tsize; ++i)
    tab1[i] = tab2[i] = rand();

  cmp_count = 0;
  clock_t before = clock();
  insert_sort_cmp(tab1, tsize, increasing);
  clock_t after = clock();
  printf("insertion_sort_cmp() took %zu comparisons and %ju ticks\n",
	 cmp_count, (uintmax_t)(after - before));

  cmp_count = 0;
  before = clock();
  bs_insert_sort_cmp(tab2, tsize, increasing);
  after = clock();
  printf("bs_insertion_sort_cmp() took %zu comparisons and %ju ticks\n",
	 cmp_count, (uintmax_t)(after - before));
  
  // The two arrays should of course be equal.
  assert(memcmp(tab1, tab2, sizeof(tab1)) == 0);*/
}
