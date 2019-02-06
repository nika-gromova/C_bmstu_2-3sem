import ctypes

lib = ctypes.CDLL('arr.dll')

fn_fill_fib = lib.fill_fib
fn_fill_fib.argtypes = (ctypes.POINTER(ctypes.c_ulong), ctypes.c_int)
fn_fill_fib.restype = ctypes.c_int

fn_first_occurrence = lib.first_occurrence
fn_first_occurrence.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_int))
fn_first_occurrence.restype = ctypes.c_int

def fill_fib(num):
    array = (ctypes.c_ulong * num)()
    fn_fill_fib(array, num)
    return list(array)

def first_occurrence(numbers):
    n_src = int(len(numbers))
    src = (ctypes.c_double * n_src)(*numbers)
    n_dst = ctypes.c_int(0)
    dst = (ctypes.c_double * n_dst.value)()
    rc = fn_first_occurrence(src, n_src, dst, n_dst)
    if rc:
        dst = (ctypes.c_double * n_dst.value)()
        rc = fn_first_occurrence(src, n_src, dst, n_dst)
        return rc, n_dst.value, list(dst)
    else:
        return rc, n_dst.value, list()
	

def func_test_fib(files_in, files_out):
    for k in range(0, len(files_in)):
        f_in = open(files_in[k], 'r')
        line = f_in.readline()
        n = int(line)
        f_in.close()
        f_out = open(files_out[k], 'w')
        result = fill_fib(n)
        for i in range(0, n):
            f_out.write("%s " %result[i])
        f_out.close()

def func_test_first(files_in, files_out):
    for k in range(0, len(files_in)):
        f_in = open(files_in[k], 'r')
        line = f_in.readline()
        n = line.split(" ")
        for i in range (0, len(n)):
            n[i] = float(n[i])
        f_in.close()
        f_out = open(files_out[k], 'w')
        rc, res_size, result = first_occurrence(n)
        for i in range(0, res_size):
            f_out.write("%s " %result[i])
        f_out.close()


files_in_fib = ["tests\in_1.txt", "tests\in_2.txt", "tests\in_3.txt", "tests\in_4.txt", "tests\in_5.txt"]
files_out_fib = ["tests\out1.txt", "tests\out2.txt", "tests\out3.txt", "tests\out4.txt", "tests\out5.txt"]

files_in_first = ["tests\in_6.txt", "tests\in_7.txt", "tests\in_8.txt", "tests\in_9.txt", "tests\in_10.txt"]
files_out_first = ["tests\out6.txt", "tests\out7.txt", "tests\out8.txt", "tests\out9.txt", "tests\out10.txt"]

func_test_fib(files_in_fib, files_out_fib)
func_test_first(files_in_first, files_out_first)

