#include <stdio.h>
#include <math.h>
#include <stdlib.h>
# define MAX_COLUMN 80
#include <stdint.h>

unsigned int cmp_count;



unsigned int_width(double i)
{
unsigned nb = 0;
  if (i > 0)
  {
    nb = log10(i) + 1;
  }
  else if (i < 0)
  {
    i = i * (-1);
    nb = log10((double)i) + 2;
	}
  else
  {
    nb = 1;
  }
return nb;
}
 
//------------------------------------------------------
unsigned ints_width(const int* tab, unsigned count)
{
unsigned nb[count];
unsigned max_nb = 0;

  if(tab != NULL)
  {
    for (unsigned i = 0; i < count; ++i)
    {
      nb[i] = int_width(tab[i]);
#if 0     
	( if (tab[i] > 0)
      {
        nb[i] = log10(tab[i]) + 1;
      }
      else if (i < 0)
      {
        i = (-1) * i;
        nb[i] = log10(tab[i]) + 2;
      }
      else
      {
        nb[i] = 1;
      }
#endif
    }

  for(unsigned i = 0; i < count; ++i)
  {
    if(max_nb < nb[i])
    {
      max_nb = nb[i];
    }
  }
  return max_nb;
  }
return -1;
}

//----------------print_int_array----------------------------------------
#if 0  
ne marche pas !!!!!
void print_int_array(FILE* out, const int* tab, unsigned count)
{
int column = 0;
int max_size = ints_width(tab, count);
printf("maxsize is %i\n", max_size);

  for (int i = 0; i < int_width(count); i++)
  {
    fprintf(stdout, " ");
    column++;
  }
  fprintf(stdout, "[0]");
  column = column + 3;

int j;
  for(int i = 0; i < count; i++)
  {
    //换行条件： 当x <= 80/最大size+1 - [x]占用格数
    for (int x = 1; x <= (80 / (max_size + 1)); x++)
    {
      if ((80 / (max_size + 1) - 1) * x == i)
      {
 column = 0;
        printf("\n");
        for(j = 0; j < int_width(count) - int_width(j); j++)
        {
            fprintf(stdout, " ");
            column++;
        }
        fprintf(stdout, "[%i]", i);
        column = column + 3;
      }

  }
      int space = max_size - int_width(tab[i]) + 1;
      for (int s = 0; s < space; s++)
      {
        fprintf(stdout, " ");
        column ++;
      }
      fprintf(stdout, "%i", tab[i]);
      column = column + max_size;
  }
printf("\n");
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



//------------------------------------------------------------------------

void insert_sort(int* tab, unsigned count)
{
int i, j;
int temp;

	for(i = 0; i < count; ++i)
	{
			temp = *(tab + i);
			for (j = i; j > 0 && *(tab + j - 1) > temp; j--)
			{
				*(tab + j) = *(tab + j - 1);
			}
			*(tab + j) = temp;
	}
}


void insert_sort_cmp(int* tab, unsigned count, int (*cmp)(int a, int b))
{
double temp = 0;
int j, i = 0;
	for(i = 0; i < count; i++)
	{
		temp = *(tab + 1);	
		for(j = i; j > 0 && cmp(*(tab + j - 1), *(tab + j)); j--)
		{
			*(tab + j) = *(tab + j - 1);
		}
		*(tab + j) = temp;
	}
}
int increasing(int a, int b)
{
   ++cmp_count;
   if (a < b)
     return -1;
   return a > b;
}

double decreasing(double a, double b)
{
   if (a > b)
     return -1;
   return a < b;
}


//---------------------Linear search -----------------------------
unsigned linear_search(const int* tab, unsigned count, int val, int (*cmp)(int a, int b))
{
unsigned i;
	if(sizeof(tab) == 0)
	{
		return count;
	}
	for(i = 0; i < count; ++i)
	{
		if((*cmp)(tab[i], val) == 1)
		{
			break;
		}
		else if (tab[i] == val)
		{
			break;
		}
	}
return i;
}

//-------------------Binary search-----------------------------------------

unsigned binary_search(int* tab, unsigned count, int val, int (*cmp)(int a, int b))
{
unsigned low = 0;
unsigned high = count - 1;
unsigned mid;
	if(sizeof(tab) == 0)
	{
		return count;
	}
	while (low < high)
	{
 		mid = (low + high) / 2;
		int midVal = tab[mid];
	//increacing return -1	
		if ((*cmp)(midVal, val) == -1)
		{
			low = mid + 1;
		}
		else if ((*cmp)(val, midVal) == -1)
		{
			high = mid - 1;
		}
	return mid;
	}
return low;
}

void bs_insert_sort_cmp(int *tab, unsigned count, int (*cmp)(int a, int b))
{
	
}
#define my_test(val) \
  cmp_count = 0; \
  printf("binary_search(a, %u, %d, increasing) = %u\n", \
         asize, (val), binary_search(a, asize, (val), increasing)); \
  printf("\twith %u comparisons\n", cmp_count);

/*
#define my_test(val) \
  cmp_count = 0; \
  printf("binary_search(a, %u, %d, increasing) = %u\n", \
         asize, (val), binary_search(a, asize, (val), increasing)); \
  printf("\twith %u comparisons\n", cmp_count);
*/
int main (void)
{
#if 0
int a[] = {
  1, 2, 3, 4, 5, 6, 13, -35, 129, -4, 123, -4555, 1341, 2432, 111, 0, 1230
};
int b[] = {  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6,
  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6,
  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6,
  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6,
  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6,
  1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6
};
puts("-- a[]");
print_int_array(stdout, a, sizeof(a)/sizeof(*a));
puts("\n-- b[]");
print_int_array(stdout, b, sizeof(b)/sizeof(*b));
puts("\n-- b[] after b[8] = 123456");
b[8] = 123456;
print_int_array(stdout, b, sizeof(b)/sizeof(*b));
puts("\n-- a[0..9]");
print_int_array(stdout, a, 10);
puts("\n-- a[0..10]");
print_int_array(stdout, a, 11);


#if 0
int a[] = {
  1, 2, 3, 4, 5, 6, 13, -35, 129, -4, 123, -4555, 1341, 2432, 111, 0, 1230
};

unsigned asize = sizeof(a)/sizeof(*a);
puts("before");
print_int_array(stdout, a, asize);
insert_sort(a, asize);
puts("after");
print_int_array(stdout, a, asize);
#endif
#endif

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
}

