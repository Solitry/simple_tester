#!/usr/bin/env python3
import argparse
import os
import subprocess
import re

from matplotlib.colors import LightSource


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("folder", help="target test folder")
    parser.add_argument("code", help="code file name")
    args = parser.parse_args()
    return args


def check_folder_exist(folder):
    if not os.path.exists(folder):
        print("'{}' is not exist!".format(folder))
        exit(1)

    if not os.path.isdir(folder):
        print("'{}' is not a folder!".format(folder))
        exit(1)


def check_code_exist(folder, code):
    full_code_path = os.path.join(folder, code)

    if not os.path.exists(full_code_path):
        print("'{}' is not exist in folder '{}'!".format(code, folder))
        exit(1)
    
    if not os.path.isfile(full_code_path):
        print("'{}' is not a file!".format(code))
        exit(1)


def check_ext_of_code(code):
    _, ext = os.path.splitext(code)

    if ext != ".c":
        print("'{}' may not be a c code file (should with .c extension)!".format(code))
        exit(1)


def compile_c_code(folder, code):
    name, _ = os.path.splitext(code)

    full_exec_name = os.path.join(folder, name)
    full_code_name = os.path.join(folder, code)

    command = ["gcc", "-o", full_exec_name, full_code_name, "-lm", "-Wall"]

    cp = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    
    if cp.returncode != 0:
        print("Compile error with command: {}".format(' '.join(command)))
        str_output = cp.stdout.decode("utf-8")
        max_len_size = max(len(line) for line in str_output.split("\n"))
        print("-" * max_len_size)
        print(str_output)
        print("-" * max_len_size)
        return None

    return full_exec_name


def collect_all_file_with_pattern(pattern, folder):
    ret = {}

    for f in os.listdir(folder):
        if os.path.isfile(os.path.join(folder, f)):
            match_ret = pattern.match(f)
            if match_ret:
                key = match_ret.groups()[0]
                ret[key] = f
    
    return ret


input_pattern = re.compile("^input(.*).txt$")
output_pattern = re.compile("^output(.*).txt$")


def collect_all_test_data(folder):
    input_files = collect_all_file_with_pattern(input_pattern, folder)
    output_files = collect_all_file_with_pattern(output_pattern, folder)
    
    # cross check to warning
    for key in input_files:
        if key not in output_files:
            print("Note: input '{}' has no corresponding output! (key = {})".format(input_files[key], key))
    
    for key in output_files:
        if key not in input_files:
            print("Note: output '{}' has no corresponding input! (key = {})".format(output_files[key], key))
    
    # collect all paired data
    ret = {}

    for key in input_files:
        if key in output_files:
            ret[key] = (input_files[key], output_files[key])
    
    return ret


def print_with_line(content):
    lines = content.split("\n")
    max_idx_len = len(str(len(lines)))
    format_str = "{{:>{}}}|{{}}".format(max_idx_len)
    for idx, line in enumerate(lines):
        print(format_str.format(idx, line))


def run_single_test(key, input_file, output_file, exec_name):
    with open(input_file, "rb") as input_f:
        input_data_bytes = input_f.read()

    with open(output_file, "r") as output_f:
        output_data = output_f.read()

    cp = subprocess.run([exec_name], input=input_data_bytes, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    exec_output = cp.stdout.decode("utf-8")

    ret_pf = True

    print("\n" + "-" * 20 + " {:<4} ".format(key) + "-" * 20)

    if cp.returncode != 0:
        print("Your code does not exit normally! (reutrn code = {})".format(cp.returncode))
        if len(exec_output) > 0:
            print(exec_output)
        ret_pf = False

    if output_data != exec_output:
        print("<<< STD OUTPUT >>>")
        print_with_line(output_data)
        print("<<< YOUR OUTPUT >>>")
        print_with_line(exec_output)
        ret_pf = False

    print("-" * 20 + (" PASS " if ret_pf else " FAIL ") + "-" * 20)

    return ret_pf


class LogicalKey(object):
    def __init__(self, v):
        try:
            self.v = int(v)
            self.num = 0
        except ValueError:
            self.v = v
            self.num = 1
    
    def __lt__(self, other):
        return (self.num, self.v) < (other.num, other.v)


def sort_key_in_logical_order(key_list):
    ret_list = sorted(key_list, key=lambda t: LogicalKey(t))
    return ret_list


def run_test_on_target_folder(folder, exec_name):
    data = collect_all_test_data(folder)

    if len(data) == 0:
        print("Cannot find any vaild test data!")
        exit(0)

    ordered_key = sort_key_in_logical_order(data.keys())

    pass_count = 0

    for key in ordered_key:
        input_name, output_name = data[key]
        full_input_name = os.path.join(folder, input_name)
        full_output_name = os.path.join(folder, output_name)
        
        pf = run_single_test(key, full_input_name, full_output_name, exec_name)
        if pf:
            pass_count += 1

    print("\nPass {} / {}".format(pass_count, len(data)))


if __name__ == "__main__":
    arg = parse_args()

    check_folder_exist(arg.folder)
    check_code_exist(arg.folder, arg.code)
    check_ext_of_code(arg.code)

    exec_name = compile_c_code(arg.folder, arg.code)
    if not exec_name:
        # compile error
        exit(1)

    run_test_on_target_folder(arg.folder, exec_name)
    