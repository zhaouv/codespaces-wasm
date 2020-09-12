
#include <emscripten/emscripten.h>

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    cout << "main" << endl;
    return 0;
}

#ifdef __cplusplus
extern "C"
{
#endif

    EMSCRIPTEN_KEEPALIVE
    int32_t int_add(int32_t a, int32_t b)
    {
        return a + b;
    }

    EMSCRIPTEN_KEEPALIVE
    double double_add(double a, double b)
    {
        return a + b;
    }

    EMSCRIPTEN_KEEPALIVE
    const char *ret_string()
    {
        return (char *)"hello";
    }

    EMSCRIPTEN_KEEPALIVE
    const char *cat_string(char *input)
    {
        const std::string &cc = "hello " + std::string(input);
        const char *c = cc.c_str();
        return c;
    }

    EMSCRIPTEN_KEEPALIVE
    void int_arr(int32_t *arr, int32_t n)
    {
        for (int32_t i = 0; i < n; i++)
        {
            arr[i] = arr[i] + i * i;
        }
    }

    EMSCRIPTEN_KEEPALIVE
    void double_arr(double *arr, int32_t n)
    {
        for (int32_t i = 0; i < n; i++)
        {
            arr[i] = arr[i] + i * i;
        }
    }

#ifdef __cplusplus
}
#endif