#include <stdio.h>
#include <signal.h>
// K&R style function definitions

struct Point {
    int x;
    int y;
};


static void func1(p, i)
char **p;
int i;
{
    printf("%s\n", p[i]);
}

static int func2(a, b, c)
int a;
double b;
char c;
{
    return a + (int)b + c;
}

static void func3(arr, n)
int arr[];
int n;
{
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

static void func4(ptr, size)
int *ptr;
int size;
{
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
}


static void func5(struct Point p)
//struct Point p;
{
    printf("Point(%d, %d)\n", p.x, p.y);
}

static void func6(int a, struct Point p, char *str)
//int a;
//struct Point p;
//char *str;
{
    printf("a: %d, Point(%d, %d), str: %s\n", a, p.x, p.y, str);
}

static void func7(f, x, y)
int (*f)(int, int);
int x, y;
{
    int result = f(x, y);
    printf("Result: %d\n", result);
}

int add(int a, int b) {
    return a + b;
}

int main() {
    char *array[] = { "one", "two", "three" };
    func1(array, 1);

    printf("%d\n", func2(1, 2.5, 'a'));

    int arr[] = {1, 2, 3, 4, 5};
    func3(arr, 5);

    func4(arr, 5);

    struct Point pt = {3, 4};
    func5(pt);
    func6(10, pt, "hello");

    func7(add, 3, 4);

    return 0;
}
